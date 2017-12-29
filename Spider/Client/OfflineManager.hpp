#pragma once

#include "Queue.hpp"
#include "FileManager.hpp"

namespace spider
{
	namespace client
	{
		class OfflineManager
		{
		private:
			SendingQueueSP	_sendingQueue;
			FileManager		_fileManager;

			void	archive(const std::shared_ptr<RawPacket>& msg);
			void	unarchive();

		public:
			OfflineManager() {}
			OfflineManager(SendingQueueSP&);
			~OfflineManager();

			void stock();
			void pop();
		};
	}
}