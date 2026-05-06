#pragma once

#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"
#include "CommandsHandler.hpp"

class Kick : public Commands
{
private:
  Kick &operator=(const Kick &other);
  Kick(const Kick &copy);

public:
  Kick();

  void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Kick();
};
