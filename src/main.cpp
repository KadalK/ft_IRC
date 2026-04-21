// #include "Server.hpp"
// #include "Client.hpp"
// #include "Channel.hpp"
// #include <map>
// #include <algorithm>
// #include "Commands.hpp"
// #include "PrivMsg.hpp"
//
// int main()
// {
//     //ARGC et ARGV RECUPERER PORT ET PASSWORD
//
//     int port = 6667;
//     std::string password = "chef";
//     Server myServer(port, password);
//     try
//     {
//         myServer.init();
//         myServer.run();
//     }
//     catch (std::exception &e)
//     {
//         std::cout << e.what() << std::endl;
//     }
//     return 0;
// }

/* 
 * AJOUTER TOUTES LES COMMANDES AU STDMAP
 * FAIRE UN PREPARSING QUI TOKENISE POUR ENVOYER AUX COMMANDES
 * STOCKER DANS UN TABLEAU DE STRING
 * ENVOYER CE TABLEAU EN FONCTION DE LA COMMANDE
*/
// void parser(std::string rawMessage)
// {
//
//   PrivMsg p;
//   Join j;
//   Kick k;
//
//   std::map<std::string, *Commands> commands = {{"PRIVMSG", p->execute()}, {"JOIN", j->execute()}}; //add toutes les commandes
//
//   size_t pos;
//   std::map<std::string, *Commands>::iterator i;
//
//   pos = rawMessage.find(' ');
//   if (pos == std::string::npos)
//     return(-1); // throw exception
//   if (rawMessage[pos] == ' ' && rawMessage[pos + 1] == ' ')
//     return (-2);
//   i = commands.find(rawMessage.substr(0, pos));
//   if (i == commands.end())
//     return (-3);
//   std::cout << "Found : " << commands[i] << std::endl;
//   return 0;
// }

// void parser(std::string rawMessage)
// {
//
//   PrivMsg p;
//   Join j;
//   Kick k;
//
//   std::map<std::string, *Commands> commands = {{"PRIVMSG", p->execute()}, {"JOIN", j->execute()}}; //add toutes les commandes
//
//   size_t pos;
//   std::map<std::string, *Commands>::iterator i;
//
//   pos = rawMessage.find(' ');
//   if (pos == std::string::npos)
//     return(-1); // throw exception
//   if (rawMessage[pos] == ' ' && rawMessage[pos + 1] == ' ')
//     return (-2);
//   i = commands.find(rawMessage.substr(0, pos));
//   if (i == commands.end())
//     return (-3);
//   ft_tokenizer(rawMessage.substr(pos + 1));
//   // std::cout << "Found : " << commands[i] << std::endl;
//   return 0;
// }


#include <iostream>
#include <algorithm>
#include <vector>

// std::vector<std::string> extract_tokens(std::string str)
// {
//   std::vector<std::string> v;
//   size_t start = 0;
//   size_t pos;
//   while ((pos = str.find(",", start)) != std::string::npos)
//   {
//     if (!str.substr(start, pos - start).empty())
//       v.push_back(str.substr(start, pos - start));
//     start = pos + 1;
//   }
//   if (!str.substr(start).empty())
//     v.push_back(str.substr(start));
//   return (v);
// }

std::vector<std::string> ft_tokenizer(std::string rawCommand)
{
  int space_count;
  int start = 0;
  std::vector<std::string> tokens;
  size_t i;

  // if (*rawCommand.begin() == ' ' || *rawCommand.size() == ' ')
  //   return (tokens);
  //
  for (i = 0; i < rawCommand.size(); i++)
  {
    if (rawCommand[i] == ' ')
    {
       if (rawCommand[i + 1] == ' ')
        return (tokens);
      else
      {
        tokens.push_back(rawCommand.substr(start, i - start));
        start = i + 1;
      }
    }
  }
  tokens.push_back(rawCommand.substr(start, i - start));
  return (tokens);
}

int main()
{
  std::string str = "/privmsg salut,ca,va coucou bon";
  std::vector<std::string> v;
  v = ft_tokenizer(str);
  for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    std::cout << "[" << *it << "]" << std::endl;
  return 0;
}
