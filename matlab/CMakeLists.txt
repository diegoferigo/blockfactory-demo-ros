# Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT). All rights reserved.
# This software may be modified and distributed under the terms of the
# GNU Lesser General Public License v2.1 or any later version.

find_package(BlockFactory COMPONENTS SimulinkCoder REQUIRED)

include(TargetFromGeneratedCode)

set(SIMULINK_MODEL_NAME "RosPubSubExample")

# This macro creates a target named as the mdl file for the autogenerated class
target_from_generated_code(
    MODELNAME ${SIMULINK_MODEL_NAME}
    SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/${SIMULINK_MODEL_NAME}_grt_rtw)
