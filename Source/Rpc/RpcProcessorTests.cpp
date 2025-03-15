#include "WriterStreamWrapper.h"
#include "ReaderStreamWrapper.h"

#include "RpcProcessor.h"
#include "RpcPacker.h"
#include "RpcUnpacker.h"
#include "Rpc.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST(RpcProcessor, ProcedureDoesNotExist)
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

    PackRpcRequest(wrapper, "subtract", 1, 2);

    std::stringstream output;
    WriterStreamWrapper outputWrapper(output);
    ReaderStreamWrapper inputWrapper(input);

    ASSERT_ANY_THROW(srv.Process(inputWrapper, outputWrapper));

    ReaderStreamWrapper reader(output);
    RpcUnpacker unpacker(reader);
    
    ASSERT_EQ(unpacker.ReadVersion(), CurrentVersion);
    ASSERT_EQ(unpacker.Read<RpcStatus>(), RpcStatus::ProcedureNotFound);
}

TEST(RpcProcessor, ProcedureNameTooLong)
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

    std::string procedure;
    procedure.append(3333, 'a');
    PackRpcRequest(wrapper, procedure, 1, 2);

    std::stringstream output;
    WriterStreamWrapper outputWrapper(output);
    ReaderStreamWrapper inputWrapper(input);

    ASSERT_ANY_THROW(srv.Process(inputWrapper, outputWrapper));

    ReaderStreamWrapper reader(output);
    RpcUnpacker unpacker(reader);
    
    ASSERT_EQ(unpacker.ReadVersion(), CurrentVersion);
    ASSERT_EQ(unpacker.Read<RpcStatus>(), RpcStatus::InvalidProcedure);
}

TEST(RpcProcessor, InvalidArgumentType)
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

    ASSERT_ANY_THROW(srv.Process(inputWrapper, outputWrapper));

    ReaderStreamWrapper reader(output);
    RpcUnpacker unpacker(reader);
    
    ASSERT_EQ(unpacker.ReadVersion(), CurrentVersion);
    ASSERT_EQ(unpacker.Read<RpcStatus>(), RpcStatus::InvalidType);
}

TEST(RpcProcessor, AddProcedureWorks)
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
    
    ASSERT_EQ(unpacker.ReadVersion(), CurrentVersion);
    ASSERT_EQ(unpacker.Read<RpcStatus>(), RpcStatus::Ok);
    const auto result = unpacker.Read<int32_t>();
    ASSERT_EQ(3, result);
}