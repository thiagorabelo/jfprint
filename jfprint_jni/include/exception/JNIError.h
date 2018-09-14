
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


class JNIPointerError : std::exception
{
	public:
		JNIPointerError(JNIError& cause) noexcept;
		~JNIPointerError() noexcept;

		virtual const char* what() const noexcept;
		virtual const char* get_msg() const noexcept;
		virtual const char* get_location_info() const noexcept;
		virtual const char* get_function_info() const noexcept;

	private:
		JNIError& cause;
};


#endif /* JNIERROR_H */

