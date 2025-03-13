#include "RpcSrv.h"
#include "RpcException.h"

#include <cassert>
#include <iostream>

namespace Coppermind::Rpc
{
    RpcSrv::RpcSrv(std::unique_ptr<Net::TcpSocket> listener, std::unique_ptr<RpcProcessor> processor)
        : m_listener(std::move(listener)), m_processor(std::move(processor))
    {
    }
    
    void RpcSrv::Run()
    {
        while (1)
        {
            try
            {
                auto client = m_listener->Accept();

                try
                {
                    while (1)
                    {
                        m_processor->Process(*client, *client);
                    }
                }
                catch (const RpcException& e)
                {
                    std::cerr << "Rpc Error (" << static_cast<int>(e.Status()) << "): " << e.what() << "\n";
                }
                catch (const std::system_error& e)
                {
                    std::cerr << "System Error (" << e.code() << "): " << e.what() << "\n";
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Unknown Error: " << e.what() << "\n";
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "TCP Error: " << e.what() << "\n";
            }
        }
    }
}