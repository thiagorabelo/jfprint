
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


JNIError::JNIError(const char* cause, const char* location_info, const char* function_info)
: BaseException(cause, location_info, function_info)
{
}

JNIError::JNIError(const JNIError& orig)
: BaseException(orig)
{
}

JNIError::~JNIError()
{
}


JNIPointerError::JNIPointerError(JNIError& cause)
: cause(cause)
{
}

JNIPointerError::~JNIPointerError()
{
}

const char* JNIPointerError::what() const
{
    return cause.what();
}

const char* JNIPointerError::get_msg() const
{
    return cause.get_msg();
}

const char* JNIPointerError::get_location_info() const
{
    return cause.get_function_info();
}

const char* JNIPointerError::get_function_info() const
{
    cause.get_function_info();
}
