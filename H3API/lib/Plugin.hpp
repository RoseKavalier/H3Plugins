#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include "patcher_x86.hpp"
#include "H3Types.hpp"

class Plugin
{
public:
	/**
	 * @brief Based on where the function trampoline is to be installed.
	 */
	enum HType
	{
		/**
		 * @brief Original function is called at the specified address.
		 */
		Call = 0,
		/**
		 * @brief Original function *begins* at the specified address.
		 */
		Splice = 1,
		/**
		 * @brief Original function is provided as a pointer (e.g. virtual table, argument).
		 */
		Pointer = 2,
	};
	/**
	 * @brief How the function trampoline will be created.
	 */
	enum HSubtype
	{
		/**
		 * @brief No bridge is created, control is directly given to the replacement function.
		 * In this case, the function convention must be the same as the original one and will
		 * not have a HiHook* argument.
		 * For __thiscall functions, you may use __fastcall(this, dummy_value, arg1, ...).
		 */
		Direct = 0,
		/**
		 * @brief A bridge is created, passing a HiHook* as first argument to the replacement
		 * function which should be of __stdcall calling convention.
		 * Consider this your default subtype unless you have specific needs.
		 */
		Extended = 1,
		/**
		 * @brief The same as Extended, however all registers are safely restored
		 * to their initial values in the bridge.
		 */
		Safe = 2,
	};
	/**
	 * @brief The calling convention of the function being replaced.
	 */
	enum HConvention
	{
		/**
		 * @brief Original function uses __stdcall calling convention.
		 */
		Stdcall = 0,
		/**
		 * @brief Original function uses __thiscall calling convention.
		 * If using a Direct subtype, you can declare a __fastcall(this, unused_parameter, arg1, ...)
		 * function which will allow you to simulate a __thiscall calling convention.
		 */
		Thiscall = 1,
		/**
		 * @brief Original function uses __fastcall calling convention.
		 */
		Fastcall = 2,
		/**
		 * @brief Original function uses __cdecl calling convention.
		 */
		Cdecl = 3,
	};
	enum Status
	{
		AlreadyInitiated = -1,
		Success          = 0,
		NoPatcher        = 1,
		InstanceExists   = 2,
		InstanceFailed   = 3,
	};

	Plugin();
	/**
	 * @brief Wraps around access to patcher_x86's api to get a copy of Patcher*
	 * and create your own PatcherInstance*.
	 *
	 * @param plugin_name The name of the PatcherInstance you wish to create.
	 * @return Information about the success or failure of the operation.
	*/
	Status Init(LPCSTR plugin_name);

	//============================================================
	//
	//                PatcherInstance methods
	//
	//============================================================

	/**
	 * @brief Creates a local trampoline to a function with register access.
	 *
	 * @param address The location where to place the hook.
	 * @param func A int(__stdcall *)(LoHook*, HookContext*); type function.
	 * @return Created LoHook* with specified parameters
	 */
	LoHook* Create(_ptr_ address, _LoHookFunc_ func);
	/**
	 * @brief Creates a local trampoline to a function with register access.
	 *
	 * @param address The location where to place the hook.
	 * @param func A int(__stdcall *)(LoHook&, HookContext&); type function.
	 * @return Created LoHook* with specified parameters
	 */
	LoHook* Create(_ptr_ address, _LoHookReferenceFunc_ func);

	/**
	 * @brief Creates a trampoline to replace a function, providing access to function arguments but not registers.
	 * The hook type is automatically deduced between Call and Splice and subtype is assumed to be Extended.
	 *
	 * @tparam T Typename to stand in for the hooked function without annoying warnings.
	 * @param address The location where to place the hook.
	 * @param call_type The convention of the function being replaced, Stdcall, Thiscall, Fastcall or Cdecl
	 * @param func A function matching HiHook requirements.
	 * @return Created HiHook* with specified parameters.
	 */
	template<typename T>
	HiHook* Create(_ptr_ address, HConvention call_type, T func);
	/**
	 * @brief Creates a trampoline to replace a function, providing access to function arguments but not registers.
	 * The hook subtype is assumed to be Extended.
	 *
	 * @tparam T Typename to stand in for the hooked function without annoying warnings.
	 * @param address The location where to place the hook.
	 * @param function_type Depends on where the hook is located: see HType description.
	 * @param call_type The convention of the function being replaced: see HConvention description.
	 * @param func A function matching HiHook requirements.
	 * @return Created HiHook* with specified parameters.
	 */
	template<typename T>
	HiHook* Create(_ptr_ address, HType function_type, HConvention call_type, T func);
	/**
	 * @brief Creates a trampoline to replace a function, providing access to function arguments but not registers.
	 * The hook subtype is assumed to be Extended.
	 *
	 * @tparam T Typename to stand in for the hooked function without annoying warnings.
	 * @param address The location where to place the hook.
	 * @param function_type Depends on where the hook is located: see HType description.
	 * @param hook_subtype Controls how the trampoline will be created: see HSubtype description.
	 * @param call_type The convention of the function being replaced: see HConvention description.
	 * @param func A function matching HiHook requirements.
	 * @return Created HiHook* with specified parameters.
	 */
	template<typename T>
	HiHook* Create(_ptr_ address, HType function_type, HSubtype hook_subtype, HConvention call_type, T func);

