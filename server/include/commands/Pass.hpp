#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Pass : public Commands
{
private:
  Pass &operator=(const Pass &other);
  Pass(const Pass &copy);
  Pass();
  std::string _passServ;

public:
  Pass(std::string passServ);

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Pass();
};
