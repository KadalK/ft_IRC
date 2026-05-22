#include "commands/Who.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

Who::Who() {}


void Who::execute(Client &, ClientHandler &, ChannelHandler &,
  const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    /// FAIRE LES LIST DES TRUCS CHIANTS
  }
  if (arg.size() == 1)
  {

  }
  if (arg.size() == 2 && arg[2][0] == 'o')
  {
    // renvoyer que les operateurs du serveur AH PAS
  }
}

Who::~Who() {}
