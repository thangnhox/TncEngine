#pragma once

#include <unordered_map>
#include <string>

namespace TncEngine {

    class StringUtils
    {
    public:
        enum class StringType
        {
            LowerCase = 0, UpperCase
        };

    public:
        static std::string LoadFile(const std::string& filepath);
        static std::unordered_map<std::string, std::string> SplitString(const std::string& keyToken, const std::string& string);
        static uint32_t CountChar(const std::string& string, char character, uint32_t begin, uint32_t end);
        static std::string PathToFileName(const std::string& filePath, bool fileExtension = true);
        static std::string ChangeType(const std::string& text, StringType type);
    };

}