#pragma once
#include "Reader.h"
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

		template<> int32_t Read();
		template<> uint32_t Read();
		template<> std::string Read();
	};
}