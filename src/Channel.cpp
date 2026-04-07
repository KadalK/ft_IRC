#include "Channel.hpp"

Channel::Channel() : name("Default"), clients(0) {}
Channel::Channel(const Channel& copy)  : name(copy.name), clients(copy.clients) {}
Channel& Channel::operator=(const Channel& other){
	if (this != &other)
	{
		this->name = other.name;
		this->clients = other.clients;
	}
	return(*this);
}
Channel::~Channel(){}
