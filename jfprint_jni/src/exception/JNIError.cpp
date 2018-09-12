
/*
 * File:   JNIError.cpp
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 11:08
 */

#include "exception/JNIError.h"
#include <string>
#include <sstream>


static std::string build_msg(const char* handling, const char* resource)
{
    std::ostringstream ss;
    ss << handling << " [" << resource << "]";
    return ss.str();
}


JNIError::JNIError(const char* msg, const char* location_info, const char* function_info)
: BaseException(msg, location_info, function_info)
{
}

JNIError::JNIError(const char* on_handling, const char* resource, const char* location_info, const char* function_info)
: BaseException(build_msg(on_handling, resource).c_str(), location_info, function_info)
{
}

JNIError::JNIError(const JNIError& orig)
: BaseException(orig)
{
}

JNIError::~JNIError()
{
}



JNIGetObjectClassError::JNIGetObjectClassError(const char* msg,
                                               const char* location_info,
                                               const char* function_info)
: JNIError("Can not retrieve object class", msg, location_info, function_info)
{
}

JNIGetObjectClassError::JNIGetObjectClassError(const char* location_info, const char* function_info)
: JNIError("Can not retrieve object class", location_info, function_info)
{
}

JNIGetObjectClassError::JNIGetObjectClassError(const JNIGetObjectClassError& orig)
: JNIError(orig)
{
}

JNIGetObjectClassError::~JNIGetObjectClassError()
{
}


JNIFindClassError::JNIFindClassError(const char* msg, const char* location_info, const char* function_info)
: JNIError("Can not find class", msg, location_info, function_info)
{
}

JNIFindClassError::JNIFindClassError(const char* location_info, const char* function_info)
: JNIError("Can not find class", location_info, function_info)
{
}

JNIFindClassError::JNIFindClassError(const JNIFindClassError& orig)
: JNIError(orig)
{
}

JNIFindClassError::~JNIFindClassError()
{
}


JNIGetIdError::JNIGetIdError(const char* msg, const char* location_info, const char* function_info)
: JNIError("Can not retrieve id", msg, location_info, function_info)
{
}

JNIGetIdError::JNIGetIdError(const char* location_info, const char* function_info)
: JNIError("Can not retrieve id", location_info, function_info)
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
: JNIError("Can not set field value", msg, location_info, function_info)
{
}

JNISetFieldValueError::JNISetFieldValueError(const char* location_info, const char* function_info)
: JNIError("Can not set field value", location_info, function_info)
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
: JNIError("Can not get field value", msg, location_info, function_info)
{
}

JNIGetFieldValueError::JNIGetFieldValueError(const char* location_info, const char* function_info)
: JNIError("Can not get field value", location_info, function_info)
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
: JNIError("Can not call method", msg, location_info, function_info)
{
}

JNICallMethodError::JNICallMethodError(const char* location_info, const char* function_info)
: JNIError("Can not call method", location_info, function_info)
{
}

JNICallMethodError::JNICallMethodError(const JNICallMethodError& orig)
: JNIError(orig)
{
}

JNICallMethodError::~JNICallMethodError()
{
}


JNINewObjectError::JNINewObjectError(const char* msg, const char* location_info, const char* function_info)
: JNIError("Can not instantiate new object", msg, location_info, function_info)
{
}

JNINewObjectError::JNINewObjectError(const char* location_info, const char* function_info)
: JNIError("Can not instantiate new object", location_info, function_info)
{
}

JNINewObjectError::JNINewObjectError(const JNINewObjectError& orig)
: JNIError(orig)
{
}

JNINewObjectError::~JNINewObjectError()
{
}
