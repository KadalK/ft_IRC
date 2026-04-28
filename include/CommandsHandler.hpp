#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "commands/Join.hpp"
#include "commands/Nick.hpp"
#include "commands/Pass.hpp"
#include "commands/User.hpp"
#include "Commands.hpp"
#include "ClientHandler.hpp"
#include "ChannelHandler.hpp"

class Commands;
class ClientHandler;
class ChannelHandler;
class Client;
class Join;
class Nick;
class Pass;
class User;

class CommandsHandler {

private:

  //Add all commands
  std::map<std::string, Commands*> _commands;
  // std::vector<std::string> tokens;
  ClientHandler &_clientHandler;
  ChannelHandler &_channelHandler;

  Join  *_join;
  Pass *_pass;
  // PrivMsg *_pmsg;
  Nick *_nick;
  User *_user;

  CommandsHandler(const CommandsHandler &src);
  CommandsHandler &operator=(const CommandsHandler &rhs);

  Commands *findCommand(std::string inputCommand);
public:
  // CommandsHandler();
  CommandsHandler(ClientHandler &clientHandler, ChannelHandler &channelHandler, std::string passServ);
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
