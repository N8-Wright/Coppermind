#include "TcpSocket.h"
#include "Networking.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
using namespace Coppermind::Net;

TEST_CASE("TcpSocket constructor works without throwing exception", "[TcpSocket]")
{
    Network net;
    REQUIRE_NOTHROW(net.CreateTcpSocket("3940"));
}
