#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <iostream>
#include "Client.hpp"

class Channel
{

private :
	std::string name;
	std::vector<Client *> clients;
public:
	Channel();
	Channel(const Channel &copy);
	Channel &operator=(const Channel &other);

	~Channel();
};

#endif
