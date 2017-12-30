#include "FileManagerException.hpp"

namespace spider
{
	
	namespace exception
	{

		FileManagerException::FileManagerException(const std::string& message) throw() :
			ProgException("FileManagerException: " + message)
		{
		}

		FileManagerException::FileManagerException() throw() :
			ProgException("FileManagerException")
		{
		}

		FileManagerException::~FileManagerException() throw()
		{
		}

}

}