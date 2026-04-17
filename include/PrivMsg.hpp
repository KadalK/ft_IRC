#pragma once

#include "Commands.hpp"

struct parameters
{
  //
  std::string textMessage;
};

class PrivMsg : public Commands
{
private:
public:
  PrivMsg();
  PrivMsg(PrivMsg const &src);
  ~PrivMsg();

  PrivMsg &operator=(PrivMsg const &rhs);

  size_t parsingMessage(parameters &p, std::string rawText);
  size_t execute(void);
  void errorMessage(size_t errorValue);
};
