#ifndef SERIALIZATION_HPP_
# define SERIALIZATION_HPP_

# include <sstream>
# include <boost/iostreams/stream.hpp>
# include <boost/archive/text_oarchive.hpp>
# include <boost/archive/text_iarchive.hpp>
# include <boost/serialization/export.hpp>
# include <boost/archive/binary_oarchive.hpp>
# include <boost/archive/binary_iarchive.hpp>
# include "UsingClass.hpp"
# include "ContainerDevice.hpp"

namespace spider {
class Serialization {
 public:
  Serialization() = default;
  ~Serialization() = default;

  template<class C>
  Sptr<RawPacket> serialize(C act) {
    Sptr<RawPacket> raw_msg_ptr = std::make_shared<std::vector<char>>();

    typedef spider::myboost::ContainerDevice<RawPacket> io_device_type;
    boost::iostreams::stream<io_device_type> io(*raw_msg_ptr);

    boost::archive::text_oarchive archive(io);
    archive & act;

    return raw_msg_ptr;
  };

  template<class C>
  Sptr<C> deserialize(std::vector<char> &raw_msg) {
    typedef spider::myboost::ContainerDevice<std::vector<char> > io_device_type;
    boost::iostreams::stream<io_device_type> io(raw_msg);

    auto obj = std::make_shared<C>();
    boost::archive::text_iarchive archive(io);
    archive & *obj;
    return obj;
  }
};
}

#endif /* SERIALIZATION_HPP_ */