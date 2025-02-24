#include "WriterStreamWrapper.h"
#include <ostream>

namespace Coppermind::IO
{
    WriterStreamWrapper::WriterStreamWrapper(std::ostream &stream)
        : m_stream(stream)
    {
    }

    size_t WriterStreamWrapper::Write(const std::span<const char> bytes)
    {
        const auto a = m_stream.tellp();
        m_stream.write(bytes.data(), bytes.size());
        return m_stream.tellp() - a;
    }
}