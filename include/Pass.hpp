#pragma once

#include "Server.hpp"
#include "Commands.hpp"

class Pass : public Commands {
private:
	Pass& operator=(const Pass& other);
	Pass(const Pass& copy);
	Pass();
public:
	// Pass(const Server& server);

	void execute(Client* client, std::vector<std::string>);
	~Pass();
};