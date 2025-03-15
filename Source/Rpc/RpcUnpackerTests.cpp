#include "BinaryPacker.h"
#include "ReaderStreamWrapper.h"
#include "Rpc.h"
#include "RpcException.h"
#include "RpcUnpacker.h"
#include "WriterStreamWrapper.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST(RpcUnpacker, ThrowsWhenInvalidVersionEncountered)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);

    BinaryPacker packer(writer);
    packer << CurrentVersion + 10;

    ReaderStreamWrapper reader(stream);
    RpcUnpacker unpacker(reader);
    ASSERT_THROW(unpacker.ReadVersion(), RpcException);
}