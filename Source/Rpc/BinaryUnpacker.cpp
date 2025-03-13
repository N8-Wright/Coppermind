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
	RpcType BinaryUnpacker::Read()
	{
		RpcTypeWireType value;
		std::array<char, sizeof(RpcTypeWireType)> buffer;
		if (m_reader.Read(buffer) != sizeof(value))
		{
			throw std::runtime_error("Unable to read correct number of bytes in RpcType");
		}

		memcpy(&value, buffer.data(), sizeof(value));
		return static_cast<RpcType>(value);
	}

	template<>
	RpcStatus BinaryUnpacker::Read()
	{
		RpcStatusWireType value;
		std::array<char, sizeof(RpcStatusWireType)> buffer;
		if (m_reader.Read(buffer) != sizeof(value))
		{
			throw std::runtime_error("Unable to read correct number of bytes in RpcStatus");
		}

		memcpy(&value, buffer.data(), sizeof(value));
		return static_cast<RpcStatus>(value);
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

	template <>
    std::optional<std::string> BinaryUnpacker::ReadSized(size_t maxBytes)
    {
        const auto size = Read<uint32_t>();
		if (size <= maxBytes)
		{
			std::string str;
			str.resize(size);
			if (m_reader.Read(str) != str.size())
			{
				throw std::runtime_error("Unable to read correct number of bytes in string");
			}
			
			return str;
		}
		else
		{
			return {};
		}
    }
}
