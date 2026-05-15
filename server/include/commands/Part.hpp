#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Part : public Commands
{
private:
  Part &operator=(const Part &other);
  Part(const Part &copy);

public:
  Part();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Part();
};
