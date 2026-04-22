#include "Pass.hpp"


// Pass::Pass(const Pass& copy) : Commands(copy) {}
// Pass::Pass() {}

// Pass::Pass(const Server& server)  {
//
// }

//changer std::vector<std::vector<std::string> > pass std::vector<std::vector> pass
//faire un preparsing des element a utiliser dans la fonction


void Pass::execute(Client* client, std::vector<std::string>  pass){
	//securite longueur etout si RFC
	if (!client)
	{
		std::cout << "[DEBUG] CLIENT is NULL !" << std::endl;
		//send un msg au client
		// client->setBufferOut("CLIENT is NULL !");
		return;
	}
	if (pass.empty() || pass.size() < 2)
	{
		std::cout << "[DEBUG]: password empty" << std::endl;
		//send un msg au client
		return;
	}

	std::string passWord = pass[0];

	if (client->isRegistered())
	{
		std::cout << "[DEBUG]: Already register" << std::endl;
		//send un msg au client
		return;
	}
	if (passWord != this->_server.getPass())
	{
		std::cout << "[DEBUG]: password incorrect" << std::endl;
		//send un msg au client
		return;
	}
	client->setAuth(true);
}

	Pass::~Pass(){}
