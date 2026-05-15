#include "commands/Pass.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

Pass::Pass(std::string passServ) : _passServ(passServ) {}

void Pass::execute(Client &sender, ClientHandler &, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "PASS"));
    return;
  }

  const std::string &pass = arg[0];

  if (sender.getPassBool())
  {
    sender.appendBufferOut(
        Replies::ERR_ALREADYREGISTERED(sender.getNickname()));
    return;
  }

  if (pass != this->_passServ)
  {
    sender.appendBufferOut(Replies::ERR_PASSWDMISMATCH(sender.getNickname()));
    return;
  }

  sender.setPassBool(true);
  if (sender.getUserBool() && sender.getNickBool())
    sender.setAuth(true);
  return;
}

Pass::~Pass() {}
