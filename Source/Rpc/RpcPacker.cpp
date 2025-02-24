#include "RpcPacker.h"
#include "Rpc.h"
#include <ostream>
namespace Coppermind::Rpc
{
    RpcPacker::RpcPacker(IO::Writer& writer, std::string_view procedureName)
        : BinaryPacker(writer)
    {
        *this << CurrentVersion << procedureName;
    }

    RpcPacker::RpcPacker(IO::Writer& stream)
        : BinaryPacker(stream)
    {
        *this << CurrentVersion;
    }
}
