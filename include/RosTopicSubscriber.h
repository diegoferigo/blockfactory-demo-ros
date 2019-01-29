/*
 * Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * GNU Lesser General Public License v2.1 or any later version.
 */

#ifndef TOOLBOX_ROS_ROSTOPICSUBSCRIBER_H
#define TOOLBOX_ROS_ROSTOPICSUBSCRIBER_H

#include <BlockFactory/Core/Block.h>
#include <BlockFactory/Core/BlockInformation.h>

#include <memory>
#include <string>

namespace rostoolbox {
    class RosTopicSubscriber;
} // namespace rostoolbox

class rostoolbox::RosTopicSubscriber : public blockfactory::core::Block
{
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;

public:
    RosTopicSubscriber();
    ~RosTopicSubscriber() override;

    unsigned numberOfParameters() override;
    bool parseParameters(blockfactory::core::BlockInformation* blockInfo) override;
    bool configureSizeAndPorts(blockfactory::core::BlockInformation* blockInfo) override;
    bool initialize(blockfactory::core::BlockInformation* blockInfo) override;
    bool
    initializeInitialConditions(const blockfactory::core::BlockInformation* blockInfo) override;
    bool output(const blockfactory::core::BlockInformation* blockInfo) override;
    bool terminate(const blockfactory::core::BlockInformation* blockInfo) override;
};

#endif // TOOLBOX_ROS_ROSTOPICSUBSCRIBER_H
