#pragma once

#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"
#include "CommandsHandler.hpp"

class Names : public Commands
{
private:
  Names &operator=(const Names &other);
  Names(const Names &copy);

public:
  Names();

  void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Names();
};
