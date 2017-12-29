#include "CurrentServer.hpp"
#include "PacketLogger.hpp"

namespace spider
{
	namespace client
	{
		CurrentServer::CurrentServer(
			const SendingQueueSP& sendingQueue,
			const std::string& ip,
			const std::string& port) :
			_socket(_ioService),
			_ip(ip),
			_port(port),
			_strand(_ioService),
			_sendingQueue(sendingQueue)
		{
		}

		CurrentServer::~CurrentServer()
		{
			_socket.close();
		}

		bool CurrentServer::isOnline() const
		{
			return _socket.is_open();
		}

		void CurrentServer::start()
		{
			try {
				connect();
			} catch (const std::exception& e) {
				_socket.close();
				(void)e;
			}
		}

		void CurrentServer::connect()
		{
			tcp::resolver::query		query(_ip, _port);
			tcp::resolver				resolver(_ioService);
			boost::system::error_code	error;
			auto						it = resolver.resolve(query, error);

			// Resolve
			if (!error) {
				_endpoint = *it;
				std::cout << "Server IP: " << _endpoint.address()
						<< " - Port: " << _endpoint.port() << std::endl;
			} else {
				std::string invArg = "Can't resolve IP ("
					+ _ip + ") or Port ("
					+ _port + ") ("
					+ error.message()
					+ ")";
				throw exception::NetworkException(invArg);
			}

			// Connect
			if (isOnline()) {
				_socket.close();
			}
			_socket.connect(_endpoint);
		}

		void CurrentServer::run()
		{
			try {
				receive();
				startPacketSend();
				_ioService.run();
			} catch (const exception::ProgException& e) {
				_socket.close();
				(void)e;
			}
		}

		void CurrentServer::startPacketSend()
		{
			_ioService.post(_strand.wrap([me = shared_from_this()]()
			{
				if (me->_sendingQueue->_sendingQueue.size() > 0) {
					me->send();
				} else {
					me->startPacketSend();
				}
			}));
		}

		void CurrentServer::send()
		{
			if (!isOnline()) {
				throw exception::NetworkException("Send: Can't connect to server socket.");
			}

			async_write(_socket,
				boost::asio::buffer(*_sendingQueue->_sendingQueue.front().first, _sendingQueue->_sendingQueue.front().first->size()),
				_strand.wrap([me = shared_from_this()]
				(const boost::system::error_code& ec,
					std::size_t)
			{
				me->sendBody(ec);
			}));
		}

		void CurrentServer::sendBody(const boost::system::error_code& error)
		{
			if (!isOnline()) {
				throw exception::NetworkException("SendBody: Can't connect to server socket.");
			}

			std::cout << "Sending header package: ";
			packetLogger(_sendingQueue->_sendingQueue.front().first);

			async_write(_socket,
				boost::asio::buffer(*_sendingQueue->_sendingQueue.front().second, _sendingQueue->_sendingQueue.front().second->size()),
				_strand.wrap([me = shared_from_this()]
				(const boost::system::error_code& ec,
					std::size_t)
			{
				me->sendHandler(ec);
			}));
		}

		void CurrentServer::sendHandler(const boost::system::error_code& error)
		{
			if (error) {
				throw exception::NetworkException("SendHandler: " + error.message());
			} else {

				std::cout << "Sending body package: ";
				packetLogger(_sendingQueue->_sendingQueue.front().second);
				
				_sendingQueue->_sendingQueue.pop();
				startPacketSend();
			}
		}

		void CurrentServer::receive()
		{
			boost::asio::async_read(
				_socket,
				_recBuf,
				[me = shared_from_this()]
				(const boost::system::error_code& ec,
				std::size_t bytesXfer)
			{
				me->receiveHandler(ec, bytesXfer);
			});
		}

		void CurrentServer::receiveHandler(const boost::system::error_code& error,
										   std::size_t bytesTransferred)
		{
			if (error) {
				throw exception::NetworkException("Receive: " + error.message());
			} else {
				std::istream	stream(&_recBuf);
				std::string		packetString;
				std::cout << "DEBUG: Received: " << packetString << std::endl;
				
				stream >> packetString;
				_recQueue.push_back(packetString);

				receive();
			}
		}
	}
}