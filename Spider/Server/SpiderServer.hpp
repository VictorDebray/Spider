#ifndef SPIDER_SERVER_HPP_
# define SPIDER_SERVER_HPP_

# include <string>
# include <thread>
# include <atomic>
# include <memory>
# include <cstdint>
# include <unordered_map>

# include "MongoConnector.hpp"
# include "SpiderNetwork.hpp"

namespace spider
{
  class SpiderNetwork;
}

namespace spider
{
  class SpiderServer
  {
   private:
    using deserialFunc = Sptr<spider::AData> (SpiderServer::*)(RawPacket &);

    Sptr<Serialization> serialization_;
    Sptr<MongoConnector> mongoConnector_;
    ReceivedQueueSP receivedQueue_;
    CommandQueueSP commandQueue_;
    Sptr<SpiderNetwork> network_;
    boost::asio::io_service::strand		receiveStrand_;
    boost::asio::io_service::strand		commandStrand_;
    std::thread                         deserializerThread_;
    std::unordered_map<Type_e, deserialFunc> deserialFuncTab_;

   public:
    static const uint16_t defaultPort = 12345;

   public:
    explicit SpiderServer(uint16_t port = defaultPort) noexcept;
    ~SpiderServer() noexcept;

   public:
    void run();

   private:
    void handleCommand();

   private:
    void deserializeHandler();
    Sptr<spider::AData> deserialLogMouse(RawPacket &rawPacket);
    Sptr<spider::AData> deserialLogInput(RawPacket &rawPacket);
  };
}

#endif /* SPIDER_SERVER_HPP_ */