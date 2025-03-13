#pragma once
#include <cstdint>
namespace Coppermind::Rpc
{
    static constexpr uint32_t CurrentVersion = 1;

    enum class RpcType
    {
        Uint = 1,
        Int = 2,
        String = 3,
    };

    enum class RpcStatus
    {
        Ok = 1,
        InternalError = 2,
        InvalidType = 3,
        InvalidProcedure = 4,
        ProcedureNotFound = 5,
    };

    using RpcTypeWireType = uint8_t;
    using RpcStatusWireType = uint8_t;
}
