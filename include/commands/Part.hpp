#pragma once

#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"
#include "CommandsHandler.hpp"

class Part : public Commands
{
private:
  Part &operator=(const Part &other);
  Part(const Part &copy);

public:
  Part();

  void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Part();
};
