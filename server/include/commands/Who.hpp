#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Who : public Commands
{
private:
  Who &operator=(const Who &other);
  Who(const Who &copy);

public:
  Who();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Who();
};
