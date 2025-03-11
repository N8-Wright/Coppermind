#pragma once
#include <span>

namespace Coppermind::IO
{
    /// @brief An interface for reading bytes.
    class Reader
    {
    public:
        /// @brief Read bytes.
        /// @param bytes The span of bytes to read into. A best effort is made
        ///              to read the size of the span requested.
        /// @return The number of bytes actually read.
        virtual size_t Read(std::span<char> bytes) = 0;
    };
}