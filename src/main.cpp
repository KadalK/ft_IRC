#include <sstream>
#include "Server.hpp"
#include <iostream>
#include "Client.hpp"

bool g_isRunning = true;

void signal_handler(int signum)
{
    (void)signum;
	g_isRunning = false;
	std::cout << "\nThe server is closing..." << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);
    signal(SIGINT,signal_handler);
    signal(SIGQUIT,signal_handler);
    // faire une verif sur le password et le port (au niveau du format)
    std::stringstream ss(argv[1]);
    int port;
    ss >> port;
    std::string password = argv[2];
    Server myServer(port, password);
    try
    {
        myServer.init();
        myServer.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (1);
    }
    return 0;
}
