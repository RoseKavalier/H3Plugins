#include "Plugin.hpp"
#include "h3api/H3_Memory.hpp"

Plugin::Plugin() :
	m_patcher(), m_instance()
{
}

Plugin::Status Plugin::Init(LPCSTR plugin_name)
{
	if (m_patcher)
		return Status::AlreadyInitiated;
	if (NULL == (m_patcher = GetPatcher()))
		return Status::NoPatcher;
	if (m_patcher->GetInstance(plugin_name))
		return Status::InstanceExists;
	if (!(m_instance = m_patcher->CreateInstance(plugin_name)))
		return Status::InstanceFailed;
	return Status::Success;
}

LoHook* Plugin::Create(_ptr_ address, _LoHookFunc_ func)
{
	return m_instance->CreateLoHook(address, func);
}

LoHook* Plugin::Create(_ptr_ address, _LoHookReferenceFunc_ func)
{
	return Create(address, _LoHookFunc_(func));
}

LoHook* Plugin::Hook(_ptr_ address, _LoHookFunc_ func)
{
	return m_instance->WriteLoHook(address, func);
}

LoHook* Plugin::Hook(_ptr_ address, _LoHookReferenceFunc_ func)
{
	return m_instance->WriteLoHook(address, func);
}

BOOL Plugin::Hook(_ptr_ address, H3NakedFunction function, _dword_ bytes_to_write /*= 5*/)
{
	return h3::H3Patcher::NakedHook(address, function, bytes_to_write);
}

Patch* Plugin::WriteJmp(_ptr_ address, _ptr_ destination)
{
	return m_instance->WriteJmp(address, destination);
}

Patch* Plugin::WriteByte(_ptr_ address, _byte_ value)
{
	return m_instance->WriteByte(address, value);
}

Patch* Plugin::WriteWord(_ptr_ address, _word_ value)
{
	return m_instance->WriteWord(address, value);
}

Patch* Plugin::WriteDword(_ptr_ address, _dword_ value)
{
	return m_instance->WriteDword(address, value);
}

Patch* Plugin::WriteHexPatch(_ptr_ address, LPCSTR hex_string)
{
	return m_instance->WriteHexPatch(address, hex_string);
}

BOOL Plugin::BytePatch(_ptr_ address, _byte_ value)
{
	return h3::H3Patcher::BytePatch(address, value);
}

BOOL Plugin::WordPatch(_ptr_ address, _word_ value)
{
	return h3::H3Patcher::WordPatch(address, value);
}

BOOL Plugin::DwordPatch(_ptr_ address, _dword_ value)
{
	return h3::H3Patcher::DwordPatch(address, value);
}

Variable* Plugin::VarFind(LPCSTR name)
{
	return m_patcher->VarFind(name);
}

HiHook* Plugin::GetFirstHiHookAt(_ptr_ address)
{
	return m_patcher->GetFirstHiHookAt(address);
}

HiHook* Plugin::GetLastHiHookAt(_ptr_ address)
{
	return m_patcher->GetLastHiHookAt(address);
}

PatcherInstance* Plugin::GetInstance(LPCSTR instance_name)
{
	return m_patcher->GetInstance(instance_name);
}

VOID Plugin::ShowError(LPCSTR plugin_name, Status status)
{
	LPCSTR message;
	switch (status)
	{
	case Status::AlreadyInitiated:
		message = ErrorInitiated;
		break;
	case Status::InstanceExists:
		message = ErrorInstanceExists;
		break;
	case Status::InstanceFailed:
		message = ErrorInstanceFailed;
		break;
	case Status::NoPatcher:
		message = ErrorNoPatcher;
		break;
	default:
		return;
	}
	
	h3::H3Error::ShowError(message, plugin_name);
}

BOOL Plugin::isCall(_ptr_ address)
{
	return *reinterpret_cast<_byte_*>(address) == h3::H3Patcher::CALL
		|| *reinterpret_cast<_word_*>(address) == h3::H3Patcher::CALL_DWORD;
}