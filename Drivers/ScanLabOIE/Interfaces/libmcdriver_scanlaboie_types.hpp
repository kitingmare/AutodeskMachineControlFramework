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

Abstract: This is an autogenerated C++-Header file with basic types in
order to allow an easy use of MC Driver ScanLab Open Interface Extension

Interface version: 2.0.0

*/

#ifndef __LIBMCDRIVER_SCANLABOIE_TYPES_HEADER_CPP
#define __LIBMCDRIVER_SCANLABOIE_TYPES_HEADER_CPP


/*************************************************************************************************************************
 Scalar types definition
**************************************************************************************************************************/

#ifdef LIBMCDRIVER_SCANLABOIE_USELEGACYINTEGERTYPES

typedef unsigned char LibMCDriver_ScanLabOIE_uint8;
typedef unsigned short LibMCDriver_ScanLabOIE_uint16 ;
typedef unsigned int LibMCDriver_ScanLabOIE_uint32;
typedef unsigned long long LibMCDriver_ScanLabOIE_uint64;
typedef char LibMCDriver_ScanLabOIE_int8;
typedef short LibMCDriver_ScanLabOIE_int16;
typedef int LibMCDriver_ScanLabOIE_int32;
typedef long long LibMCDriver_ScanLabOIE_int64;

#else // LIBMCDRIVER_SCANLABOIE_USELEGACYINTEGERTYPES

#include <stdint.h>

typedef uint8_t LibMCDriver_ScanLabOIE_uint8;
typedef uint16_t LibMCDriver_ScanLabOIE_uint16;
typedef uint32_t LibMCDriver_ScanLabOIE_uint32;
typedef uint64_t LibMCDriver_ScanLabOIE_uint64;
typedef int8_t LibMCDriver_ScanLabOIE_int8;
typedef int16_t LibMCDriver_ScanLabOIE_int16;
typedef int32_t LibMCDriver_ScanLabOIE_int32;
typedef int64_t LibMCDriver_ScanLabOIE_int64 ;

#endif // LIBMCDRIVER_SCANLABOIE_USELEGACYINTEGERTYPES

typedef float LibMCDriver_ScanLabOIE_single;
typedef double LibMCDriver_ScanLabOIE_double;

/*************************************************************************************************************************
 General type definitions
**************************************************************************************************************************/

typedef LibMCDriver_ScanLabOIE_int32 LibMCDriver_ScanLabOIEResult;
typedef void * LibMCDriver_ScanLabOIEHandle;
typedef void * LibMCDriver_ScanLabOIE_pvoid;

/*************************************************************************************************************************
 Version for LibMCDriver_ScanLabOIE
**************************************************************************************************************************/

#define LIBMCDRIVER_SCANLABOIE_VERSION_MAJOR 2
#define LIBMCDRIVER_SCANLABOIE_VERSION_MINOR 0
#define LIBMCDRIVER_SCANLABOIE_VERSION_MICRO 0
#define LIBMCDRIVER_SCANLABOIE_VERSION_PRERELEASEINFO ""
#define LIBMCDRIVER_SCANLABOIE_VERSION_BUILDINFO ""

/*************************************************************************************************************************
 Error constants for LibMCDriver_ScanLabOIE
**************************************************************************************************************************/

