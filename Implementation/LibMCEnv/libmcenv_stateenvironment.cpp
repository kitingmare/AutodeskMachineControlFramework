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

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "libmcenv_stateenvironment.hpp"
#include "libmcenv_interfaceexception.hpp"

#include "libmcenv_signalhandler.hpp"
#include "libmcenv_signaltrigger.hpp"
#include "libmcenv_toolpathaccessor.hpp"
#include "libmcenv_build.hpp"
#include "libmcenv_imagedata.hpp"
#include "libmcenv_testenvironment.hpp"
#include "libmcenv_xmldocument.hpp"

#include "amc_logger.hpp"
#include "amc_driverhandler.hpp"
#include "amc_parameterhandler.hpp"
#include "amc_ui_handler.hpp"
#include "amc_statemachinedata.hpp"
#include "amc_xmldocument.hpp"

#include "common_chrono.hpp"
#include <thread> 

// Include custom headers here.

using namespace LibMCEnv::Impl;



/*************************************************************************************************************************
 Class definition of CStateEnvironment 
**************************************************************************************************************************/

CStateEnvironment::CStateEnvironment(AMC::PSystemState pSystemState, AMC::PParameterHandler pParameterHandler, std::string sInstanceName)
	: m_pSystemState (pSystemState), m_pParameterHandler (pParameterHandler), m_sInstanceName(sInstanceName)
{
	if (pSystemState.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);
	if (pParameterHandler.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);

}


std::string CStateEnvironment::GetMachineState(const std::string& sMachineInstance)
{
	return m_pSystemState->stateMachineData()->getInstanceStateName(sMachineInstance);
}


ISignalTrigger* CStateEnvironment::PrepareSignal(const std::string& sMachineInstance, const std::string& sSignalName)
{
	if (!m_pSystemState->stateSignalHandler()->hasSignalDefinition(sMachineInstance, sSignalName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_COULDNOTFINDSIGNALDEFINITON);

	return new CSignalTrigger(m_pSystemState->getStateSignalHandlerInstance (), sMachineInstance, sSignalName);

}

bool CStateEnvironment::WaitForSignal(const std::string& sSignalName, const LibMCEnv_uint32 nTimeOut, ISignalHandler*& pHandlerInstance)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	auto endTime = startTime + std::chrono::milliseconds(nTimeOut);

	bool bIsTimeOut = false;
	while (!bIsTimeOut) {

		std::string sCurrentSignalUUID;

		if (m_pSystemState->stateSignalHandler()->checkSignal(m_sInstanceName, sSignalName, sCurrentSignalUUID)) {
			pHandlerInstance = new CSignalHandler(m_pSystemState->getStateSignalHandlerInstance(), sCurrentSignalUUID);

			return true;
		}

		bIsTimeOut = std::chrono::high_resolution_clock::now() >= endTime;

		if (!bIsTimeOut) {
			if (CheckForTermination())
				throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_TERMINATED);

			AMCCommon::CChrono chrono;
			chrono.sleepMilliseconds(DEFAULT_WAITFOR_SLEEP_MS);
		}
	}

	return false; 
}

ISignalHandler* CStateEnvironment::GetUnhandledSignal(const std::string& sSignalTypeName)
{
	std::string sCurrentSignalUUID;

	if (m_pSystemState->stateSignalHandler()->checkSignal(m_sInstanceName, sSignalTypeName, sCurrentSignalUUID)) {
		return new CSignalHandler(m_pSystemState->getStateSignalHandlerInstance(), sCurrentSignalUUID);
	}

	return nullptr;
}

ISignalHandler* CStateEnvironment::GetUnhandledSignalByUUID(const std::string& sUUID, const bool bMustExist)
{
	std::string sNormalizedSignalUUID = AMCCommon::CUtils::normalizeUUIDString (sUUID);

	if (m_pSystemState->stateSignalHandler()->checkSignalUUID(m_sInstanceName, sNormalizedSignalUUID)) {
		return new CSignalHandler(m_pSystemState->getStateSignalHandlerInstance(), sNormalizedSignalUUID);
	}
	else {
		if (bMustExist)
			throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_SIGNALUUIDNOTACTIVE, "signal uuid not active: " + sNormalizedSignalUUID);

		return nullptr;
	}


}


IBuild* CStateEnvironment::GetBuildJob(const std::string& sBuildUUID)
{
	auto pBuildJobHandler = m_pSystemState->buildJobHandler();
	auto pBuildJob = pBuildJobHandler->RetrieveJob(sBuildUUID);
	return new CBuild(pBuildJob, m_pSystemState);
}


void CStateEnvironment::UnloadAllToolpathes()
{
	m_pSystemState->toolpathHandler()->unloadAllEntities();
}



