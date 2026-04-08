#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <iostream>
#include "Client.hpp"

class Channel {
private:
	std::string _name;
	std::string _topic;
	std::vector <Client*> _clients;

public:
	Channel(const std::string& name);

	void	setTopic(std::string& topic);

	const std::string&	getName() const;
	const std::string&	getTopic() const;

	void	addClient(Client* client);
	void	removeClient(Client* client);

	void	broadcast(const std::string& msg, Client* sender);
	bool	hasClient(Client* client) const;

	~Channel();
};

#endif