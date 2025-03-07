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


Abstract: This is a stub class definition of CXMLDocumentAttribute

*/

#include "libmcenv_xmldocumentattribute.hpp"
#include "libmcenv_interfaceexception.hpp"
#include "amc_xmldocumentnode.hpp"

// Include custom headers here.
#include "libmc_exceptiontypes.hpp"

#include "common_utils.hpp"

using namespace LibMCEnv::Impl;

/*************************************************************************************************************************
 Class definition of CXMLDocumentAttribute 
**************************************************************************************************************************/

CXMLDocumentAttribute::CXMLDocumentAttribute(AMC::PXMLDocumentAttributeInstance pAttributeInstance)
	: m_pAttributeInstance (pAttributeInstance)
{
	if (pAttributeInstance.get() == nullptr)
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDPARAM);
}

CXMLDocumentAttribute::~CXMLDocumentAttribute()
{

}

std::string CXMLDocumentAttribute::GetNameSpace()
{
	return m_pAttributeInstance->getNameSpace()->getNameSpaceName();
}


std::string CXMLDocumentAttribute::GetName()
{
	return m_pAttributeInstance->getAttributeName();
}

std::string CXMLDocumentAttribute::GetValue()
{
	return m_pAttributeInstance->getValue();
}

bool CXMLDocumentAttribute::IsValidInteger(const LibMCEnv_int64 nMinValue, const LibMCEnv_int64 nMaxValue)
{
	std::string sValue = m_pAttributeInstance->getValue();
	try {
		int64_t nValue = std::stoll (sValue);

		return (nValue >= nMinValue) && (nValue <= nMaxValue);
	}
	catch (...) {
		throw ELibMCCustomException(LIBMCENV_ERROR_INVALIDINTEGERVALUEATTRIBUTE, sValue);
	}
}

LibMCEnv_int64 CXMLDocumentAttribute::GetIntegerValue(const LibMCEnv_int64 nMinValue, const LibMCEnv_int64 nMaxValue)
{
	std::string sValue = m_pAttributeInstance->getValue();
	try {
		int64_t nValue = std::stoll(sValue);

		if ((nValue < nMinValue) && (nValue > nMaxValue))
			throw ELibMCCustomException(LIBMCENV_ERROR_INTEGERVALUEATTRIBUTEOUTOFRANGE, sValue);

		return nValue;

	}
	catch (...) {
		throw ELibMCCustomException(LIBMCENV_ERROR_INVALIDINTEGERVALUEATTRIBUTE, sValue);
	}
}

bool CXMLDocumentAttribute::IsValidDouble(const LibMCEnv_double dMinValue, const LibMCEnv_double dMaxValue)
{
	std::string sValue = m_pAttributeInstance->getValue();
	try {
		double dValue = std::stod(sValue);

		return (dValue >= dMinValue) && (dValue <= dMaxValue);
	}
	catch (...) {
		throw ELibMCCustomException(LIBMCENV_ERROR_INVALIDDOUBLEVALUEATTRIBUTE, sValue);
	}
}

LibMCEnv_double CXMLDocumentAttribute::GetDoubleValue(const LibMCEnv_double dMinValue, const LibMCEnv_double dMaxValue)
{
	std::string sValue = m_pAttributeInstance->getValue();
	try {
		double dValue = std::stod(sValue);

		if ((dValue < dMinValue) && (dValue > dMaxValue))
			throw ELibMCCustomException(LIBMCENV_ERROR_DOUBLEVALUEATTRIBUTEOUTOFRANGE, sValue);

		return dValue;

	}
	catch (...) {
		throw ELibMCCustomException(LIBMCENV_ERROR_INVALIDDOUBLEVALUEATTRIBUTE, sValue);
	}
}

bool CXMLDocumentAttribute::IsValidBool()
{
	std::string sValue = AMCCommon::CUtils::toLowerString (AMCCommon::CUtils::trimString ( m_pAttributeInstance->getValue()));
	if ((sValue == "true") || (sValue == "false"))
		return true;
		
	return IsValidInteger(INT64_MIN, INT64_MAX);
}

bool CXMLDocumentAttribute::GetBoolValue(const LibMCEnv_double dMinValue, const LibMCEnv_double dMaxValue)
{
	std::string sValue = AMCCommon::CUtils::toLowerString(AMCCommon::CUtils::trimString(m_pAttributeInstance->getValue()));
	if (sValue == "true")
		return true;
	if (sValue == "false")
		return false;

	return (GetIntegerValue(INT64_MIN, INT64_MAX) != 0);
}

void CXMLDocumentAttribute::SetValue(const std::string & sValue)
{
	m_pAttributeInstance->setValue (sValue);
}

void CXMLDocumentAttribute::SetIntegerValue(const LibMCEnv_int64 nValue)
{
	m_pAttributeInstance->setValue(std::to_string (nValue));
}

void CXMLDocumentAttribute::SetDoubleValue(const LibMCEnv_double dValue)
{
	m_pAttributeInstance->setValue(std::to_string(dValue));
}

void CXMLDocumentAttribute::SetBoolValue(const bool bValue)
{
	if (bValue)
		m_pAttributeInstance->setValue("true");
	else
		m_pAttributeInstance->setValue("false");
}

void CXMLDocumentAttribute::Remove()
{
	if (m_pAttributeInstance.get() != nullptr) {
		auto pInstance = m_pAttributeInstance;
		pInstance->getNode()->RemoveAttribute(pInstance->getNameSpace().get(), pInstance->getAttributeName());
	}
}

