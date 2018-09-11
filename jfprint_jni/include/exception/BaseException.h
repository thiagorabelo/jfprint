
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
		BaseException(const char* msg, const char* location_info, const char* function_info);
		BaseException(const BaseException& orig);

		virtual ~BaseException();
		virtual const char *what() const noexcept;

	private:
		const char* msg;
		const char* location_info;
		const char* function_info;
		const char *_what;
};

#endif /* BASEEXCEPTION_H */

