#pragma once
#include "Writer.h"
#include "Rpc.h"

#include <ostream>
#include <string_view>

namespace Coppermind::Rpc
{
	class BinaryPacker
	{
	private:
		IO::Writer& m_writer;

	public:
		explicit BinaryPacker(IO::Writer& writer);

		template<typename T>
		friend BinaryPacker& operator<<(BinaryPacker& packer, const T& value)
		{
			value.Serialize(packer);
			return packer;
		}

		friend BinaryPacker& operator<<(BinaryPacker& os, RpcType value);
		friend BinaryPacker& operator<<(BinaryPacker& os, uint8_t value);
		friend BinaryPacker& operator<<(BinaryPacker& os, int32_t value);
		friend BinaryPacker& operator<<(BinaryPacker& os, uint32_t value);
		friend BinaryPacker& operator<<(BinaryPacker& os, std::string_view value);
		friend BinaryPacker& operator<<(BinaryPacker& os, const std::string& value);
		friend BinaryPacker& operator<<(BinaryPacker& os, const char* value);
	};
}