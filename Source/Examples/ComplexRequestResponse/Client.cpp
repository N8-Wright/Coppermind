#include "Request.h"
#include "Response.h"

#include "Networking.h"
#include "TcpSocket.h"
#include "RpcClient.h"

#include <iostream>
using namespace Coppermind;

void ProcessResponse(Rpc::RpcUnpacker& input)
{
    const auto res = input.Read<Response>();
    std::cout << "Received response for request \"" << res.Id() << "\" with a message \"" << res.Result() << "\"\n";
}

int main()
{
    Net::Network net;
    try
    {
        auto client = Rpc::RpcClient(net.CreateTcpSocket("localhost", "8080"));

        Request req("Tim", 199, "Test metadata");
        client.Call("Request", ProcessResponse, req);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what();
    }
    return 0;
}