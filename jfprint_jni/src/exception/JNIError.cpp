
/*
 * File:   JNIError.cpp
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 11:08
 */

#include "exception/JNIError.h"

JNIError::JNIError(const char* msg, const char* location_info, const char* function_info)
: BaseException(msg, location_info, function_info)
{
}

JNIError::JNIError(const JNIError& orig)
: BaseException(orig)
{
}

JNIError::~JNIError()
{
}


JNIGetIdError::JNIGetIdError(const char* msg, const char* location_info, const char* function_info)
: JNIError(msg, location_info, function_info)
{
}

JNIGetIdError::JNIGetIdError(const JNIGetIdError& orig)
: JNIError(orig)
{
}

JNIGetIdError::~JNIGetIdError()
{
}


JNISetFieldValueError::JNISetFieldValueError(const char* msg, const char* location_info, const char* function_info)
: JNIError(msg, location_info, function_info)
{
}

JNISetFieldValueError::JNISetFieldValueError(const JNISetFieldValueError& orig)
: JNIError(orig)
{
}

JNISetFieldValueError::~JNISetFieldValueError()
{
}


JNIGetFieldValueError::JNIGetFieldValueError(const char* msg, const char* location_info, const char* function_info)
: JNIError(msg, location_info, function_info)
{
}

JNIGetFieldValueError::JNIGetFieldValueError(const JNIGetFieldValueError& orig)
: JNIError(orig)
{
}

JNIGetFieldValueError::~JNIGetFieldValueError()
{
}


JNICallMethodError::JNICallMethodError(const char* msg, const char* location_info, const char* function_info)
: JNIError(msg, location_info, function_info)
{
}

JNICallMethodError::JNICallMethodError(const JNICallMethodError& orig)
: JNIError(orig)
{
}

JNICallMethodError::~JNICallMethodError()
{
}
