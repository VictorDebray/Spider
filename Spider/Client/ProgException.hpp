#ifndef			PROG_EXCEPTION_HPP
# define		PROG_EXCEPTION_HPP

# include <exception>
# include <string>

namespace spider
{

	namespace exception
	{

		class ProgException : public std::exception
		{
		private:
			std::string			_message;

		public:
								ProgException(const std::string& e) throw();
								ProgException() throw();
			virtual				~ProgException() throw();
			virtual const char	*what() const throw();
		};

	}

}

#endif			/* PROG_EXCEPTION_HPP */
