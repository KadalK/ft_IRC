#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Nick : public Commands
{
private:
  Nick &operator=(const Nick &other);
  Nick(const Nick &copy);

public:
  Nick();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Nick();
};
