#pragma once

#include "Writer.h"

#include "BinaryUnpacker.h"
#include "BinaryPacker.h"
#include "TcpSocket.h"

#include <unordered_map>
#include <functional>
#include <string>
#include <iosfwd>
#include <memory>

namespace Coppermind::Rpc
{
	class RpcProcessor
	{
	private:
		using ArgDecoder = std::function<void(BinaryUnpacker&, BinaryPacker&)>;
		std::unordered_map<std::string, ArgDecoder> m_procedures;

	public:
		void Add(std::string rpc, ArgDecoder decoder);
		void Process(IO::Reader& input, IO::Writer& output);
	};
}