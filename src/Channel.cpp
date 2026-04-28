#include "Channel.hpp"

Channel::Channel(const std::string& name, Client *client) : _name(name), _inviteOnly(false), _topicRestrict(false), _userLimit(0), _userCount(1)
{
  this->_clients[client] = true;
}

const std::string& Channel::getName() const
{
	return(this->_name);
}

const std::string&	Channel::getTopic() const
{
	return(this->_topic);
}

const std::string&	Channel::getPassword() const
{
	return(this->_password);
}

bool Channel::getInviteOnly() const
{
	return(this->_inviteOnly);
}

void	Channel::setTopic(std::string& topic){
	this->_topic = topic;
}

bool Channel::canJoinChannel(Client &client, std::string inPassword)
{
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
  std::vector<Client*>::iterator it;

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

void	Channel::addClient(Client* client)
{
  std::pair<std::map<Client*, bool>::iterator, bool> ret;

  ret = this->_clients.insert(std::pair<Client*, bool>(client, false));
  if (ret.second == false)
    client->setBufferOut("already joined\n");
  else
  {
    std::vector<Client*>::iterator it;
    
    client->setBufferOut("Client joined the channel\n");
    it = std::find(this->_invited.begin(), this->_invited.end(), client);
    if (it != this->_invited.end())
      this->_invited.erase(it);
    this->_userCount += 1;
  }
}

void Channel::inviteClient(Client *client)
{
  if (this->isClientInvited(*client) == true)
    std::cout << "already invited to the channel" << std::endl;
  else
    this->_invited.push_back(client);
  return ;
}

void Channel::removeClient(Client* client)
{
  std::map<Client*, bool>::iterator it;

  it = this->_clients.find(client);
  if (it != this->_clients.end())
    _clients.erase(it);
  else
    std::cout << "client no in channel" << std::endl;
  //SI TOUS LES CLIENTS SONT PARTI DELETE CHANNEL
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




Channel::~Channel(){}
