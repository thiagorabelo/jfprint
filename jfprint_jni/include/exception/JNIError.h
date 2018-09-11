
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
		JNIError(const JNIError& orig);
		virtual ~JNIError();
};


class JNIGetIdError : public JNIError
{
	public:
		JNIGetIdError(const char* msg, const char* location_info, const char* function_info);
		JNIGetIdError(const JNIGetIdError& orig);
		virtual ~JNIGetIdError();
};


class JNISetFieldValueError : public JNIError
{
	public:
		JNISetFieldValueError(const char* msg, const char* location_info, const char* function_info);
		JNISetFieldValueError(const JNISetFieldValueError& orig);
		virtual ~JNISetFieldValueError();
};


class JNIGetFieldValueError : public JNIError
{
	public:
		JNIGetFieldValueError(const char* msg, const char* location_info, const char* function_info);
		JNIGetFieldValueError(const JNIGetFieldValueError& orig);
		virtual ~JNIGetFieldValueError();
};


class JNICallMethodError : public JNIError
{
	public:
		JNICallMethodError(const char* msg, const char* location_info, const char* function_info);
		JNICallMethodError(const JNICallMethodError& orig);
		virtual ~JNICallMethodError();
};


#endif /* JNIERROR_H */

