#pragma once

#include "../Common.h"

#include "../app/WindowSettings.h"
#include <SFML/Window/Keyboard.hpp>

#ifdef _WIN32
#define __WIN32
#endif // WIN32

#ifdef __WIN32
	#include <Windows.h>
#endif // __WIN32

#include <cstring>

constexpr uint LEVEL_FATAL = 0;
constexpr uint LEVEL_ERROR = 1;
constexpr uint LEVEL_WARN  = 2;
constexpr uint LEVEL_INFO  = 3;

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return string("Can't convert (") + typeid(T).name() + string(")! (to_string)");
	}
}

// To be honest, no idea what half of this is doing. Not my code..
// https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/utils/Log.h
namespace Log
{
	static char to_string_buffer[1024 * 10];
	static char sprintf_buffer[1024 * 10];

	template <class T>
	struct has_iterator
	{
		template<class U> static char(&test(typename U::iterator const*))[1];
		template<class U> static char(&test(...))[2]{ return; }
		static const bool value = (sizeof(test<T>(0)) == 1);
	};
	
	template <typename T>
	static const char* to_string_internal(const T& v, const std::true_type& ignored)
	{
		sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
		return to_string_buffer;
	}

	template <typename T>
	static const char* to_string_internal(const T& t, const std::false_type& ignored)
	{
		auto x = std::to_string(t);
		return strcpy(to_string_buffer, x.c_str());
	}

	template <typename T>
	static const char* to_string(const T& t)
	{
		return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
	}

	template <>
	static const char* to_string<char>(const char& t)
	{
		return &t;
	}

	template <>
	static const char* to_string<char*>(char* const& t)
	{
		return t;
	}

	template <>
	static const char* to_string<unsigned char const*>(unsigned char const* const& t)
	{
		return (const char*)t;
	}

	template <>
	static const char* to_string<const char*>(const char* const& t)
	{
		return t;
	}

	template <>
	static const char* to_string<std::string>(const std::string& t)
	{
		return t.c_str();
	}

	template <>
	static const char* to_string<bool>(const bool& t)
	{
		return t ? "true" : "false";
	}

	template<typename X, typename Y>
	static const char* to_string(const std::pair<typename X, typename Y>& v)
	{
		sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
		return to_string_buffer;
	}

	template <typename First>
	static void print_log_internal(char* buffer, int32& position, First&& first)
	{
		const char* formatted = Log::to_string<First>(first);
		int32 length = strlen(formatted);
		memcpy(&buffer[position], formatted, length);
		position += length;
	}

