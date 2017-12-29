#ifndef CURRENT_SERVER_HPP
# define CURRENT_SERVER_HPP

# include <iostream>
# include <cstddef>
# include <boost/asio.hpp>
# include <system_error>
# include "NetworkException.hpp"
# include <string>
# include <deque>
# include "Queue.hpp"

namespace spider
{

	namespace client
	{

		class CurrentServer : public std::enable_shared_from_this<CurrentServer>
		{
		private:
			using tcp = boost::asio::ip::tcp;

			static const short			_MSG_MAX_LENGTH;
			static const bool			_ERROR;
			static const bool			_SUCCESS;

			std::string							_ip;
			std::string							_port;
			tcp::endpoint						_endpoint;
			boost::asio::io_service				_ioService;
			tcp::socket							_socket;
			boost::asio::io_service::strand		_strand;

			boost::asio::streambuf		_recBuf;
			std::deque<std::string>		_recQueue;
			SendingQueueSP				_sendingQueue;

			void				connect();
			void				send();
			void				sendBody(const boost::system::error_code& error);
			void				startPacketSend();
			void				sendHandler(const boost::system::error_code& error);
			void				receive();
			void				receiveHandler(const boost::system::error_code& error,
											   std::size_t bytesTransferred);
		public:
			CurrentServer(const SendingQueueSP& sendingQueue,
						  const std::string& ip = "",
						  const std::string& port = "");
			~CurrentServer();

			bool				isOnline() const;
			void				start();
			void				run();
			
		};

	}
}

#endif /* !CURRENT_SERVER_HPP */