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


Abstract: This is a stub class definition of CXMLDocument

*/

#include "libmcenv_xmldocument.hpp"
#include "libmcenv_interfaceexception.hpp"

// Include custom headers here.
#include "libmcenv_xmldocumentnode.hpp"


using namespace LibMCEnv::Impl;

/*************************************************************************************************************************
 Class definition of CXMLDocument 
**************************************************************************************************************************/

CXMLDocument::CXMLDocument(AMC::PXMLDocumentInstance pXMLDocument)
    : m_pXMLDocument (pXMLDocument)
{
    if (pXMLDocument.get() == nullptr)
        throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);

}

CXMLDocument::~CXMLDocument()
{

}


std::string CXMLDocument::GetDefaultNamespace()
{
    return m_pXMLDocument->GetDefaultNamespace()->getNameSpaceName();
}

LibMCEnv_uint64 CXMLDocument::GetNamespaceCount()
{
    return m_pXMLDocument->GetNamespaceCount();
}

void CXMLDocument::GetNamespace(const LibMCEnv_uint64 nIndex, std::string & sNamespace, std::string & sNamespacePrefix)
{
    return m_pXMLDocument->GetNamespace(nIndex, sNamespace, sNamespacePrefix);
}

bool CXMLDocument::HasNamespace(const std::string & sNamespace)
{
    return m_pXMLDocument->HasNamespace(sNamespace);
}

std::string CXMLDocument::GetNamespacePrefix(const std::string & sNamespace)
{
    return m_pXMLDocument->GetNamespacePrefix(sNamespace);
}

void CXMLDocument::RegisterNamespace(const std::string & sNamespace, const std::string & sNamespacePrefix)
{
    m_pXMLDocument->RegisterNamespace(sNamespace, sNamespacePrefix);
}

IXMLDocumentNode * CXMLDocument::GetRootNode()
{
    return new CXMLDocumentNode(m_pXMLDocument, m_pXMLDocument->GetRootNode());
}

std::string CXMLDocument::SaveToString(const bool bAddLineBreaks)
{
    return m_pXMLDocument->SaveToString(bAddLineBreaks);
}