	template <typename First, typename... Args>
	static void print_log_internal(char* buffer, int32& position, First&& first, Args&&... args)
	{
		const char* formatted = Log::to_string<First>(first);
		int32 length = strlen(formatted);
		memcpy(&buffer[position], formatted, length);
		position += length;
		if (sizeof...(Args))
			print_log_internal(buffer, position, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void logMessage(int32 level, bool newline, Args... args)
	{
		char buffer[1024 * 10];
		int32 position = 0;
		print_log_internal(buffer, position, std::forward<Args>(args)...);

		if (newline)
			buffer[position++] = '\n';

		buffer[position] = 0;
		
		// Windows console supports colors :)
#ifdef __WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (level)
		{
		case LEVEL_WARN:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break; 
		case LEVEL_ERROR:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break; 
		case LEVEL_FATAL:
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;	
		}
#endif // __WIN32
		printf("%s", buffer);
#ifdef __WIN32
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
#endif // __WIN32
	}
}

// Define custom "to_string" here
namespace Log
{
	// Example:
	template<>
	static const char* to_string<WindowSettings>(const WindowSettings& v)
	{
		std::string string = std::string("WindowSettings: (") + to_string(v.width) + " x " + to_string(v.height) + ", Fullscreen: "
			+ to_string(v.fullscreen) + ", VSync: " + to_string(v.vsync) + ")";
		char* result = new char[string.length()];
		strcpy(result, &string[0]);
		return result;
	}

	template<>
	static const char* to_string<sf::Keyboard::Key>(const sf::Keyboard::Key& v)
	{
		std::string string = "-1";
		// C++17 PLS ENUM.PARSE
		switch (v)
		{
		case sf::Keyboard::A:
			string = "A";
			break;
		case sf::Keyboard::B:
			string = "B";
			break;
		case sf::Keyboard::C:
			string = "C";
			break;
		case sf::Keyboard::D:
			string = "D";
			break;
		case sf::Keyboard::E:
			string = "E";
			break;
		case sf::Keyboard::F:
			string = "F";
			break;
		case sf::Keyboard::G:
			string = "G";
			break;
		case sf::Keyboard::H:
			string = "H";
			break;
		case sf::Keyboard::I:
			string = "I";
			break;
		case sf::Keyboard::J:
			string = "J";
			break;
		case sf::Keyboard::K:
			string = "K";
			break;
		case sf::Keyboard::L:
			string = "L";
			break;
		case sf::Keyboard::M:
			string = "M";
			break;
		case sf::Keyboard::N:
			string = "N";
			break;
		case sf::Keyboard::O:
			string = "O";
			break;
		case sf::Keyboard::P:
			string = "P";
			break;
		case sf::Keyboard::Q:
			string = "Q";
			break;
		case sf::Keyboard::R:
			string = "R";
			break;
		case sf::Keyboard::S:
			string = "S";
			break;
		case sf::Keyboard::T:
			string = "T";
			break;
		case sf::Keyboard::U:
			string = "U";
			break;
		case sf::Keyboard::V:
			string = "V";
			break;
		case sf::Keyboard::W:
			string = "W";
			break;
		case sf::Keyboard::X:
			string = "X";
			break;
		case sf::Keyboard::Y:
			string = "Y";
			break;
		case sf::Keyboard::Z:
			string = "Z";
			break;
		case sf::Keyboard::Num0:
			string = "Num0";
			break;
		case sf::Keyboard::Num1:
			string = "Num1";
			break;
		case sf::Keyboard::Num2:
			string = "Num2";
			break;
		case sf::Keyboard::Num3:
			string = "Num3";
			break;
		case sf::Keyboard::Num4:
			string = "Num4";
			break;
		case sf::Keyboard::Num5:
			string = "Num5";
			break;
		case sf::Keyboard::Num6:
			string = "Num6";
			break;
		case sf::Keyboard::Num7:
			string = "Num7";
			break;
		case sf::Keyboard::Num8:
			string = "Num8";
			break;
		case sf::Keyboard::Num9:
			string = "Num9";
			break;
		case sf::Keyboard::Escape:
			string = "Escape";
			break;
		case sf::Keyboard::LControl:
			string = "LControl";
			break;
		case sf::Keyboard::LShift:
			string = "LShift";
			break;
		case sf::Keyboard::LAlt:
			string = "LAlt";
			break;
		case sf::Keyboard::LSystem:
			string = "LSystem";
			break;
		case sf::Keyboard::RControl:
			string = "RControl";
			break;
		case sf::Keyboard::RShift:
			string = "RShift";
			break;
		case sf::Keyboard::RAlt:
			string = "RAlt";
			break;
		case sf::Keyboard::RSystem:
			string = "RSystem";
			break;
		case sf::Keyboard::Menu:
			string = "Menu";
			break;
		case sf::Keyboard::LBracket:
			string = "LBracket";
			break;
		case sf::Keyboard::RBracket:
			string = "RBracket";
			break;
		case sf::Keyboard::SemiColon:
			string = "SemiColon";
			break;
		case sf::Keyboard::Comma:
			string = "Comma";
			break;
		case sf::Keyboard::Period:
			string = "Period";
			break;
		case sf::Keyboard::Quote:
			string = "Quote";
			break;
		case sf::Keyboard::Slash:
			string = "Slash";
			break;
		case sf::Keyboard::BackSlash:
			string = "BackSlash";
			break;
		case sf::Keyboard::Tilde:
			string = "Tilde";
			break;
		case sf::Keyboard::Equal:
			string = "Equal";
			break;
		case sf::Keyboard::Dash:
			string = "Dash";
			break;
		case sf::Keyboard::Space:
			string = "Space";
			break;
		case sf::Keyboard::Return:
			string = "Return";
			break;
		case sf::Keyboard::BackSpace:
			string = "BackSpace";
			break;
		case sf::Keyboard::Tab:
			string = "Tab";
			break;
		case sf::Keyboard::PageUp:
			string = "PageUp";
			break;
		case sf::Keyboard::PageDown:
			string = "PageDown";
			break;
		case sf::Keyboard::End:
			string = "End";
			break;
		case sf::Keyboard::Home:
			string = "Home";
			break;
		case sf::Keyboard::Insert:
			string = "Insert";
			break;
		case sf::Keyboard::Delete:
			string = "Delete";
			break;
		case sf::Keyboard::Add:
			string = "Add";
			break;
		case sf::Keyboard::Subtract:
			string = "Subtract";
			break;
		case sf::Keyboard::Multiply:
			string = "Multiply";
			break;
		case sf::Keyboard::Divide:
			string = "Divide";
			break;
		case sf::Keyboard::Left:
			string = "Left";
			break;
		case sf::Keyboard::Right:
			string = "Right";
			break;
		case sf::Keyboard::Up:
			string = "Up";
			break;
		case sf::Keyboard::Down:
			string = "Down";
			break;
		case sf::Keyboard::Numpad0:
			string = "Numpad0";
			break;
		case sf::Keyboard::Numpad1:
			string = "Numpad1";
			break;
		case sf::Keyboard::Numpad2:
			string = "Numpad2";
			break;
		case sf::Keyboard::Numpad3:
			string = "Numpad3";
			break;
		case sf::Keyboard::Numpad4:
			string = "Numpad4";
			break;
		case sf::Keyboard::Numpad5:
			string = "Numpad5";
			break;
		case sf::Keyboard::Numpad6:
			string = "Numpad6";
			break;
		case sf::Keyboard::Numpad7:
			string = "Numpad7";
			break;
		case sf::Keyboard::Numpad8:
			string = "Numpad8";
			break;
		case sf::Keyboard::Numpad9:
			string = "Numpad9";
			break;
		case sf::Keyboard::F1:
			string = "F1";
			break;
		case sf::Keyboard::F2:
			string = "F2";
			break;
		case sf::Keyboard::F3:
			string = "F3";
			break;
		case sf::Keyboard::F4:
			string = "F4";
			break;
		case sf::Keyboard::F5:
			string = "F5";
			break;
		case sf::Keyboard::F6:
			string = "F6";
			break;
		case sf::Keyboard::F7:
			string = "F7";
			break;
		case sf::Keyboard::F8:
			string = "F8";
			break;
		case sf::Keyboard::F9:
			string = "F9";
			break;
		case sf::Keyboard::F10:
			string = "F10";
			break;
		case sf::Keyboard::F11:
			string = "F11";
			break;
		case sf::Keyboard::F12:
			string = "F12";
			break;
		case sf::Keyboard::F13:
			string = "F13";
			break;
		case sf::Keyboard::F14:
			string = "F14";
			break;
		case sf::Keyboard::F15:
			string = "F15";
			break;
		case sf::Keyboard::Pause:
			string = "Pause";
			break;
		}
		char* result = new char[string.length()];
		strcpy(result, &string[0]);
		return result;
	}
	//
}

#define LOG_FATAL(...) Log::logMessage(LEVEL_FATAL, true, "LOG:    ", __VA_ARGS__)
#define LOG_FATAL_APPEND(...) Log::logMessage(LEVEL_FATAL, false, __VA_ARGS__)

#define LOG_ERROR(...) Log::logMessage(LEVEL_ERROR, true, "LOG:    ", __VA_ARGS__)
#define LOG_ERROR_APPEND(...) Log::logMessage(LEVEL_ERROR, false, __VA_ARGS__)

#define LOG_WARN(...) Log::logMessage(LEVEL_WARN, true, "LOG:    ", __VA_ARGS__)
#define LOG_WARN_APPEND(...) Log::logMessage(LEVEL_WARN, false, __VA_ARGS__)

#define LOG_INFO(...) Log::logMessage(LEVEL_INFO, true, "LOG:    ", __VA_ARGS__)
#define LOG_INFO_APPEND(...) Log::logMessage(LEVEL_INFO, false, __VA_ARGS__)
