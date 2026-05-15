#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class User : public Commands
{
private:
  User &operator=(const User &other);
  User(const User &copy);

public:
  User();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~User();
};
