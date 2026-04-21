#include "Commands.hpp"

// Commands::Commands(){}
// Commands::Commands(Commands const &src) { (void)src; }

Commands::Commands(Server& server) : _server(server){}
Commands::~Commands() {}
Commands &Commands::operator=(Commands const &rhs) {(void)rhs;}

void Commands::parsingMessage(std::string) {}
void Commands::execute() {}
void Commands::errorMessage(size_t errorValue) {}
