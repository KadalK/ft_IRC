#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class Commands;
class ClientHandler;
class ChannelHandler;
class Client;

class CommandsHandler {

private:
  PrivMsg *_pmsg;
  Password *_pass;
  //Add all commands
  std::map<std::string, *Commands> _commands;
  // std::vector<std::string> tokens;
  ClientHandler &_clientHandler;
  ChannelHandler &_channelHandler;

  CommandsHandler();
  CommandsHandler(const CommandsHandler &src);
  CommandsHandler &operator=(const CommandsHandler &rhs);

  Commands *findCommand(std::string inputCommand);
public:
  CommandsHandler(ClientHandler *ClientHandler, ChannelHandler *ChannelHandler);
  ~CommandsHandler();

  void processCommand(Client &client, ClientHandler &_ClientHandler, channelHandler &_channelHandler, std::string rawMessage);


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
