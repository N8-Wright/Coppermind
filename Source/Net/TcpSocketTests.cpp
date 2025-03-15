#include "TcpSocket.h"
#include "Networking.h"

#include <gtest/gtest.h>

using namespace Coppermind::Net;

TEST(TcpSocket, ConstructorDoesNotThrow)
{
    Network net;
    ASSERT_NO_THROW(net.CreateTcpSocket("3940"));
}
