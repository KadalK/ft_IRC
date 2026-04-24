#include "Pass.hpp"


// Pass::Pass(const Pass& copy) : Commands(copy) {}
// Pass::Pass() {}

// Pass::Pass(const Server& server)  {
//
// }

//changer std::vector<std::vector<std::string> > pass std::vector<std::vector> pass
//faire un preparsing des element a utiliser dans la fonction


void Pass::execute(Client& client, const std::vector<std::string>& arg, std::string passServ)
{
	//TODO : Se referer a la RFC pour le format du mot de passe voila
	if (arg.size() < 2)
	{
		std::cout << "[DEBUG]: Invalid format" << std::endl;
		client.setBufferOut("Invalid format");
		return;
	}

	const std::string& pass = arg[1];

	// if (client.isRegistered())
	{
		std::cout << "[DEBUG]: Already registered" << std::endl;
		client.setBufferOut("Already registered");
		return;
	}

	if (pass != passServ)
	{
		std::cout << "[DEBUG]: invalid password" << std::endl;
		client.setBufferOut("invalid password");
		return;
	}

	client.setAuth(true);
}

	Pass::~Pass(){}
