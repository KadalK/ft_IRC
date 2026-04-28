#ifndef PASS_HPP
#define PASS_HPP

#include "Server.hpp"
#include "Commands.hpp"
#include "ClientHandler.hpp"

class Pass : public Commands {
private:
	Pass& operator=(const Pass& other);
	Pass(const Pass& copy);
	Pass();
	std::string _pass;
public:
	// Pass(std::string pass);
	// Pass(const Server& server);

	static void execute(Client& client,  const std::vector<std::string>& arg,  std::string& passServ);
	~Pass();
};

#endif