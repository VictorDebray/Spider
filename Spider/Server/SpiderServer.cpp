#include <LogMouse.hpp>
#include <LogInput.hpp>
#include "SpiderServer.hpp"

namespace spider
{
SpiderServer::SpiderServer(uint16_t port) noexcept
    : serialization_(std::make_shared<Serialization>()),
      mongoConnector_(std::make_shared<MongoConnector>("localhost", "27017", "spider")),
      receivedQueue_(std::make_shared<ReceivedQueue>()),
      commandQueue_(std::make_shared<CommandQueue>()),
      network_(std::make_shared<SpiderNetwork>("0.0.0.0", port, serialization_,
                                               receivedQueue_, commandQueue_)),
      receiveStrand_(*network_->getIoService()),
      commandStrand_(*network_->getIoService()),
      deserializerThread_(&SpiderServer::deserializeHandler, this),
      deserialFuncTab_({
                           {LOGMOUSE, &SpiderServer::deserialLogMouse},
                           {LOGINPUT, &SpiderServer::deserialLogInput},
                       })
{
  this->run();
}

SpiderServer::~SpiderServer() noexcept
{
  deserializerThread_.join();
}

void SpiderServer::run()
{
//	inputThread_ = std::thread(&SpiderServer::handleInput, this);
  network_->run();
  std::cout << "SpiderServer shutdown." << std::endl;
}

void SpiderServer::deserializeHandler()
{
  std::cout << "Started deserializer.." << std::endl;
  while (true) {
    std::lock_guard<std::mutex> guard(receivedQueue_->_mutex);
    while (!receivedQueue_->queue_.empty()) {
      auto it = &receivedQueue_->queue_.front();
      Sptr<spider::AData> data = (this->*deserialFuncTab_[it->first])(it->second);
      mongoConnector_->insertInDB(data, it->first);
      receivedQueue_->queue_.pop();
    }
  }
}

Sptr<spider::AData> SpiderServer::deserialLogMouse(RawPacket &rawPacket)
{
  auto packet = serialization_->deserialize<LogMouse>(rawPacket);
  packet->print();
  return packet;
}

Sptr<spider::AData> SpiderServer::deserialLogInput(RawPacket &rawPacket)
{
  auto packet = serialization_->deserialize<LogInput>(rawPacket);
  packet->print();
  return packet;
}

void SpiderServer::handleCommand()
{
  try
  {
    std::string line;
    while (std::getline(std::cin, line))
    {
      if (line == "stop")
        network_->stop();
    }
    network_->stop(); //_quit = true;
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
}
