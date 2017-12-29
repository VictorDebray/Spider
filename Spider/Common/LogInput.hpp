#ifndef LOGINPUT_HPP_
# define LOGINPUT_HPP_

# include <boost/serialization/access.hpp>
# include <boost/serialization/base_object.hpp>
# include <string>

# include "AData.hpp"

namespace spider
{
	class LogInput : public AData
	{
	protected:
		friend class boost::serialization::access;
	
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /*version*/)
		{
			ar & boost::serialization::base_object<AData>(*this);
			ar & windowName_;
			ar & input_;
		}

		std::string		windowName_;
		std::string		input_;
	
	public:
		LogInput() :
			AData(),
			windowName_(""),
			input_("")
		{}
		
		LogInput(const std::string& id, int timeStamp, const std::string& windowName, const std::string& input) :
			AData(id, timeStamp, LOGINPUT),
			windowName_(windowName),
			input_(input)
		{}
		
		~LogInput() override = default;
      void print();

		const std::string&		getWindowName() const { return (windowName_); }
		const std::string&		getInput() const { return (input_); }
	};
}

#endif // !LOGINPUT_HPP_