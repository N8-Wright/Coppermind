#pragma once
#include "TcpSocket.h"
#include "RpcProcessor.h"

#include <memory>

namespace Coppermind::Rpc
{
    class RpcSrv
    {
        std::unique_ptr<Net::TcpSocket> m_listener;
        std::unique_ptr<RpcProcessor> m_processor;

    public:
        RpcSrv(std::unique_ptr<Net::TcpSocket> listener, std::unique_ptr<RpcProcessor> processor);
        void Run();
    };
}