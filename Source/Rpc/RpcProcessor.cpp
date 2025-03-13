#include "RpcProcessor.h"
#include "RpcException.h"
#include "RpcUnpacker.h"
#include "RpcPacker.h"

#include <istream>
#include <ostream>
#include <iostream>
namespace Coppermind::Rpc
{
    void RpcProcessor::Add(std::string rpc, Procedure procedure)
    {
		m_procedures.emplace(std::move(rpc), std::move(procedure));
	}

	void RpcProcessor::Process(IO::Reader& input, IO::Writer& output)
	{
		RpcUnpacker unpacker(input);
		RpcPacker packer(output);

		try
		{
			const auto rpcVersion = unpacker.ReadVersion();
			if (rpcVersion == 1)
			{
				const auto procedureName = unpacker.ReadProcedureName();
				auto procedure = m_procedures.find(procedureName);
				if (procedure != m_procedures.end())
				{
					procedure->second(unpacker, packer);
				}
			}
			else
			{
				throw RpcException("Unable to process request of this version");
			}
		}
		catch (const RpcException& e)
		{
			packer << e.Status();
			throw e;
		}
	}
}