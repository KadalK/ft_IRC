#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Topic : public Commands
{
private:
  Topic(Topic const &src);
  Topic &operator=(Topic const &rhs);

public:
  Topic();
  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);
  ~Topic();
};
