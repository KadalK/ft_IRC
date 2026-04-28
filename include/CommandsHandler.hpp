#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "Join.hpp"
#include "Commands.hpp"
#include "Pass.hpp"
#include "Nick.hpp"

class Commands;
class ClientHandler;
class ChannelHandler;
class Client;
class Join;
class Nick;
class Pass;

class CommandsHandler {

private:
  PrivMsg *_pmsg;
  Join  *_join;
  Pass *_pass;
  Nick *_nick;

  //Add all commands
  std::map<std::string, Commands*> _commands;
  // std::vector<std::string> tokens;
  ClientHandler &_clientHandler;
  ChannelHandler &_channelHandler;

  CommandsHandler(const CommandsHandler &src);
  CommandsHandler &operator=(const CommandsHandler &rhs);

  Commands *findCommand(std::string inputCommand);
public:
  // CommandsHandler();
  CommandsHandler(ClientHandler &clientHandler, ChannelHandler &channelHandler);
  ~CommandsHandler();

  void processCommand(Client &client, ClientHandler &clientHandler, ChannelHandler &channelHandler, std::string rawMessage);
};

// class CommandsHandler {
//
// private:
//   std::map<std::string, std::string> commands; //debug test
//   std::vector<std::string> tokens;
//
//   CommandsHandler(const CommandsHandler &src);
//   CommandsHandler &operator=(const CommandsHandler &rhs);
//
//   std::string findCommand(std::string inputCommand);
// public:
//   CommandsHandler();
//   ~CommandsHandler();
//
//   void processCommand(std::string rawMessage);
//
// };
