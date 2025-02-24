#include "BinaryPacker.h"
#include "Networking.h"
#include <array>

namespace Coppermind::Rpc
{
	BinaryPacker::BinaryPacker(IO::Writer &writer)
		: m_writer(writer)
    {
    }

	BinaryPacker& operator<<(BinaryPacker& packer, int32_t value)
	{
		value = htonl(value);
		std::array<char, sizeof(value)> buffer;
		memcpy(buffer.data(), &value, buffer.size());
		if (packer.m_writer.Write(buffer) != sizeof(value))
		{
			throw std::runtime_error("Unable to write int32_t");
		}

		return packer;
	}

	BinaryPacker& operator<<(BinaryPacker& packer, uint32_t value)
	{
		value = htonl(value);
		std::array<char, sizeof(value)> buffer;
		memcpy(buffer.data(), &value, buffer.size());
		if (packer.m_writer.Write(buffer) != sizeof(value))
		{
			throw std::runtime_error("Unable to write uint32_t");
		}

		return packer;
	}

	BinaryPacker& operator<<(BinaryPacker& packer, std::string_view value)
	{
		const auto size = static_cast<uint32_t>(value.size());
		packer << size;

		const std::span<const char> bytes(value.begin(), value.size());
		if (packer.m_writer.Write(bytes) != value.size())
		{
			throw std::runtime_error("Unable to write string");
		}
		
		return packer;
	}

	BinaryPacker& operator<<(BinaryPacker& packer, const std::string& value)
	{
		packer << std::string_view(value);
		return packer;
	}

	BinaryPacker& operator<<(BinaryPacker& packer, const char* value)
	{
		packer << std::string_view(value);
		return packer;
	}
}
