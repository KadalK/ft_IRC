#pragma once

#include "Commands.hpp"
#include <vector>
// #include "Client.hpp"

  // struct param
  // {
  //   std::string textMsg;
  // };

class PrivMsg : public Commands
{
private:
  PrivMsg(PrivMsg const &src);
  PrivMsg &operator=(PrivMsg const &rhs);
public:
  PrivMsg();

  void parsingMessage(std::string rawText);
  void execute(Client*, Server*,  std::vector<std::string>);
  void errorMessage(size_t errorValue);
  ~PrivMsg();
};
