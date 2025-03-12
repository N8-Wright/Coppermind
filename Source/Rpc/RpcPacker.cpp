#include "RpcPacker.h"
#include "Rpc.h"
#include <ostream>
namespace Coppermind::Rpc
{
    RpcPacker::RpcPacker(IO::Writer& writer, std::string_view procedureName)
        : m_packer(BinaryPacker(writer))
    {
        m_packer << CurrentVersion; // Don't write type info for rpc version
        *this << procedureName;
    }

    RpcPacker::RpcPacker(IO::Writer& stream)
        : m_packer(BinaryPacker(stream))
    {
        m_packer << CurrentVersion; // Don't write type info for rpc version
    }

    RpcPacker &operator<<(RpcPacker &os, int32_t value)
    {
        os.m_packer << static_cast<uint8_t>(RpcType::Int);
        os.m_packer << value;
        return os;
    }

    RpcPacker &operator<<(RpcPacker &os, uint32_t value)
    {
        os.m_packer << static_cast<uint8_t>(RpcType::Uint);
        os.m_packer << value;
        return os;
    }

    RpcPacker &operator<<(RpcPacker &os, std::string_view value)
    {
        os.m_packer << static_cast<uint8_t>(RpcType::String);
        os.m_packer << value;
        return os;
    }

    RpcPacker &operator<<(RpcPacker &os, const std::string &value)
    {
        return operator<<(os, std::string_view(value));
    }

    RpcPacker &operator<<(RpcPacker &os, const char *value)
    {
        return operator<<(os, std::string_view(value));
    }
}
