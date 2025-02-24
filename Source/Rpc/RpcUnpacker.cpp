#include "RpcUnpacker.h"
#include "Rpc.h"
#include "RpcException.h"
#include <istream>

namespace Coppermind::Rpc
{
    RpcUnpacker::RpcUnpacker(IO::Reader& reader)
        : BinaryUnpacker(reader)
    {
    }

    uint32_t RpcUnpacker::ReadVersion()
    {
        const auto version = Read<uint32_t>();
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
}