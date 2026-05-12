#include "CommandsHandler.hpp"
<<<<<<< Updated upstream
#include "commands/Invite.hpp"
#include <iostream>

CommandsHandler::CommandsHandler(ClientHandler &clientHandler,
                                 ChannelHandler &channelHandler,
                                 std::string passServ)
    : _clientHandler(clientHandler), _channelHandler(channelHandler),
      _join(new Join), _pass(new Pass(passServ)), _nick(new Nick),
      _user(new User), _pvmsg(new PrivMsg), _mode(new Mode), _topic(new Topic),
      _invite(new Invite), _kick(new Kick)
=======
#include <iostream>

CommandsHandler::CommandsHandler(ClientHandler &clientHandler,
                                 ChannelHandler &channelHandler, std::string passServ)
    : _clientHandler(clientHandler), _channelHandler(channelHandler),
      _join(new Join), _pass(new Pass(passServ)), _nick(new Nick), _user(new User)
>>>>>>> Stashed changes
{
  this->_commands["JOIN"] = _join;
  this->_commands["PASS"] = _pass;
  this->_commands["NICK"] = _nick;
  this->_commands["USER"] = _user;
<<<<<<< Updated upstream
  this->_commands["PRIVMSG"] = _pvmsg;
  this->_commands["MODE"] = _mode;
  this->_commands["TOPIC"] = _topic;
  this->_commands["INVITE"] = _invite;
  this->_commands["KICK"] = _kick;
=======
>>>>>>> Stashed changes
}

CommandsHandler::~CommandsHandler()
{
<<<<<<< Updated upstream
=======
  // delete _pmsg;
>>>>>>> Stashed changes
  delete _pass;
  delete _join;
  delete _nick;
  delete _user;
<<<<<<< Updated upstream
  delete _pvmsg;
  delete _mode;
  delete _topic;
  delete _invite;
  delete _kick;
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
      tokens.push_back(rawCommand.substr(start + 1));
=======
      tokens.push_back(rawCommand.substr(start));
>>>>>>> Stashed changes
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
    return NULL; // Commande existe pas - Throw exception
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
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
  if (rawMessage.size() > 512)
    rawMessage = rawMessage.substr(0, 512);
  pos = rawMessage.find(' ');
=======

  pos = rawMessage.find(' ');
  if (pos == std::string::npos)
    return; // Manque arguments - throw exception
>>>>>>> Stashed changes
  cmd = findCommand(rawMessage.substr(0, pos));
  if (cmd == NULL)
    return; // Commande existe pas - throw exception
  cmdStr = rawMessage.substr(0, pos);
  if (isRegisterCmd(cmdStr) == false && client.isRegistered() == false)
<<<<<<< Updated upstream
    return; // Client pas registered et commande necessite registered
  if (pos != std::string::npos)
    tokens = tokenizeCommand(rawMessage.substr(pos));
=======
    return ; //Client pas registered et commande necessite registered
  tokens = tokenizeCommand(rawMessage.substr(pos));
>>>>>>> Stashed changes
  for (std::vector<std::string>::iterator it = tokens.begin();
       it != tokens.end(); it++)                 // debug test
    std::cout << "[" << *it << "]" << std::endl; // debug test
  cmd->execute(client, clientHandler, channelHandler, tokens);
}
