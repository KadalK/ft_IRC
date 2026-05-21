#include "commands/Invite.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "Replies.hpp"

Invite::Invite() {}

void Invite::execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
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
      if (it->second->isClientInvited(sender) == true)
        sender.appendBufferOut(
            Replies::RPL_INVITELIST(sender.getNickname(), it->first));
    }
    return (sender.appendBufferOut(
        Replies::RPL_ENDOFINVITELIST(sender.getNickname())));
  }
  if (arg.size() < 2)
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "INVITE")));
  channel = chH.getChannelByName(arg[1]);
  if (!channel)
    return (sender.appendBufferOut(
        Replies::ERR_NOSUCHANNEL(sender.getNickname(), arg[1])));
  if (channel->isClientInChannel(sender) == false)
    return (sender.appendBufferOut(
        Replies::ERR_NOTONCHANNEL(sender.getNickname(), arg[1])));
  clientInvited = clH.getClientByNickname(arg[0]);
  if (!clientInvited)
    return (sender.appendBufferOut(
        Replies::ERR_NOSUCHNICK(sender.getNickname(), arg[0])));
  if (channel->isClientInChannel(*clientInvited) == true)
    return (sender.appendBufferOut(
        Replies::ERR_USERONCHANNEL(sender.getNickname(), arg[0], arg[1])));
  if (channel->getInviteOnly() == true &&
      channel->isClientOperator(sender) == false)
    return (sender.appendBufferOut(
        Replies::ERR_CHANNOPRIVSNEEDED(sender.getNickname(), arg[1])));
  if (channel->inviteClient(clientInvited) == true)
  {
    sender.appendBufferOut(
        Replies::RPL_INVITING(sender.getNickname(), arg[0], arg[1]));
    clientInvited->appendBufferOut(
        Replies::BC_INVITE(sender.getFullName(), arg[0], arg[1]));
  }
}

Invite::~Invite() {}
