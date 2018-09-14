
/*
 * File:   BaseException.h
 * Author: thiago
 *
 * Created on 11 de Setembro de 2018, 11:20
 */

#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>


class BaseException : public std::exception
{
	public:
		BaseException(const char* msg, const char* location_info, const char* function_info) noexcept;
		BaseException(const BaseException& orig) noexcept;

		virtual ~BaseException() noexcept;
		virtual const char* what() const noexcept;

		virtual const char* get_msg() const noexcept;
		virtual const char* get_location_info() const noexcept;
		virtual const char* get_function_info() const noexcept;

	private:
		const char* msg;
		const char* location_info;
		const char* function_info;
		const char* _what;
};

#endif /* BASEEXCEPTION_H */

