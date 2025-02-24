#include "WriterStreamWrapper.h"
#include "ReaderStreamWrapper.h"

#include "RpcPacker.h"
#include "BinaryUnpacker.h"
#include "Rpc.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;
TEST_CASE("RPC Packer encodes version information", "[RpcPacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);

    RpcPacker packer(writer, "Test");


    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    REQUIRE(unpacker.Read<uint32_t>() == CurrentVersion);
    REQUIRE(unpacker.Read<std::string>() == "Test");
}