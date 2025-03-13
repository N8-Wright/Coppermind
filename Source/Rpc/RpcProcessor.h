#pragma once

#include "Writer.h"

#include "RpcPacker.h"
#include "RpcUnpacker.h"
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
		using Procedure = std::function<void(RpcUnpacker&, RpcPacker&)>;
		std::unordered_map<std::string, Procedure> m_procedures;

	public:
		void Add(std::string rpc, Procedure decoder);
		void Process(IO::Reader& input, IO::Writer& output);
	};
}