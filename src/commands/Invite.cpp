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
        client.appendBufferOut(
            Replies::RPL_INVITELIST(client.getNickname(), it->first));
    }
    return (client.appendBufferOut(
        Replies::RPL_ENDOFINVITELIST(client.getNickname())));
  }
  if (arg.size() < 2)
    return (client.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE")));
  channel = chH.getChannelByName(arg[1]);
  if (!channel)
    return (client.appendBufferOut(
        Replies::ERR_NOSUCHANNEL(client.getNickname(), arg[1])));
  if (channel->isClientInChannel(client) == false)
    return (client.appendBufferOut(
        Replies::ERR_NOTONCHANNEL(client.getNickname(), arg[0])));
  clientInvited = clH.getClientByNickname(arg[0]);
  if (!clientInvited)
    return (client.appendBufferOut(
        Replies::ERR_NOSUCHNICK(client.getNickname(), arg[0])));
  if (channel->isClientInChannel(*clientInvited) == true)
    return (client.appendBufferOut(
        Replies::ERR_USERONCHANNEL(client.getNickname(), arg[0], arg[1])));
  if (channel->getInviteOnly() == true &&
      channel->isClientOperator(client) == false)
    return (client.appendBufferOut(
        Replies::ERR_CHANNOPRIVSNEEDED(client.getNickname(), arg[1])));
  if (channel->inviteClient(clientInvited) == true)
  {
    client.appendBufferOut(
        Replies::RPL_INVITING(client.getNickname(), arg[0], arg[1]));
    clientInvited->appendBufferOut(
        Replies::BC_INVITE(client.getNickname(), arg[1]));
    return;
  }
  return;
}

Invite::~Invite() {}
