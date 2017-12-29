#ifndef SPIDER_NETWORK_HPP_
# define SPIDER_NETWORK_HPP_
# include <map>
# include <string>
# include <memory>
# include <set>

# include "Accept.hpp"
# include "SpiderClient.hpp"

namespace spider
{
  class SpiderNetwork
  {
   private:
    Sptr<::myboost::asio::Accept> acceptor_;
    Sptr<Serialization> serialization_;
    std::set<Sptr<SpiderClient>> clients_;
    ReceivedQueueSP receivedQueue_;
    CommandQueueSP commandQueue_;
    boost::asio::io_service::strand receiveStrand_;
    boost::asio::io_service::strand commandStrand_;


   public:
    SpiderNetwork(const std::string &addr, int port, Sptr<Serialization> serialization,
                  ReceivedQueueSP rec, CommandQueueSP com);
    ~SpiderNetwork() = default;

   public:
    void run();
    void stop();
    void addSpider(const Sptr<SpiderClient> &spider);
    void removeSpider(const Sptr<SpiderClient> &spider);
    Sptr<boost::asio::io_service> getIoService() const;
    boost::asio::io_service::strand &getReceiveStrand();
    boost::asio::io_service::strand &getCommandStrand();


   private:
    void startAccept();
    void acceptHandler(Sptr<::myboost::asio::Connection> newSock);
  };
}

#endif /* SPIDER_NETWORK_HPP_ */