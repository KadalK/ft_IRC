#include "CommandsHandler.hpp"
#include <iostream>

CommandsHandler::CommandsHandler(ClientHandler &clientHandler,
                                 ChannelHandler &channelHandler)
    : _clientHandler(clientHandler), _channelHandler(channelHandler),
      _join(new Join)
{
  this->_commands["JOIN"] = _join;
  // this->_commands["PASS"] = _pass;
  // this->_commands["NICK"] = _nick;
}

CommandsHandler::~CommandsHandler()
{
  // delete _pmsg;
  // delete _pass;
  delete _join;
  // delete _pass;
  // delete _nick;
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
      tokens.push_back(rawCommand.substr(start));
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

void CommandsHandler::processCommand(Client &client,
                                     ClientHandler &clientHandler,
                                     ChannelHandler &channelHandler,
                                     std::string rawMessage)
{
  std::vector<std::string> tokens;
  Commands *cmd;
  size_t pos;

  pos = rawMessage.find(' ');
  if (pos == std::string::npos)
    return; // Manque arguments - throw exception
  cmd = findCommand(rawMessage.substr(0, pos));
  if (cmd == NULL)
    return; // Commande existe pas - throw exception
  tokens = tokenizeCommand(rawMessage.substr(pos));
  for (std::vector<std::string>::iterator it = tokens.begin();
       it != tokens.end(); it++)                 // debug test
    std::cout << "[" << *it << "]" << std::endl; // debug test
  cmd->execute(client, clientHandler, channelHandler, tokens);
}

////debug
// CommandsHandler::CommandsHandler()
//{
//   this->commands = {{"PRIVMSG", "je suis un message prive"}, {"JOIN", "je
//   suis un join"}}; //debug
// }
//
// CommandsHandler::~CommandsHandler()
//{
// }
//
// static std::vector<std::string> tokenizeCommand(std::string rawCommand)
//{
//   size_t start = 0;
//   std::vector<std::string> tokens;
//   size_t i = 0;
//
//   while (i < rawCommand.size())
//   {
//     if (rawCommand[i] == ':')
//     {
//       tokens.push_back(rawCommand.substr(start));
//       return (tokens);
//     }
//     if (rawCommand[i] == ' ')
//     {
//        if (!rawCommand.substr(start, i - start).empty())
//         tokens.push_back(rawCommand.substr(start, i - start));
//       while (rawCommand[i] == ' ')
//         i++;
//       start = i;
//     }
//     else
//       i++;
//   }
//   if (!rawCommand.substr(start).empty())
//     tokens.push_back(rawCommand.substr(start));
//   return (tokens);
// }
////debug
// std::string CommandsHandler::findCommand(std::string inputCommand)
//{
//   std::map<std::string, std::string>::iterator i; //debug test
//
//   i = this->commands.find(inputCommand);
//   if (i == this->commands.end())
//     return NULL; //Commande existe pas - Throw exception
//   return i->second;
// }
//
////debug
// void CommandsHandler::processCommand(std::string rawMessage)
//{
//   std::vector<std::string> tokens;
//   std::string cmd;
//   size_t pos;
//
//   pos = rawMessage.find(' ');
//   if (pos == std::string::npos)
//   {
//     std::cout << "1" << std::endl;
//     return; // Manque arguments - throw exception
//   }
//   cmd = findCommand(rawMessage.substr(0, pos));
//   std::cout << cmd << std::endl;
//   if (cmd.empty())
//   {
//     std::cout << "2" << std::endl;
//     return; // Manque arguments - throw exception
//   }
//   std::cout << "{" << rawMessage.substr(pos) << "}" << std::endl;
//   tokens = tokenizeCommand(rawMessage.substr(pos));
//   for (std::vector<std::string>::iterator it = tokens.begin(); it !=
//   tokens.end(); it++) //debug test
//     std::cout << "[" << *it << "]" << std::endl; //debug test
// }
