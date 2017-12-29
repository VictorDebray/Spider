#ifndef FILE_MANAGER_HPP
# define FILE_MANAGER_HPP

# include <iostream>
# include <fstream>
# include <queue>
# include "FileManagerException.hpp"
# include "AData.hpp"
# include "Queue.hpp"

namespace spider
{
	namespace client
	{
		class FileManager
		{
		public:
			enum Mode
			{
				UNINITIALIZED,
				STREAM_BINARY_IN,
				STREAM_BINARY_OUT,
				STREAM_IN,
				STREAM_OUT
			};


		private:
			std::fstream	_file;
			std::string		_path;
			Mode			_mode;

			void			throwExcept(const std::string& msg);

		public:
			FileManager(const std::string& path = "");
			~FileManager();

			void				changeMode(const Mode mode);
			void				removeFile();
			bool				fileExists();
			void				writeBinary(char *msg, size_t size);
			std::vector<char>	readBinary();
			void				write(const std::string& str);
			std::string			read();
		};
	}
}

#endif /* !FILE_MANAGER_HPP */
