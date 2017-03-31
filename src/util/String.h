#pragma once

#include <memory>
#include <vector>
#include <cstdlib>

// Should fix gcc compiler errors
#include <cstring>

#include "Types.h"

typedef std::string String;

constexpr int STRINGFORMAT_BUFFER_SIZE = 10 * 1024;

namespace StringFormat {

	static char* s_buffer = new char[STRINGFORMAT_BUFFER_SIZE];;

	template<typename T>
	static String Hex(const T& input)
	{
		// Tell me if memset still gives compiler error @Hopson
		memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
		sprintf(s_buffer, "%02x", input);
		return String(s_buffer);
	}

	template<typename T>
	static String Hex(const T* input, uint size)
	{
		memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
		for (uint i = 0; i < size; i++)
			sprintf(s_buffer + i * 3, "%02x ", input[i]);
		return String(s_buffer);
	}

	static String Float(const float input, uint places = 2)
	{
		memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
		sprintf(s_buffer, "%.*f", places, input);
		return String(s_buffer);
	}

	template<typename T>
	static String toString(const T& input)
	{
		return std::to_string(input);
	}
};

std::vector<String> splitString(const String& string, const String& delimiters);
std::vector<String> splitString(const String& string, const char delimiter);
std::vector<String> tokenize(const String& string);
std::vector<String> getLines(const String& string);

const char* findToken(const char* str, const String& token);
const char* findToken(const String& string, const String& token);
int32 findStringPosition(const String& string, const String& search, uint offset = 0);
String stringRange(const String& string, uint start, uint length);
String removeStringRange(const String& string, uint start, uint length);

String getBlock(const char* str, const char** outPosition = nullptr);
String getBlock(const String& string, uint offset = 0);

String getStatement(const char* str, const char** outPosition = nullptr);

bool stringContains(const String& string, const String& chars);
bool startsWith(const String& string, const String& start);
int32 nextInt(const String& string);






