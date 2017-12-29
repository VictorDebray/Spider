#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "PacketFactory.hpp"
#include "Header.hpp"
#include "LogInput.hpp"
#include "LogMouse.hpp"

namespace spider {
PacketFactory::PacketFactory(DataQueueSP dataQueue, SendingQueueSP sendingQueue) :
    _dataQueue(dataQueue),
    _sendingQueue(sendingQueue) {}

PacketFactory::~PacketFactory() {}

Sptr<RawPacket> PacketFactory::genSerializedBody(Sptr<AData> data) {
  Sptr<RawPacket> serializedBody;
  switch (data->getType()) {
    case Type_e::COMMAND : {
      serializedBody = serializeData<Command, AData>(data);
      break;
    }
    case Type_e::LOGINPUT : {
      serializedBody = serializeData<LogInput, AData>(data);
      break;
    }
    case Type_e::LOGMOUSE : {
      serializedBody = serializeData<LogMouse, AData>(data);
      break;
    }
    default: {
      throw std::logic_error("Command type not found.");
    }
  }
  return serializedBody;
}

Sptr<RawPacket> PacketFactory::genSerializedHeader(size_t size, Type_e type) {
  auto header = std::make_shared<Header>(size, type);
  Sptr<RawPacket> serializedHeader = serializeData<Header, Header>(header);
  return serializedHeader;
}

void PacketFactory::run() {
  while (true) {
    if (!_dataQueue->_dataQueue.empty()) {
      try {
        auto body = _dataQueue->_dataQueue.front();
        Sptr<RawPacket> bodyRPacket = genSerializedBody(body);
        Sptr<RawPacket> headerRPacket = genSerializedHeader(bodyRPacket->size(), body->getType());

				std::lock_guard<std::mutex> guard1(_sendingQueue->_mutex);
				_sendingQueue->_sendingQueue.push({headerRPacket, bodyRPacket});
				std::lock_guard<std::mutex> guard2(_dataQueue->_mutex);
				_dataQueue->_dataQueue.pop();
			} catch (const std::exception &e){
				throw e;
			}
		}
		}
	}
}

