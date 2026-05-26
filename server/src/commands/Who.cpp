#include "commands/Who.hpp"
#include "ChannelHandler.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "Replies.hpp"

Who::Who() {}

void Who::execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
                  const std::vector<std::string> &arg)
{
  Channel *channel;

  std::map<int, Client *> clients = clH.getRegistery();
  std::map<std::string, Channel *> listchan = chH.getChannelList();
  if (arg.empty() || (arg[0] == "*" && arg[0].length() == 1))
  {
    if (listchan.empty())
    {
      for (std::map<int, Client *>::iterator itAC = clients.begin();
           itAC != clients.end(); itAC++)
      {
        std::string FullInfo = itAC->second->getFullInfo("*", false);
        sender.appendBufferOut(Replies::RPL_WHOREPLY(sender.getNickname(), FullInfo));
      }
    }
    else
    {
      for (std::map<int, Client *>::iterator itAC = clients.begin();
           itAC != clients.end(); itAC++)
      {
        for (std::map<std::string, Channel *>::iterator itACh = listchan.begin(); itACh != listchan.end(); ++itACh)
        {
          if (itACh->second->isClientInChannel(sender) == false)
          {
            if (itACh->second->isClientInChannel(*itAC->second) == true)
            {
              bool isOP = itACh->second->isClientOperator(*itAC->second);
              std::string FullInfo = itAC->second->getFullInfo(itACh->second->getName(), isOP);
              sender.appendBufferOut(Replies::RPL_WHOREPLY(sender.getNickname(), FullInfo));
            }
          }
        }
      }
    }
    sender.appendBufferOut(Replies::RPL_ENDOFWHO(sender.getNickname(), "*"));
  }
  else if (arg.size() >= 1)
  {
    channel = chH.getChannelByName(arg[0]);
    if (channel)
    {
      std::map<Client *, bool> clients = channel->getClients();
      for (std::map<Client *, bool>::iterator it = clients.begin();
           it != clients.end(); it++)
      {
        std::string FullInfo = it->first->getFullInfo(channel->getName(), it->second);
        sender.appendBufferOut(Replies::RPL_WHOREPLY(sender.getNickname(), FullInfo));
      }
      sender.appendBufferOut(Replies::RPL_ENDOFWHO(sender.getNickname(), channel->getName()));
    }
    else
    {
      Client *client = clH.getClientByNickname(arg[0]);
      if (client)
      {
        for (std::map<int, Client *>::iterator it = clients.begin();
             it != clients.end(); it++)
        {
          if (it->second->getNickname() == arg[0])
          {
            for (std::map<std::string, Channel *>::iterator itACh = listchan.begin(); itACh != listchan.end(); ++itACh)
            {
              if (itACh->second->isClientInChannel(sender) == true)
              {
                if (itACh->second->isClientInChannel(*client) == true)
                {
                  bool isOP = itACh->second->isClientOperator(*client);
                  std::string FullInfo = client->getFullInfo(itACh->second->getName(), isOP);
                  sender.appendBufferOut(Replies::RPL_WHOREPLY(sender.getNickname(), FullInfo));
                }
              }
            }
          }
        }
        sender.appendBufferOut(Replies::RPL_ENDOFWHO(sender.getNickname(), client->getNickname()));
      }
    }
  }
}
  Who::~Who() {}