	/**
	 * @brief Creates and applies a local trampoline to a function with register access.
	 *
	 * @param address The location where to place the hook.
	 * @param func A int(__stdcall *)(LoHook*, HookContext*); type function.
	 * @return Applied LoHook* with specified parameters
	 */
	LoHook* Hook(_ptr_ address, _LoHookFunc_ func);
	/**
	 * @brief Creates and applies a local trampoline to a function with register access.
	 *
	 * @param address The location where to place the hook.
	 * @param func A int(__stdcall *)(LoHook&, HookContext&); type function.
	 * @return Applied LoHook* with specified parameters
	 */
	LoHook* Hook(_ptr_ address, _LoHookReferenceFunc_ func);

	/**
	 * @brief Creates and appliesa trampoline to replace a function,
	 * providing access to function arguments but not registers.
	 * The hook type is automatically deduced between Call and Splice and subtype is assumed to be Extended.
	 *
	 * @tparam T Typename to stand in for the hooked function without annoying warnings.
	 * @param address The location where to place the hook.
	 * @param call_type The convention of the function being replaced, Stdcall, Thiscall, Fastcall or Cdecl
	 * @param func A function matching HiHook requirements.
	 * @return Applied HiHook* with specified parameters.
	 */
	template<typename T>
	HiHook* Hook(_ptr_ address, HConvention call_type, T func);
	/**
	 * @brief Creates and applies a trampoline to replace a function,
	 * providing access to function arguments but not registers.
	 * The hook subtype is assumed to be Extended.
	 *
	 * @tparam T Typename to stand in for the hooked function without annoying warnings.
	 * @param address The location where to place the hook.
	 * @param function_type Depends on where the hook is located: see HType description.
	 * @param call_type The convention of the function being replaced: see HConvention description.
	 * @param func A function matching HiHook requirements.
	 * @return Applied HiHook* with specified parameters.
	 */
	template<typename T>
	HiHook* Hook(_ptr_ address, HType function_type, HConvention call_type, T func);
	/**
	 * @brief Creates and applies a trampoline to replace a function,
	 * providing access to function arguments but not registers.
	 * The hook subtype is assumed to be Extended.
	 *
	 * @tparam T Typename to stand in for the hooked function without annoying warnings.
	 * @param address The location where to place the hook.
	 * @param function_type Depends on where the hook is located: see HType description.
	 * @param hook_subtype Controls how the trampoline will be created: see HSubtype description.
	 * @param call_type The convention of the function being replaced: see HConvention description.
	 * @param func A function matching HiHook requirements.
	 * @return Applied HiHook* with specified parameters.
	 */
	template<typename T>
	HiHook* Hook(_ptr_ address, HType function_type, HSubtype hook_subtype, HConvention call_type, T func);

	/**
	 * @brief Writes a JMP instruction between the two specified addresses.
	 *
	 * @param address Location of the JMP instruction.
	 * @param destination End point of the JMP instruction.
	 * @return Applied Patch* resulting of the operation.
	*/
	Patch* WriteJmp(_ptr_ address, _ptr_ destination);
	/**
	 * @brief Replaces a byte in memory.
	 *
	 * @param address Location of the patch.
	 * @param value The new data to be used.
	 * @return Applied Patch* resulting of the operation.
	*/
	Patch* WriteByte(_ptr_ address, _byte_ value);
	/**
	 * @brief Replaces a word in memory.
	 *
	 * @param address Location of the patch.
	 * @param value The new data to be used.
	 * @return Applied Patch* resulting of the operation.
	*/
	Patch* WriteWord(_ptr_ address, _word_ value);
	/**
	 * @brief Replaces a dword in memory.
	 *
	 * @param address Location of the patch.
	 * @param value The new data to be used.
	 * @return Applied Patch* resulting of the operation.
	*/
	Patch* WriteDword(_ptr_ address, _dword_ value);
	/**
	 * @brief Writes a series of hex bytes at the specified location.
	 *
	 * @param address Location of the patch.
	 * @param hex_string A string of characters in hexadecimal format only, with spaces allowed.
	 * "0123456789 ABCDEF abcdef" are all valid inputs.
	 * @return Applied Patch* resulting of the operation.
	*/
	Patch* WriteHexPatch(_ptr_ address, LPCSTR hex_string);

