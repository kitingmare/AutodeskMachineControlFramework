/*++

Copyright (C) 2020 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Autodesk Inc. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


This file has been generated by the Automatic Component Toolkit (ACT) version 1.8.0-develop.

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of MC Driver Raylase

Interface version: 2.0.0

*/

#ifndef __LIBMCDRIVER_RAYLASE_DYNAMICHEADER_CPPTYPES
#define __LIBMCDRIVER_RAYLASE_DYNAMICHEADER_CPPTYPES

#include "libmcdriver_raylase_types.hpp"

#include "libmcenv_types.hpp"


/*************************************************************************************************************************
 Class definition for Base
**************************************************************************************************************************/

/*************************************************************************************************************************
 Class definition for Driver
**************************************************************************************************************************/

/**
* Configures a driver with its specific configuration data.
*
* @param[in] pDriver - Driver instance.
* @param[in] pConfigurationString - Configuration data of driver.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_ConfigurePtr) (LibMCDriver_Raylase_Driver pDriver, const char * pConfigurationString);

/**
* returns the name identifier of the driver
*
* @param[in] pDriver - Driver instance.
* @param[in] nNameBufferSize - size of the buffer (including trailing 0)
* @param[out] pNameNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pNameBuffer -  buffer of Name of the driver., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_GetNamePtr) (LibMCDriver_Raylase_Driver pDriver, const LibMCDriver_Raylase_uint32 nNameBufferSize, LibMCDriver_Raylase_uint32* pNameNeededChars, char * pNameBuffer);

/**
* returns the type identifier of the driver
*
* @param[in] pDriver - Driver instance.
* @param[in] nTypeBufferSize - size of the buffer (including trailing 0)
* @param[out] pTypeNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pTypeBuffer -  buffer of Type of the driver., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_GetTypePtr) (LibMCDriver_Raylase_Driver pDriver, const LibMCDriver_Raylase_uint32 nTypeBufferSize, LibMCDriver_Raylase_uint32* pTypeNeededChars, char * pTypeBuffer);

/**
* returns the version identifiers of the driver
*
* @param[in] pDriver - Driver instance.
* @param[out] pMajor - Major version.
* @param[out] pMinor - Minor version.
* @param[out] pMicro - Micro version.
* @param[in] nBuildBufferSize - size of the buffer (including trailing 0)
* @param[out] pBuildNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pBuildBuffer -  buffer of Build identifier., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_GetVersionPtr) (LibMCDriver_Raylase_Driver pDriver, LibMCDriver_Raylase_uint32 * pMajor, LibMCDriver_Raylase_uint32 * pMinor, LibMCDriver_Raylase_uint32 * pMicro, const LibMCDriver_Raylase_uint32 nBuildBufferSize, LibMCDriver_Raylase_uint32* pBuildNeededChars, char * pBuildBuffer);

/**
* Updates the driver parameters in the driver environment. Should only be called in the driver thread.
*
* @param[in] pDriver - Driver instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_QueryParametersPtr) (LibMCDriver_Raylase_Driver pDriver);

/**
* Updates the driver parameters in the driver environment. Might be called out of thread. Implementation MUST be able to handle parallel calls.
*
* @param[in] pDriver - Driver instance.
* @param[in] pDriverUpdateInstance - Status update instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_QueryParametersExPtr) (LibMCDriver_Raylase_Driver pDriver, LibMCEnv_DriverStatusUpdateSession pDriverUpdateInstance);

/*************************************************************************************************************************
 Class definition for RaylaseCard
**************************************************************************************************************************/

/**
* Checks if the card is connected.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[out] pIsConnected - Flag if the card is disconnected.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_IsConnectedPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, bool * pIsConnected);

/**
* Disconnects and unregisters the card.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_DisconnectPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard);

/**
* Resets the card settings to system defaults.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_ResetToSystemDefaultsPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard);

/**
* Turns the laser on.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_LaserOnPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard);

/**
* Turns the laser off.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_LaserOffPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard);

/**
* Arms or disarms the laser.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[in] bShallBeArmed - Shall the laser be armed or disarmed.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_ArmLaserPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, bool bShallBeArmed);

/**
* Checks if the laser is armed.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[out] pLaserIsArmed - Flag if the laser is armed.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_IsLaserArmedPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, bool * pLaserIsArmed);

/**
* Enables the pilot pointer.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[in] bShallBeEnabled - Shall the pilot be enabled.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_EnablePilotPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, bool bShallBeEnabled);

/**
* Checks if the pilot is enabled.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[out] pPilotIsEnabled - Flag if the pilot is enabled.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_PilotIsEnabledPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, bool * pPilotIsEnabled);

/**
* Returns the laser status.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[out] pPilotIsEnabled - Flag if the pilot is enabled.
* @param[out] pLaserIsArmed - Flag if the laser is armed.
* @param[out] pLaserAlarm - Flag if the laser is in alarm state.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_GetLaserStatusPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, bool * pPilotIsEnabled, bool * pLaserIsArmed, bool * pLaserAlarm);

/**
* Draws a layer of a build stream. Blocks until the layer is drawn.
*
* @param[in] pRaylaseCard - RaylaseCard instance.
* @param[in] pStreamUUID - UUID of the build stream. Must have been loaded in memory by the system.
* @param[in] nLayerIndex - Layer index of the build file.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseRaylaseCard_DrawLayerPtr) (LibMCDriver_Raylase_RaylaseCard pRaylaseCard, const char * pStreamUUID, LibMCDriver_Raylase_uint32 nLayerIndex);

/*************************************************************************************************************************
 Class definition for Driver_Raylase
**************************************************************************************************************************/

