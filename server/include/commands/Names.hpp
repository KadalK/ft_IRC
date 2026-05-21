#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Names : public Commands
{
private:
  Names &operator=(const Names &other);
  Names(const Names &copy);

public:
  Names();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Names();
};
