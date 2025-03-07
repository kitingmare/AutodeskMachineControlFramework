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


#include "amc_systemstate.hpp"
#include "libmc_exceptiontypes.hpp"

#include "amc_logger.hpp"
#include "amc_parameterhandler.hpp"
#include "amc_statesignalhandler.hpp"
#include "amc_driverhandler.hpp"
#include "amc_toolpathhandler.hpp"
#include "amc_servicehandler.hpp"
#include "amc_ui_handler.hpp"
#include "amc_statemachinedata.hpp"

#include "libmcdata_dynamic.hpp"

#include "common_chrono.hpp"

#define __STRINGIZE(x) #x
#define __STRINGIZE_VALUE_OF(x) __STRINGIZE(x)


namespace AMC {

	CSystemState::CSystemState(AMC::PLogger pLogger, LibMCData::PDataModel pDataModel, LibMCEnv::PWrapper pEnvWrapper, const std::string& sTestEnvironmentPath)
		: m_sTestEnvironmentPath (sTestEnvironmentPath)
	{
		LibMCAssertNotNull(pLogger.get());
		LibMCAssertNotNull(pDataModel.get());
		LibMCAssertNotNull(pEnvWrapper.get());

		m_pGlobalChrono = std::make_shared<AMCCommon::CChrono>();

		m_pLogger = pLogger;
		m_pDataModel = pDataModel;

		// Retrieve Installation UUID and Secret
		m_pDataModel->GetInstallationInformation(m_sInstallationUUID, m_sInstallationSecret);

		// Create Data Model Instances
		m_pStorage = m_pDataModel->CreateStorage();
		m_pBuildJobHandler = m_pDataModel->CreateBuildJobHandler();
		m_pLoginHandler = m_pDataModel->CreateLoginHandler();
		m_pPersistencyHandler = m_pDataModel->CreatePersistencyHandler();

		m_pToolpathHandler = std::make_shared<CToolpathHandler>(m_pStorage, m_pBuildJobHandler);
		m_pDriverHandler = std::make_shared<CDriverHandler>(pEnvWrapper, m_pToolpathHandler, m_pLogger);
		m_pSignalHandler = std::make_shared<CStateSignalHandler>();
		m_pServiceHandler = std::make_shared<CServiceHandler>(m_pLogger);
		m_pStateMachineData = std::make_shared<CStateMachineData>();
		m_pUIHandler = std::make_shared<CUIHandler>(m_pStateMachineData, m_pSignalHandler,  pEnvWrapper, m_pLogger, getTestEnvironmentPath ());

		auto pSystemParameterHandler = std::make_shared<CParameterHandler>("System");
		auto pSystemInformationGroup = std::make_shared<CParameterGroup>("information", "Information");
		pSystemInformationGroup->addNewStringParameter("githash", "Git Hash", getGitHash ());
		pSystemInformationGroup->addNewStringParameter("clienthash", "Client Hash", getClientHash());
		pSystemInformationGroup->addNewStringParameter("compile_time", "Compile time", std::string (__DATE__) + " " + std::string (__TIME__));
		pSystemInformationGroup->addNewStringParameter("installation_uuid", "Installation", getInstallationUUID ());
		pSystemParameterHandler->addGroup(pSystemInformationGroup);

		m_pStateMachineData->registerParameterHandler("system", pSystemParameterHandler);

	}

	CSystemState::~CSystemState()
	{
	}

	CLogger* CSystemState::logger()
	{
		return m_pLogger.get();
	}


	CStateSignalHandler* CSystemState::stateSignalHandler()
	{
		return m_pSignalHandler.get();
	}

	CDriverHandler* CSystemState::driverHandler()
	{
		return m_pDriverHandler.get();
	}

	CToolpathHandler* CSystemState::toolpathHandler()
	{
		return m_pToolpathHandler.get();
	}

	CServiceHandler* CSystemState::serviceHandler()
	{
		return m_pServiceHandler.get();
	}

	CUIHandler* CSystemState::uiHandler()
	{
		return m_pUIHandler.get();
	}

	CStateMachineData* CSystemState::stateMachineData()
	{
		return m_pStateMachineData.get();

	}



	PLogger CSystemState::getLoggerInstance()
	{
		return m_pLogger;
	}

	PStateSignalHandler CSystemState::getStateSignalHandlerInstance()
	{
		return m_pSignalHandler;
	}

	PDriverHandler CSystemState::getDriverHandlerInstance()
	{
		return m_pDriverHandler;
	}

	PToolpathHandler CSystemState::getToolpathHandlerInstance()
	{
		return m_pToolpathHandler;
	}

	PStateMachineData CSystemState::getStateMachineData()
	{
		return m_pStateMachineData;
	}


	LibMCData::PLoginHandler CSystemState::getLoginHandlerInstance()
	{
		return m_pLoginHandler;
	}

	LibMCData::PBuildJobHandler CSystemState::getBuildJobHandlerInstance()
	{
		return m_pBuildJobHandler;
	}

	LibMCData::PPersistencyHandler CSystemState::getPersistencyHandler()
	{
		return m_pPersistencyHandler;
	}

	AMCCommon::PChrono CSystemState::getGlobalChronoInstance()
	{
		return m_pGlobalChrono;

	}

	LibMCData::CStorage * CSystemState::storage()
	{
		return m_pStorage.get();
	}

	LibMCData::CBuildJobHandler* CSystemState::buildJobHandler()
	{
		return m_pBuildJobHandler.get();
	}

	LibMCData::CLoginHandler* CSystemState::loginHandler()
	{
		return m_pLoginHandler.get();
	}

	AMCCommon::CChrono* CSystemState::globalChrono()
	{
		return m_pGlobalChrono.get();
	}

	void CSystemState::addLibraryPath(const std::string& sLibraryName, const std::string& sLibraryPath, const std::string& sLibraryResourcePath)
	{
		m_LibraryPathes.insert(std::make_pair(sLibraryName, std::make_pair (sLibraryPath, sLibraryResourcePath)));
		m_pToolpathHandler->setLibraryPath(sLibraryName, sLibraryPath);
	}

	std::string CSystemState::getLibraryPath(const std::string& sLibraryName)
	{
		auto iIter = m_LibraryPathes.find(sLibraryName);
		if (iIter == m_LibraryPathes.end())
			throw ELibMCCustomException(LIBMC_ERROR_LIBRARYPATHNOTFOUND, sLibraryName);

		return iIter->second.first;
	}

	std::string CSystemState::getLibraryResourcePath(const std::string& sLibraryName)
	{
		auto iIter = m_LibraryPathes.find(sLibraryName);
		if (iIter == m_LibraryPathes.end())
			throw ELibMCCustomException(LIBMC_ERROR_LIBRARYPATHNOTFOUND, sLibraryName);

		return iIter->second.second;

	}

	std::string CSystemState::getSystemUserID()
	{
		// TODO: Retrieve a unique User ID for the current running session
		return "amc";
	}


	std::string CSystemState::getInstallationUUID()
	{
		return m_sInstallationUUID;
	}

	std::string CSystemState::getInstallationSecret()
	{
		return m_sInstallationSecret;
	}

	std::string CSystemState::getGitHash()
	{
		return __STRINGIZE_VALUE_OF(__GITHASH);
	}

	std::string CSystemState::getClientHash()
	{
		return __STRINGIZE_VALUE_OF(__CLIENTHASH);
	}

	std::string CSystemState::getTestEnvironmentPath()
	{
		return m_sTestEnvironmentPath;
	}
}
