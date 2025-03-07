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

#define __AMCIMPL_UI_MODULE

#include "amc_ui_module.hpp"
#include "libmc_exceptiontypes.hpp"
#include "Common/common_utils.hpp"


using namespace AMC;


CUIModuleEnvironment::CUIModuleEnvironment(PStateMachineData pStateMachineData, PResourcePackage pResourcePackage, LibMCData::PBuildJobHandler pBuildJobHandler, CUIModule_ContentRegistry* pContentRegistry, PLogger pLogger)
	: m_pStateMachineData(pStateMachineData), m_pResourcePackage (pResourcePackage), m_pBuildJobHandler (pBuildJobHandler), m_pContentRegistry(pContentRegistry), m_pLogger (pLogger)
{
	LibMCAssertNotNull(pStateMachineData.get());
	LibMCAssertNotNull(pResourcePackage.get());
	LibMCAssertNotNull(pBuildJobHandler.get());
	LibMCAssertNotNull(pLogger.get());
	LibMCAssertNotNull(pContentRegistry);
}

PStateMachineData CUIModuleEnvironment::stateMachineData()
{
	return m_pStateMachineData;
}

PResourcePackage CUIModuleEnvironment::resourcePackage()
{
	return m_pResourcePackage;
}

LibMCData::PBuildJobHandler CUIModuleEnvironment::buildJobHandler()
{
	return m_pBuildJobHandler;
}

CUIModule_ContentRegistry* CUIModuleEnvironment::contentRegistry()
{
	return m_pContentRegistry;
}

CLogger* CUIModuleEnvironment::getLogger()
{
	return m_pLogger.get();
}



CUIModule::CUIModule(const std::string& sName)
	: m_sName (sName), m_sUUID (AMCCommon::CUtils::createUUID ())
{

}

CUIModule::~CUIModule()
{

}

std::string CUIModule::getName()
{
	return m_sName;
}

std::string CUIModule::getUUID()
{
	return m_sUUID;
}

std::string CUIModule::getNameFromXML(pugi::xml_node& xmlNode)
{
	auto nameAttrib = xmlNode.attribute("name");
	if (nameAttrib.empty())
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDMODULENAME);
	return nameAttrib.as_string();
}

std::string CUIModule::getTypeFromXML(pugi::xml_node& xmlNode)
{
	return xmlNode.name();
}