/*
 * RosPubSubExample.cpp
 *
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, educational organizations only. Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "RosPubSubExample".
 *
 * Model version              : 1.30
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C++ source code generated on : Tue Jan 15 12:19:20 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "RosPubSubExample.h"
#include "RosPubSubExample_private.h"

/* Model step function */
void RosPubSubExampleModelClass::step()
{
  real_T DataWrote_tmp;

  /* Sin: '<Root>/Sine' incorporates:
   *  Sin: '<Root>/Cosine'
   */
  DataWrote_tmp = (&RosPubSubExample_M)->Timing.t[0];

  /* SignalConversion: '<Root>/TmpSignal ConversionAtRosTopicPublisherInport1' incorporates:
   *  Sin: '<Root>/Cosine'
   *  Sin: '<Root>/Sine'
   */
  RosPubSubExample_B.DataWrote[0] = std::sin(RosPubSubExample_P.Sine_Freq *
    DataWrote_tmp + RosPubSubExample_P.Sine_Phase) * RosPubSubExample_P.Sine_Amp
    + RosPubSubExample_P.Sine_Bias;
  RosPubSubExample_B.DataWrote[1] = std::sin(RosPubSubExample_P.Cosine_Freq *
    DataWrote_tmp + RosPubSubExample_P.Cosine_Phase) *
    RosPubSubExample_P.Cosine_Amp + RosPubSubExample_P.Cosine_Bias;

  /* S-Function (BlockFactory): '<Root>/RosTopicPublisher' */
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (RosPubSubExample_DW.RosTopicPublisher_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (RosPubSubExample_DW.RosTopicPublisher_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/RosTopicPublisher

  /* S-Function (BlockFactory): '<Root>/RosTopicSubscriber' */
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (RosPubSubExample_DW.RosTopicSubscriber_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (RosPubSubExample_DW.RosTopicSubscriber_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/RosTopicSubscriber

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++(&RosPubSubExample_M)->Timing.clockTick0)) {
    ++(&RosPubSubExample_M)->Timing.clockTickH0;
  }

  (&RosPubSubExample_M)->Timing.t[0] = (&RosPubSubExample_M)->Timing.clockTick0 *
    (&RosPubSubExample_M)->Timing.stepSize0 + (&RosPubSubExample_M)
    ->Timing.clockTickH0 * (&RosPubSubExample_M)->Timing.stepSize0 *
    4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    (&RosPubSubExample_M)->Timing.clockTick1++;
    if (!(&RosPubSubExample_M)->Timing.clockTick1) {
      (&RosPubSubExample_M)->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void RosPubSubExampleModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&RosPubSubExample_M), 0,
                sizeof(RT_MODEL_RosPubSubExample_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&RosPubSubExample_M)->solverInfo,
                          &(&RosPubSubExample_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&RosPubSubExample_M)->solverInfo, &rtmGetTPtr
                ((&RosPubSubExample_M)));
    rtsiSetStepSizePtr(&(&RosPubSubExample_M)->solverInfo, &(&RosPubSubExample_M)
                       ->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&(&RosPubSubExample_M)->solverInfo,
                          (&rtmGetErrorStatus((&RosPubSubExample_M))));
    rtsiSetRTModelPtr(&(&RosPubSubExample_M)->solverInfo, (&RosPubSubExample_M));
  }

  rtsiSetSimTimeStep(&(&RosPubSubExample_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&(&RosPubSubExample_M)->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(getRTM(), &(&RosPubSubExample_M)->Timing.tArray[0]);
  (&RosPubSubExample_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &RosPubSubExample_B), 0,
                sizeof(B_RosPubSubExample_T));

  /* states (dwork) */
  (void) memset((void *)&RosPubSubExample_DW, 0,
                sizeof(DW_RosPubSubExample_T));

  /* Start for S-Function (BlockFactory): '<Root>/RosTopicPublisher' */
  {
    // Create and store the CoderBlockInformation object
    blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
      coder::CoderBlockInformation();
    RosPubSubExample_DW.RosTopicPublisher_PWORK.blockPWork[1] = static_cast<void*>
      (blockInfo);

    // Initialize the parameters
    // -------------------------
    blockfactory::core::Parameters params;
    params.storeParameter<double>(1.0,
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      DOUBLE, 3.0, 1.0, 1.0, "MessageQueue"));
    params.storeParameter<std::string>("/PubSubExample",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 2.0, 1.0, 1.0, "TopicName"));
    params.storeParameter<std::string>("RosToolbox",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 1.0, 1.0, 1.0, "libName"));
    params.storeParameter<std::string>("RosTopicPublisher",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 0.0, 1.0, 1.0, "className"));

    // Store the parameters in the CoderBlockInformation object
    blockInfo->storeRTWParameters(params);

    // Initialize input / output Signals
    // ---------------------------------

    // Inputs
    blockInfo->setInputSignal(0, static_cast<void*>
      (&RosPubSubExample_B.DataWrote[0]), {
      1, 2
    } );

    // Outputs

    // Initialize the class
    // --------------------

    // Get the block factory
    auto factory = blockfactory::core::ClassFactorySingleton::getInstance().
      getClassFactory(
                      {
                      "RosToolbox", "RosTopicPublisher"
                      } );

    if (!factory) {
      bfError << "Failed to get factory object (className=" <<
        "RosTopicPublisher"
        << ",libName=" << "RosToolbox" << ")";
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    if (!factory->isValid()) {
      bfError << "Factory error (" << static_cast<std::uint32_t>
        (factory->getStatus())
        << "): " << factory->getError().c_str();
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Run a dummy configureSizeAndPorts step. This is currently required for properly
    // handling optional input / outputs static variables.
    // TODO: find a better way to handle them.
    {
      // Create a new class. This object will be destroyed at the end of the scope.
      shlibpp::SharedLibraryClass<blockfactory::core::Block> blockPtr(*factory);
      auto tmpCoderBlockInfo = std::unique_ptr<blockfactory::coder::
        CoderBlockInformation>(
        new blockfactory::coder::CoderBlockInformation);
      tmpCoderBlockInfo->storeRTWParameters(params);
      blockPtr->configureSizeAndPorts(tmpCoderBlockInfo.get());
    }

    // Allocate the block
    blockfactory::core::Block* blockPtr = factory->create();
    factory->addRef();

    // Initialize the block
    bool ok = blockPtr->initialize(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Call the initializeInitialConditions() method
    ok = blockPtr->initializeInitialConditions(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[InitializeInitialConditions]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Store the block in the PWork vector
    RosPubSubExample_DW.RosTopicPublisher_PWORK.blockPWork[0] = static_cast<void*>
      (blockPtr);
  }

  // End of S-Function Block: <Root>/RosTopicPublisher

  /* Start for S-Function (BlockFactory): '<Root>/RosTopicSubscriber' */
  {
    // Create and store the CoderBlockInformation object
    blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
      coder::CoderBlockInformation();
    RosPubSubExample_DW.RosTopicSubscriber_PWORK.blockPWork[1] = static_cast<
      void*>(blockInfo);

    // Initialize the parameters
    // -------------------------
    blockfactory::core::Parameters params;
    params.storeParameter<double>(2.0,
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      DOUBLE, 3.0, 1.0, 1.0, "MsgSize"));
    params.storeParameter<std::string>("/PubSubExample",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 2.0, 1.0, 1.0, "TopicName"));
    params.storeParameter<std::string>("RosToolbox",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 1.0, 1.0, 1.0, "libName"));
    params.storeParameter<std::string>("RosTopicSubscriber",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 0.0, 1.0, 1.0, "className"));

    // Store the parameters in the CoderBlockInformation object
    blockInfo->storeRTWParameters(params);

    // Initialize input / output Signals
    // ---------------------------------

    // Inputs

    // Outputs
    blockInfo->setOutputSignal(0, static_cast<void*>
      (&RosPubSubExample_B.DataRead[0]), {
      1, 2
    } );

    // Initialize the class
    // --------------------

    // Get the block factory
    auto factory = blockfactory::core::ClassFactorySingleton::getInstance().
      getClassFactory(
                      {
                      "RosToolbox", "RosTopicSubscriber"
                      } );

    if (!factory) {
      bfError << "Failed to get factory object (className=" <<
        "RosTopicSubscriber"
        << ",libName=" << "RosToolbox" << ")";
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    if (!factory->isValid()) {
      bfError << "Factory error (" << static_cast<std::uint32_t>
        (factory->getStatus())
        << "): " << factory->getError().c_str();
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Run a dummy configureSizeAndPorts step. This is currently required for properly
    // handling optional input / outputs static variables.
    // TODO: find a better way to handle them.
    {
      // Create a new class. This object will be destroyed at the end of the scope.
      shlibpp::SharedLibraryClass<blockfactory::core::Block> blockPtr(*factory);
      auto tmpCoderBlockInfo = std::unique_ptr<blockfactory::coder::
        CoderBlockInformation>(
        new blockfactory::coder::CoderBlockInformation);
      tmpCoderBlockInfo->storeRTWParameters(params);
      blockPtr->configureSizeAndPorts(tmpCoderBlockInfo.get());
    }

    // Allocate the block
    blockfactory::core::Block* blockPtr = factory->create();
    factory->addRef();

    // Initialize the block
    bool ok = blockPtr->initialize(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Call the initializeInitialConditions() method
    ok = blockPtr->initializeInitialConditions(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[InitializeInitialConditions]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Store the block in the PWork vector
    RosPubSubExample_DW.RosTopicSubscriber_PWORK.blockPWork[0] = static_cast<
      void*>(blockPtr);
  }

  // End of S-Function Block: <Root>/RosTopicSubscriber
}

/* Model terminate function */
void RosPubSubExampleModelClass::terminate()
{
  /* Terminate for S-Function (BlockFactory): '<Root>/RosTopicPublisher' */
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (RosPubSubExample_DW.RosTopicPublisher_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (RosPubSubExample_DW.RosTopicPublisher_PWORK.blockPWork[0]);

    // Get the block factory
    auto factory = blockfactory::core::ClassFactorySingleton::getInstance().
      getClassFactory(
                      {
                      "RosToolbox", "RosTopicPublisher"
                      } );

    if (!factory) {
      bfError << "Failed to get factory object (className=" <<
        "RosTopicPublisher"
        << ",libName=" << "RosToolbox" << ")";
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    if (!factory->isValid()) {
      bfError << "Factory error (" << static_cast<std::uint32_t>
        (factory->getStatus())
        << "): " << factory->getError().c_str();
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Terminate the class
    // -------------------
    bool ok;
    ok = blockPtr->terminate(blockInfo);

    // Destroy the block
    factory->destroy(blockPtr);
    blockPtr = nullptr;

    // Decrease the counter of the factory
    factory->removeRef();
    if (factory->getReferenceCount() == 1) {
      // Delete the memory ownership of the shared pointer used in this function
      factory.reset();

      // Delete the factory object
      if (!blockfactory::core::ClassFactorySingleton::getInstance().
          destroyFactory(
                         {"RosToolbox", "RosTopicPublisher"})) {
        bfError << "Failed to destroy the factory";

        // Do not return since other actions need to be performed
      }
    }

    // Delete the BlockInformation object
    delete blockInfo;
    blockInfo = nullptr;

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Terminate]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/RosTopicPublisher

  /* Terminate for S-Function (BlockFactory): '<Root>/RosTopicSubscriber' */
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (RosPubSubExample_DW.RosTopicSubscriber_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (RosPubSubExample_DW.RosTopicSubscriber_PWORK.blockPWork[0]);

    // Get the block factory
    auto factory = blockfactory::core::ClassFactorySingleton::getInstance().
      getClassFactory(
                      {
                      "RosToolbox", "RosTopicSubscriber"
                      } );

    if (!factory) {
      bfError << "Failed to get factory object (className=" <<
        "RosTopicSubscriber"
        << ",libName=" << "RosToolbox" << ")";
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    if (!factory->isValid()) {
      bfError << "Factory error (" << static_cast<std::uint32_t>
        (factory->getStatus())
        << "): " << factory->getError().c_str();
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Initialize]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }

    // Terminate the class
    // -------------------
    bool ok;
    ok = blockPtr->terminate(blockInfo);

    // Destroy the block
    factory->destroy(blockPtr);
    blockPtr = nullptr;

    // Decrease the counter of the factory
    factory->removeRef();
    if (factory->getReferenceCount() == 1) {
      // Delete the memory ownership of the shared pointer used in this function
      factory.reset();

      // Delete the factory object
      if (!blockfactory::core::ClassFactorySingleton::getInstance().
          destroyFactory(
                         {"RosToolbox", "RosTopicSubscriber"})) {
        bfError << "Failed to destroy the factory";

        // Do not return since other actions need to be performed
      }
    }

    // Delete the BlockInformation object
    delete blockInfo;
    blockInfo = nullptr;

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Terminate]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      if (getRTM()->errorStatus) {
        delete getRTM()->errorStatus;
        getRTM()->errorStatus = nullptr;
      }

      getRTM()->errorStatus = new char[1024];
      sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/RosTopicSubscriber
}

/* Constructor */
RosPubSubExampleModelClass::RosPubSubExampleModelClass()
{
  static const P_RosPubSubExample_T RosPubSubExample_P_temp = {
    /* Expression: 1
     * Referenced by: '<Root>/Sine'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<Root>/Sine'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<Root>/Sine'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<Root>/Sine'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<Root>/Cosine'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<Root>/Cosine'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<Root>/Cosine'
     */
    1.0,

    /* Expression: pi/2
     * Referenced by: '<Root>/Cosine'
     */
    1.5707963267948966
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  RosPubSubExample_P = RosPubSubExample_P_temp;
}

/* Destructor */
RosPubSubExampleModelClass::~RosPubSubExampleModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_RosPubSubExample_T * RosPubSubExampleModelClass::getRTM()
{
  return (&RosPubSubExample_M);
}
