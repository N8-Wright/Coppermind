#include "Networking.h"
#include "TcpSocket.h"
#include <iostream>
#include <cstdlib>
#include <cerrno>

namespace Coppermind::Net
{
	int GetLastError()
	{
		#ifdef _WIN32
		return WSAGetLastError();
		#else
		return errno;
		#endif
	}

	Network::Network()
	{
		#ifdef _WIN32
		WSADATA wsaData;
	    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	    {
	        std::cerr << "WSAStartup failed\n";
	        exit(1);
	    }

	    if (LOBYTE(wsaData.wVersion) != 2 ||
	        HIBYTE(wsaData.wVersion) != 2)
	    {
	        std::cerr << "Version 2.2 of Winsock not available.\n";
	        WSACleanup();
	        exit(2);
	    }
	    #endif
	}

	Network::~Network()
	{
		#ifdef _WIN32
		WSACleanup();
		#endif
	}

	std::unique_ptr<TcpSocket> Network::CreateTcpSocket(std::string_view port)
	{
		return std::unique_ptr<TcpSocket>(new TcpSocket(port));
	}
}
