#pragma once
#include <span>

namespace Coppermind::IO
{
    /// @brief An interface for writing bytes.
    class Writer
    {
    public:
        /// @brief Write bytes
        /// @param bytes The span of bytes to write. A best effort is made to
        ///              write all bytes in the span.
        /// @return The number of bytes written.
        virtual size_t Write(const std::span<const char> bytes) = 0;
    };
}