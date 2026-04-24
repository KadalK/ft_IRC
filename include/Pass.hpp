#pragma once

#include "Server.hpp"
#include "Commands.hpp"


class Pass : public Commands {
private:
	Pass& operator=(const Pass& other);
	Pass(const Pass& copy);
	Pass();
	std::string _pass;
public:
	// Pass(std::string pass);
	// Pass(const Server& server);

	static void execute(Client& client, const std::vector<std::string>& arg , std::string pasServ);
	~Pass();
};
