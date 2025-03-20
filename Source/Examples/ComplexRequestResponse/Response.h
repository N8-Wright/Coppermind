#pragma once
#include "RpcUnpacker.h"
#include "RpcPacker.h"

#include <cstdint>
#include <string>
#include <string_view>

class Response
{
	std::string m_result;
	int32_t m_id;

public:
    Response()
		: m_result(""), m_id(0)
	{
	}

	Response(std::string_view result, int32_t id)
		: m_result(result), m_id(id)
	{
	}

	const std::string& Result() const noexcept
	{
		return m_result;
	}

	const int32_t Id() const noexcept
	{
		return m_id;
	}

	void Serialize(Coppermind::Rpc::RpcPacker& packer) const
	{
		packer << m_result;
		packer << m_id;
	}

	void Deserialize(Coppermind::Rpc::RpcUnpacker& unpacker)
	{
		m_result = unpacker.Read<std::string>();
		m_id = unpacker.Read<int32_t>();
	}
};