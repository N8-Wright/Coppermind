#pragma once
#include "Reader.h"
#include "Writer.h"

#include "Networking.h"
#include <string_view>
#include <memory>
#include <span>
namespace Coppermind::Net
{
	class TcpSocket : public IO::Reader, public IO::Writer
	{
		SocketHandle m_socketHandle;

		TcpSocket(std::string_view port);
		TcpSocket(std::string_view address, std::string_view port);
		TcpSocket(SocketHandle);

		friend Network;
	public:
		~TcpSocket();

		TcpSocket(const TcpSocket&) = delete;
		TcpSocket& operator=(const TcpSocket&) = delete;
		TcpSocket(TcpSocket&&) noexcept;
		TcpSocket& operator=(TcpSocket&&) noexcept;

		std::unique_ptr<TcpSocket> Accept() const;
		virtual size_t Write(const std::span<const char> data) override;
		virtual size_t Read(std::span<char> buffer) override;
	};
}