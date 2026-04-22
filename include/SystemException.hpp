#ifndef SYSTEMEXCEPTION_HPP
#define SYSTEMEXCEPTION_HPP

#include <exception>
#include <string>
#include <cerrno>
#include <cstring>

class SystemException : public std::exception
{
private:
	std::string _message;

public:
	SystemException(const std::string &context)
	{
		this->_message = context + " : " + std::strerror(errno);
	}

	virtual ~SystemException() throw() {}

	virtual const char *what() const throw()
	{
		return this->_message.c_str();
	}
};

#endif
