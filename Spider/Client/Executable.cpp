#include "Executable.hpp"

namespace spider
{
	namespace client
	{

		Executable::Executable(std::string const &name)
			: _name(name)
		{}

		Executable::~Executable()
		{}

		bool	Executable::createRegistryKey(const HKEY hkey, const std::string &pathToKey, const std::string &name) const
		{
			DWORD	lpdwDisposition = 3;
			LPCTSTR	lpSubKey = TEXT(pathToKey.c_str());
			bool	ret = true;
			HKEY	hkey2;
			TCHAR	szPath[MAX_PATH];

			GetModuleFileName(NULL, szPath, MAX_PATH);
			LPCTSTR data = TEXT(szPath);
			size_t lenght = strlen(data);
			if (RegCreateKeyEx(hkey, lpSubKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey2, &lpdwDisposition) != ERROR_SUCCESS)
				return false;
			if (RegSetValueEx(hkey2, _name.c_str(), 0, REG_SZ, (LPBYTE)data, (DWORD)lenght) != ERROR_SUCCESS)
				ret = false;
			RegCloseKey(hkey2);
			return ret;
		}

		void	Executable::createAutoProcess() const
		{
			if (createRegistryKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", _name) != true)
				throw std::invalid_argument("createRegistryKey failed: " + std::to_string(__LINE__)); //TODO: Change for custom
		}

		std::string		Executable::getName() const
		{
			return (_name);
		}
	}
}
