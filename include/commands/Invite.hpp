#pragma once

#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"
#include "CommandsHandler.hpp"

class Invite : public Commands
{
private:
  Invite &operator=(const Invite &other);
  Invite(const Invite &copy);

public:
  Invite();

  void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Invite();
};
