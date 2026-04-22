#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
// #include "Commands.hpp"
// #include "PrivMsg.hpp"

std::vector<std::string> ft_tokenizer(std::string rawCommand)
{
  int space_count;
  int start = 0;
  std::vector<std::string> tokens;
  size_t i;

  for (i = 0; i < rawCommand.size(); i++)
  {
    if (rawCommand[i] == ' ')
    {
      if (!rawCommand.substr(start, i - start).empty())
        tokens.push_back(rawCommand.substr(start, i - start));
      while (rawCommand[i] == ' ')
        i++;
      start = i;
    }
  }
  if (!rawCommand.substr(start, i - start).empty())
    tokens.push_back(rawCommand.substr(start, i - start));
  return (tokens);
}

void parser(std::string rawMessage)
{
  PrivMsg p;
  std::vector<std::string> v;
  std::map<std::string, *Commands> commands = {{"PRIVMSG", p}}; //add toutes les commandes

  size_t pos;
  std::map<std::string, *Commands>::iterator i;

  pos = rawMessage.find(' ');
  if (pos == std::string::npos)
    return; // Manque arguments - throw exception
  std::cout << "Commande : " << rawMessage.substr(0, pos) << std::endl;
  i = commands.find(rawMessage.substr(0, pos));
  if (i == commands.end())
    return; //Commande existe pas - Throw exception
  while (rawMessage[pos] == ' ')
    pos++;
  v = ft_tokenizer(rawMessage.substr(pos));
  i->second->execute(v);
  return;
}

// void parser(std::string rawMessage)
// {
//   std::vector<std::string> v;
//   std::map<std::string, std::string> commands = {{"PRIVMSG", "je suis un message prive"}, {"JOIN", "je suis un join"}}; //add toutes les commandes
//
//   size_t pos;
//   std::map<std::string, std::string>::iterator i;
//
//   pos = rawMessage.find(' ');
//   if (pos == std::string::npos)
//     return; // Manque arguments - throw exception
//   std::cout << "Commande : " << rawMessage.substr(0, pos) << std::endl;
//   i = commands.find(rawMessage.substr(0, pos));
//   if (i == commands.end())
//     return; //Commande existe pas - Throw exception
//   while (rawMessage[pos] == ' ')
//     pos++;
//   v = ft_tokenizer(rawMessage.substr(pos));
//   for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
//     std::cout << "[" << *it << "]" << std::endl;
//   std::cout << i->second << std::endl;
//   return;
// }