void CStateEnvironment::GetDriverLibrary(const std::string& sDriverName, std::string& sDriverType, LibMCEnv_pvoid& pDriverLookup)
{
	m_pSystemState->driverHandler()->GetDriverInformation (sDriverName, sDriverType, pDriverLookup);
}

void CStateEnvironment::CreateDriverAccess(const std::string& sDriverName, LibMCEnv_pvoid& pDriverHandle) 
{	
	pDriverHandle = m_pSystemState->driverHandler()->acquireDriver(sDriverName, m_sInstanceName);
}



void CStateEnvironment::SetNextState(const std::string & sStateName)
{
	m_sNextState = sStateName;
}

std::string CStateEnvironment::getNextState()
{
	return m_sNextState;
}

void CStateEnvironment::LogMessage(const std::string& sLogString)
{
	m_pSystemState->logger()->logMessage(sLogString, m_sInstanceName, AMC::eLogLevel::Message);
}

void CStateEnvironment::LogWarning(const std::string& sLogString)
{
	m_pSystemState->logger()->logMessage(sLogString, m_sInstanceName, AMC::eLogLevel::Warning);
}

void CStateEnvironment::LogInfo(const std::string& sLogString)
{
	m_pSystemState->logger()->logMessage(sLogString, m_sInstanceName, AMC::eLogLevel::Info);
}

void CStateEnvironment::Sleep(const LibMCEnv_uint32 nDelay)
{
	AMCCommon::CChrono chrono;
	chrono.sleepMilliseconds(nDelay);
}

bool CStateEnvironment::CheckForTermination()
{
	// TODO
	return false;
}



void CStateEnvironment::StoreSignal(const std::string& sName, ISignalHandler* pHandler)
{
	if (pHandler == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);

	AMC::CParameterGroup* pGroup = m_pSystemState->stateMachineData()->getDataStore(m_sInstanceName);

	if (!pGroup->hasParameter(sName)) {
		pGroup->addNewStringParameter(sName, "", pHandler->GetSignalID());
	}
	else {
		pGroup->setParameterValueByName(sName, pHandler->GetSignalID());
	}

}

ISignalHandler* CStateEnvironment::RetrieveSignal(const std::string& sName)
{
	AMC::CParameterGroup* pGroup = m_pSystemState->stateMachineData()->getDataStore(m_sInstanceName);

	std::string sSignalID = pGroup->getParameterValueByName(sName);
	return new CSignalHandler(m_pSystemState->getStateSignalHandlerInstance(), sSignalID);
}


void CStateEnvironment::ClearStoredValue(const std::string& sName)
{
	AMC::CParameterGroup* pGroup = m_pSystemState->stateMachineData()->getDataStore(m_sInstanceName);
	pGroup->removeValue(sName);

}

void CStateEnvironment::SetStringParameter(const std::string& sParameterGroup, const std::string& sParameterName, const std::string& sValue)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	pGroup->setParameterValueByName(sParameterName, sValue);
}


void CStateEnvironment::SetUUIDParameter(const std::string& sParameterGroup, const std::string& sParameterName, const std::string& sValue)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	pGroup->setParameterValueByName(sParameterName, AMCCommon::CUtils::normalizeUUIDString (sValue));
}


void CStateEnvironment::SetDoubleParameter(const std::string& sParameterGroup, const std::string& sParameterName, const LibMCEnv_double dValue)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	pGroup->setDoubleParameterValueByName(sParameterName, dValue);
}

void CStateEnvironment::SetIntegerParameter(const std::string& sParameterGroup, const std::string& sParameterName, const LibMCEnv_int64 nValue)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	pGroup->setIntParameterValueByName(sParameterName, nValue);
}

void CStateEnvironment::SetBoolParameter(const std::string& sParameterGroup, const std::string& sParameterName, const bool bValue)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	pGroup->setBoolParameterValueByName(sParameterName, bValue);
}

std::string CStateEnvironment::GetStringParameter(const std::string& sParameterGroup, const std::string& sParameterName)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	return pGroup->getParameterValueByName(sParameterName);
}


std::string CStateEnvironment::GetUUIDParameter(const std::string& sParameterGroup, const std::string& sParameterName)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	return AMCCommon::CUtils::normalizeUUIDString (pGroup->getParameterValueByName(sParameterName));
}

LibMCEnv_double CStateEnvironment::GetDoubleParameter(const std::string& sParameterGroup, const std::string& sParameterName)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	return pGroup->getDoubleParameterValueByName(sParameterName);
}

LibMCEnv_int64 CStateEnvironment::GetIntegerParameter(const std::string& sParameterGroup, const std::string& sParameterName)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	return pGroup->getIntParameterValueByName(sParameterName);
}

