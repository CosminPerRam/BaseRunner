
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>

namespace files
{
    std::string getFileContent(const std::string& filePath, bool throws)
    {
        std::ifstream fin(filePath);

        if(!fin.is_open())
        {
            std::string error = "Unable to open file: " + filePath + "!";
            if(throws)
                throw std::runtime_error(error);
            else 
                std::cerr<<error<<std::endl;
        }

        std::ostringstream stream;
        stream << fin.rdbuf();

        return stream.str();
    }
}