
/*
 * File:   FPrintError.h
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 19:33
 */

#ifndef FPRINTERROR_H
#define FPRINTERROR_H

#include "exception/BaseException.h"


class FPrintError : public BaseException {
	public:
		FPrintError(const char* msg, const char* location_info, const char* function_info);
		FPrintError(const FPrintError& orig);
		virtual ~FPrintError();
};



class FPrintOpenDeviceError : public FPrintError {
	public:
		FPrintOpenDeviceError(const char* msg, const char* location_info, const char* function_info);
		FPrintOpenDeviceError(const FPrintOpenDeviceError& orig);
		virtual ~FPrintOpenDeviceError();
};


class FPrintRetrieveDeviceInfoError : public FPrintError {
	public:
		FPrintRetrieveDeviceInfoError(const char* msg, const char* location_info, const char* function_info);
		FPrintRetrieveDeviceInfoError(const FPrintRetrieveDeviceInfoError& orig);
		virtual ~FPrintRetrieveDeviceInfoError();
};


class FPrintRetrievePrintDataError : public FPrintError {
	public:
		FPrintRetrievePrintDataError(const char* msg, const char* location_info, const char* function_info);
		FPrintRetrievePrintDataError(const FPrintRetrievePrintDataError& orig);
		virtual ~FPrintRetrievePrintDataError();
};


class FPrintRetrieveDiscoveredError : public FPrintError {
	public:
		FPrintRetrieveDiscoveredError(const char* msg, const char* location_info, const char* function_info);
		FPrintRetrieveDiscoveredError(const FPrintRetrieveDiscoveredError& orig);
		virtual ~FPrintRetrieveDiscoveredError();
};


class FPrintDiscoverPrintError : public FPrintError {
	public:
		FPrintDiscoverPrintError(const char* msg, const char* location_info, const char* function_info);
		FPrintDiscoverPrintError(const FPrintDiscoverPrintError& orig);
		virtual ~FPrintDiscoverPrintError();
};


#endif /* FPRINTERROR_H */

