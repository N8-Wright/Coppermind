#pragma once
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif
#include <string_view>
#include <memory>
namespace Coppermind::Net
{
	#ifdef _WIN32
	typedef int AddressLength;

	using SocketHandle = SOCKET;
	static constexpr SocketHandle InvalidSocket = INVALID_SOCKET;
	static constexpr auto SocketError = SOCKET_ERROR;
	static inline SocketHandle CloseSocket(SocketHandle sock) { return closesocket(sock); }
	#else
	typedef socklen_t AddressLength;

	using SocketHandle = int;
	static constexpr SocketHandle InvalidSocket = -1;
	static constexpr auto SocketError = -1;
	static inline SocketHandle CloseSocket(SocketHandle sock) { return close(sock); }
	#endif

	int GetLastError();

	class TcpSocket;
	class Network
	{
	public:
		Network();
		~Network();

		std::unique_ptr<TcpSocket> CreateTcpSocket(std::string_view port);
		std::unique_ptr<TcpSocket> CreateTcpSocket(std::string_view address, std::string_view port);
	};
}