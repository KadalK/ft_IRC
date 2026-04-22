#include "Channel.hpp"

Channel::Channel(const std::string& name) : _name(name){
	if (name.empty())
		throw std::invalid_argument("Channel name cannot be empty");
	if (name[0] != '#')
		throw std::invalid_argument("Invalid channel name");
}

const std::string& Channel::getName() const{
	return(this->_name);
}

const std::string&	Channel::getTopic() const{
	return(this->_topic);
}

void	Channel::setTopic(std::string& topic){
	this->_topic = topic;
}

void	Channel::addClient(Client* client){
	if (!client){
		std::cout << " [DEBUG] addClient  client is NULL\n";
		return;
	}
	// if (hasClient(client)){
	// 	std::cout << "[DEBUG] addClient client is already in\n";
	// 	return;
	// }

	this->_clients.push_back(client);
}

void Channel::removeClient(Client* client)
{
	if (!client)
	{
		std::cout << "[DEBUG] removeClient client is NULL\n";
		return;
	}

	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
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




Channel::~Channel(){}
