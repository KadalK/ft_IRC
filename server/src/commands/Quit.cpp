#include "commands/Quit.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"

Quit::Quit() {}

void Quit::execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{

  std::string msg = "";

  if (!arg.empty())
    msg = arg[0];

  std::map<int, Client *> clients = clH.getRegistery();
  std::map<std::string, Channel *> listChan = chH.getChannelList();

  for (std::map<int, Client *>::iterator itAC = clients.begin();
       itAC != clients.end(); itAC++)
  {
    for (std::map<std::string, Channel *>::iterator itACh = listChan.begin();
         itACh != listChan.end(); ++itACh)
    {
      if (itACh->second->isClientInChannel(sender) == true)
      {
        if (itACh->second->isClientInChannel(*itAC->second) == true)
        {
          itAC->second->appendBufferOut(sender.getFullName() + " QUIT :" + msg +
                                        "\r\n");
          break;
        }
      }
    }
  }
  sender.setToDisconnect(true);
}

Quit::~Quit() {}
