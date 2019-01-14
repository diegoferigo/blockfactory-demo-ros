/*
 * Copyright (C) 2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * GNU Lesser General Public License v2.1 or any later version.
 */

#include "RosTopicSubscriber.h"
#include "common.h"

#include <BlockFactory/Core/Log.h>
#include <BlockFactory/Core/Parameter.h>
#include <BlockFactory/Core/Signal.h>

#include <mutex>
#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <vector>

using namespace rostoolbox;

class RosTopicSubscriber::Impl
{
public:
    mutable std::mutex mutex;

    std::string topicName;
    std::vector<double> message;

    ros::Subscriber sub;
    std::unique_ptr<ros::AsyncSpinner> spinner;
    std::unique_ptr<ros::NodeHandle> nodeHandle;

    bool readFirstData = false;

    void callback(const std_msgs::Float64MultiArrayConstPtr& msg)
    {
        if (!readFirstData) {
            readFirstData = true;
        }

        std::lock_guard<std::mutex> lock(mutex);

        // Should be no-op
        message.resize(msg->data.size());

        // Copy the message
        for (unsigned i = 0; i < msg->data.size(); ++i) {
            message[i] = msg->data[i];
        }
    }
};

RosTopicSubscriber::RosTopicSubscriber()
    : pImpl(std::make_unique<Impl>())
{}

RosTopicSubscriber::~RosTopicSubscriber() = default;

unsigned RosTopicSubscriber::numberOfParameters()
{
    return Block::numberOfParameters() + 2;
}

bool RosTopicSubscriber::parseParameters(blockfactory::core::BlockInformation* blockInfo)
{
    // Metadata for the TopicName parameter
    const blockfactory::core::ParameterMetadata topicNameParameter(
        blockfactory::core::ParameterType::STRING,
        /*index=*/Block::numberOfParameters(),
        /*rows=*/1,
        /*cols=*/1,
        "TopicName");

    // Metadata for the MsgSize parameter
    const blockfactory::core::ParameterMetadata messageSizeParameter(
        blockfactory::core::ParameterType::DOUBLE,
        /*index=*/Block::numberOfParameters() + 1,
        /*rows=*/1,
        /*cols=*/1,
        "MsgSize");

    // Add the parameter metadata into the BlockInformation
    bool ok = true;
    ok = ok && blockInfo->addParameterMetadata(messageSizeParameter);
    ok = ok && blockInfo->addParameterMetadata(topicNameParameter);

    if (!ok) {
        bfError << "Failed to store parameters metadata";
        return false;
    }

    // Store the parameter and return true if it succeeds
    return blockInfo->parseParameters(m_parameters);
}

// Keep in mind that after this step, all the allocated memory will be deleted.
// Memory persistency is guaranteed starting from the initialize() method.
bool RosTopicSubscriber::configureSizeAndPorts(blockfactory::core::BlockInformation* blockInfo)
{
    // The base blockfactory::core::Block class needs to be configured first
    if (!blockfactory::core::Block::configureSizeAndPorts(blockInfo)) {
        return false;
    }

    // Parse the parameters
    if (!RosTopicSubscriber::parseParameters(blockInfo)) {
        bfError << "Failed to parse parameters.";
        return false;
    }

    // Read the MsgSize parameter
    int msgSize;
    if (!m_parameters.getParameter("MsgSize", msgSize)) {
        bfError << "Failed to parse MsgSize parameter";
        return false;
    }

    // Configure the output port
    blockfactory::core::BlockInformation::PortData output{
        /*portIndex=*/0, std::vector<int>{msgSize}, blockfactory::core::DataType::DOUBLE};

    // Populate a data structure with the input / output data
    blockfactory::core::BlockInformation::IOData ioData;
    ioData.output.push_back(output);

    // Store port data into the BlockInformation
    if (!blockInfo->setIOPortsData(ioData)) {
        bfError << "Failed to configure input / output ports";
        return false;
    }

    return true;
}

bool RosTopicSubscriber::initialize(blockfactory::core::BlockInformation* blockInfo)
{
    // The base blockfactory::core::Block class need to be initialized first
    if (!Block::initialize(blockInfo)) {
        return false;
    }

    // Parse the parameters
    if (!RosTopicSubscriber::parseParameters(blockInfo)) {
        bfError << "Failed to parse parameters.";
        return false;
    }

    // Read the TopicName parameter and store it as a private member
    if (!m_parameters.getParameter("TopicName", pImpl->topicName)) {
        bfError << "Failed to parse TopicName parameter";
        return false;
    }

    // Read the MsgSize parameter
    int msgSize;
    if (!m_parameters.getParameter("MsgSize", msgSize)) {
        bfError << "Failed to parse MsgSize parameter";
        return false;
    }

    // Initialize the buffer size
    pImpl->message.resize(static_cast<size_t>(msgSize));

    // Initialize the node
    ros::init(ros::M_string{}, ROS_NODE_NAME);

    // Check that roscore is running
    if (!ros::master::check()) {
        bfError << "roscore is not running";
        return false;
    }

    // Create the node
    pImpl->nodeHandle = std::make_unique<ros::NodeHandle>();

    // Register the callback. We keep only the newest message (queue = 1).
    // http://wiki.ros.org/roscpp/Overview/Publishers%20and%20Subscribers#Class_Methods
    pImpl->sub = pImpl->nodeHandle->subscribe(
        pImpl->topicName, /*callback_queue=*/1, &Impl::callback, &(*pImpl));

    // Read the topic asynchronously from another thread (a mutex will be used to access data
    // in a thread-safe way)
    // http://wiki.ros.org/roscpp/Overview/Callbacks%20and%20Spinning
    pImpl->spinner = std::make_unique<ros::AsyncSpinner>(/*thread_count=*/1);

    return true;
}

bool RosTopicSubscriber::initializeInitialConditions(
    const blockfactory::core::BlockInformation* /*blockInfo*/)
{
    if (!pImpl->spinner->canStart()) {
        bfError << "Failed to start the spinner";
        return false;
    }

    // Start the thread that process incoming data
    pImpl->spinner->start();

    return true;
}

bool RosTopicSubscriber::output(const blockfactory::core::BlockInformation* blockInfo)
{
    // If no messages are read, exit.
    // This is an easy handling of this case, a class that implements a complete support
    // of ROS topics should handle this differently.
    if (!pImpl->readFirstData) {
        return true;
    }

    // Get the output signal
    blockfactory::core::OutputSignalPtr output = blockInfo->getOutputPortSignal(/*index=*/0);

    // Check the signal validity
    if (!output) {
        bfError << "Output signal not valid";
        return false;
    }

    {
        std::unique_lock<std::mutex>(pImpl->mutex);

        // Check that the width of the received signal matches what is expected
        if (output->getWidth() != static_cast<int>(pImpl->message.size())) {
            bfError << "Output signal has a width of " << output->getWidth()
                    << " while the received message has a size of " << pImpl->message.size();
            return false;
        }

        // Copy the message to the output port buffer
        std::copy(pImpl->message.begin(), pImpl->message.end(), output->getBuffer<double>());
    }

    return true;
}

bool RosTopicSubscriber::terminate(const blockfactory::core::BlockInformation* /*blockInfo*/)
{
    return true;
}
