
/*
 * File:   BaseException.cpp
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 11:20
 */

#include "exception/BaseException.h"
#include <sstream>
#include <string>
#include <cstring>

/* Helper functions */

static void build_what_msg(char **dest, std::ostringstream& ss)
{
    std::string src = ss.str();
    *dest = new char[src.length() + 1];
    std::strcpy(*dest, src.c_str());
}

static void build_what_msg(char **dest, const char* msg,
                                 const char* location_info,
                                 const char* function_info)
{
    std::ostringstream ss;
    ss << msg << " - " << location_info << ", " << function_info;

    build_what_msg(dest, ss);
}

/* End helper functions */


BaseException::BaseException(const char* msg,
                             const char* location_info,
                             const char* function_info)
: std::exception(), msg(msg), location_info(location_info), function_info(function_info)
{
    build_what_msg(const_cast<char**>(&_what), msg, location_info, function_info);
}


BaseException::BaseException(const BaseException& orig)
: std::exception(), msg(orig.msg), location_info(orig.location_info), function_info(orig.function_info)
{
    build_what_msg(const_cast<char**>(&_what), msg, location_info, function_info);
}


BaseException::~BaseException()
{
    delete [] _what;
}


const char* BaseException::what() const noexcept
{
    return _what;
}
