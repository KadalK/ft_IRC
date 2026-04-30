#include "Channel.hpp"
#include <cstdlib>

Channel::Channel(const std::string &name)
    : _name(name), _inviteOnly(false), _topicRestrict(false),
      _hasPassword(false), _hasUserLimit(false), _userLimit(0), _userCount(0)
{
  this->_modeFt['i'] = &Channel::mode_i;
  this->_modeFt['t'] = &Channel::mode_t;
  this->_modeFt['k'] = &Channel::mode_k;
  this->_modeFt['o'] = &Channel::mode_o;
  this->_modeFt['l'] = &Channel::mode_l;
}

const std::string &Channel::getName() const { return (this->_name); }

const std::string &Channel::getTopic() const { return (this->_topic); }

const std::string &Channel::getPassword() const { return (this->_password); }

bool Channel::getInviteOnly() const { return (this->_inviteOnly); }

void Channel::setTopic(std::string &topic) { this->_topic = topic; }

bool Channel::canJoinChannel(Client &client, std::string inPassword)
{
  int fd = client.getFd();
  for (std::map<Client *, bool>::iterator it = this->_clients.begin();
       it != this->_clients.end(); ++it)
  {
    if (it->first->getFd() == fd)
    {
      client.appendBufferOut(client.getNickname() +
                             " : Already join the channel\n");
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

std::map<Client *, bool>::iterator
Channel::findClientByNick(const std::string &nick)
{
  std::map<Client *, bool>::iterator it = this->_clients.begin();

  while (it != this->_clients.end() && it->first->getNickname() != nick)
    it++;
  return (it);
}

std::string Channel::getClientInChan()
{
  std::string list;
  for (std::map<Client *, bool>::iterator it = this->_clients.begin();
       it != this->_clients.end(); ++it)
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

  std::string replyJoin = ":" + client->getNickname() + "!" +
                          client->getUsername() + "@" + client->getHostname() +
                          " JOIN :" + this->_name + "\r\n";
  client->appendBufferOut(replyJoin);
  std::string replyTopic = ": ircserv 331 " + client->getNickname() + " " +
                           this->_name + " :No topic is set\r\n";
  client->appendBufferOut(replyTopic);
  std::string replyNames = ": ircserv 353 " + client->getNickname() + " " +
                           this->_name + " :" + list +
                           "\r\n"; // LIST ALL CLIENTS ON CHANNEL
  client->appendBufferOut(replyNames);
  std::string replyEndOfNames = ": ircserv 366 " + client->getNickname() + " " +
                                this->_name + " :End of /NAMES list.\r\n";
  client->appendBufferOut(replyEndOfNames);
}

void Channel::broadcast(const std::string &msg, Client *sender)
{
  for (std::map<Client *, bool>::iterator it; it != this->_clients.end(); it++)
  {
    if (it->first != sender)
      it->first->appendBufferOut(msg);
  }
  return;
}

void Channel::mode_i(bool flag, const std::string &, Client *)
{
  if (this->_inviteOnly == flag)
  {
    std::cout << "Channel already in this mode" << std::endl;
    return;
  }
  this->_inviteOnly = flag;
  std::cout << "Added invite-only mode" << std::endl;
}

void Channel::mode_t(bool flag, const std::string &, Client *)
{
  if (this->_topicRestrict == flag)
  {
    std::cout << "Channel already in this mode" << std::endl;
    return;
  }
  this->_topicRestrict = flag;
  std::cout << "Modified topic-restrict mode" << std::endl;
}

void Channel::mode_k(bool flag, const std::string &arg, Client *)
{
  if (arg.empty())
  {
    std::cout << "Need more params" << std::endl;
    return;
  }
  if (this->_hasPassword == flag)
  {
    std::cout << "Already same mode" << std::endl;
    return;
  }
  if (flag == true)
  {
    if (!this->_password.empty())
    {
      std::cout << "ya deja un mot de passe" << std::endl;
      return;
    }
    this->_password = arg;
    this->_hasPassword = flag;
  }
  else
  {
    if (arg != this->_password)
    {
      std::cout << "Wrong paswsowrd to clear" << std::endl;
      return;
    }
    this->_password.clear();
    this->_hasPassword = flag;
    std::cout << "Cleared password" << std::endl;
  }
}

void Channel::mode_o(bool flag, const std::string &arg, Client *sender)
{
  if (arg.empty())
  {
    std::cout << "Need more params" << std::endl;
    return;
  }

  std::map<Client *, bool>::iterator itSend;

  itSend = this->_clients.find(sender);
  if (itSend == this->_clients.end())
  {
    std::cout << "sender pas dans le channel" << std::cout;
    return;
  }
  if (itSend->second == false)
  {
    std::cout << "sender n'a pas les droits" << std::cout;
    return;
  }

  std::map<Client *, bool>::iterator itReceiv;

  itReceiv = this->findClientByNick(arg);
  if (itReceiv == this->_clients.end())
  {
    std::cout << "receiver pas dans le channel" << std::cout;
    return;
  }
  if (itReceiv->second == flag)
    return;
  itReceiv->second = flag;
  std::cout << ":" << itSend->first->getNickname() << " " << this->_name << " "
            << (flag ? "+o" : "-o") << " " << itReceiv->first->getNickname()
            << std::endl;
  // BROADCAST A TOUT LE MONDE
}

void Channel::mode_l(bool flag, const std::string &arg, Client *)
{
  if (arg.empty() && flag == true)
  {
    std::cout << "Need more params" << std::endl;
    return;
  }
  if (this->_hasUserLimit == flag)
  {
    std::cout << "Channel already in this mode" << std::endl;
    return;
  }
  this->_hasUserLimit = flag;
  if (!arg.empty())
    this->_userLimit = std::atoi(arg.c_str());
  else
    this->_userLimit = 0;
}

Channel::~Channel() {}
