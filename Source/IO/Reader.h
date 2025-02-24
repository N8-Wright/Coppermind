#pragma once
#include <span>

namespace Coppermind::IO
{
    class Reader
    {
    public:
        virtual size_t Read(std::span<char> bytes) = 0;
    };
}