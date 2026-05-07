#include "Channel.hpp"
#include <cstdlib>
#include <sstream>

Channel::Channel(const std::string &name)
    : _name(name), _inviteOnly(false), _topicRestrict(false),
      _hasPassword(false), _hasTopic(false), _hasUserLimit(false),
      _userLimit(0), _userCount(0)
{
  this->_modeFt['i'] = &Channel::mode_i;
  this->_modeFt['t'] = &Channel::mode_t;
  this->_modeFt['k'] = &Channel::mode_k;
  this->_modeFt['o'] = &Channel::mode_o;
  this->_modeFt['l'] = &Channel::mode_l;
  // Avoir l'heure de creation du channel
}

size_t Channel::getUserCount() const { return (this->_userCount); }

size_t Channel::getUserLimit() const { return (this->_userLimit); }

const std::string &Channel::getName() const { return (this->_name); }

const std::string &Channel::getTopic() const { return (this->_topic); }

const std::string &Channel::getPassword() const { return (this->_password); }

bool Channel::getInviteOnly() const { return (this->_inviteOnly); }

bool Channel::getTopicRestrict() const { return (this->_topicRestrict); }

bool Channel::getHasTopic() const { return (this->_hasTopic); }

bool Channel::getHasUserLimit() const { return (this->_hasUserLimit); }

bool Channel::getHasPassword() const { return (this->_hasPassword); }

std::string Channel::getUserLimitString() const
{
  std::stringstream ss;
  ss << this->_userLimit;

  return (ss.str());
}

const std::map<Client *, bool> &Channel::getClients() const
{
  return (this->_clients);
}

void Channel::setTopic(std::string &topic) { this->_topic = topic; }

void Channel::setTopicBool(bool flag) { this->_hasTopic = flag; }

bool Channel::canJoinChannel(Client &client, std::string inPassword)

{
  if (this->isClientInChannel(client) == true)
  {
    client.appendBufferOut(client.getNickname() +
                           " : Already join the channel\n");
    return (false);
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

bool Channel::isClientInChannel(Client &client)
{
  std::map<Client *, bool>::iterator itSend;

  itSend = this->_clients.find(&client);
  if (itSend == this->_clients.end())
    return false;
  return true;
}

bool Channel::isClientOperator(Client &client)
{
  std::map<Client *, bool>::iterator itClient;

  itClient = this->_clients.find(&client);
  return (itClient->second);
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

bool Channel::inviteClient(Client *client)
{
  if (this->isClientInvited(*client) == true)
    return (false);
  else
  {
    this->_invited.push_back(client);
    return (true);
  }
}

void Channel::removeClient(Client *client)
{
  std::map<Client *, bool>::iterator it;
  it = this->_clients.find(client);
  if (it != this->_clients.end() && this->_userCount != 0)
  {
    this->_clients.erase(it);
    this->_userCount--;
  }
  else
    std::cout << "client no in channel" << std::endl;
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
  std::string replyTopic = ":ircserv 331 " + client->getNickname() + " " +
                           this->_name + " :No topic is set\r\n";
  client->appendBufferOut(replyTopic);
  std::string replyNames = ":ircserv 353 " + client->getNickname() + " = " +
                           this->_name + " :" + list +
                           "\r\n"; // LIST ALL CLIENTS ON CHANNEL
  client->appendBufferOut(replyNames);
  std::string replyEndOfNames = ":ircserv 366 " + client->getNickname() + " " +
                                this->_name + " :End of /NAMES list.\r\n";
  client->appendBufferOut(replyEndOfNames);
}

void Channel::broadcast(const std::string &msg, Client *sender)
{
  for (std::map<Client *, bool>::iterator it = this->_clients.begin();
       it != this->_clients.end(); it++)
  {
    if (it->first && it->first != sender)
      it->first->appendBufferOut(msg);
  }
  return;
}

void Channel::mode_i(bool flag, const std::string &, Client *sender)
{
  std::map<Client *, bool>::iterator itSend;

  itSend = this->_clients.find(sender);
  if (itSend->second == false)
    return;
  if (this->_inviteOnly == flag)
    return;
  this->_inviteOnly = flag;
}

void Channel::mode_t(bool flag, const std::string &, Client *sender)
{
  std::map<Client *, bool>::iterator itSend;

  itSend = this->_clients.find(sender);
  if (itSend->second == false)
    return;
  if (this->_topicRestrict == flag)
    return;
  this->_topicRestrict = flag;
}

#define invalidChars " :,\0\r\n"

static bool isValidKeyFormat(const std::string &key)
{
  if (key.size() > 23)
    return (false);
  size_t pos = key.find_first_of(invalidChars);
  if (pos != std::string::npos)
    return (false);
  return (true);
}

void Channel::mode_k(bool flag, const std::string &arg, Client *sender)
{
  if (arg.empty())
    return;
  if (!isValidKeyFormat(arg))
    return (sender->appendBufferOut(
        Replies::ERR_INVALIDKEY(sender->getNickname(), this->_name)));
  if (flag == true)
  {
    if (this->_hasPassword == flag)
      return (sender->appendBufferOut(Replies::ERR_KEYSET(this->_name)));
    this->_password = arg;
    this->_hasPassword = flag;
  }
  else
  {
    if (this->_hasPassword == flag)
      return;
    if (arg != this->_password)
      return (sender->appendBufferOut(Replies::ERR_KEYSET(this->_name)));
    this->_password.clear();
    this->_hasPassword = flag;
  }
}

void Channel::mode_o(bool flag, const std::string &arg, Client *sender)
{
  if (arg.empty())
  {
    return;
  }

  std::map<Client *, bool>::iterator itReceiv;

  itReceiv = this->findClientByNick(arg);
  if (itReceiv == this->_clients.end())
  {
    return (sender->appendBufferOut(Replies::ERR_USERNOTINCHANNEL(
        sender->getFullName(), arg, this->_name)));
  }
  if (itReceiv->second == flag)
    return;
  itReceiv->second = flag;
}

static bool isInteger(const std::string &str)
{
  if ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))
    return (false);

  char *p;
  strtol(str.c_str(), &p, 10);

  if (*p == 0)
    return (true);
  return (false);
}

void Channel::mode_l(bool flag, const std::string &arg, Client *)
{
  if (flag == true)
  {
    if (arg.empty())
      return;
    if (!isInteger(arg))
      return;
    this->_userLimit = atol(arg.c_str());
  }
  else
    this->_userLimit = 0;
  this->_hasUserLimit = flag;
  return;
}

const std::string Channel::getModeString() const
{
  std::string flags = "+";
  std::string params = "";

  if (this->_inviteOnly)
    flags += "i";
  if (this->_topicRestrict)
    flags += "t";
  if (this->_hasPassword)
    flags += "k";
  if (this->_hasUserLimit)
  {
    flags += "l";
    params += " " + this->getUserLimitString();
  }
  if (flags.size() == 1)
    flags = "";
  return (flags + params);
}

Channel::~Channel() {}
