#include "commands/Nick.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "Replies.hpp"

Nick::Nick() {}

static bool validNick(const std::string &nick)
{
  if (!std::isalpha(static_cast<unsigned char>(nick[0])) && nick[0] != '_')
    return false;

  for (size_t i = 0; i < nick.size(); ++i)
  {
    if (!std::isalnum(static_cast<unsigned char>(nick[i])) && nick[i] != '_' &&
        nick[i] != '-')
      return false;
  }
  return true;
}

void Nick::execute(Client &sender, ClientHandler &clH, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    sender.appendBufferOut(Replies::ERR_NONICKGIVEN(sender.getNickname()));
    return;
  }

  const std::string &nick = arg[0];
  if (!validNick(nick))
  {
    sender.appendBufferOut(
        Replies::ERR_ERRONEUSNICKNAME(sender.getNickname(), nick));
    return;
  }

  Client *existing = clH.getClientByNickname(nick);
  if (existing)
  {
    sender.appendBufferOut(
        Replies::ERR_NICKNAMEINUSE(sender.getNickname(), nick));
    return;
  }
  if (sender.getPassBool() && sender.getUserBool())
  {
    if (sender.getNickBool() == false)
      sender.setAuth(true);
  }
  if (!sender.getNickBool())
    sender.setNickBool(true);
  else
  {
    // ENVOIE A TOUS LES CLIENTS DU SERVER -> MEILLEUR POUR QUERY
    std::map<int, Client *> clients = clH.getRegistery();
    for (std::map<int, Client *>::iterator it = clients.begin();
         it != clients.end(); it++)
    {
      it->second->appendBufferOut(
          Replies::BC_NICK(sender.getFullName(), arg[0]));
    }
    // ENVOIE QUE AUX GENS QUI ONT DES SERVER EN COMMUN (DOIT FAIRE UN STD::SET)
    // for (std::map<std::string, Channel *>::const_iterator it =
    //          chH.getChannelList().begin();
    //      it != chH.getChannelList().end(); ++it)
    // {
    //   if (it->second->isClientInChannel(sender))
    //   {
    //     it->second->broadcast(Replies::BC_NICK(sender.getFullName(), arg[0]),
    //                           &sender, false);
    //   }
    // }
  }
  sender.setNickname(nick);
}

Nick::~Nick() {}
