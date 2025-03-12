#pragma once
#include "Reader.h"
#include "Rpc.h"

#include <cstdint>
#include <string>
namespace Coppermind::Rpc
{
	class BinaryUnpacker
	{
	private:
		IO::Reader& m_reader;

	public:
		BinaryUnpacker(IO::Reader& reader);

		template<typename T>
		T Read()
		{
			T value;
			value.Deserialize(*this);
			return value;
		}

		template<> RpcType Read();
		template<> int32_t Read();
		template<> uint32_t Read();
		template<> std::string Read();

		template<typename T>
		T ReadSized(size_t maxBytes);

		template<> std::string ReadSized(size_t);
	};
}