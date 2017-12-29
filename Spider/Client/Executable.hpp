#pragma once

#include <string>
#include <Windows.h>
#include <shellapi.h>

namespace spider
{
	namespace client
	{

		class Executable
		{
		public:
			Executable(std::string const& name = "Spider.exe");
			~Executable();
			void		createAutoProcess() const;
			bool		createRegistryKey(const HKEY, const std::string &, const std::string &) const;
			std::string	getName() const;

		private:
			std::string	_name;
		};
	}
}