	//============================================================
	//
	//                 h3::H3Patcher methods
	//
	//============================================================

	/**
	 * @brief Automatically writes a value to memory.
	 * Warning! Be sure that the type is well-defined or you may patch an integer by default.
	 *
	 * @tparam T Type of value.
	 * @param address Location of patch.
	 * @param value New data to write.
	*/
	template<typename T>
	BOOL Write(_ptr_ address, T value);
	/**
	 * @brief Replace a byte in memory, using lightweight h3::H3Patcher methods.
	 *
	 * @param address Location of the replacement.
	 * @param value The new data to be used.
	 */
	BOOL BytePatch(_ptr_ address, _byte_ value);
	/**
	 * @brief Replace a word in memory, using lightweight h3::H3Patcher methods.
	 *
	 * @param address Location of the replacement.
	 * @param value The new data to be used.
	 */
	BOOL WordPatch(_ptr_ address, _word_ value);
	/**
	 * @brief Replace a dword in memory, using lightweight h3::H3Patcher methods.
	 *
	 * @param address Location of the replacement.
	 * @param value The new data to be used.
	 */
	BOOL DwordPatch(_ptr_ address, _dword_ value);
	/**
	 * @brief Replaces an array of bytes in memory, using lightweight h3::H3Patcher methods.
	 *
	 * @param address Location of the replacement.
	 * @param values An array of bytes to replace existing data
	 * e.g. {0xA2, 0x1F, 0x90, 0x90, 0x90}
	*/
	template<size_t _Size>
	BOOL HexPatch(_ptr_ address, const _byte_(&values)[_Size]);
	/**
	 * @brief Writes the most basic type of hook there is using lightweight h3::H3Patcher methods.
	 * You are in charge or restoring the original code in your function.
	 *
	 * @param address Location of the hook.
	 * @param function __declspec(naked)(void *)() function type
	 * @param total_bytes The number of bytes to be replaced by JMP and NOP instructions.
	 */
	BOOL Hook(_ptr_ address, H3NakedFunction function, _dword_ total_bytes = 5);
	/**
	 * @brief writes pointer of data type (its address)
	 *
	 * @tparam T any data type
	 * @param address address to write to
	 * @param data a global or constexpr array, double or other value to be written as a pointer
	 */
	template<typename T>
	BOOL AddressOfPatch(const UINT address, const T& data);
	/**
	 * @brief writes pointer of data type (its address) to multiple locations
	 *
	 * @tparam Type any data type
	 * @tparam size number of items in \p address array
	 * @param address Locations to write to
	 * @param data a global or constexpr array, double or other value to be written as a pointer
	 * @return H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4>::type
	 */
	template<typename Type, size_t size>
	BOOL AddressOfPatch(const UINT(&address)[size], const Type& data);
	/**
	 * @brief Writes data type to an object reference without having to dereference to obtain their address.
	 *
	 * @tparam T Type of the object.
	 * @param reference Data member of the object to modify.
	 * @param data Replacement value.
	 */
	template<typename T>
	BOOL ObjectPatch(T& reference, T data);

	//============================================================
	//
	//                Patcher methods
	//
	//============================================================

	/**
	 * @brief Find a patcher_x86 Variable.
	 *
	 * @param name The name of the variable you wish to get.
	 * @return The specified Variable*, nullptr if not found.
	 */
	Variable* VarFind(LPCSTR name);
	template<typename T>
	/**
	 * @brief Creates a patcher_x86 Variable with the specified value.
	 *
	 * @tparam T Any type of data, although it should be no more than 4 bytes.
	 * @param name The associated name with the Variable.
	 * @param value The data you wish to store in the Variable.
	 * @return The created Variable* with specified parameters.
	 */
	Variable* VarInit(LPCSTR name, T value);
	/**
	 * @brief Safely performs VarFind() and GetValue operations.
	 *
	 * @tparam T Any type of data, although it should be no more than 4 bytes.
	 * @param name The associated name with the Variable.
	 * @param default_value The default value to be used in case the Variable is not found.
	 * @return Either the Variable's value or default_value.
	 */
	template<typename T>
	T VarGetValue(LPCSTR name, T default_value);

