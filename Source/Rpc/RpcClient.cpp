#include "RpcClient.h"

namespace Coppermind::Rpc
{
    RpcClient::RpcClient(std::unique_ptr<Net::TcpSocket> client)
        : m_client(std::move(client))
    {
    }
}