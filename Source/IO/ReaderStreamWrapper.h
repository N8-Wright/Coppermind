#pragma once
#include <iosfwd>
#include "Reader.h"

namespace Coppermind::IO
{
    /// @brief Wraps an input stream in a @ref Coppermind::IO::Reader
    class ReaderStreamWrapper : public Reader
    {
        std::istream& m_stream;

    public:
        explicit ReaderStreamWrapper(std::istream& stream);
        virtual size_t Read(std::span<char> bytes) override;
    };
}