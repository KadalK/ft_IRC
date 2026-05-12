#pragma once

<<<<<<< Updated upstream
#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"
#include "commands/Invite.hpp"
#include "commands/Join.hpp"
#include "commands/Kick.hpp"
#include "commands/Mode.hpp"
#include "commands/Nick.hpp"
#include "commands/Pass.hpp"
#include "commands/PrivMsg.hpp"
#include "commands/Topic.hpp"
#include "commands/User.hpp"
#include <iostream>
#include <map>
=======

#include <map>
#include <iostream>
#include "commands/Join.hpp"
#include "commands/Nick.hpp"
#include "commands/Pass.hpp"
#include "commands/User.hpp"
#include "Commands.hpp"
#include "ClientHandler.hpp"
#include "ChannelHandler.hpp"
>>>>>>> Stashed changes

class Commands;
class ClientHandler;
class ChannelHandler;
class Client;
class Join;
class Nick;
class Pass;
class User;
<<<<<<< Updated upstream
class PrivMsg;
class Mode;
class Topic;
class Invite;
class Kick;
=======
>>>>>>> Stashed changes

class CommandsHandler
{

private:
<<<<<<< Updated upstream
  // Add all commands
  std::map<std::string, Commands *> _commands;
=======

  //Add all commands
  std::map<std::string, Commands*> _commands;
>>>>>>> Stashed changes
  // std::vector<std::string> tokens;
  ClientHandler &_clientHandler;
  ChannelHandler &_channelHandler;

<<<<<<< Updated upstream
  Join *_join;
  Pass *_pass;
  Nick *_nick;
  User *_user;
  PrivMsg *_pvmsg;
  Mode *_mode;
  Topic *_topic;
  Invite *_invite;
  Kick *_kick;
=======
  Join  *_join;
  Pass *_pass;
  // PrivMsg *_pmsg;
  Nick *_nick;
  User *_user;
>>>>>>> Stashed changes

  CommandsHandler(const CommandsHandler &src);
  CommandsHandler &operator=(const CommandsHandler &rhs);

  Commands *findCommand(std::string inputCommand);

public:
  // CommandsHandler();
<<<<<<< Updated upstream
  CommandsHandler(ClientHandler &clientHandler, ChannelHandler &channelHandler,
                  std::string passServ);
=======
  CommandsHandler(ClientHandler &clientHandler, ChannelHandler &channelHandler, std::string passServ);
>>>>>>> Stashed changes
  ~CommandsHandler();

  void processCommand(Client &client, ClientHandler &clientHandler,
                      ChannelHandler &channelHandler, std::string rawMessage);
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
