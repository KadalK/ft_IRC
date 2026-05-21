#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Mode : public Commands
{
private:
  Mode(Mode const &src);
  Mode &operator=(Mode const &rhs);

public:
  Mode();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Mode();
};
