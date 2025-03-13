#include "WriterStreamWrapper.h"
#include "ReaderStreamWrapper.h"

#include "RpcProcessor.h"
#include "RpcPacker.h"
#include "RpcUnpacker.h"
#include "Rpc.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST_CASE("Invalid argument type", "[RpcProcessor]")
{
    RpcProcessor srv;
    srv.Add("add", [](RpcUnpacker& input, RpcPacker& output)
    {
        auto a = input.Read<int32_t>();
        auto b = input.Read<int32_t>();

        output << RpcStatus::Ok;
        output << a + b;
    });

    std::stringstream input;
    WriterStreamWrapper wrapper(input);
    PackRpcRequest(wrapper, "add", 1, "2");

    std::stringstream output;
    WriterStreamWrapper outputWrapper(output);
    ReaderStreamWrapper inputWrapper(input);

    REQUIRE_THROWS(srv.Process(inputWrapper, outputWrapper));

    ReaderStreamWrapper reader(output);
    RpcUnpacker unpacker(reader);
    
    REQUIRE(unpacker.ReadVersion() == CurrentVersion);
    REQUIRE(unpacker.Read<RpcStatus>() == RpcStatus::InvalidType);
}

TEST_CASE("Add procedure works", "[RpcProcessor]")
{
    RpcProcessor srv;
    srv.Add("add", [](RpcUnpacker& input, RpcPacker& output)
    {
        auto a = input.Read<int32_t>();
        auto b = input.Read<int32_t>();

        output << RpcStatus::Ok;
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
    REQUIRE(unpacker.Read<RpcStatus>() == RpcStatus::Ok);
    const auto result = unpacker.Read<int32_t>();
    REQUIRE(3 == result);
}