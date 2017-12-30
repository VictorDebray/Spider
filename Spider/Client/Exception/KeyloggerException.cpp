#include "KeyloggerException.hpp"

namespace spider
{

	namespace exception
	{

		KeyloggerException::KeyloggerException(const std::string& message) throw() :
			ProgException("FileManagerException: " + message)
		{
		}

		KeyloggerException::KeyloggerException() throw() :
			ProgException("FileManagerException")
		{
		}

		KeyloggerException::~KeyloggerException() throw()
		{
		}

	}

}