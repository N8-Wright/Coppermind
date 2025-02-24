#include "ReaderStreamWrapper.h"
#include <istream>
namespace Coppermind::IO
{
    ReaderStreamWrapper::ReaderStreamWrapper(std::istream &stream)
        : m_stream(stream)
    {
    }

    size_t ReaderStreamWrapper::Read(std::span<char> bytes)
    {
        m_stream.read(bytes.data(), bytes.size());
        return m_stream.gcount();
    }
}