#include "Commands.hpp"

Commands::Commands() {}
Commands::Commands(Commands const &src) { (void)src; }
Commands::~Commands() {}
Commands &Commands::operator=(Commands const &rhs) {(void)rhs;}

size_t Commands::parsingMessage(std::string) {return 0;}
size_t Commands::execute(void) {return 0;}
void Commands::errorMessage(size_t ErrorValue) {return 0};
