#ifndef USING_CLASS_HPP_
# define USING_CLASS_HPP_
# include <memory>
# include <boost/asio.hpp>

namespace spider {
enum Type_e {
  COMMAND,
  LOGINPUT,
  LOGMOUSE
};
}

template <class T>
using Sptr		= std::shared_ptr<T>;
template <class T>
using Uptr		= std::unique_ptr<T>;
using BoostSocket = boost::asio::ip::tcp::socket;

using RawPacket = std::vector<char>;
using t_readHandler = std::function<void(size_t)>;
using t_writeHandler = std::function<void(size_t)>;
using t_errorHandler = std::function<void()>;


#endif /* USING_CLASS_HPPH */