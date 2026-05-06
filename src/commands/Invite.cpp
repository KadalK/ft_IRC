#include "commands/Invite.hpp"

Invite::Invite() {}

void Invite::execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
                     const std::vector<std::string> &arg)
{
  Channel *channel;
  Client *clientInvited;

  if (arg.empty())
  {
    const std::map<std::string, Channel *> channelList = chH.getChannelList();
    for (std::map<std::string, Channel *>::const_iterator it =
             channelList.begin();
         it != channelList.end(); it++)
    {
      if (it->second->isClientInvited(client) == true)
      {
        std::string reply =
            ":ircserv 336 " + client.getNickname() + " " + it->first + "\r\n";
        client.appendBufferOut(reply);
        // 336 "<client> <channel>"
      }
    }
    return;
  }
  if (arg.size() < 2)
  {
    // 461 "<client> <command> :Not enough parameters"
    std::cout << "not enough params" << std::endl;
    return;
  }
  channel = chH.getChannelByName(arg[1]);
  if (!channel)
  {
    std::cout << "No such channel" << std::endl;
    // 403 "<client> <channel> :No such channel"
    return;
  }
  clientInvited = clH.getClientByNickname(arg[0]);
  if (!clientInvited)
  {
    std::cout << "No such nickname" << std::endl;
    // 401 "<client> :No such nickname"
    return;
  }
  if (channel->isClientInChannel(*clientInvited) == true)
  {
    std::cout << "already in channel" << std::endl;
    // 443 "<client> <nick> <channel> :is already on channel"
    return;
  }
  if (channel->getInviteOnly() == true &&
      channel->isClientOperator(client) == false)
  {
    std::cout << "not operator" << std::endl;
    // 482 "<client> <channel> :You're not channel operator"
    return;
  }
  if (channel->inviteClient(clientInvited) == true)
  {
    std::cout << "invited client" << std::endl;
    // 341 "<client> <nick> <channel>"
    return;
  }
  return;
}

Invite::~Invite() {}
