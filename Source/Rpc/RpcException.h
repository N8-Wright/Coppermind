#pragma once
#include "Rpc.h"

#include <exception>
#include <string>
#include <string_view>
namespace Coppermind::Rpc
{
    class RpcException : public std::exception
    {
        RpcStatus m_status;
        std::string m_what;
    public:
        RpcException(std::string_view what, RpcStatus status = RpcStatus::InternalError);
        const char* what() const override;
        const RpcStatus Status() const noexcept;
    };
}