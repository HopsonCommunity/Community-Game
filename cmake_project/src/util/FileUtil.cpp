#include "FileUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string getFileContents(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Unable to read " << filePath << "\n";
    }

    std::stringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
}
