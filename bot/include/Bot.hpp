#pragma once

#include <string>

class Bot{
private:
	Bot(const Bot& copy);
	Bot& operator=(const Bot& copy);
public:
	Bot();

	std::string talk(const std::string& input);
	~Bot();
};