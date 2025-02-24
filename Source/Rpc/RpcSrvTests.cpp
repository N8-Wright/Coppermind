#include "WriterStreamWrapper.h"
#include "ReaderStreamWrapper.h"

#include "RpcSrv.h"
#include "RpcPacker.h"
#include "RpcUnpacker.h"
#include "Rpc.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST_CASE("Add procedure works", "[RpcSrv]")
{
    RpcSrv srv;
    srv.Add("add", [](BinaryUnpacker& input, BinaryPacker& output)
    {
        auto a = input.Read<int32_t>();
        auto b = input.Read<int32_t>();
        output << a + b;
    });


    std::stringstream input;
    WriterStreamWrapper wrapper(input);
    PackRpcRequest(wrapper, "add", 1, 2);

    std::stringstream output;
    WriterStreamWrapper outputWrapper(output);
    ReaderStreamWrapper inputWrapper(input);

    srv.Process(inputWrapper, outputWrapper);

    ReaderStreamWrapper reader(output);
    RpcUnpacker unpacker(reader);
    
    REQUIRE(unpacker.ReadVersion() == CurrentVersion);
    const auto result = unpacker.Read<int32_t>();
    REQUIRE(3 == result);
}