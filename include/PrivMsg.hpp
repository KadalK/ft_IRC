#pragma once

#include "Commands.hpp"

  struct param
  {
    std::string textMsg;
  };

class PrivMsg : public Commands
{
private:
public:
  PrivMsg();
  PrivMsg(PrivMsg const &src);
  ~PrivMsg();

  PrivMsg &operator=(PrivMsg const &rhs);

  void parsingMessage(param &p, std::string rawText);
  void execute(void);
  void errorMessage(size_t errorValue);
};
