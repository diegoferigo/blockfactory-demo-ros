/*
 * Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * GNU Lesser General Public License v2.1 or any later version.
 */

#include "RosTopicPublisher.h"
#include "common.h"

#include <BlockFactory/Core/Log.h>
#include <BlockFactory/Core/Parameter.h>
#include <BlockFactory/Core/Signal.h>

#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <vector>

using namespace rostoolbox;

class RosTopicPublisher::Impl
{
public:
    int messageQueue;
    std::string topicName;

    ros::Publisher chatter_pub;
    std_msgs::Float64MultiArray message;
    std::unique_ptr<ros::NodeHandle> nodeHandle;
};

RosTopicPublisher::RosTopicPublisher()
    : pImpl(std::make_unique<Impl>())
{}

RosTopicPublisher::~RosTopicPublisher() = default;

unsigned RosTopicPublisher::numberOfParameters()
{
    return Block::numberOfParameters() + 2;
}

bool RosTopicPublisher::parseParameters(blockfactory::core::BlockInformation* blockInfo)
{
    // Metadata for the TopicName parameter
    const blockfactory::core::ParameterMetadata topicNameParameter(
        blockfactory::core::ParameterType::STRING,
        /*index=*/Block::numberOfParameters(),
        /*rows=*/1,
        /*cols=*/1,
        "TopicName");

    // Metadata for the MessageQueue parameter
    const blockfactory::core::ParameterMetadata messageQueue(
        blockfactory::core::ParameterType::DOUBLE,
        /*index=*/Block::numberOfParameters() + 1,
        /*rows=*/1,
        /*cols=*/1,
        "MessageQueue");

    // Add the parameter metadata into BlockInformation
    bool ok = true;
    ok = ok && blockInfo->addParameterMetadata(messageQueue);
    ok = ok && blockInfo->addParameterMetadata(topicNameParameter);

    if (!ok) {
        bfError << "Failed to store parameter metadata";
        return false;
    }

    // Store the parameter and return true if it succeeds
    return blockInfo->parseParameters(m_parameters);
}

// Keep in mind that after this step, all the allocated memory will be deleted.
// Memory persistency is guaranteed starting from the initialize() method.
bool RosTopicPublisher::configureSizeAndPorts(blockfactory::core::BlockInformation* blockInfo)
{
    // The base blockfactory::core::Block class needs to be configured first
    if (!blockfactory::core::Block::configureSizeAndPorts(blockInfo)) {
        return false;
    }

    // Configure the input port
    blockfactory::core::Port::Info input{/*portIndex=*/0,
                                         std::vector<int>{blockfactory::core::Port::DynamicSize},
                                         blockfactory::core::Port::DataType::DOUBLE};

    // Populate a data structure with the input / output data
    blockfactory::core::InputPortsInfo inputPortsInfo;
    inputPortsInfo.push_back(input);

    // Store port data into the BlockInformation
    if (!blockInfo->setPortsInfo(inputPortsInfo, {})) {
        bfError << "Failed to configure input / output ports";
        return false;
    }

    return true;
}

bool RosTopicPublisher::initialize(blockfactory::core::BlockInformation* blockInfo)
{
    // The base blockfactory::core::Block class need to be initialized first
    if (!Block::initialize(blockInfo)) {
        return false;
    }

    // Parse the parameters
    if (!RosTopicPublisher::parseParameters(blockInfo)) {
        bfError << "Failed to parse parameters.";
        return false;
    }

    // Read the TopicName parameter and store it as a private member
    if (!m_parameters.getParameter("TopicName", pImpl->topicName)) {
        bfError << "Failed to parse TopicName parameter";
        return false;
    }

    // Read the MessageQueue parameter and store it as a private member
    if (!m_parameters.getParameter("MessageQueue", pImpl->messageQueue)) {
        bfError << "Failed to parse MessageQueue parameter";
        return false;
    }

    // Initialize the node
    ros::init(ros::M_string{}, ROS_NODE_NAME);

    // Check that roscore is running
    if (!ros::master::check()) {
        bfError << "roscore is not running";
        return false;
    }

    // Create the node
    pImpl->nodeHandle = std::make_unique<ros::NodeHandle>();

    // Setup dimensions
    pImpl->message.layout.dim.emplace_back();
    pImpl->message.layout.dim[0].size = 0;
    pImpl->message.layout.dim[0].stride = 1;
    pImpl->message.layout.dim[0].label = pImpl->topicName;

    // Notify roscore that we want to publish
    pImpl->chatter_pub = pImpl->nodeHandle->advertise<std_msgs::Float64MultiArray>(
        pImpl->topicName, static_cast<uint32_t>(pImpl->messageQueue));

    return true;
}

bool RosTopicPublisher::output(const blockfactory::core::BlockInformation* blockInfo)
{
    // Get the input signal
    blockfactory::core::InputSignalPtr input = blockInfo->getInputPortSignal(/*index=*/0);

    // Check the signal validity
    if (!input) {
        bfError << "Input signal not valid";
        return false;
    }

    // Resize the buffer the first run (after it should be a no-op)
    pImpl->message.data.resize(static_cast<size_t>(input->getWidth()));
    pImpl->message.layout.dim[0].size = static_cast<uint32_t>(pImpl->message.data.size());

    for (unsigned i = 0; i < static_cast<unsigned>(input->getWidth()); ++i) {
        pImpl->message.data[i] = input->get<double>(i);
    }

    // Publish the message
    pImpl->chatter_pub.publish(pImpl->message);

    return true;
}

bool RosTopicPublisher::terminate(const blockfactory::core::BlockInformation* /*blockInfo*/)
{
    return true;
}
