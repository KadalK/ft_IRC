#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <map>
#include <algorithm>
#include "Commands.hpp"
#include "PrivMsg.hpp"

int main()
{
    //ARGC et ARGV RECUPERER PORT ET PASSWORD

    int port = 6667;
    std::string password = "chef";
    Server myServer(port, password);
    try
    {
        myServer.init();
        myServer.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

/* 
 * AJOUTER TOUTES LES COMMANDES AU STDMAP
 * FAIRE UN PREPARSING QUI TOKENISE POUR ENVOYER AUX COMMANDES
 * STOCKER DANS UN TABLEAU DE STRING
 * ENVOYER CE TABLEAU EN FONCTION DE LA COMMANDE
*/
void parser(std::string rawMessage)
{

  PrivMsg p;
  Join j;
  Kick k;

  std::map<std::string, *Commands> commands = {{"PRIVMSG", p->execute()}, {"JOIN", j->execute()}}; //add toutes les commandes

  size_t pos;
  std::map<std::string, *Commands>::iterator i;

  pos = rawMessage.find(' ');
  if (pos == std::string::npos)
    return(-1); // throw exception
  if (rawMessage[pos] == ' ' && rawMessage[pos + 1] == ' ')
    return (-2);
  i = commands.find(rawMessage.substr(0, pos));
  if (i == commands.end())
    return (-3);
  std::cout << "Found : " << commands[i] << std::endl;
  return 0;
}

