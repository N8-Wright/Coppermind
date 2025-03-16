#pragma once
#include "RpcUnpacker.h"
#include "RpcPacker.h"

#include <cstdint>
#include <string>
#include <string_view>

class Request
{
	std::string m_name;
	int32_t m_id;
	std::string m_metadata;

public:
	Request()
		: m_name(""), m_id(0), m_metadata("")
	{
	}

	Request(std::string_view name, int32_t id, std::string_view metadata)
		: m_name(name), m_id(id), m_metadata(metadata)
	{
	}

	const std::string& Name() const noexcept
	{
		return m_name;
	}

	const int32_t Id() const noexcept
	{
		return m_id;
	}

	const std::string& Metadata() const noexcept
	{
		return m_metadata;
	}

	void Serialize(Coppermind::Rpc::RpcPacker& packer) const
	{
		packer << m_name;
		packer << m_id;
		packer << m_metadata;
	}

	void Deserialize(Coppermind::Rpc::RpcUnpacker& unpacker)
	{
		m_name = unpacker.Read<std::string>();
		m_id = unpacker.Read<int32_t>();
		m_metadata = unpacker.Read<std::string>();
	}
};