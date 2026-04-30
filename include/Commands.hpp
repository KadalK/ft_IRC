#pragma once

#include <vector>
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"

class Commands {
private:
  Commands(Commands const &src);
  Commands &operator=(Commands const &rhs);
protected:

public:
  Commands();
  virtual ~Commands();

  // virtual void parsingMessage(std::string) = 0;
	virtual void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg) = 0;
  // virtual void errorMessage(size_t errorValue) = 0;

  // JE SAIS PAS ENCORE CA MANQUE DE TRUCS
};
