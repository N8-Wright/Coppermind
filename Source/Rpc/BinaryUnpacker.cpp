#include "BinaryUnpacker.h"
#include "Networking.h"
#include <istream>
#include <array>
namespace Coppermind::Rpc
{
	BinaryUnpacker::BinaryUnpacker(IO::Reader& reader)
		: m_reader(reader)
	{
	}

	template<>
	int32_t BinaryUnpacker::Read()
	{
		int32_t value;

		std::array<char, sizeof(value)> buffer;
		if (m_reader.Read(buffer) != sizeof(value))
		{
			throw std::runtime_error("Unable to read correct number of bytes in int32_t");
		}

		memcpy(&value, buffer.data(), sizeof(value));
		return ntohl(value);
	}

	template<>
	uint32_t BinaryUnpacker::Read()
	{
		uint32_t value;

		std::array<char, sizeof(value)> buffer;
		if (m_reader.Read(buffer) != sizeof(value))
		{
			throw std::runtime_error("Unable to read correct number of bytes in uint32_t");
		}

		memcpy(&value, buffer.data(), sizeof(value));
		return ntohl(value);
	}

	template<>
	std::string BinaryUnpacker::Read()
	{
		const auto size = Read<uint32_t>();
		std::string str;
		str.resize(size);
		if (m_reader.Read(str) != str.size())
		{
			throw std::runtime_error("Unable to read correct number of bytes in string");
		}
		
		return str;
	}
}
