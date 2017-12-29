#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <queue>
# include <mutex>
# include "UsingClass.hpp"
# include "AData.hpp"

namespace spider
{	
	/*
	** Base queue class
	*/
	struct AQueue
	{
	public:
		std::mutex	_mutex;
	};

	/*
	** Data coming from WinAPI,
	** and to be prepared by the packetFactory
	*/
	struct DataQueue : public AQueue
	{
	public:
		std::queue<Sptr<AData>>		_dataQueue;
	};

	/*
	** Serialized strings coming from the packetFactory,
	** and to be sent (CurrentServer) or stocked (FileManager)
	*/
	struct SendingQueue : public AQueue
	{
	  std::queue<std::pair<Sptr<RawPacket>, Sptr<RawPacket>>>	_sendingQueue;
	};

	struct ReceivedQueue : public AQueue
	{
	  std::queue<std::pair<spider::Type_e, RawPacket>> 			queue_;
	};

	struct CommandQueue : public AQueue
	{
	  std::queue<std::pair<RawPacket /*header*/, RawPacket/*Command*/>> queue_;
	};
//using CommandQueueSP = Sptr<CommandQueue>;


	using DataQueueSP = std::shared_ptr<DataQueue>;
	using SendingQueueSP = std::shared_ptr<SendingQueue>;
	using ReceivedQueueSP = Sptr<ReceivedQueue>;
	using CommandQueueSP = Sptr<CommandQueue>;
}

#endif /* !QUEUE_HPP */