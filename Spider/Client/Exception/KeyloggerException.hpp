#ifndef			KEYLOGGER_EXCEPTION_HPP
# define		KEYLOGGER_EXCEPTION_HPP

# include		<iostream>
# include		"ProgException.hpp"

namespace spider
{

	namespace exception
	{
		class			KeyloggerException : public ProgException
		{
		public:
			KeyloggerException(const std::string& e) throw();
			KeyloggerException() throw();
			virtual	~KeyloggerException() throw();
		};

	}

}

#endif			/* KEYLOGGER_HPP */