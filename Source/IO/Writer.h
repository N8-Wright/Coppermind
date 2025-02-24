#pragma once
#include <span>

namespace Coppermind::IO
{
    class Writer
    {
    public:
        virtual size_t Write(const std::span<const char> bytes) = 0;
    };
}