#include <iostream>

#include "SpiderServer.hpp"

int	main(int ac, char **av)
{
  try
    {
      if (ac == 2) {
        std::string portString = av[1];
        if (std::all_of(portString.begin(), portString.end(), ::isdigit)) {
          int port = std::stoi(portString);
          if (port > 1024 || port < 65535)
            spider::SpiderServer server(12345);
          else
            std::cout << "Please enter a port between 1024 and 65535." << std::endl;
        } else
          std::cout << "The port must be digit only." << std::endl;
      } else
        std::cout << "HELP: ./server [PORT NUMBER 1024-65535]." << std::endl;
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
