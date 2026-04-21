#pragma once

#include "iostream"
#include "Server.hpp"

class Commands {
private:
  Commands();
  Commands(Commands const &src);
protected:
  Server& _server;
public:
  Commands(Server& server);
  virtual ~Commands();

  Commands &operator=(Commands const &rhs);

  virtual void parsingMessage(std::string) = 0;
  virtual void execute() = 0;
  virtual void errorMessage(size_t errorValue) = 0;

  // JE SAIS PAS ENCORE CA MANQUE DE TRUCS
};
