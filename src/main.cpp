#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int main()
{
    //ARGC et ARGV RECUPERER PORT ET PASSWORD

    int port = 6667;
    std::string password = "chef";
    Server myServer(port, password);
    try
    {
        myServer.init();
        myServer.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
