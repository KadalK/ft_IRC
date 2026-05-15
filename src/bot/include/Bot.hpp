#pragma once
#include "../../include/Client.hpp"
#include <vector>

#include <string>

class Bot{
private:
	Client *_client;
	std::vector<std::string> _memories;
	Bot(const Bot& copy);
	Bot& operator=(const Bot& copy);
public:
	Bot();

	std::string talk(const std::string& input);
	~Bot();
};