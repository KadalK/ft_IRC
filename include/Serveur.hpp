#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Channel.hpp"

class Serveur{
public:
	Serveur();
	Serveur(const Serveur& copy);
	Serveur& operator=(const Serveur& other);
	std::string name;
	std::vector <Channel*> channels;

	void addClient(Client* c);
	void removeClient(Client* c);
	void broadcast(const std::string& msg);
	~Serveur();
};

#endif