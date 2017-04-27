﻿#pragma once

#include "../Common.h"

#include "../app/WindowSettings.h"

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
		const char* formatted = to_string<First>(first);
		int32 length = strlen(formatted);
		memcpy(&buffer[position], formatted, length);
		position += length;
	}

	template <typename First, typename... Args>
	static void print_log_internal(char* buffer, int32& position, First&& first, Args&&... args)
	{
		const char* formatted = to_string<First>(first);
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
