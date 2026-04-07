#include "Serveur.hpp"

Serveur::Serveur() : name("Default"), channels(0) {}
Serveur::Serveur(const Serveur& copy)  : name(copy.name), channels(copy.channels) {}
Serveur& Serveur::operator=(const Serveur& other){
	if (this != &other)
	{
		this->name = other.name;
		this->channels = other.channels;
	}
	return(*this);
}

void Serveur::addClient(Client* c){
	(void) c;
	std::cout << "fontion addClient Serveur";
}
void Serveur::removeClient(Client* c){
	(void)c;
	std::cout << "fontion removeClient Serveur";

}
void Serveur::broadcast(const std::string& msg){
	(void)msg;
	std::cout << "fontion broadcast Serveur";
}

Serveur::~Serveur(){}
