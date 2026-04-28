#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class Commands;
class ClientHandler;
class ChannelHandler;
class Client;
class Join;

class CommandsHandler {

private:
  PrivMsg *_pmsg;
  PassWord *_pass;
  //Add all commands
  std::map<std::string, Commands*> _commands;
  // std::vector<std::string> tokens;
  ClientHandler &_clientHandler;
  ChannelHandler &_channelHandler;
  Join *_join;

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
