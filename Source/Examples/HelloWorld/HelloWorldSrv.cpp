#include "Rpc.h"
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
        const auto name = input.ReadSized<std::string>(50);
        if (name)
        {
            output << Rpc::RpcStatus::Ok;
            output << "Hello, " + name.value();
        }
    });


    Net::Network net;
    Rpc::RpcSrv srv(net.CreateTcpSocket("8080"), std::move(processor));
    srv.Run();
    return 0;
}