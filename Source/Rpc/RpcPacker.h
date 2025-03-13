#pragma once
#include "Writer.h"
#include "Rpc.h"
#include "BinaryPacker.h"
#include <iosfwd>
namespace Coppermind::Rpc
{
    class RpcPacker
    {
    private:
        BinaryPacker m_packer;
    public:
        RpcPacker(IO::Writer& writer, std::string_view procedureName);
        RpcPacker(IO::Writer& stream);

        template<typename T>
		friend RpcPacker& operator<<(RpcPacker& packer, const T& value)
		{
			value.Serialize(packer);
			return packer;
		}

        friend RpcPacker& operator<<(RpcPacker& packer, RpcStatus);
		friend RpcPacker& operator<<(RpcPacker& packer, int32_t value);
		friend RpcPacker& operator<<(RpcPacker& packer, uint32_t value);
		friend RpcPacker& operator<<(RpcPacker& packer, std::string_view value);
		friend RpcPacker& operator<<(RpcPacker& packer, const std::string& value);
		friend RpcPacker& operator<<(RpcPacker& packer, const char* value);
    };

    template<typename... Args>
    void PackRpcRequest(IO::Writer& stream, std::string_view procedureName, Args... args)
    {
        RpcPacker packer(stream, procedureName);
        ([&]
        {
            packer << args;
        }(), ...);
    }
}