#include "Request.h"
#include "Response.h"

#include "TcpSocket.h"
#include "Networking.h"
#include "RpcProcessor.h"
#include "RpcSrv.h"

#include <iostream>

using namespace Coppermind;

int main()
{
    auto processor = std::make_unique<Rpc::RpcProcessor>();
    processor->Add("Request", [](auto& input, auto& output)
        {
            const auto req = input.Read<Request>();

            std::cout << "Recieved request: \n"
                << "Name: " << req.Name() << "\n"
                << "Id: " << req.Id() << "\n"
                << "Metadata: " << req.Metadata() << "\n";

            output << Rpc::RpcStatus::Ok;
        });


    Net::Network net;
    Rpc::RpcSrv srv(net.CreateTcpSocket("8080"), std::move(processor));
    srv.Run();
	return 0;
}