/**
* Sets the driver in Simulation mode.
*
* @param[in] pDriver_Raylase - Driver_Raylase instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_Raylase_SetToSimulationModePtr) (LibMCDriver_Raylase_Driver_Raylase pDriver_Raylase);

/**
* Returns if the driver is in Simulation mode.
*
* @param[in] pDriver_Raylase - Driver_Raylase instance.
* @param[out] pIsSimulationMode - Simulation mode is active.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_Raylase_IsSimulationModePtr) (LibMCDriver_Raylase_Driver_Raylase pDriver_Raylase, bool * pIsSimulationMode);

/**
* Sets the machine resource name of the SDK to load. MUST be called before LoadSDK or it has no effect.
*
* @param[in] pDriver_Raylase - Driver_Raylase instance.
* @param[in] pResourceName - Resource name of core machine package. Empty means standard naming applies.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_Raylase_SetCustomSDKResourcePtr) (LibMCDriver_Raylase_Driver_Raylase pDriver_Raylase, const char * pResourceName);

/**
* Initializes the Raylase SDK.
*
* @param[in] pDriver_Raylase - Driver_Raylase instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_Raylase_LoadSDKPtr) (LibMCDriver_Raylase_Driver_Raylase pDriver_Raylase);

/**
* Connects to the Raylase Scanner Card. Fails if connection is not successful.
*
* @param[in] pDriver_Raylase - Driver_Raylase instance.
* @param[in] pCardName - Name of scanner to be connected to. MUST not be in use.
* @param[in] pCardIP - IP Address to connect to.
* @param[in] nPort - Port to connect to.
* @param[in] dMaxLaserPowerInWatts - Maximum laser power in Watts.
* @param[out] pRaylaseCardInstance - Instance of connected card.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_Raylase_ConnectByIPPtr) (LibMCDriver_Raylase_Driver_Raylase pDriver_Raylase, const char * pCardName, const char * pCardIP, LibMCDriver_Raylase_uint32 nPort, LibMCDriver_Raylase_double dMaxLaserPowerInWatts, LibMCDriver_Raylase_RaylaseCard * pRaylaseCardInstance);

/**
* Retrieves a connected card instance.
*
* @param[in] pDriver_Raylase - Driver_Raylase instance.
* @param[in] pCardName - Name of scanner card to retrieve. MUST have been connected before.
* @param[out] pRaylaseCardInstance - Instance of connected card.
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseDriver_Raylase_GetConnectedCardPtr) (LibMCDriver_Raylase_Driver_Raylase pDriver_Raylase, const char * pCardName, LibMCDriver_Raylase_RaylaseCard * pRaylaseCardInstance);

/*************************************************************************************************************************
 Global functions
**************************************************************************************************************************/

/**
* retrieves the binary version of this library.
*
* @param[out] pMajor - returns the major version of this library
* @param[out] pMinor - returns the minor version of this library
* @param[out] pMicro - returns the micro version of this library
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseGetVersionPtr) (LibMCDriver_Raylase_uint32 * pMajor, LibMCDriver_Raylase_uint32 * pMinor, LibMCDriver_Raylase_uint32 * pMicro);

/**
* Returns the last error recorded on this object
*
* @param[in] pInstance - Instance Handle
* @param[in] nErrorMessageBufferSize - size of the buffer (including trailing 0)
* @param[out] pErrorMessageNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pErrorMessageBuffer -  buffer of Message of the last error, may be NULL
* @param[out] pHasError - Is there a last error to query
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseGetLastErrorPtr) (LibMCDriver_Raylase_Base pInstance, const LibMCDriver_Raylase_uint32 nErrorMessageBufferSize, LibMCDriver_Raylase_uint32* pErrorMessageNeededChars, char * pErrorMessageBuffer, bool * pHasError);

/**
* Releases shared ownership of an Instance
*
* @param[in] pInstance - Instance Handle
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseReleaseInstancePtr) (LibMCDriver_Raylase_Base pInstance);

/**
* Acquires shared ownership of an Instance
*
* @param[in] pInstance - Instance Handle
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseAcquireInstancePtr) (LibMCDriver_Raylase_Base pInstance);

/**
* Injects an imported component for usage within this component
*
* @param[in] pNameSpace - NameSpace of the injected component
* @param[in] pSymbolAddressMethod - Address of the SymbolAddressMethod of the injected component
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseInjectComponentPtr) (const char * pNameSpace, LibMCDriver_Raylase_pvoid pSymbolAddressMethod);

/**
* Returns the address of the SymbolLookupMethod
*
* @param[out] pSymbolLookupMethod - Address of the SymbolAddressMethod
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseGetSymbolLookupMethodPtr) (LibMCDriver_Raylase_pvoid * pSymbolLookupMethod);

/**
* Creates a driver instance with a specific name.
*
* @param[in] pName - Name of driver to be created.
* @param[in] pType - Type of driver to be created.
* @param[in] pDriverEnvironment - Environment of this driver.
* @param[out] pInstance - New Driver instance
* @return error code or 0 (success)
*/
typedef LibMCDriver_RaylaseResult (*PLibMCDriver_RaylaseCreateDriverPtr) (const char * pName, const char * pType, LibMCEnv_DriverEnvironment pDriverEnvironment, LibMCDriver_Raylase_Driver * pInstance);

