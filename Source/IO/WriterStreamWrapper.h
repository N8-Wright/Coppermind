#pragma once
#include "Writer.h"

#include <iosfwd>

namespace Coppermind::IO
{
    class WriterStreamWrapper : public Writer
    {
        std::ostream& m_stream;

    public:
        explicit WriterStreamWrapper(std::ostream& stream);
        virtual size_t Write(const std::span<const char> bytes) override;
    };
}