#define LIBMCDRIVER_SCANLABOIE_SUCCESS 0
#define LIBMCDRIVER_SCANLABOIE_ERROR_NOTIMPLEMENTED 1 /** functionality not implemented */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDPARAM 2 /** an invalid parameter was passed */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDCAST 3 /** a type cast failed */
#define LIBMCDRIVER_SCANLABOIE_ERROR_BUFFERTOOSMALL 4 /** a provided buffer is too small */
#define LIBMCDRIVER_SCANLABOIE_ERROR_GENERICEXCEPTION 5 /** a generic exception occurred */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTLOADLIBRARY 6 /** the library could not be loaded */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTFINDLIBRARYEXPORT 7 /** a required exported symbol could not be found in the library */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INCOMPATIBLEBINARYVERSION 8 /** the version of the binary interface does not match the bindings interface */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDRIVERTYPE 1000 /** Invalid OIE Driver type */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDRIVERNAME 1001 /** Invalid OIE Driver name */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDRIVERENVIRONMENT 1002 /** Invalid OIE Driver environment */
#define LIBMCDRIVER_SCANLABOIE_ERROR_SDKALREADYINITIALIZED 1003 /** SDK already initialized. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSCANLABOIESDK 1004 /** Invalid Scanlab OIE SDK. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_DEVICENOTAVAILABLEANYMORE 1005 /** Device not available anymore. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTADDDEVICE 1006 /** Could not add device. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEALREADYCONNECTED 1007 /** Device already connected. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEALREADYREMOVED 1008 /** Device already removed. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_DEVICENOTCONNECTED 1009 /** Device not connected. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPCOUNTONDEVICE 1010 /** Invalid app count on device. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPINDEX 1011 /** Invalid app index. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPNAME 1012 /** Invalid app name. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPVERSION 1013 /** Invalid app version. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRESPONSETIMEOUT 1014 /** Invalid response timeout. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPPACKAGEBUFFER 1015 /** Invalid app package buffer. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRESOURCENAME 1016 /** Invalid resource name. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTORELIBRESSLRESOURCE 1017 /** Could not store LibreSSL resource. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTORELIBCRYPTORESOURCE 1018 /** Could not store LibCrypto resource. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOREQT5CORERESOURCE 1019 /** Could not store QT5Core resource. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOREQT5NETWORKRESOURCE 1020 /** Could not store QT5Network resource. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_SCANLABOIESDKNOTLOADED 1021 /** Scanlab OIE SDK not loaded. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDEVICENAME 1022 /** Invalid device name. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEHASNOTBEENFOUND 1023 /** Device has not been found. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEISALREADYEXISTING 1024 /** Device is already existing. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_EMPTYDEVICENAME 1025 /** Empty device name. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDVALUESPERRECORD 1026 /** Invalid values per record. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDBUFFERSIZE 1027 /** Invalid buffer size. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_PACKETISNOTRECORDING 1028 /** Packet is not recording. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_TOOMANYVALUESINPACKET 1029 /** Too many values in packet. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_NOTENOUGHVALUESINPACKET 1030 /** Not enough values in packet. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_BUFFEROVERFLOW 1031 /** Buffer overflow. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRTCSIGNALCOUNT 1032 /** Invalid RTC signal count. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSENSORSIGNALCOUNT 1033 /** Invalid Sensor signal count. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_NODATARECORDINGAVAILABLE 1034 /** No data recording available. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRTCVALUESPERRECORD 1035 /** Invalid RTC values per record. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRECORDINDEX 1036 /** Invalid record index. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSIGNALINDEX 1037 /** Invalid signal index. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTARTAPP 1038 /** Could not start app. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOPAPP 1039 /** Could not stop app. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSENSORINDEX 1040 /** Invalid sensor index. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRTCINDEX 1041 /** Invalid RTC index. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOREOIECALIBRATIONLIBRARYBUFFER 1042 /** Could not store OIE Calibration library buffer. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTORERTCSTREAMPARSERBUFFER 1043 /** Could not store RTC Stream parser buffer. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTGETRTCSIGNALIDS 1044 /** Could not get RTC Signal IDs. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTCREATEDEVICECONFIGURATION 1045 /** Could not create device configuration. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_UNSUPPORTEDOIESDKVERSION 1046 /** Unsupported OIE SDK Version. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDEVICECONFIGURATION 1047 /** Invalid device configuration. */
#define LIBMCDRIVER_SCANLABOIE_ERROR_OIESDKLIBRARYRETURNSINVALIDVERSION 1048 /** OIE SDK Library returns invalid version. */

/*************************************************************************************************************************
 Error strings for LibMCDriver_ScanLabOIE
**************************************************************************************************************************/

