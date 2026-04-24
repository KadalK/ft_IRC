#include "Channel.hpp"

Channel::Channel(const std::string& name, Client *client) : _name(name), _inviteOnly(false), _topicRestrict(false), _userLimit(0)
{
  this->_clients = {{client, true}};
  this->_invited = {};
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

void	Channel::setTopic(std::string& topic){
	this->_topic = topic;
}

void	Channel::addClient(Client* client)
{
  std::pair<std::map<Client*, bool>, bool> ret;

  ret = this->_clients.insert(std::pair<Client*, bool>(client, false));
  if (ret = false)
    std::cout << "already join the channel" << std::endl;
  else
  {
    std::vector<Client*>::iterator it;

    it = std::find(this->_invited.begin(), this->_invited.end(), client);
    if (it != this->_invited.end())
      this->_invited.erase(it);
  }
}

void Channel:inviteClient(Client *client)
{
  std::vector<Client*>::iterator it;

  it = std::find(this->_invited.begin(), this->_invited.end(), client);
  if (it != this->_invited.end())
    std::cout << "already invited to the channel" << std::endl;
  else
    this->_invited.push_back(it);
  return ;
}

void Channel::removeClient(Client* client)
{
  std::map<Client *, bool>::iterator it;

  it = this->_clients.find();
  if (it != this->_clients.end())
    _clients.erase(it);
  else
    std::cout << "client no in channel" << std::endl;
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
