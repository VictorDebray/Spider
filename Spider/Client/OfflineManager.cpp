#include <iostream>
#include "PacketLogger.hpp"
#include "OfflineManager.hpp"

namespace spider
{
	namespace client
	{

		OfflineManager::OfflineManager(SendingQueueSP& sendingQueue) :
			_sendingQueue(sendingQueue),
			_fileManager("spider.data")
		{}

		OfflineManager::~OfflineManager()
		{}

		void OfflineManager::stock()
		{
			std::cout << "Server offline. Preparing to store data in cache." << std::endl;
			std::lock_guard<std::mutex>	guard(_sendingQueue->_mutex);

			if (!_sendingQueue->_sendingQueue.empty()) {
				archive(_sendingQueue->_sendingQueue.front().first);
				archive(_sendingQueue->_sendingQueue.front().second);
				_sendingQueue->_sendingQueue.pop();
			}
		}

		void OfflineManager::pop()
		{
			std::cout << "Server online. Preparing to send stored files." << std::endl;
			unarchive();
			_fileManager.removeFile();
		}

		void OfflineManager::archive(const std::shared_ptr<RawPacket>& msg)
		{
			std::cout << "Archiving packet: ";
			packetLogger(msg);

			try {
				char *tab = new char[msg->size()];
				int i;
				for (i = 0; i < msg->size(); i++) {
					tab[i] = msg->at(i);
				}
				tab[i] = 0;
				_fileManager.writeBinary(tab, msg->size());

			} catch (const exception::FileManagerException& e) {
				std::cerr << e.what() << std::endl;
			}
		}

		void OfflineManager::unarchive()
		{
			Sptr<RawPacket>	rawPacket;
			Sptr<RawPacket>	nullableBody;

			rawPacket = std::make_shared<RawPacket>(_fileManager.readBinary());
			std::cout << "Unarchiving packet: ";
			packetLogger(rawPacket);

			std::lock_guard<std::mutex> guard(_sendingQueue->_mutex);

			_sendingQueue->_sendingQueue.push({rawPacket, nullableBody});
			
		}
	}
}