/*************************************************************************************************************************
 Function Table Structure
**************************************************************************************************************************/

typedef struct {
	void * m_LibraryHandle;
	PLibMCDriver_RaylaseDriver_ConfigurePtr m_Driver_Configure;
	PLibMCDriver_RaylaseDriver_GetNamePtr m_Driver_GetName;
	PLibMCDriver_RaylaseDriver_GetTypePtr m_Driver_GetType;
	PLibMCDriver_RaylaseDriver_GetVersionPtr m_Driver_GetVersion;
	PLibMCDriver_RaylaseDriver_QueryParametersPtr m_Driver_QueryParameters;
	PLibMCDriver_RaylaseDriver_QueryParametersExPtr m_Driver_QueryParametersEx;
	PLibMCDriver_RaylaseRaylaseCard_IsConnectedPtr m_RaylaseCard_IsConnected;
	PLibMCDriver_RaylaseRaylaseCard_DisconnectPtr m_RaylaseCard_Disconnect;
	PLibMCDriver_RaylaseRaylaseCard_ResetToSystemDefaultsPtr m_RaylaseCard_ResetToSystemDefaults;
	PLibMCDriver_RaylaseRaylaseCard_LaserOnPtr m_RaylaseCard_LaserOn;
	PLibMCDriver_RaylaseRaylaseCard_LaserOffPtr m_RaylaseCard_LaserOff;
	PLibMCDriver_RaylaseRaylaseCard_ArmLaserPtr m_RaylaseCard_ArmLaser;
	PLibMCDriver_RaylaseRaylaseCard_IsLaserArmedPtr m_RaylaseCard_IsLaserArmed;
	PLibMCDriver_RaylaseRaylaseCard_EnablePilotPtr m_RaylaseCard_EnablePilot;
	PLibMCDriver_RaylaseRaylaseCard_PilotIsEnabledPtr m_RaylaseCard_PilotIsEnabled;
	PLibMCDriver_RaylaseRaylaseCard_GetLaserStatusPtr m_RaylaseCard_GetLaserStatus;
	PLibMCDriver_RaylaseRaylaseCard_DrawLayerPtr m_RaylaseCard_DrawLayer;
	PLibMCDriver_RaylaseDriver_Raylase_SetToSimulationModePtr m_Driver_Raylase_SetToSimulationMode;
	PLibMCDriver_RaylaseDriver_Raylase_IsSimulationModePtr m_Driver_Raylase_IsSimulationMode;
	PLibMCDriver_RaylaseDriver_Raylase_SetCustomSDKResourcePtr m_Driver_Raylase_SetCustomSDKResource;
	PLibMCDriver_RaylaseDriver_Raylase_LoadSDKPtr m_Driver_Raylase_LoadSDK;
	PLibMCDriver_RaylaseDriver_Raylase_ConnectByIPPtr m_Driver_Raylase_ConnectByIP;
	PLibMCDriver_RaylaseDriver_Raylase_GetConnectedCardPtr m_Driver_Raylase_GetConnectedCard;
	PLibMCDriver_RaylaseGetVersionPtr m_GetVersion;
	PLibMCDriver_RaylaseGetLastErrorPtr m_GetLastError;
	PLibMCDriver_RaylaseReleaseInstancePtr m_ReleaseInstance;
	PLibMCDriver_RaylaseAcquireInstancePtr m_AcquireInstance;
	PLibMCDriver_RaylaseInjectComponentPtr m_InjectComponent;
	PLibMCDriver_RaylaseGetSymbolLookupMethodPtr m_GetSymbolLookupMethod;
	PLibMCDriver_RaylaseCreateDriverPtr m_CreateDriver;
} sLibMCDriver_RaylaseDynamicWrapperTable;

#endif // __LIBMCDRIVER_RAYLASE_DYNAMICHEADER_CPPTYPES

