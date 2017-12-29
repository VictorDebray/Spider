#include "SpiderClient.hpp"
#include "SpiderNetwork.hpp"
#include "Queue.hpp"


namespace spider
{
SpiderClient::SpiderClient(Sptr<::myboost::asio::Connection> sock, SpiderNetwork &net,
                           Sptr<Serialization> serialization, ReceivedQueueSP queue,
                           CommandQueueSP com)
    : serialization_(serialization),
      readBuff_(),
      writeBuffPair_(),
      socket_(std::move(sock)),
      network_(net),
      receivedQueue_(queue),
      commandQueue_(com)
{
  auto headerSp = std::make_shared<Header>(12515, COMMAND);
  Sptr<RawPacket> header = serialization_->serialize<Header>(*headerSp);
  headerSize_ = header->size();
  readBuff_.resize(headerSize_);
}

void SpiderClient::spy()
{
  std::weak_ptr<SpiderClient> self(shared_from_this());
  std::shared_ptr<SpiderClient> nwself(shared_from_this());
  socket_->async_error(std::bind([this](std::weak_ptr<SpiderClient> lself) {
    if (auto sself = lself.lock())
    {
      network_.removeSpider(sself);
    }
  }, self));
  startRead();
}

void SpiderClient::startRead()
{
  socket_->async_read(readBuff_, headerSize_, [me=shared_from_this()] (size_t csize) {
    if (csize <= 0) {
      me->startWrite();
      return;
    }
    auto headerVec = me->serialization_->deserialize<Header>(me->readBuff_);
    me->handleReadBody(headerVec->dataSize_, headerVec->type_);
  });
}

void SpiderClient::handleReadBody(size_t size, Type_e type)
{
  readBuff_.clear();
  readBuff_.resize(size);
  std::fill(readBuff_.begin(), readBuff_.end(), 0);
  socket_->async_read(readBuff_, size, [me=shared_from_this(), type] (size_t /*csize*/) {
    me->handleSaveBody(type);
  });
}

void SpiderClient::handleSaveBody(Type_e type)
{
  network_.getIoService()->post(
      network_.getReceiveStrand().wrap(
          [me=shared_from_this(), type] ()
          {
            me->receivedQueue_->queue_.push(std::make_pair(type, me->readBuff_));
            me->startRead();
          }));
}

void SpiderClient::startWrite()
{
  network_.getIoService()->post(
      network_.getCommandStrand().wrap([me=shared_from_this()] ()
                        {
                          if (!me->commandQueue_->queue_.empty()) {
                            me->handleWriteHeader();
                          } else {
                            me->startRead();
                          }
                        }));
}

void SpiderClient::handleWriteHeader()
{
  std::fill(writeBuffPair_.first.begin(), writeBuffPair_.first.end(), 0);
  std::fill(writeBuffPair_.second.begin(), writeBuffPair_.second.end(), 0);
  std::pair<RawPacket, RawPacket> _write(std::move(commandQueue_->queue_.front()));
  socket_->async_write(writeBuffPair_.first, [me=shared_from_this()](size_t writeSize)
  {
    if (writeSize <= 0)
      return;
    me->handleWriteCommand();
  });
}


void SpiderClient::handleWriteCommand()
{
  socket_->async_write(writeBuffPair_.second, [me=shared_from_this()](size_t writeSize)
  {
    if (writeSize <= 0)
      return;
    me->startRead();
  });
}
}
