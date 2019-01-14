/*
 * Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * GNU Lesser General Public License v2.1 or any later version.
 */

#include "RosTopicPublisher.h"
#include "RosTopicSubscriber.h"

// Class factory API
#include <shlibpp/SharedLibraryClassApi.h>

// Add the classes that implement Block to the plugin factory
SHLIBPP_DEFINE_SHARED_SUBCLASS(RosTopicPublisher,
                               rostoolbox::RosTopicPublisher,
                               blockfactory::core::Block);
SHLIBPP_DEFINE_SHARED_SUBCLASS(RosTopicSubscriber,
                               rostoolbox::RosTopicSubscriber,
                               blockfactory::core::Block);
