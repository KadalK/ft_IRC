#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <iostream>
#include "Client.hpp"

class Channel{
public:
	Channel();
	Channel(const Channel& copy);
	Channel& operator=(const Channel& other);
	std::string name;
	std::vector <Client*> clients;
	~Channel();
};

#endif