#include "WriterStreamWrapper.h"
#include "ReaderStreamWrapper.h"

#include "RpcUnpacker.h"
#include "BinaryPacker.h"
#include "Rpc.h"
#include "RpcException.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST_CASE("RPC Unpacker throws when invalid version encountered", "[RpcUnpacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);

    BinaryPacker packer(writer);
    packer << CurrentVersion + 10;

    ReaderStreamWrapper reader(stream);
    RpcUnpacker unpacker(reader);
    REQUIRE_THROWS_AS(unpacker.ReadVersion(), RpcException);
}