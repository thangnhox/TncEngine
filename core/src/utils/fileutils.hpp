#pragma once

//std
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <stdexcept>

namespace vulkanEngine
{

    static std::vector<char> loadFile(const std::string& filePath)
    {
        std::fstream file;
        file.open(filePath, std::ios::in | std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            //throw std::runtime_error("failed to open file: " + filePath);
            return std::vector<char>(0);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    static std::string loadFile(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");
		fseek(file, 0, SEEK_END);
		size_t length = ftell(file);
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