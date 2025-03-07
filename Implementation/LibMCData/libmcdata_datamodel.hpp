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

#ifndef __LIBMCDATA_DATAMODEL
#define __LIBMCDATA_DATAMODEL

#include "libmcdata_interfaces.hpp"

// Parent classes
#include "libmcdata_base.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "amcdata_sqlhandler.hpp"
#include "amcdata_storagepath.hpp"

namespace LibMCData {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CDataModel 
**************************************************************************************************************************/

class CDataModel : public virtual IDataModel, public virtual CBase {
private:

protected:

	AMCData::PSQLHandler m_pSQLHandler;
	AMCData::PStoragePath m_pStoragePath;

	LibMCData::eDataBaseType m_eDataBaseType;

	std::string m_sInstallationUUID;
	std::string m_sInstallationSecret;

	std::string m_sTempBasePath;

	LibMCData::LogCallback m_pLogCallback;
	LibMCData_pvoid m_pLogUserData;

public:

	CDataModel();

	virtual ~CDataModel();

	void InitialiseDatabase(const std::string & sDataDirectory, const LibMCData::eDataBaseType dataBaseType, const std::string & sConnectionString) override;

	LibMCData_uint32 GetDataModelVersion() override;

	void GetInstallationInformation(std::string& sInstallationUUID, std::string& sInstallationSecret) override;

	IStorage * CreateStorage() override;

	ILogSession* CreateNewLogSession() override;

	IBuildJobHandler* CreateBuildJobHandler() override;

	ILoginHandler* CreateLoginHandler() override;

	IPersistencyHandler* CreatePersistencyHandler() override;

	void SetBaseTempDirectory(const std::string& sTempDirectory) override;

	std::string GetBaseTempDirectory() override;

	void SetLogCallback(const LibMCData::LogCallback pLogCallback, const LibMCData_pvoid pUserData) override;

	void ClearLogCallback() override;

	bool HasLogCallback() override;
	
	void TriggerLogCallback(const std::string& sLogMessage, const std::string& sSubSystem, const LibMCData::eLogLevel eLogLevel, const std::string& sTimestamp) override;


};

} // namespace Impl
} // namespace LibMCData

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDATA_DATAMODEL
