#ifndef			NETWORK_EXCEPTION_HPP
# define		FILE_MANAGER_EXCEPTION_HPP

# include		<iostream>
# include		"ProgException.hpp"

namespace spider
{

	namespace exception
	{
		class			NetworkException : public ProgException
		{
		public:
			NetworkException(const std::string& e) throw();
			NetworkException() throw();
			virtual	~NetworkException() throw();
		};

	}

}

#endif	