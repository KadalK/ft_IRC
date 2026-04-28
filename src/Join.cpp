#include "Join.hpp"

Join::Join(){}


/*
 2 arguments :
  - le nom du channel : "#channelName" (OBLIGATOIRE)
    - Si pas -> Error
    - Si oui :
      - Existe deja :
        - Check si password
        - Check Invite only
          - Check si Client invite
        - Check si client deja join
        - Ajouter client a la liste
      - Existe pas :
        - Creer un channel
  - le mot de passe : "motdepasse" (Pas obligatoire mais bloquant si le channel en demande un)
 */
std::vector<std::string> extractTokens(const std::string &str)
{
  std::vector<std::string> v;
  size_t start = 0;
  size_t pos;
  while ((pos = str.find(",", start)) != std::string::npos)
  {
    if (!str.substr(start, pos - start).empty())
      v.push_back(str.substr(start, pos - start));
    start = pos + 1;
  }
  if (!str.substr(start).empty())
    v.push_back(str.substr(start));
  return (v);
}
/*
BEAUCOUP DE PROBLEMES
 - clH pas utiliser.
 - Faire tout le parsing dans ChannelHandler plutot que channel
 - Password commenter car il faut un 2eme iterator (je ferais plus tard)
 - revoir logique
*
*/
void Join::execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg)
{
  (void)clH;
  std::vector<std::string> channels;
  std::vector <std::string> passwords;
  if (arg.empty() == true)
  {
    std::cout << "Missing arguments" << std::endl;
    return ;
  }
  channels = extractTokens(arg[0]);
  if (arg.size() > 1 && arg[1].empty() == false)
    passwords = extractTokens(arg[1]);
  for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
  {
    if ((*it)[0] != '#')
       std::cout << *it << " :No such channel" << std::endl;
    else
    {
      Channel *chToJoin = chH.getChannelByName(*it);
      if (chToJoin == NULL)
        chH.createChannel(*it, &client);
      else
      {
        if (chToJoin->getInviteOnly() == true && chToJoin->isClientInvited(client) == false)
          std::cout << *it << " :Cannot join channel (+i)" << std::endl;
        // else if (!(chToJoin->getPassword()).empty() && chToJoin->getPassword() != passwords[it])
        //   std::cout << *it << " :Cannot join channel (+k)" << std::endl;
        else if (chToJoin->isChannelFull() == true)
          std::cout << *it << " :Cannot join channel (+l)" << std::endl;
        else
          chToJoin->addClient(&client);
        // Suppose to send confirmation message + all mode to client that joined.
        // + msg to all channel member to notify newcomer
      }
    }
  }


}

Join::~Join(){}
