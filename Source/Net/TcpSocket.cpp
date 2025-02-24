#include "Networking.h"
#include "TcpSocket.h"
#include <system_error>
namespace Coppermind::Net
{
	#ifdef _WIN32
	static void ReuseAddress(SOCKET socket)
	{
		// lose the pesky "Address already in use" error message
		BOOL yes = TRUE;

		char optval[sizeof(yes)];
		memcpy(optval, &yes, sizeof(yes));

		if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, optval, sizeof(yes)) == -1)
		{
			throw std::runtime_error("Unable to set SO_REUSEADDR on socket");
		} 
	}
	#else
	static void ReuseAddress(int socket)
	{
		// lose the pesky "Address already in use" error message
		int yes = 1;
		if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		{
			throw std::system_error(GetLastError(), std::system_category());
		} 
	}
	#endif

	TcpSocket::TcpSocket(std::string_view port)
	{
		struct addrinfo hints = {};
		struct addrinfo* res = nullptr;

		hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE; // fill in my IP for me

		const auto result = getaddrinfo(nullptr, port.data(), &hints, &res);
		if (result != 0)
		{
			throw std::system_error(result, std::system_category());
		}

		m_socketHandle = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (m_socketHandle == InvalidSocket)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}

		ReuseAddress(m_socketHandle);

		if (bind(m_socketHandle, res->ai_addr, res->ai_addrlen) == -1)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}

		if (listen(m_socketHandle, 128) == -1)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}
	}

	TcpSocket::TcpSocket(SocketHandle handle)
		: m_socketHandle(handle)
	{
	}

	TcpSocket::~TcpSocket()
	{
		if (m_socketHandle != InvalidSocket)
		{
			CloseSocket(m_socketHandle);
		}
	}

	TcpSocket::TcpSocket(TcpSocket&& sock) noexcept
		: m_socketHandle(std::exchange(sock.m_socketHandle, InvalidSocket))
    {
    }

    TcpSocket &TcpSocket::operator=(TcpSocket&& sock) noexcept
    {
		m_socketHandle = std::exchange(sock.m_socketHandle, InvalidSocket);
		return *this;
    }

    std::unique_ptr<TcpSocket> TcpSocket::Accept() const
	{
	    struct sockaddr_storage addr;
	    AddressLength size = sizeof(addr);
		const auto client = accept(m_socketHandle, reinterpret_cast<struct sockaddr*>(&addr), &size);
		if (client == InvalidSocket)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}

		return std::unique_ptr<TcpSocket>(new TcpSocket(client));
	}

	size_t TcpSocket::Write(const std::span<const char> data)
	{
		const auto bytesSent = send(m_socketHandle, data.data(), data.size(), 0);
		if (bytesSent == InvalidSocket)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}

		return bytesSent;
	}

	size_t TcpSocket::Read(std::span<char> buffer)
	{
		const auto bytesReceived = recv(m_socketHandle, buffer.data(), buffer.size(), 0);
		if (bytesReceived == InvalidSocket)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}

		return bytesReceived;
	}
}
