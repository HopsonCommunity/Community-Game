#pragma once

#include <cstring>
#include <iostream>

namespace Util
{
	std::string ReadFile(const std::string& filepath)
	{
		FILE* file = fopen(filepath.c_str(), "rb");
		if (file == nullptr)
		{
			std::cout << "[FileReader.h] Couldn't open file \"" << filepath.c_str() << "\"!" << std::endl;
			return "";
		}

		fseek(file, 0, SEEK_END);

		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}
}
