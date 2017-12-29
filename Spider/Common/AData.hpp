#ifndef ADATA_HPP_
# define ADATA_HPP_

# include "UsingClass.hpp"
# include <boost/serialization/access.hpp>
# include <string>

namespace spider
{
class AData
{
 protected:
  friend class boost::serialization::access;

  template<class Archive>

  void serialize(Archive & ar, const unsigned int /*version*/)
  {
	  ar & id_;
	  ar & timeStamp_;
	  ar & Type_;
  }

  std::string			id_;
  int					timeStamp_;
  Type_e				Type_;

 public:
  AData() :
		  id_(""),
		  timeStamp_(0)
  {}

  AData(const std::string& id, int timeStamp, Type_e type) :
		  id_(id),
		  timeStamp_(timeStamp),
		  Type_(type)
  {}

  virtual ~AData() = default;
  void print();

  void		          setId(const std::string& id) { id_ = id; }
  const std::string&  getId() const { return(id_); }
  int			      getTimeStamp() const { return(timeStamp_); }
  Type_e		      getType() const { return(Type_); }
};
}

#endif // !ADATA_HPP_