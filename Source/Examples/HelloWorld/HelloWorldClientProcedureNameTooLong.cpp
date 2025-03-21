#include "Networking.h"
#include "TcpSocket.h"
#include "RpcClient.h"

#include <iostream>
using namespace Coppermind;

void ProcessResponse(Rpc::RpcUnpacker& input)
{
    const auto result = input.Read<std::string>();
    std::cout << "Received response: " << result << "\n";
}

int main()
{
    Net::Network net;
    try
    {
        auto client = Rpc::RpcClient(net.CreateTcpSocket("localhost", "8080"));

        std::string procedure;
        procedure.append(3000, 'c');
        client.Call(procedure, ProcessResponse, "Jim");     
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what();
    }
    return 0;
}