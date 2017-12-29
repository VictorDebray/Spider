#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "FileManagerException.hpp"

namespace spider
{
	namespace client
	{
		class ConfigManager
		{
		private:
			std::string		_dns;
			std::string		_port;
			std::ifstream	_file;

		public:
			ConfigManager();
			~ConfigManager();

			const std::string&	getDns() const;
			const std::string&	getPort() const;
		};
	}
}