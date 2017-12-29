#ifndef _ASIO_SOCKET_HPP_
# define _ASIO_SOCKET_HPP_

# include <iostream>
# include <boost/asio.hpp>
# include "UsingClass.hpp"

namespace myboost::asio
{
class Connection
{
 private:
  t_errorHandler errorCall_;
//    boost::asio::ip::tcp
//    familyFromAddr(const boost::asio::ip::address &addr) const;

 protected:
  boost::asio::ip::tcp::socket socket_;
  bool connected_;

 public:
  explicit Connection(boost::asio::io_service &io_service);
  ~Connection() = default;

  void async_write(const std::vector<char> &data,
                   const t_writeHandler &callback);
  void async_read(std::vector<char> &buffer, size_t size,
                  const t_readHandler &callback);
  void async_error(const t_errorHandler &callback);

  boost::asio::ip::tcp::socket &getSocket();

  bool isConnected() const;

 protected:
  void onWrite(const t_writeHandler &callback,
               const boost::system::error_code &ec, size_t size);
  void
  onRead(const t_readHandler &callback, const boost::system::error_code &ec,
         size_t size);
};
}

#endif /* _ASIO_SOCKET_HPP_ */
