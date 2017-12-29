#include "FileManager.hpp"

namespace spider
{
	namespace client
	{
		FileManager::FileManager(const std::string& path) :
			_path(path)
		{
			_mode = UNINITIALIZED;
		}

		FileManager::~FileManager()
		{
			_file.close();
		}

		void FileManager::throwExcept(const std::string& msg)
		{
			throw exception::FileManagerException(msg);
		}

		void FileManager::changeMode(const Mode mode)
		{
			if (_mode == mode) {
				return;
			}
			if (_file.is_open()) {
				_file.close();
			}
			switch (mode) {
				case STREAM_BINARY_IN:
					_file.open(_path, std::ios::binary | std::ios::in | std::ios::app);
					_mode = STREAM_BINARY_IN;
					break;
				case STREAM_BINARY_OUT:
					_file.open(_path, std::ios::binary | std::ios::out | std::ios::app);
					_mode = STREAM_BINARY_OUT;
					break;
				case STREAM_IN:
					_file.open(_path, std::fstream::in | std::ios::app);
					_mode = STREAM_IN;
					break;
				case STREAM_OUT:
					_file.open(_path, std::fstream::out | std::ios::app);
					_mode = STREAM_OUT;
					break;
				default:
					break;
			}
		}

		void FileManager::removeFile()
		{
			if (remove(_path.c_str())) {
				throwExcept("Can't delete " + _path);
			}
		}

		void FileManager::writeBinary(char *msg, size_t size)
		{
			changeMode(Mode::STREAM_BINARY_OUT);
			if (_file.is_open()) {
				_file.write(msg, size);
			} else {
				throwExcept(_path + " is not open. Can't write in it.");
			}
		}

		std::vector<char> FileManager::readBinary()
		{
			changeMode(Mode::STREAM_BINARY_IN);

			std::vector<char> buffer((
				std::istreambuf_iterator<char>(_file)),
				(std::istreambuf_iterator<char>()));

			return buffer;
		}

		void FileManager::write(const std::string& str)
		{
			changeMode(Mode::STREAM_OUT);

			if (_file.is_open()) {
				_file << str;
			} else {
				throwExcept(_path + " is not open. Can't write in it.");
			}

		}

		std::string FileManager::read()
		{
			std::string line = "";

			changeMode(Mode::STREAM_IN);
			if (_file.is_open()) {
				std::getline(_file, line);
			}

			return line;
		}

		bool FileManager::fileExists()
		{
			struct stat buffer;
			return (stat(_path.c_str(), &buffer) == 0);
		}

	}
}