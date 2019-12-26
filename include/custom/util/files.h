
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>

namespace files
{
    const std::string res = "../res/";
    const std::string data = "../res/data/";

    std::string getFileContent(const std::string& filePath)
    {
        std::ifstream fin(filePath);

        if(!fin.is_open())
        {
            std::string error = "Unable to open file: " + filePath + "!";
            
            throw std::runtime_error(error);
        }

        std::ostringstream stream;
        stream << fin.rdbuf();

        return stream.str();
    }

    void setFileContent(const std::string& filePath, const std::string& data)
    {
        std::ofstream fout(filePath);

        fout << data;

        return;
    }
}