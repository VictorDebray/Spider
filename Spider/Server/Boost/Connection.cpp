/*
** SpiderServer for CLION in /clion_ide/
**
** Made by Victor Debray
** Login   <victor.debray@epitech.net>
**
** Started on  03/10/2017
** Last update 03/10/2017
*/

#include "Connection.hpp"

namespace myboost::asio
{
Connection::Connection(boost::asio::io_service &io_service)
    : socket_(io_service), connected_(false)
{

}

void Connection::async_write(const std::vector<char> &data,
                             const t_writeHandler &callback)
{
  auto f = std::bind(&Connection::onWrite, this, callback,
                     std::placeholders::_1, std::placeholders::_2);
  boost::asio::async_write(socket_, boost::asio::buffer(data), f);
}

void Connection::async_read(std::vector<char> &buffer, size_t size,
                            const t_readHandler &callback)
{
  auto f = std::bind(&Connection::onRead, this,
                     callback, std::placeholders::_1, std::placeholders::_2);
  boost::asio::async_read(socket_, boost::asio::buffer(buffer, size), boost::asio::transfer_at_least(1), f);
}

void Connection::async_error(const t_errorHandler &callback)
{
  errorCall_ = callback;
}

bool Connection::isConnected() const
{
  return connected_;
}

void Connection::onWrite(const t_writeHandler &callback,
                         const boost::system::error_code &ec, size_t size)
{
  if (ec) {
    connected_ = false;
    std::cerr << "Connection write" << size << ": " << ec.message() << std::endl;
    errorCall_();
  }
  else
  {
    callback(size);
  }
}

void Connection::onRead(const t_readHandler &callback,
                        const boost::system::error_code &ec, size_t size)
{
  if (ec)
  {
    connected_ = false;
    std::cerr << "Connection read " << size <<  ": " << ec.message() << std::endl;
    errorCall_();
  } else {
    callback(size);
  }
}

//  boost::asio::ip::tcp
//  Connection::familyFromAddr(const boost::asio::ip::address &addr) const
//  {
//    if (addr.is_v4())
//      return boost::asio::ip::tcp::v4();
//    else
//      if (addr.is_v6())
//	return boost::asio::ip::tcp::v6();
//    throw std::runtime_error("Family address is not v4 nor v6.");
//  }

boost::asio::ip::tcp::socket &Connection::getSocket()
{
  return socket_;
};
}
