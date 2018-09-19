
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


JNIError::JNIError(const char* cause, const char* location_info, const char* function_info) noexcept
: BaseException(cause, location_info, function_info)
{
}

JNIError::JNIError(const JNIError& orig) noexcept
: BaseException(orig)
{
}

JNIError::~JNIError() noexcept
{
}


JNIGenericError::JNIGenericError(JNIError& cause) noexcept
: cause(cause)
{
}

JNIGenericError::~JNIGenericError()
{
}

const char* JNIGenericError::what() const noexcept
{
    return cause.what();
}

const char* JNIGenericError::get_msg() const noexcept
{
    return cause.get_msg();
}

const char* JNIGenericError::get_location_info() const noexcept
{
    return cause.get_function_info();
}

const char* JNIGenericError::get_function_info() const noexcept
{
    cause.get_function_info();
}


JNIGetPointerError::JNIGetPointerError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNIGetPointerError::~JNIGetPointerError() noexcept
{
}


JNISetPointerError::JNISetPointerError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNISetPointerError::~JNISetPointerError() noexcept
{
}


JNINewInstanceError::JNINewInstanceError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNINewInstanceError::~JNINewInstanceError() noexcept
{
}


JNISetWrapperObjError::JNISetWrapperObjError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNISetWrapperObjError::~JNISetWrapperObjError() noexcept
{
}


JNICNULLTerminatedError::JNICNULLTerminatedError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNICNULLTerminatedError::~JNICNULLTerminatedError() noexcept
{
}


JNINewByteArrayError::JNINewByteArrayError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNINewByteArrayError::~JNINewByteArrayError() noexcept
{
}


JNIByteArrayError::JNIByteArrayError(JNIError& cause) noexcept
: JNIGenericError(cause)
{
}

JNIByteArrayError::~JNIByteArrayError() noexcept
{
}
