
/*
 * File:   FPrintError.cpp
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 19:33
 */

#include "exception/FPrintError.h"

FPrintError::FPrintError(const char* msg, const char* location_info, const char* function_info)
: BaseException(msg, location_info, function_info)
{
}

FPrintError::FPrintError(const FPrintError& orig)
: BaseException(orig)
{
}

FPrintError::~FPrintError()
{
}



FPrintOpenDeviceError::FPrintOpenDeviceError(const char* msg,
                                             const char* location_info,
                                             const char* function_info)
: FPrintError(msg, location_info, function_info)
{
}

FPrintOpenDeviceError::FPrintOpenDeviceError(const FPrintOpenDeviceError& orig)
: FPrintError(orig)
{
}

FPrintOpenDeviceError::~FPrintOpenDeviceError()
{
}


FPrintRetrieveDeviceInfoError::FPrintRetrieveDeviceInfoError(const char* msg,
                                                             const char* location_info,
                                                             const char* function_info)
: FPrintError(msg, location_info, function_info)
{
}

FPrintRetrieveDeviceInfoError::FPrintRetrieveDeviceInfoError(const FPrintRetrieveDeviceInfoError& orig)
: FPrintError(orig)
{
}

FPrintRetrieveDeviceInfoError::~FPrintRetrieveDeviceInfoError()
{
}


FPrintRetrievePrintDataError::FPrintRetrievePrintDataError(const char* msg,
                                                           const char* location_info,
                                                           const char* function_info)
: FPrintError(msg, location_info, function_info)
{
}

FPrintRetrievePrintDataError::FPrintRetrievePrintDataError(const FPrintRetrievePrintDataError& orig)
: FPrintError(orig)
{
}

FPrintRetrievePrintDataError::~FPrintRetrievePrintDataError()
{
}


FPrintRetrieveDiscoveredError::FPrintRetrieveDiscoveredError(const char* msg,
                                                             const char* location_info,
                                                             const char* function_info)
: FPrintError(msg, location_info, function_info)
{
}

FPrintRetrieveDiscoveredError::FPrintRetrieveDiscoveredError(const FPrintRetrieveDiscoveredError& orig)
: FPrintError(orig)
{
}

FPrintRetrieveDiscoveredError::~FPrintRetrieveDiscoveredError()
{
}


FPrintDiscoverPrintError::FPrintDiscoverPrintError(const char* msg,
                                                   const char* location_info,
                                                   const char* function_info)
: FPrintError(msg, location_info, function_info)
{
}

FPrintDiscoverPrintError::FPrintDiscoverPrintError(const FPrintDiscoverPrintError& orig)
: FPrintError(orig)
{
}

FPrintDiscoverPrintError::~FPrintDiscoverPrintError()
{
}
