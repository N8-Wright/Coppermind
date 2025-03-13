#pragma once
#include "Reader.h"
#include "BinaryUnpacker.h"
#include "Rpc.h"
#include <iosfwd>
#include <optional>
#include <cstdint>
#include <string>
namespace Coppermind::Rpc
{
    class RpcUnpacker
    {
    private:
        static constexpr const auto ProcedureNameMaxBytes = 2;
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
		std::optional<T> ReadSized(size_t maxBytes);

		template<> std::optional<std::string> ReadSized(size_t);
    };
}