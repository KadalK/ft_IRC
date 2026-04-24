#pragma once

#include "iostream"
#include "Server.hpp"
#include "vector"

class Commands {
private:
  Commands(Commands const &src);
  Commands &operator=(Commands const &rhs);
  Commands();
protected:
  Commands(Server& server);

public:
  virtual ~Commands();

  virtual void parsingMessage(std::string) = 0;
  virtual void execute(Client*, std::vector<std::string>) = 0;
  virtual void errorMessage(size_t errorValue) = 0;

  // JE SAIS PAS ENCORE CA MANQUE DE TRUCS
};
