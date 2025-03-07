#[[++

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

]]

cmake_minimum_required(VERSION 3.5)

##########################################################################################
### Change the next line for making new ui plugins
##########################################################################################

set (PLUGINPROJECT userinterface)

##########################################################################################
### generic CMake code
##########################################################################################

project(LibMCPlugin_${PLUGINPROJECT})

string(TOLOWER ${PLUGINPROJECT} PLUGINSUFFIX)
set (PLUGINNAME libmcplugin_${PLUGINSUFFIX})


set (CMAKE_CXX_STANDARD 11)

# The location of autogenerated interfaces
set(CMAKE_FRAMEWORK_DIR ${PROJECT_BINARY_DIR}/../../Framework)
set(CMAKE_CURRENT_OUTPUT_DIR ${PROJECT_BINARY_DIR}/../../Output)

set(CMAKE_CURRENT_HEADER_DIR ${CMAKE_FRAMEWORK_DIR}/HeadersDev/CppDynamic)
set(CMAKE_CURRENT_AUTOGENERATED_DIR ${CMAKE_FRAMEWORK_DIR}/InterfacesDev)
set(CMAKE_CURRENT_PLUGIN_DIR ${CMAKE_FRAMEWORK_DIR}/PluginCpp)
set(CMAKE_CURRENT_DRIVERHEADER_DIR ${CMAKE_FRAMEWORK_DIR}/HeadersDriver/CppDynamic)

file(STRINGS ${PROJECT_BINARY_DIR}/../../githash.txt GLOBALGITHASH)
message(STATUS "User interface git hash: \"${GLOBALGITHASH}\"")

file(GLOB LIBMCPLUGIN_FRAMEWORK
	${CMAKE_CURRENT_PLUGIN_DIR}/libmcui*.cpp
	${CMAKE_CURRENT_AUTOGENERATED_DIR}/libmcui_interfaceexception.cpp
	${CMAKE_CURRENT_AUTOGENERATED_DIR}/libmcui_interfacewrapper.cpp
)

file(GLOB LIBMCPLUGIN_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

source_group("framework" FILES ${LIBMCPLUGIN_FRAMEWORK} )
source_group("source" FILES ${LIBMCPLUGIN_SRC} )
add_library(${PLUGINNAME} SHARED ${LIBMCPLUGIN_SRC} ${LIBMCPLUGIN_FRAMEWORK})
# Do not prefix the binary's name with "lib" on Unix systems:
set_target_properties(${PLUGINNAME} PROPERTIES PREFIX "" IMPORT_PREFIX "" )
# The following two properties are crucial to reduce the number of undesirably exported symbols
set_target_properties(${PLUGINNAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(${PLUGINNAME} PROPERTIES VISIBILITY_INLINES_HIDDEN ON)

# This makes sure symbols are exported
target_compile_options(${PLUGINNAME} PRIVATE "-D__LIBMCPLUGIN_EXPORTS")
target_compile_options(${PLUGINNAME} PRIVATE "-D__LIBMCUI_EXPORTS")
target_include_directories(${PLUGINNAME} PRIVATE ${CMAKE_CURRENT_AUTOGENERATED_DIR})
target_include_directories(${PLUGINNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PLUGINNAME} PRIVATE ${CMAKE_CURRENT_PLUGIN_DIR})
target_include_directories(${PLUGINNAME} PRIVATE ${CMAKE_CURRENT_HEADER_DIR})
target_include_directories(${PLUGINNAME} PRIVATE ${CMAKE_CURRENT_DRIVERHEADER_DIR})

if(WIN32)
if (MSVC)
else()
target_link_options(${PLUGINNAME} PRIVATE -static-libgcc -static-libstdc++ --static )
endif (MSVC)
endif()

set_target_properties(${PLUGINNAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_OUTPUT_DIR}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_OUTPUT_DIR}"
	VS_DEBUGGER_COMMAND "${CMAKE_CURRENT_OUTPUT_DIR}/amc_server.exe"
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_OUTPUT_DIR}"	
	OUTPUT_NAME "${GLOBALGITHASH}_plugin_${PLUGINSUFFIX}"
)


##########################################################################################
### Add dependencies for drivers below
###########################################################################################

