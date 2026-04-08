#ifndef MANAGECHANNEL_HPP
#define MANAGECHANNEL_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include "Channel.hpp"

class ManageChannel{
public:
	ManageChannel();

	void deleteChannel(const Channel& client);
	void createChannel(const Channel& client);
	~ManageChannel();
};

#endif