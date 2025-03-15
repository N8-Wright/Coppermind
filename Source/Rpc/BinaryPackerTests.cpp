#include "BinaryPacker.h"
#include "BinaryUnpacker.h"
#include "ReaderStreamWrapper.h"
#include "WriterStreamWrapper.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST(BinaryPacker, PackIntegers)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);

    packer << 99;
    packer << 22;

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    ASSERT_EQ(unpacker.Read<int32_t>(), 99);
    ASSERT_EQ(unpacker.Read<int32_t>(), 22);
}

class TestClass
{
public:
	int a = 0;
	int b = 0;
    TestClass()
	{
	}

    TestClass(int a, int b)
		: a(a), b(b)
	{
	}

	template<typename T>
	void Serialize(T& packer) const
	{
		packer << a;
		packer << b;
	}

	template<typename T>
	void Deserialize(T& unpacker)
	{
		a = unpacker.Read<int32_t>();
		b = unpacker.Read<int32_t>();
	}
};

TEST(BinaryPacker, PackClass)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);
    TestClass test(88, 99);
    packer << test;

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<TestClass>();
    ASSERT_EQ(test.a, output.a);
    ASSERT_EQ(test.b, output.b);
}

TEST(BinaryPacker, PackCString)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);

    packer << "Hello, World!";

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<std::string>();
    ASSERT_EQ(std::string("Hello, World!"), output);
}

TEST(BinaryPacker, PackString)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);

    BinaryPacker packer(writer);
    packer << std::string("Hello, World!");

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<std::string>();
    ASSERT_EQ(std::string("Hello, World!"), output);
}

TEST(BinaryPacker, PackStringView)
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);

    auto value = std::string_view("Hello, World!");
    packer << value;

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<std::string>();
    ASSERT_EQ(std::string("Hello, World!"), output);
}
