#pragma once

#include <map>
#include <string>

class Commands;
class ClientHandler;
class ChannelHandler;
class Client;
class Join;
class Nick;
class Pass;
class User;
class PrivMsg;
class Mode;
class Topic;
class Invite;
class Kick;
class Part;
class Names;
class List;
class Who;
class Away;

class CommandsHandler
{

private:
  std::map<std::string, Commands *> _commands;

  ClientHandler &_clientHandler;
  ChannelHandler &_channelHandler;

  Join *_join;
  Pass *_pass;
  Nick *_nick;
  User *_user;
  PrivMsg *_pvmsg;
  Mode *_mode;
  Topic *_topic;
  Invite *_invite;
  Kick *_kick;
  Names *_names;
  List *_list;
  Part *_part;
  Who *_who;
  Away *_away;

  CommandsHandler(const CommandsHandler &src);
  CommandsHandler &operator=(const CommandsHandler &rhs);

  Commands *findCommand(std::string inputCommand);

public:
  CommandsHandler(ClientHandler &clientHandler, ChannelHandler &channelHandler,
                  std::string passServ);
  ~CommandsHandler();

  void processCommand(Client &client, ClientHandler &clientHandler,
                      ChannelHandler &channelHandler, std::string rawMessage);
};
