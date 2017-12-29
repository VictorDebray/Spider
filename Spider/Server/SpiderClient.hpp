#ifndef SPIDER_CLIENT_HPP_
# define SPIDER_CLIENT_HPP_

# include <memory>
# include <string>
# include <vector>

# include "Header.hpp"
# include "AData.hpp"
# include "Connection.hpp"
# include "Serialization.hpp"
# include "Queue.hpp"

namespace spider {
  class SpiderNetwork;
}

namespace spider
{
  class SpiderClient : public std::enable_shared_from_this<SpiderClient>
  {
   private:
    std::shared_ptr<Serialization> serialization_;
    RawPacket readBuff_;
    std::pair<RawPacket, RawPacket> writeBuffPair_;
    std::shared_ptr<::myboost::asio::Connection> socket_;
    SpiderNetwork &network_;
    ReceivedQueueSP receivedQueue_;
    CommandQueueSP commandQueue_;
    size_t headerSize_;


   public:
    SpiderClient(std::shared_ptr<::myboost::asio::Connection> sock,
	   SpiderNetwork &net, std::shared_ptr<Serialization> serialization_,
                 ReceivedQueueSP receivedQueue, CommandQueueSP commandQueue);

    SpiderClient(const SpiderClient &other) = delete;

    SpiderClient &operator=(const SpiderClient &other) = delete;

   public:
    void spy();

    void startRead();

    void startWrite();

    void handleReadBody(size_t size, Type_e type);
    void handleSaveBody(Type_e type);

    void handleWriteHeader();
    void handleWriteCommand();


  };
}

#endif /* SPIDER_CLIENT_HPP_ */
