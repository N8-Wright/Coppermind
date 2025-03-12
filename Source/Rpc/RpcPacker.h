#pragma once
#include "Writer.h"
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
        explicit RpcPacker(IO::Writer& stream);

        template<typename T>
		friend RpcPacker& operator<<(RpcPacker& packer, const T& value)
		{
			value.Serialize(packer);
			return packer;
		}

		friend RpcPacker& operator<<(RpcPacker& os, int32_t value);
		friend RpcPacker& operator<<(RpcPacker& os, uint32_t value);
		friend RpcPacker& operator<<(RpcPacker& os, std::string_view value);
		friend RpcPacker& operator<<(RpcPacker& os, const std::string& value);
		friend RpcPacker& operator<<(RpcPacker& os, const char* value);
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