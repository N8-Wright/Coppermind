#pragma once
#include <exception>
#include <string>
#include <string_view>
namespace Coppermind::Rpc
{
    class RpcException : public std::exception
    {
        std::string m_what;
    public:
        RpcException(std::string_view what);
        const char* what() const override;
    };
}