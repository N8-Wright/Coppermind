#include "RpcException.h"

namespace Coppermind::Rpc
{
    RpcException::RpcException(std::string_view what)
        : m_what(what)
    {
    }

    const char *RpcException::what() const
    {
        return m_what.c_str();
    }
}