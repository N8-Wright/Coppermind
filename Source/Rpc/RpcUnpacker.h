#pragma once
#include "Reader.h"
#include "BinaryUnpacker.h"
#include "Rpc.h"
#include <iosfwd>
namespace Coppermind::Rpc
{
    class RpcUnpacker
    {
    private:
        BinaryUnpacker m_unpacker;
    public:
        RpcUnpacker(IO::Reader& reader);

        uint32_t ReadVersion();
        std::string ReadProcedureName();

        template<typename T>
		T Read();
		template<> int32_t Read();
		template<> uint32_t Read();
        template<> RpcStatus Read();
		template<> std::string Read();

		template<typename T>
		T ReadSized(size_t maxBytes);

		template<> std::string ReadSized(size_t);
    };
}