inline const char * LIBMCDRIVER_SCANLABOIE_GETERRORSTRING (LibMCDriver_ScanLabOIEResult nErrorCode) {
  switch (nErrorCode) {
    case LIBMCDRIVER_SCANLABOIE_SUCCESS: return "no error";
    case LIBMCDRIVER_SCANLABOIE_ERROR_NOTIMPLEMENTED: return "functionality not implemented";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDPARAM: return "an invalid parameter was passed";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDCAST: return "a type cast failed";
    case LIBMCDRIVER_SCANLABOIE_ERROR_BUFFERTOOSMALL: return "a provided buffer is too small";
    case LIBMCDRIVER_SCANLABOIE_ERROR_GENERICEXCEPTION: return "a generic exception occurred";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTLOADLIBRARY: return "the library could not be loaded";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTFINDLIBRARYEXPORT: return "a required exported symbol could not be found in the library";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INCOMPATIBLEBINARYVERSION: return "the version of the binary interface does not match the bindings interface";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDRIVERTYPE: return "Invalid OIE Driver type";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDRIVERNAME: return "Invalid OIE Driver name";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDRIVERENVIRONMENT: return "Invalid OIE Driver environment";
    case LIBMCDRIVER_SCANLABOIE_ERROR_SDKALREADYINITIALIZED: return "SDK already initialized.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSCANLABOIESDK: return "Invalid Scanlab OIE SDK.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_DEVICENOTAVAILABLEANYMORE: return "Device not available anymore.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTADDDEVICE: return "Could not add device.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEALREADYCONNECTED: return "Device already connected.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEALREADYREMOVED: return "Device already removed.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_DEVICENOTCONNECTED: return "Device not connected.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPCOUNTONDEVICE: return "Invalid app count on device.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPINDEX: return "Invalid app index.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPNAME: return "Invalid app name.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPVERSION: return "Invalid app version.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRESPONSETIMEOUT: return "Invalid response timeout.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDAPPPACKAGEBUFFER: return "Invalid app package buffer.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRESOURCENAME: return "Invalid resource name.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTORELIBRESSLRESOURCE: return "Could not store LibreSSL resource.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTORELIBCRYPTORESOURCE: return "Could not store LibCrypto resource.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOREQT5CORERESOURCE: return "Could not store QT5Core resource.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOREQT5NETWORKRESOURCE: return "Could not store QT5Network resource.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_SCANLABOIESDKNOTLOADED: return "Scanlab OIE SDK not loaded.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDEVICENAME: return "Invalid device name.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEHASNOTBEENFOUND: return "Device has not been found.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_DEVICEISALREADYEXISTING: return "Device is already existing.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_EMPTYDEVICENAME: return "Empty device name.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDVALUESPERRECORD: return "Invalid values per record.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDBUFFERSIZE: return "Invalid buffer size.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_PACKETISNOTRECORDING: return "Packet is not recording.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_TOOMANYVALUESINPACKET: return "Too many values in packet.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_NOTENOUGHVALUESINPACKET: return "Not enough values in packet.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_BUFFEROVERFLOW: return "Buffer overflow.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRTCSIGNALCOUNT: return "Invalid RTC signal count.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSENSORSIGNALCOUNT: return "Invalid Sensor signal count.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_NODATARECORDINGAVAILABLE: return "No data recording available.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRTCVALUESPERRECORD: return "Invalid RTC values per record.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRECORDINDEX: return "Invalid record index.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSIGNALINDEX: return "Invalid signal index.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTARTAPP: return "Could not start app.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOPAPP: return "Could not stop app.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDSENSORINDEX: return "Invalid sensor index.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDRTCINDEX: return "Invalid RTC index.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTOREOIECALIBRATIONLIBRARYBUFFER: return "Could not store OIE Calibration library buffer.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTSTORERTCSTREAMPARSERBUFFER: return "Could not store RTC Stream parser buffer.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTGETRTCSIGNALIDS: return "Could not get RTC Signal IDs.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_COULDNOTCREATEDEVICECONFIGURATION: return "Could not create device configuration.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_UNSUPPORTEDOIESDKVERSION: return "Unsupported OIE SDK Version.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_INVALIDDEVICECONFIGURATION: return "Invalid device configuration.";
    case LIBMCDRIVER_SCANLABOIE_ERROR_OIESDKLIBRARYRETURNSINVALIDVERSION: return "OIE SDK Library returns invalid version.";
    default: return "unknown error";
  }
}

/*************************************************************************************************************************
 Declaration of handle classes 
**************************************************************************************************************************/

typedef LibMCDriver_ScanLabOIEHandle LibMCDriver_ScanLabOIE_Base;
typedef LibMCDriver_ScanLabOIEHandle LibMCDriver_ScanLabOIE_Driver;
typedef LibMCDriver_ScanLabOIEHandle LibMCDriver_ScanLabOIE_DeviceConfiguration;
typedef LibMCDriver_ScanLabOIEHandle LibMCDriver_ScanLabOIE_DataRecording;
typedef LibMCDriver_ScanLabOIEHandle LibMCDriver_ScanLabOIE_OIEDevice;
typedef LibMCDriver_ScanLabOIEHandle LibMCDriver_ScanLabOIE_Driver_ScanLab_OIE;

namespace LibMCDriver_ScanLabOIE {

  /*************************************************************************************************************************
   Declaration of enums
  **************************************************************************************************************************/
  
  enum class eRTCDeviceType : LibMCDriver_ScanLabOIE_int32 {
    Unknown = 0,
    RTC5 = 1,
    RTC6 = 2
  };
  
  enum class eOIEDeviceDriverType : LibMCDriver_ScanLabOIE_int32 {
    Unknown = 0,
    OIEVersion2 = 1,
    OIEVersion3Compatibility = 2,
    OIEVersion3 = 3
  };
  
} // namespace LibMCDriver_ScanLabOIE;

// define legacy C-names for enums, structs and function types
typedef LibMCDriver_ScanLabOIE::eRTCDeviceType eLibMCDriver_ScanLabOIERTCDeviceType;
typedef LibMCDriver_ScanLabOIE::eOIEDeviceDriverType eLibMCDriver_ScanLabOIEOIEDeviceDriverType;

#endif // __LIBMCDRIVER_SCANLABOIE_TYPES_HEADER_CPP
