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
            throw RpcException("Invalid RPC version", RpcStatus::InvalidType);
        }

        return version;
    }

    std::string RpcUnpacker::ReadProcedureName()
    {
        const auto procedure = m_unpacker.ReadSized<std::string>(ProcedureNameMaxBytes);
        if (procedure)
        {
            return procedure.value();
        }
        else
        {
            throw RpcException("Procedure name is too large", RpcStatus::InvalidProcedure);
        }
    }

    template <>
    int32_t RpcUnpacker::Read()
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::Int)
        {
            throw RpcException("Expected RpcType of Int", RpcStatus::InvalidType);
        }

        return m_unpacker.Read<int32_t>();
    }

    template <>
    uint32_t RpcUnpacker::Read()
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::Uint)
        {
            throw RpcException("Expected RpcType of Uint", RpcStatus::InvalidType);
        }

        return m_unpacker.Read<uint32_t>();
    }

    template<>
    RpcStatus RpcUnpacker::Read()
    {
        return m_unpacker.Read<RpcStatus>();
    }

    template <>
    std::string RpcUnpacker::Read()
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::String)
        {
            throw RpcException("Expected RpcType of String", RpcStatus::InvalidType);
        }

        return m_unpacker.Read<std::string>();
    }
    
    template <>
    std::optional<std::string> RpcUnpacker::ReadSized(size_t maxBytes)
    {
        const auto rpcType = m_unpacker.Read<RpcType>();
        if (rpcType != RpcType::String)
        {
            throw RpcException("Expected RpcType of String", RpcStatus::InvalidType);
        }

        return m_unpacker.ReadSized<std::string>(maxBytes);
    }
}