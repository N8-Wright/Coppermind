#pragma once
#include "Reader.h"

#include "BinaryUnpacker.h"
#include <iosfwd>
namespace Coppermind::Rpc
{
    class RpcUnpacker : public BinaryUnpacker
    {
    public:
        RpcUnpacker(IO::Reader& reader);

        uint32_t ReadVersion();
        std::string ReadProcedureName();
    };
}