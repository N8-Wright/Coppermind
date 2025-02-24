#include "RpcSrv.h"
#include "RpcProcessor.h"
#include "BinaryPacker.h"
#include "BinaryUnpacker.h"
#include "TcpSocket.h"
#include "Networking.h"

using namespace Coppermind;
int main()
{
    auto processor = std::make_unique<Rpc::RpcProcessor>();
    processor->Add("Hello", [](auto& input, auto& output)
    {
        auto name = input.Read<std::string>();
        output << "Hello, " + name;
    });


    Net::Network net;
    Rpc::RpcSrv srv(net.CreateTcpSocket("8080"), std::move(processor));
    srv.Run();
    return 0;
}