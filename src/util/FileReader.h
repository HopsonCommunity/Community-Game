#pragma once

#include <cstring>
#include <iostream>
#include <sstream>

namespace Util
{
	std::string readFile(const std::string& filepath)
	{
		std::ifstream inFile (filepath);
        	std::string source;
		std::stringstream stringStream;
		
		if (!inFile.is_open()) 
		{
			std::cout << "[FileReader.h] Couldn't open file \"" << filepath.c_str() << "\"!" << std::endl;
			return "";
		}
		
		stringStream << inFile.rdbuf();
        	source = stringStream.str();
		return source;
	}
}
