#include "BinaryUnpacker.h"
#include "ReaderStreamWrapper.h"
#include "Rpc.h"
#include "RpcPacker.h"
#include "WriterStreamWrapper.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST(RpcPacker, EncodesVersionInformation)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);

    RpcPacker packer(writer, "Test");


    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    ASSERT_EQ(unpacker.Read<uint32_t>(), CurrentVersion);
    ASSERT_EQ(unpacker.Read<std::string>(), "Test");
}