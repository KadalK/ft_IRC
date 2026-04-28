#ifndef PASS_HPP
#define PASS_HPP

#include "Commands.hpp"
#include "ClientHandler.hpp"

class Pass : public Commands {
private:
	Pass& operator=(const Pass& other);
	Pass(const Pass& copy);
  Pass();
	std::string _passServ;
public:
  Pass(std::string passServ);

  void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg);
	// static void execute(Client& client,  const std::vector<std::string>& arg,  std::string& passServ);

	~Pass();
};

#endif
