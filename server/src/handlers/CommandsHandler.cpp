#include "CommandsHandler.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "Replies.hpp"
#include "commands/Invite.hpp"
#include "commands/Join.hpp"
#include "commands/Kick.hpp"
#include "commands/List.hpp"
#include "commands/Mode.hpp"
#include "commands/Names.hpp"
#include "commands/Nick.hpp"
#include "commands/Part.hpp"
#include "commands/Pass.hpp"
#include "commands/PrivMsg.hpp"
#include "commands/Topic.hpp"
#include "commands/User.hpp"
#include <iostream>

CommandsHandler::CommandsHandler(ClientHandler &clientHandler,
                                 ChannelHandler &channelHandler,
                                 std::string passServ)
    : _clientHandler(clientHandler), _channelHandler(channelHandler),
      _join(new Join), _pass(new Pass(passServ)), _nick(new Nick),
      _user(new User), _pvmsg(new PrivMsg), _mode(new Mode), _topic(new Topic),
      _invite(new Invite), _kick(new Kick), _names(new Names), _list(new List),
      _part(new Part)
{
  this->_commands["JOIN"] = _join;
  this->_commands["PASS"] = _pass;
  this->_commands["NICK"] = _nick;
  this->_commands["USER"] = _user;
  this->_commands["PRIVMSG"] = _pvmsg;
  this->_commands["MODE"] = _mode;
  this->_commands["TOPIC"] = _topic;
  this->_commands["INVITE"] = _invite;
  this->_commands["KICK"] = _kick;
  this->_commands["NAMES"] = _names;
  this->_commands["LIST"] = _list;
  this->_commands["PART"] = _part;
}

CommandsHandler::~CommandsHandler()
{
  delete _pass;
  delete _join;
  delete _nick;
  delete _user;
  delete _pvmsg;
  delete _mode;
  delete _topic;
  delete _invite;
  delete _kick;
  delete _names;
  delete _list;
  delete _part;
}

static std::vector<std::string> tokenizeCommand(std::string rawCommand)
{
  size_t start = 0;
  std::vector<std::string> tokens;
  size_t i = 0;

  while (i < rawCommand.size())
  {
    if (rawCommand[i] == ':')
    {
      tokens.push_back(rawCommand.substr(start + 1));
      return (tokens);
    }
    if (rawCommand[i] == ' ')
    {
      if (!rawCommand.substr(start, i - start).empty())
        tokens.push_back(rawCommand.substr(start, i - start));
      while (rawCommand[i] == ' ')
        i++;
      start = i;
    }
    else
      i++;
  }
  if (!rawCommand.substr(start).empty())
    tokens.push_back(rawCommand.substr(start));
  return (tokens);
}

Commands *CommandsHandler::findCommand(std::string inputCommand)
{
  std::map<std::string, Commands *>::iterator i;

  i = this->_commands.find(inputCommand);
  if (i == this->_commands.end())
    return NULL;
  return i->second;
}

bool isRegisterCmd(const std::string &cmdStr)
{
  const char *cmds[] = {"PASS", "NICK", "USER"};
  for (size_t i = 0; i < 3; i++)
  {
    if (cmdStr == cmds[i])
      return (true);
  }
  return (false);
}

static std::string extractNickName(std::string str)
{
  size_t pos = str.find('!');
  if (pos != std::string::npos)
    return (str.substr(0, pos));
  return (str);
}

// envoyer -1 sis ca correspond pas au meme nickname
//  parametre -> client, rawMessage
static int processPrefix(Client &client, std::string rawMessage)
{
  if (rawMessage[0] != ':')
    return (0);
  size_t pos = rawMessage.find(' ');
  if (pos == std::string::npos)
    return (-1);
  std::string prefix = extractNickName(rawMessage.substr(1, pos - 1));
  std::cout << "prefix  [" << prefix << "]" << std::endl;
  if (client.getNickname() != prefix)
    return (-1);
  return (pos + 1);
}

void CommandsHandler::processCommand(Client &client,
                                     ClientHandler &clientHandler,
                                     ChannelHandler &channelHandler,
                                     std::string rawMessage)
{
  std::vector<std::string> tokens;
  std::string cmdStr;
  Commands *cmd;
  size_t pos;
  int start;
  if (rawMessage.size() > 512)
    rawMessage = rawMessage.substr(0, 512);
  start = processPrefix(client, rawMessage);
  if (start < 0)
    return (client.appendBufferOut("Warning\nBad prefix\r\n"));
  rawMessage = rawMessage.substr(start);
  pos = rawMessage.find(' ');
  cmd = findCommand(rawMessage.substr(0, pos));
  if (cmd == NULL)
  {
    client.appendBufferOut(Replies::ERR_UNKNOWNCOMMAND(
        client.getNickname(), rawMessage.substr(start, pos)));
    return;
  }
  cmdStr = rawMessage.substr(start, pos);
  if (isRegisterCmd(cmdStr) == false && client.isRegistered() == false)
    return; // Client pas registered et commande necessite registered
  if (pos != std::string::npos)
    tokens = tokenizeCommand(rawMessage.substr(pos));
  for (std::vector<std::string>::iterator it = tokens.begin();
       it != tokens.end(); it++)                 // debug test
    std::cout << "[" << *it << "]" << std::endl; // debug test
  cmd->execute(client, clientHandler, channelHandler, tokens);
}
