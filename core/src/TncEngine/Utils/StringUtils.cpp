#include "TncPCH.hpp"
#include "StringUtils.hpp"

#include <fstream>

namespace TncEngine {

    // Load file in binary mode
    // Whole file into single string
    std::string StringUtils::LoadFile(const std::string &filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (!in)
        {
            TncEngine_CORE_ERROR("Could not open file '{0}'", filepath);
            return result;
        }
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
        return result;
    }

    // Split string by keytoken
    // Each string will by identifies by key markded by token
    std::unordered_map<std::string, std::string> StringUtils::SplitString(const std::string &keyToken, const std::string &string)
    {
        std::unordered_map<std::string, std::string> result;
        size_t tokenPos = string.find(keyToken, 0);
        while (tokenPos != std::string::npos)
        {
            size_t eol = string.find_first_of("\r\n", tokenPos);
            ASSERT_CORE(eol != std::string::npos, "Invalid token mark");
            uint32_t spaceCount = CountChar(string, ' ', tokenPos, eol);
            size_t begin = tokenPos + keyToken.size() + spaceCount;
            std::string key = string.substr(begin, eol - begin);
            size_t nextLinePos = string.find_first_not_of("\r\n", eol);
            tokenPos = string.find(keyToken, nextLinePos);
            result[key] = string.substr(nextLinePos, tokenPos - (nextLinePos == std::string::npos ? string.size() - 1 : nextLinePos));
        }

        return result;
    }

    uint32_t StringUtils::CountChar(const std::string &string, char character, uint32_t begin, uint32_t end)
    {
        uint32_t count = 0;

        if (begin >= string.size() || end >= string.size() || begin >= end)
            return count;

        for (uint32_t i = begin; i <= end; i++)
        {
            if (string[i] == character)
                count++;
        }

        return count;
    }
}