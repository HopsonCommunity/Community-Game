#include "FileUtil.h"

// Code is referenced from:
// https://vicidi.wordpress.com/2015/03/09/reading-utf-file-with-bom-to-utf-8-encoded-stdstring-in-c11-on-windows/

#include <fstream>
#include <sstream>

#define ENCODING_ASCII      0
#define ENCODING_UTF8       1

std::string getFileContents(const std::string& filePath)
{
	std::string result;
	std::ifstream ifs(filePath.c_str(), std::ios::binary);
	std::stringstream ss;

	if (!ifs.is_open())
	{
		result.clear(); // Unable to read file
		return result;
	}
	
	if (ifs.eof())
		result.clear();
	else
	{
		int ch1 = ifs.get();
		int ch2 = ifs.get();
		int ch3 = ifs.get();
		if (!(ch1 == 0xef && ch2 == 0xbb && ch3 == 0xbf))
			ifs.seekg(0);
	}
	ss << ifs.rdbuf() << '\0';
	result = ss.str();

	return result;
}