#include "Channel.hpp"

Channel::Channel(const std::string& name, const Client &client) : _name(name)
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
}

void Channel::removeClient(Client* client)
{
	if (!client)
	{
		std::cout << "[DEBUG] removeClient client is NULL\n";
		return;
	}

	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it == client)
		{
			std::cout << "[DEBUG] removeClient client deleted\n";
			_clients.erase(it);
			return;
		}
	}
			std::cout << "[DEBUG] removeClient client not found\n";
}

// void Channel::broadcast(const std::string& msg, Client* sender)
// {
// 	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
// 	{
// 		if (*it != sender)
// 		{
// 			std::cout << "[DEBUG] sending \n";
// 			(*it)->send(msg);
// 		}
// 	}
// }

// bool	Channel::hasClient(Client* client) const{
// 	for (size_t i = 0; i < _clients.size(); i++)
// 	{
// 		if (this->_clients[i] == client)
// 		{
// 			std::cout << "[DEBUG] : client "  << client->getName() << " is here\n";
// 			return (true);
// 		}
// 	}

// 	std::cout << "[DEBUG] : client "  << client->getName()<< " is not here\n";
// 	return(false);
// }


Channel::~Channel(){}
