#include "commands/Mode.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"

Mode::Mode() {}

/*
 *B = [k, o]   -> Toujours un paramètre
 *C = [+l, -l] -> Paramètre uniquement pour +
 *D = [i, t]   -> Jamais de paramètre
 */

void Mode::execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  bool flag;
  Channel *channel;

  channel = chH.getChannelByName(arg[0]);
  if (!channel)
    return;
}

Mode::~Mode() {}
