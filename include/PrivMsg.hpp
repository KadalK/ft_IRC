#pragma once

#include "Commands.hpp"
#include <vector>

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
  size_t execute(std::vector<std::string> v);
  void errorMessage(size_t errorValue);
};