	/**
	 * @brief Finds the first HiHook* applied at a certain location.
	 *
	 * @param address The location you wish to search.
	 * @return The first HiHook* or nullptr if there are none.
	 */
	HiHook* GetFirstHiHookAt(_ptr_ address);
	/**
	 * @brief Finds the last HiHook* applied at a certain location.
	 *
	 * @param address The location you wish to search.
	 * @return The last HiHook* or nullptr if there are none.
	 */
	HiHook* GetLastHiHookAt(_ptr_ address);
	/**
	 * @brief Get access to another existing PatcherInstance.
	 *
	 * @param instance_name The name of the instance sought.
	 * @return PatcherInstance* of the specified instance, nullptr if not found.
	 */
	PatcherInstance* GetInstance(LPCSTR instance_name);

protected:

	static constexpr LPCSTR ErrorInitiated = "A previous attempt to initiate this plugin was already done.";
	static constexpr LPCSTR ErrorNoPatcher = "Could not obtain patcher_x86.";
	static constexpr LPCSTR ErrorInstanceExists = "This Patcher Instance already exists.";
	static constexpr LPCSTR ErrorInstanceFailed = "Could not create the requested Patcher Instance.";
	VOID ShowError(LPCSTR plugin_name, Status status);
	BOOL isCall(_ptr_ address);

	Patcher* m_patcher;
	PatcherInstance* m_instance;
};

template<typename T>
HiHook* Plugin::Create(_ptr_ address, HConvention call_type, T func)
{
	const BOOL is_call = isCall(address);
	return Create(address, is_call ? HType::Call : HType::Splice, HSubtype::Extended, call_type, func);
}

template<typename T>
HiHook* Plugin::Create(_ptr_ address, HType function_type, HConvention call_type, T func)
{
	return Create(address, function_type, HSubtype::Extended, call_type, func);
}

template<typename T>
HiHook* Plugin::Create(_ptr_ address, HType function_type, HSubtype hook_subtype, HConvention call_type, T func)
{
	return m_instance->CreateHiHook(address, static_cast<int>(function_type), static_cast<int>(hook_subtype),
		static_cast<int>(call_type), reinterpret_cast<void*>(func));
}

template<typename T>
HiHook* Plugin::Hook(_ptr_ address, HConvention call_type, T func)
{
	const BOOL is_call = isCall(address);
	return Hook(address, is_call ? HType::Call : HType::Splice, HSubtype::Extended, call_type, func);
}

template<typename T>
HiHook* Plugin::Hook(_ptr_ address, HType function_type, HConvention call_type, T func)
{
	return Hook(address, function_type, HSubtype::Extended, call_type, func);
}

template<typename T>
HiHook* Plugin::Hook(_ptr_ address, HType function_type, HSubtype hook_subtype, HConvention call_type, T func)
{
	return m_instance->WriteHiHook(address, static_cast<int>(function_type), static_cast<int>(hook_subtype),
		static_cast<int>(call_type), reinterpret_cast<void*>(func));
}

template<typename T>
BOOL Plugin::AddressOfPatch(const UINT address, const T& data)
{
	return h3::H3Patcher::AddressOfPatch(address, data);
}

template<typename Type, size_t size>
BOOL Plugin::AddressOfPatch(const UINT(&address)[size], const Type& data)
{
	return h3::H3Patcher::AddressOfPatch(address, data);
}

template<typename T>
BOOL Plugin::ObjectPatch(T& reference, T data)
{
	return h3::H3Patcher::ObjectPatch(reference, data);
}

template<typename T>
BOOL Plugin::Write(_ptr_ address, T value)
{
	return h3::H3Patcher::WriteValue(address, value);
}

template<size_t _Size>
BOOL Plugin::HexPatch(_ptr_ address, const UINT8(&values)[_Size])
{
	return h3::H3Patcher::WriteValues(address, values);
}

template<typename T>
Variable* Plugin::VarInit(LPCSTR name, T value)
{
	return m_patcher->VarInit(name, UINT32(value));
}

template<typename T>
T Plugin::VarGetValue(LPCSTR name, T default_value)
{
	return m_patcher->VarGetValue(name, default_value);
}

#endif /* PLUGIN_HPP */