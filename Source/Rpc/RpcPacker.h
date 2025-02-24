#pragma once
#include "Writer.h"
#include "BinaryPacker.h"
#include <iosfwd>
namespace Coppermind::Rpc
{
    class RpcPacker : public BinaryPacker
    {
    public:
        RpcPacker(IO::Writer& writer, std::string_view procedureName);
        explicit RpcPacker(IO::Writer& stream);
    };

    template<typename... Args>
    void PackRpcRequest(IO::Writer& stream, std::string_view procedureName, Args... args)
    {
        RpcPacker packer(stream, procedureName);
        ([&]
        {
            packer << args;
        }(), ...);
    }
}