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

    using RpcTypeWireType = uint8_t;
}
