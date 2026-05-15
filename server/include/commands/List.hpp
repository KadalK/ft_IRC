#pragma once

#include "Commands.hpp"
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class List : public Commands
{
private:
  List &operator=(const List &other);
  List(const List &copy);

public:
  List();

  void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~List();
};
