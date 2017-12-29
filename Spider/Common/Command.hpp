#ifndef COMMAND_HPP_
# define COMMAND_HPP_
# include <boost/serialization/access.hpp>
# include <boost/serialization/base_object.hpp>

# include "AData.hpp"

namespace spider
{
	class Command : public AData
	{
	protected:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /*version*/)
		{
          ar & boost::serialization::base_object<AData>(*this);
          ar & message_;
		}

		std::string	message_;

	public:
		Command() : AData(), message_("") {}
		Command(const std::string & id, int timeStamp, const std::string& message) :
			AData(id, timeStamp, COMMAND), message_(message) {}
		~Command() override = default;
	  void print();

		const std::string& getMessage() const { return (message_); }
	};
}

#endif /* !COMMAND_HPP_ */