#include <iostream>
#include <string>
#include "Bot.hpp"


int main()
{
	Bot bot;

	std::string raw;

	std::cout << "Bot ready. Type message:\n";

	while (std::getline(std::cin, raw))
	{
		std::string response = bot.talk(raw);
		std::cout << "Monique: " << response << std::endl;
	}
	return 0;
}