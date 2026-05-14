#pragma once

#include <cerrno>
#include <cstring>
#include <exception>
#include <string>

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

  virtual const char *what() const throw() { return this->_message.c_str(); }
};
