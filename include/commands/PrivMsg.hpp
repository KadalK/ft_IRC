#pragma once

#include "Commands.hpp"
#include <vector>
#include <iostream>


class Client;
class ClientHandler;
class ChannelHandler;

class PrivMsg : public Commands
{
private:
  PrivMsg(PrivMsg const &src);
  PrivMsg &operator=(PrivMsg const &rhs);
public:
  PrivMsg();

  void parsingMessage(std::string rawText);
  void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg);
  void errorMessage(size_t errorValue);
  ~PrivMsg();
};
