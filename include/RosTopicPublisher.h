/*
 * Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * GNU Lesser General Public License v2.1 or any later version.
 */

#ifndef ROSTOOLBOX_ROSTOPICPUBLISHER_H
#define ROSTOOLBOX_ROSTOPICPUBLISHER_H

#include <BlockFactory/Core/Block.h>
#include <BlockFactory/Core/BlockInformation.h>

#include <memory>
#include <string>

namespace rostoolbox {
    class RosTopicPublisher;
} // namespace rostoolbox

class rostoolbox::RosTopicPublisher : public blockfactory::core::Block
{
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;

public:
    RosTopicPublisher();
    ~RosTopicPublisher() override;

    unsigned numberOfParameters() override;
    bool parseParameters(blockfactory::core::BlockInformation* blockInfo) override;
    bool configureSizeAndPorts(blockfactory::core::BlockInformation* blockInfo) override;
    bool initialize(blockfactory::core::BlockInformation* blockInfo) override;
    bool output(const blockfactory::core::BlockInformation* blockInfo) override;
    bool terminate(const blockfactory::core::BlockInformation* blockInfo) override;
};

#endif // ROSTOOLBOX_ROSTOPICPUBLISHER_H
