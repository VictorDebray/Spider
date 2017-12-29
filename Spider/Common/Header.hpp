#ifndef HEADER_HPP_
# define HEADER_HPP_

# include "UsingClass.hpp"
# include <boost/serialization/access.hpp>

namespace spider
{
struct Header
{
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int /*version*/)
  {
	  ar & magicNumber_;
	  ar & dataSize_;
	  ar & type_;
  }

  int				magicNumber_;
  size_t			dataSize_;
  Type_e			type_;

  Header() :  magicNumber_(12345), dataSize_(), type_() {};
  Header(size_t dataSize, Type_e type, int magicNumber = 12345)
		  : magicNumber_(magicNumber), dataSize_(dataSize),
			type_(type) {};
  void print();
};
}

#endif // !HEADER_HPP_
