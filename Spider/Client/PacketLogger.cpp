#include <iostream>
#include "PacketLogger.hpp"

namespace spider
{
	void packetLogger(const Sptr<RawPacket>& msg)
	{
		for (auto i = msg->begin(); i != msg->end(); ++i)
			std::cout << *i << ' ';
		std::cout << std::endl;
	}
}