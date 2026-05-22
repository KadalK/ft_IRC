#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Away : public Commands
{
private:
  Away &operator=(const Away &other);
  Away(const Away &copy);

public:
  Away();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~Away();
};
