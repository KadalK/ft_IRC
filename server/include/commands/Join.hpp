#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Join : public Commands
{
private:
  Join &operator=(const Join &other);
  Join(const Join &copy);

public:
  Join();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Join();
};
