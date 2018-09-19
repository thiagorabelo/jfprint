
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
		JNIError(const char* cause, const char* location_info, const char* function_info) noexcept;
		JNIError(const JNIError& orig) noexcept;
		virtual ~JNIError() noexcept;
};


class JNIGenericError : public std::exception
{
	public:
		JNIGenericError(JNIError& cause) noexcept;
		~JNIGenericError() noexcept;

		virtual const char* what() const noexcept;
		virtual const char* get_msg() const noexcept;
		virtual const char* get_location_info() const noexcept;
		virtual const char* get_function_info() const noexcept;

	private:
		JNIError& cause;
};


class JNIGetPointerError : public JNIGenericError
{
	public:
		JNIGetPointerError(JNIError& cause) noexcept;
		~JNIGetPointerError() noexcept;
};


class JNISetPointerError : public JNIGenericError
{
	public:
		JNISetPointerError(JNIError& cause) noexcept;
		~JNISetPointerError() noexcept;
};


class JNINewInstanceError : public JNIGenericError
{
	public:
		JNINewInstanceError(JNIError& cause) noexcept;
		~JNINewInstanceError() noexcept;
};


class JNISetWrapperObjError : public JNIGenericError
{
	public:
		JNISetWrapperObjError(JNIError& cause) noexcept;
		~JNISetWrapperObjError() noexcept;
};


class JNICNULLTerminatedError : public JNIGenericError
{
	public:
		JNICNULLTerminatedError(JNIError& cause) noexcept;
		~JNICNULLTerminatedError() noexcept;
};


class JNINewByteArrayError : public JNIGenericError
{
	public:
		JNINewByteArrayError(JNIError& cause) noexcept;
		~JNINewByteArrayError() noexcept;
};


class JNIByteArrayError : public JNIGenericError
{
	public:
		JNIByteArrayError(JNIError& cause) noexcept;
		~JNIByteArrayError() noexcept;
};


#endif /* JNIERROR_H */

