#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Invite : public Commands
{
private:
  Invite &operator=(const Invite &other);
  Invite(const Invite &copy);

public:
  Invite();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Invite();
};
