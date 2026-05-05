#include "commands/Invite.hpp"

Invite::Invite() {}

void Invite::execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
                     const std::vector<std::string> &arg)
{
  Channel *channel;
  Client *clientInvited;

  if (arg.empty())
  {
  }
  channel = chH.getChannelByName(arg[1]);
  if (!channel)
  {
    // 403 "<client> <channel> :No such channel"
    return;
  }
  if (channel->isClientInChannel(client) == false)
  {
    // 442 "<client> <channel> :You're not on that channel"
    return;
  }
  clientInvited = clH.getClientByNickname(arg[0]);
  if (!clientInvited)
  {
    // 401 "<client> :No such nickname"
    return;
  }
  if (channel->isClientInChannel(*clientInvited) == true)
  {
    // 443 "<client> <nick> <channel> :is already on channel"
    return;
  }
  if (channel->getInviteOnly() == true &&
      channel->isClientOperator(client) == false)
  {
    // 482 "<client> <channel> :You're not channel operator"
    return;
  }
  if (channel->inviteClient(clientInvited) == true)
  {
    // 341 "<client> <nick> <channel>"
    return;
  }
  return;
}

Invite::~Invite() {}
