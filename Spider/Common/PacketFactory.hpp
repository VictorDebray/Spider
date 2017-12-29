#ifndef PACKETFACTORY_HPP_
# define PACKETFACTORY_HPP_

# include <string>

# include "Queue.hpp"
# include "AData.hpp"
# include "Command.hpp"
# include "Serialization.hpp"

namespace spider
{
	class PacketFactory
	{
	private:
		DataQueueSP		_dataQueue;
		SendingQueueSP	_sendingQueue;
	  	Serialization	_serial;

	public:
	  PacketFactory() = default;
	  PacketFactory(DataQueueSP dataQueue, SendingQueueSP sendingQueue);
	  ~PacketFactory();

		void		run();

	 private:
	  Sptr<RawPacket> genSerializedHeader(size_t size, Type_e type);
	  Sptr<RawPacket> genSerializedBody(Sptr<AData> data);

	  template <class OutType, class MotherType>
	  Sptr<RawPacket> serializeData(Sptr<MotherType> data)
	  {
		  auto obj = std::dynamic_pointer_cast<OutType>(data);
		  Sptr<RawPacket> vectorSerialized = _serial.serialize<OutType>(*obj);
		  return vectorSerialized;
	  };

	  template <class OutType>
	  Sptr<OutType> derializeData(Sptr<RawPacket> serializedPacket)
	  {
		  auto deserLog = _serial.deserialize<OutType>(*serializedPacket);
		  return deserLog;
	  };
	};
}

#endif // !PACKETFACTORY_HPP_