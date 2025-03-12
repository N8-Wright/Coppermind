#include "RpcUnpacker.h"
#include "Rpc.h"
#include "RpcException.h"
#include <istream>

namespace Coppermind::Rpc
{
    RpcUnpacker::RpcUnpacker(IO::Reader& reader)
        : m_unpacker(BinaryUnpacker(reader))
    {
    }

    uint32_t RpcUnpacker::ReadVersion()
    {
        const auto version = m_unpacker.Read<uint32_t>();
        if (version != CurrentVersion)
        {
            throw RpcException("Invalid RPC version");
        }

        return version;
    }

    std::string RpcUnpacker::ReadProcedureName()
    {
        return Read<std::string>();
    }

    template <>
    int32_t RpcUnpacker::Read()
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::Int)
        {
            throw RpcException("Expected RpcType of Int");
        }

        return m_unpacker.Read<int32_t>();
    }

    template <>
    uint32_t RpcUnpacker::Read()
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::Uint)
        {
            throw RpcException("Expected RpcType of Uint");
        }

        return m_unpacker.Read<uint32_t>();
    }

    template <>
    std::string RpcUnpacker::Read()
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::String)
        {
            throw RpcException("Expected RpcType of String");
        }

        return m_unpacker.Read<std::string>();
    }
    
    template <>
    std::string RpcUnpacker::ReadSized(size_t maxBytes)
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::String)
        {
            throw RpcException("Expected RpcType of String");
        }

        return m_unpacker.ReadSized<std::string>(maxBytes);
    }
}