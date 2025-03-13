#pragma once
#include "TcpSocket.h"
#include "RpcPacker.h"
#include "RpcUnpacker.h"
#include "RpcException.h"
#include "Rpc.h"

#include <memory>
#include <string_view>
#include <iostream>

namespace Coppermind::Rpc
{
    class RpcClient
    {
        std::unique_ptr<Net::TcpSocket> m_client;

    public:
        RpcClient(std::unique_ptr<Net::TcpSocket> client);

        template<typename ReaderFn, typename... Args>
        void Call(std::string_view procedureName, ReaderFn read, Args... args)
        {
            PackRpcRequest(*m_client, procedureName, std::forward<Args>(args)...);
            RpcUnpacker unpacker(*m_client);

            const auto rpcVersion = unpacker.ReadVersion();
            if (rpcVersion == 1)
            {
                const auto status = unpacker.Read<RpcStatus>();
                if (status == RpcStatus::Ok)
                {
                    read(unpacker);
                }
                else
                {
                    std::cerr << "Request failed: " << static_cast<int32_t>(status) << "\n";
                }
            }
            else
            {
                throw RpcException("Unable to process request of this version");
            }
        }
    };
}