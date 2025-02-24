#include "WriterStreamWrapper.h"
#include "ReaderStreamWrapper.h"

#include "BinaryPacker.h"
#include "BinaryUnpacker.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Coppermind::Rpc;
using namespace Coppermind::IO;

TEST_CASE("Integers Can Be Packed", "[BinaryPacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);

    packer << 99;
    packer << 22;

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    REQUIRE(unpacker.Read<int32_t>() == 99);
    REQUIRE(unpacker.Read<int32_t>() == 22);
}

class Test
{
public:
	int a = 0;
	int b = 0;
	Test()
	{
	}

	Test(int a, int b)
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

TEST_CASE("Test Class Can Be Packed", "[BinaryPacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);
    Test test(88, 99);
    packer << test;

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<Test>();
    REQUIRE(test.a == output.a);
    REQUIRE(test.b == output.b);
}

TEST_CASE("C String Can Be Packed", "[BinaryPacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);

    packer << "Hello, World!";

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<std::string>();
    REQUIRE(std::string("Hello, World!") == output);
}

TEST_CASE("Standard String Can Be Packed", "[BinaryPacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);

    BinaryPacker packer(writer);
    packer << std::string("Hello, World!");

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<std::string>();
    REQUIRE(std::string("Hello, World!") == output);
}

TEST_CASE("String View Can Be Packed", "[BinaryPacker]")
{
    std::stringstream stream;
    WriterStreamWrapper writer(stream);
    BinaryPacker packer(writer);

    auto value = std::string_view("Hello, World!");
    packer << value;

    ReaderStreamWrapper reader(stream);
    BinaryUnpacker unpacker(reader);
    auto output = unpacker.Read<std::string>();
    REQUIRE(std::string("Hello, World!") == output);
}
