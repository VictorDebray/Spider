#include "NetworkException.hpp"

namespace spider
{

	namespace exception
	{

		NetworkException::NetworkException(const std::string& message) throw() :
			ProgException("NetworkException: " + message)
		{
		}

		NetworkException::NetworkException() throw() :
			ProgException("NetworkException")
		{
		}

		NetworkException::~NetworkException() throw()
		{
		}

	}

}