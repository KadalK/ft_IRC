#include "Channel.hpp"

Channel::Channel(const std::string &name) : _name(name), _inviteOnly(false), _topicRestrict(false), _userLimit(0), _userCount(0)
{
}

const std::string &Channel::getName() const
{
  return (this->_name);
}

const std::string &Channel::getTopic() const
{
  return (this->_topic);
}

const std::string &Channel::getPassword() const
{
  return (this->_password);
}

bool Channel::getInviteOnly() const
{
  return (this->_inviteOnly);
}

void Channel::setTopic(std::string &topic)
{
  this->_topic = topic;
}

bool Channel::canJoinChannel(Client &client, std::string inPassword)
{
  int fd = client.getFd();
  for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
  {
    if (it->first->getFd() == fd)
    {
      client.appendBufferOut( client.getNickname() +" : Already join the channel\n");
      return (false);
    }
  }
  if (this->_inviteOnly == true && this->isClientInvited(client) == false)
  {
    std::cout << this->_name << " :Cannot join channel (+i)" << std::endl;
    return (false);
  }
  else if (!(this->_password.empty()) && this->_password != inPassword)
  {
    std::cout << this->_name << " :Cannot join channel (+k)" << std::endl;
    return (false);
  }
  else if (this->isChannelFull() == true)
  {
    std::cout << this->_name << " :Cannot join channel (+l)" << std::endl;
    return (false);
  }
  return (true);
}

bool Channel::isClientInvited(Client &client)
{
  std::vector<Client *>::iterator it;

  it = std::find(this->_invited.begin(), this->_invited.end(), &client);
  if (it != this->_invited.end())
    return (true);
  return (false);
}

bool Channel::isChannelFull(void)
{
  if (this->_userLimit == 0 || this->_userLimit > this->_userCount)
    return (false);
  return (true);
}

void Channel::addClient(Client *client)
{
  if (this->_userCount == 0)
    this->_clients.insert(std::pair<Client *, bool>(client, true));
  else
    this->_clients.insert(std::pair<Client *, bool>(client, false));
  std::vector<Client *>::iterator it;

  it = std::find(this->_invited.begin(), this->_invited.end(), client);
  if (it != this->_invited.end())
    this->_invited.erase(it);
  this->_userCount += 1;
}

void Channel::inviteClient(Client *client)
{
  if (this->isClientInvited(*client) == true)
    std::cout << "already invited to the channel" << std::endl;
  else
    this->_invited.push_back(client);
  return;
}

void Channel::removeClient(Client *client)
{
  std::map<Client *, bool>::iterator it;

  it = this->_clients.find(client);
  if (it != this->_clients.end())
    _clients.erase(it);
  else
    std::cout << "client no in channel" << std::endl;
  // SI TOUS LES CLIENTS SONT PARTI DELETE CHANNEL
}

void Channel::mode_i(bool flag, const std::string &arg)
{
  (void)arg;
  if (flag == true)
  {
    if (this->_inviteOnly == true)
    {
      std::cout << "Channel already in invite-only mode" << std::endl;
      return;
    }
    this->_inviteOnly = true;
    std::cout << "Added invite-only mode" << std::endl;
  }
  else
  {
    if (this->_inviteOnly == false)
    {
      std::cout << "Channel already not in invite-only mode" << std::endl;
      return;
    }
    this->_inviteOnly = true;
    std::cout << "Deleted invite-only mode" << std::endl;
  }
}

std::string Channel::getClientInChan()
{
  std::string list;
  for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
  {
    std::string tmp = "";
    if (it->second == true)
      tmp = "@";
    tmp += it->first->getNickname();
    if (!list.empty())
      list += " " + tmp;
    else
      list = tmp;
  }
  return list;
}

void Channel::replyJoinChannel(Client *client)
{
  std::string list = this->getClientInChan();

  std::string replyJoin = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + " JOIN :" + this->_name + "\r\n";
  client->appendBufferOut(replyJoin);
  std::string replyTopic = ": ircserv 331 " + client->getNickname() + " " + this->_name + " :No topic is set\r\n";
  client->appendBufferOut(replyTopic);
  std::string replyNames = ": ircserv 353 " + client->getNickname() + " " + this->_name + " :" + list + "\r\n"; // LIST ALL CLIENTS ON CHANNEL
  client->appendBufferOut(replyNames);
  std::string replyEndOfNames = ": ircserv 366 " + client->getNickname() + " " + this->_name + " :End of /NAMES list.\r\n";
  client->appendBufferOut(replyEndOfNames);
}

Channel::~Channel() {}