bool CStateEnvironment::GetBoolParameter(const std::string& sParameterGroup, const std::string& sParameterName)
{
	if (!m_pParameterHandler->hasGroup(sParameterGroup))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERGROUPNOTFOUND);

	auto pGroup = m_pParameterHandler->findGroup(sParameterGroup, true);
	if (!pGroup->hasParameter(sParameterName))
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_PARAMETERNOTFOUND);

	return pGroup->getBoolParameterValueByName(sParameterName);
}


void CStateEnvironment::LoadResourceData(const std::string& sResourceName, LibMCEnv_uint64 nResourceDataBufferSize, LibMCEnv_uint64* pResourceDataNeededCount, LibMCEnv_uint8* pResourceDataBuffer)
{
	auto pUIHandler = m_pSystemState->uiHandler();
	if (pUIHandler == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALERROR);

	auto pResourcePackage = pUIHandler->getCoreResourcePackage();
	if (pResourcePackage.get () == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALERROR);

	auto pResourceEntry = pResourcePackage->findEntryByName(sResourceName, true);
	auto nResourceSize = pResourceEntry->getSize();

	if (pResourceDataNeededCount != nullptr)
		*pResourceDataNeededCount = nResourceSize;

	if (pResourceDataBuffer != nullptr) {
		if (nResourceDataBufferSize < nResourceSize)
			throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_BUFFERTOOSMALL);

		pResourcePackage->readEntryEx(sResourceName, pResourceDataBuffer, nResourceDataBufferSize);
	}


}

std::string CStateEnvironment::LoadResourceString(const std::string& sResourceName)
{
	auto pUIHandler = m_pSystemState->uiHandler();
	if (pUIHandler == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALERROR);

	auto pResourcePackage = pUIHandler->getCoreResourcePackage();
	if (pResourcePackage.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALERROR);

	return pResourcePackage->readEntryUTF8String(sResourceName);
}



IImageData* CStateEnvironment::CreateEmptyImage(const LibMCEnv_uint32 nPixelSizeX, const LibMCEnv_uint32 nPixelSizeY, const LibMCEnv_double dDPIValueX, const LibMCEnv_double dDPIValueY, const LibMCEnv::eImagePixelFormat ePixelFormat)
{
	return CImageData::createEmpty(nPixelSizeX, nPixelSizeY, dDPIValueX, dDPIValueY, ePixelFormat);
}

IImageData* CStateEnvironment::LoadPNGImage(const LibMCEnv_uint64 nPNGDataBufferSize, const LibMCEnv_uint8* pPNGDataBuffer, const LibMCEnv_double dDPIValueX, const LibMCEnv_double dDPIValueY, const LibMCEnv::eImagePixelFormat ePixelFormat)
{
	return CImageData::createFromPNG(pPNGDataBuffer, nPNGDataBufferSize, dDPIValueX, dDPIValueY, ePixelFormat);
}

LibMCEnv_uint64 CStateEnvironment::GetGlobalTimerInMilliseconds()
{
	return m_pSystemState->getGlobalChronoInstance()->getExistenceTimeInMilliseconds();
}

ITestEnvironment* CStateEnvironment::GetTestEnvironment()
{
	return new CTestEnvironment(m_pSystemState->getTestEnvironmentPath ());
}

LibMCEnv::Impl::IXMLDocument* CStateEnvironment::CreateXMLDocument(const std::string& sRootNodeName, const std::string& sDefaultNamespace)
{
	auto pDocument = std::make_shared<AMC::CXMLDocumentInstance>();

	pDocument->createEmptyDocument(sRootNodeName, sDefaultNamespace);

	return new CXMLDocument(pDocument);
}

LibMCEnv::Impl::IXMLDocument* CStateEnvironment::ParseXMLString(const std::string& sXMLString)
{
	auto pDocument = std::make_shared<AMC::CXMLDocumentInstance>();

	try {
		pDocument->parseXMLString(sXMLString);
	}
	catch (std::exception& E) {
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_COULDNOTPARSEXMLSTRING, "could not parse XML string: " + std::string(E.what()));
	}

	return new CXMLDocument(pDocument);

}

LibMCEnv::Impl::IXMLDocument* CStateEnvironment::ParseXMLData(const LibMCEnv_uint64 nXMLDataBufferSize, const LibMCEnv_uint8* pXMLDataBuffer)
{
	auto pDocument = std::make_shared<AMC::CXMLDocumentInstance>();

	try {
		pDocument->parseXMLData(nXMLDataBufferSize, pXMLDataBuffer);
	}
	catch (std::exception& E) {
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_COULDNOTPARSEXMLDATA, "could not parse XML data: " + std::string(E.what()));
	}

	return new CXMLDocument(pDocument);

}
