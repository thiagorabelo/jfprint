
/*
 * File:   JNIError.h
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 11:08
 */

#ifndef JNIERROR_H
#define JNIERROR_H

#include <exception>
#include "exception/BaseException.h"

class JNIError : public BaseException
{
	public:
		JNIError(const char* msg, const char* location_info, const char* function_info);
		JNIError(const char* on_handling, const char* resource, const char* location_info, const char* function_info);
		JNIError(const JNIError& orig);
		virtual ~JNIError();
};



class JNIGetObjectClassError : public JNIError
{
	public:
		JNIGetObjectClassError(const char* msg, const char* location_info, const char* function_info);
		JNIGetObjectClassError(const char* location_info, const char* function_info);
		JNIGetObjectClassError(const JNIGetObjectClassError& orig);
		virtual ~JNIGetObjectClassError();
};


class JNIFindClassError : public JNIError
{
	public:
		JNIFindClassError(const char* msg, const char* location_info, const char* function_info);
		JNIFindClassError(const char* location_info, const char* function_info);
		JNIFindClassError(const JNIFindClassError& orig);
		virtual ~JNIFindClassError();
};


class JNIGetIdError : public JNIError
{
	public:
		JNIGetIdError(const char* msg, const char* location_info, const char* function_info);
		JNIGetIdError(const char* location_info, const char* function_info);
		JNIGetIdError(const JNIGetIdError& orig);
		virtual ~JNIGetIdError();
};


class JNISetFieldValueError : public JNIError
{
	public:
		JNISetFieldValueError(const char* msg, const char* location_info, const char* function_info);
		JNISetFieldValueError(const char* location_info, const char* function_info);
		JNISetFieldValueError(const JNISetFieldValueError& orig);
		virtual ~JNISetFieldValueError();
};


class JNIGetFieldValueError : public JNIError
{
	public:
		JNIGetFieldValueError(const char* msg, const char* location_info, const char* function_info);
		JNIGetFieldValueError(const char* location_info, const char* function_info);
		JNIGetFieldValueError(const JNIGetFieldValueError& orig);
		virtual ~JNIGetFieldValueError();
};


class JNICallMethodError : public JNIError
{
	public:
		JNICallMethodError(const char* msg, const char* location_info, const char* function_info);
		JNICallMethodError(const char* location_info, const char* function_info);
		JNICallMethodError(const JNICallMethodError& orig);
		virtual ~JNICallMethodError();
};


class JNINewObjectError : public JNIError
{
	public:
		JNINewObjectError(const char* msg, const char* location_info, const char* function_info);
		JNINewObjectError(const char* location_info, const char* function_info);
		JNINewObjectError(const JNINewObjectError& orig);
		virtual ~JNINewObjectError();
};


#endif /* JNIERROR_H */

