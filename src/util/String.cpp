#include "String.h"

#include <cctype>

std::vector<String> splitString(const String& string, const String& delimiters)
{
	size_t start = 0;
	size_t end = string.find_first_of(delimiters);

	std::vector<String> result;

	while (end <= String::npos)
	{
		String token = string.substr(start, end - start);
		if (!token.empty())
			result.push_back(token);

		if (end == String::npos)
			break;

		start = end + 1;
		end = string.find_first_of(delimiters, start);
	}

	return result;
}

std::vector<String> splitString(const String& string, const char delimiter)
{
	return splitString(string, String(1, delimiter));
}

std::vector<String> tokenize(const String& string)
{
	return splitString(string, " \t\n");
}

std::vector<String> getLines(const String& string)
{
	return splitString(string, "\n");
}

const char* findToken(const char* str, const String& token)
{
	const char* t = str;
	while (t = strstr(t, token.c_str()))
	{
		bool left = str == t || isspace(t[-1]);
		bool right = !t[token.size()] || isspace(t[token.size()]);
		if (left && right)
			return t;

		t += token.size();
	}
	return nullptr;
}

const char* findToken(const String& string, const String& token)
{
	return findToken(string.c_str(), token);
}

int32 findStringPosition(const String& string, const String& search, uint offset)
{
	const char* str = string.c_str() + offset;
	const char* found = strstr(str, search.c_str());
	if (found == nullptr)
		return -1;
	return (int32)(found - str) + offset;
}

String stringRange(const String& string, uint start, uint length)
{
	return string.substr(start, length);
}

String removeStringRange(const String& string, uint start, uint length)
{
	String result = string;
	return result.erase(start, length);
}

String getBlock(const char* str, const char** outPosition)
{
	const char* end = strstr(str, "}");
	if (!end)
		return String(str);

	if (outPosition)
		*outPosition = end;
	uint length = end - str + 1;
	return String(str, length);
}

String getBlock(const String& string, uint offset)
{
	const char* str = string.c_str() + offset;
	return getBlock(str);
}

String getStatement(const char* str, const char** outPosition)
{
	const char* end = strstr(str, ";");
	if (!end)
		return String(str);

	if (outPosition)
		*outPosition = end;
	uint length = end - str + 1;
	return String(str, length);
}

bool stringContains(const String& string, const String& chars)
{
	return string.find(chars) != String::npos;
}

bool startsWith(const String& string, const String& start)
{
	return string.find(start) == 0;
}

int32 nextInt(const String& string)
{
	const char* str = string.c_str();
	for (uint i = 0; i < string.size(); i++)
	{
		if (isdigit(string[i]))
			return atoi(&string[i]);
	}
	return -1;
}

