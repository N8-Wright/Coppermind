#include "RpcException.h"

namespace Coppermind::Rpc
{
    RpcException::RpcException(std::string_view what, RpcStatus status)
        : m_what(what), m_status(status)
    {
    }

    const char *RpcException::what() const
    {
        return m_what.c_str();
    }

    const RpcStatus RpcException::Status() const noexcept
    {
        return m_status;
    }
}