#pragma once

#include "iostream"

class Commands
{
private:
public:
  Commands();
  Commands(Commands const &src);
  virtual ~Commands();

  Commands &operator=(Commands const &rhs);

  // virtual size_t parsingMessage(std::string);
  virtual size_t execute(void);
  // virtual void errorMessage(size_t errorValue);

protected:
  // JE SAIS PAS ENCORE CA MANQUE DE TRUCS
};
