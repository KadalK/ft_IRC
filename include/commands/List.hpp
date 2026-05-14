
#pragma once

#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"
#include "CommandsHandler.hpp"

class List : public Commands
{
private:
  List &operator=(const List &other);
  List(const List &copy);

public:
  List();

  void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);

  ~List();
};
