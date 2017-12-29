#ifndef			FILE_MANAGER_EXCEPTION_HPP
# define		FILE_MANAGER_EXCEPTION_HPP

# include		<iostream>
# include		"ProgException.hpp"

namespace spider
{

	namespace exception
	{
		class			FileManagerException : public ProgException
		{
		public:
					FileManagerException(const std::string& e) throw();
					FileManagerException() throw();
			virtual	~FileManagerException() throw();
		};

	}

}

#endif			/* FILE_MANAGER_HPP */