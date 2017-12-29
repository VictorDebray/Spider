#include "ConfigManager.hpp"

namespace spider
{
	namespace client
	{
		ConfigManager::ConfigManager() :
			_file("spider.conf")
		{
			if (_file.is_open()) {
				std::getline(_file, _dns);
				std::getline(_file, _port);
			} else {
				std::cerr << "Can't open configuration file (spider.conf). Default configuration activated." << std::endl;
				_dns = "spidercochon.ddns.net";
				_port = "12345";
			}
		}

		ConfigManager::~ConfigManager()
		{
			_file.close();
		}

		const std::string& ConfigManager::getDns() const
		{
			return _dns;
		}

		const std::string& ConfigManager::getPort() const
		{
			return _port;
		}
	}
}