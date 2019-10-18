////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// library library patcher_x86.dll
// spread freely (free of charge)
// copyright: Barinov Alexander (baratorch), e-mail: baratorch@yandex.ru
// the form of implementation of low-level hooks (LoHook) is partly borrowed from Berserker (from ERA)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// version 4.2

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION.
//
//! The library provides:
// - convenient unified centralized
// tools for installing patches and hooks
// in the code of the target program.
// - additional tools: disassembler of the lengths of the opcodes and the function
// copy code with correct transfer of opcodes jmp and call c
// relative addressing
//! Library allows
// - set both simple and complex patches.
// - set high-level hooks, replacing the original functions in
// in the target code for their own, without worrying about the registers of the processor,
// stack, and return to the original code.
// - install high-level hooks one on another
// not excluding and adding functionality of hooks
// set before the last
// - install low-level hooks with high-level access to
// the registers of the processor, the stack, the erased code and the return address in the code
// - cancel any patch and hook installed with this library.
// - find out whether a particular mode is being used that uses the library
// - find out which mod (using the library) installed a specific patch / hook
// - get full access to all patches / hooks installed from other mods
// using this library
// - easily and quickly detect conflicting patches from different mods
// (using this library) 1) marking the log such conflicts as:
// - patches / hooks of different size are set to the same address
// - install patches / hooks overlapping each other with offset
// - patches are installed on top of the hooks and vice versa
// as well as 2) giving the opportunity to look at the dump (common listing) of all patches
// and hooks installed using this library at a particular time.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// LOGGING.
//
// by default in patcher_x86.dll the logging is disabled to enable it,
// you must create the patcher_x86.ini file in the same folder with the only
// write: Logging = 1 (Logging = 0 - disables logging again)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RULES OF USE.
//
// 1) each mod should call the GetPatcher () function 1 time, saving the result
// for example: Patcher * _P = GetPatcher ();
// 2) then using the Patcher :: CreateInstance method, you need to create
// instance of PatcherInstance with its unique name
// for example: PatcherInstance * _PI = _P-> CreateInstance ("MyMod");
// 3) then use the methods of classes Patcher and PatcherInstance
// directly to work with patches and hooks
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <utility>

#define _byte_ unsigned __int8
#define _word_ unsigned __int16
#define _dword_ unsigned __int32

// _bool_ - 4-byte logical type, like BOOL in the Win32 API
// if you really want, you can replace it with BOOL or a single-byte bool, for example

#ifndef _bool_
#define _bool_ __int32
#endif

// all addresses and part of the pointers are defined by this type,
// if it's more convenient for you, you can replace _ptr_ with any other type, void * or int, for example
typedef _dword_ _ptr_;



// in all structures and interfaces of the library there should be alignment - 4 bytes
#pragma pack(push, 4)


// type "variable", is used for the values ​​returned by Patcher :: VarInit and Patcher :: VarFind methods.
class Variable
{
public:
	// returns the value of 'variable' (thread safe handling)
	virtual _dword_ __stdcall GetValue() = 0;
	// sets the value of the 'variable' (thread safe handling)
	virtual void __stdcall SetValue(_dword_ value) = 0;
	// returns a pointer to a value (accessing the value through the pointer is not secure)
	virtual _dword_* __stdcall GetPValue() = 0;
};

// type 'register of flags', size - 32 bits
// used in HookContext
struct FlagsRegister
{
	_dword_ CF : 1; //0
	_dword_ reserved_1 : 1; //1
	_dword_ PF : 1; //2
	_dword_ reserved_3 : 1; //3
	_dword_ AF : 1; //4
	_dword_ reserved_5 : 1; //5
	_dword_ ZF : 1; //6
	_dword_ SF : 1; //7
	_dword_ TF : 1; //8
	_dword_ IF : 1; //9
	_dword_ DF : 1; //10
	_dword_ OF : 1; //11
	_dword_ IOPL : 2; //12-13
	_dword_ NT : 1; //14
	_dword_ reserved_15 : 1; //15
	_dword_ RF : 1; //16
	_dword_ VM : 1; //17
	_dword_ AC : 1; //18
	_dword_ VIF : 1; //19
	_dword_ VIP : 1; //20
	_dword_ ID : 1; //21
	_dword_ reserved_22 : 1; //22
	_dword_ reserved_23 : 1; //23
	_dword_ reserved_24 : 1; //24
	_dword_ reserved_25 : 1; //25
	_dword_ reserved_26 : 1; //26
	_dword_ reserved_27 : 1; //27
	_dword_ reserved_28 : 1; //28
	_dword_ reserved_29 : 1; //29
	_dword_ reserved_30 : 1; //30
	_dword_ reserved_31 : 1; //31
};

// HookContext structure
// used in functions of Lohook hook
struct HookContext
{
	int eax; //register EAX, read / modify		// +0
	int ecx; //register ECX, read / modify		// +4
	int edx; //register EDX, read / modify		// +8
	int ebx; //register EBX, read / modify		// +C
	int esp; //register ESP, read / modify		// +10
	int ebp; //register EBP, read / modify		// +14
	int esi; //register ESI, read / modify		// +18
	int edi; //register EDI, read / modify		// +1C

	_ptr_ return_address; //return address, read / modify	// +20

	FlagsRegister flags;						// +24
	// flags register, read / modify
	// for programming languages ​​that do not support bit fields (eg delphi)
	// flags can be defined as _dword_ type.

	// the Push function has a similar action to the PUSH processor command for the LoHook hook context
	// when used with the hook context set with WriteLoHook or CreateLoHook
	// the size of the memory that can be put on the stack with this function is limited to 128 bytes.
	// when used with the hook context set with WriteLoHookEx or CreateLoHookEx
	// this size is set arbitrarily by calling WriteLoHookEx or CreateLoHookEx.
	inline void Push(int v)
	{
		esp -= 4;
		*(int*)(esp) = v;
	}

	// the Pop function has a similar action to the POP command for the LoHook hook context
	inline int Pop()
	{
		int r = *(int*)(esp);
		esp += 4;
		return r;
	}
	// gives the return address from last call
	_dword_ _retn()
	{
		return *(_dword_*)(ebp + 4);
	}
	// gives the return address from 2 calls ago
	_dword_ _retn2()
	{
		return *(_dword_*)(*(_dword_*)(ebp)+4);
	}
	// gives the return address from 3 calls ago
	_dword_ _retn3()
	{
		return *(_dword_*)(*(_dword_*)*(_dword_*)(ebp)+4);
	}
	// gives the nth argument used in the last call.
	// Should be >= 1
	_dword_ arg_n(int n)
	{
		return *(_dword_*)(ebp + 4 + 4 * n);
	}

	int& ref_arg_n(int n)
	{
		return *reinterpret_cast<int*>(ebp + 4 + 4 * n);
	}

	// gives the nth local variable value used
	// Should be >= 1
	_dword_ local_n(int n)
	{
		return *(_dword_*)(ebp - 4 * n);
	}

	int& ref_local_n(int n)
	{
		return *reinterpret_cast<int*>(ebp - 4 * n);
	}

	// gives the nth local variable address
	// Should be >= 1
	_ptr_ local_stack(int n)
	{
		return (ebp - 4 * n);
	}

	_byte_ AL()
	{
		return (_byte_)eax;
	}

	_byte_& ref_al()
	{
		return *reinterpret_cast<_byte_*>(&eax);
	}

	_byte_ CL()
	{
		return (_byte_)ecx;
	}

	_byte_& ref_cl()
	{
		return *reinterpret_cast<_byte_*>(&ecx);
	}

	_byte_ DL()
	{
		return (_byte_)edx;
	}

	_byte_& ref_dl()
	{
		return *reinterpret_cast<_byte_*>(&edx);
	}

	_byte_ BL()
	{
		return (_byte_)ebx;
	}

	_byte_& ref_bl()
	{
		return *reinterpret_cast<_byte_*>(&ebx);
	}
};



// values ​​returned by a LoHook hook function
#define EXEC_DEFAULT 1 // execute normal code
#define NO_EXEC_DEFAULT 0 // skip normal code
#define SKIP_DEFAULT 0


// values ​​returned by Patch :: GetType ()
#define PATCH_  0
#define LOHOOK_ 1
#define HIHOOK_ 2


// values ​​passed to PatcherInstance :: Write () and PatcherInstance :: CreatePatch ()
#define DATA_ 0
#define CODE_ 1


// Abstract class Patch
// you can create an instance with
// using the methods of class PatcherInstance
class Patch
{
public:
	// returns the address on which to install the patch
	virtual _ptr_ __stdcall GetAddress() = 0;

	// returns the size of the patch
	virtual _dword_ __stdcall GetSize() = 0;

	// returns the unique name of the PatcherInstance instance with which the patch was created
	virtual char* __stdcall GetOwner() = 0;

	// returns the type of the patch
	// for not hook always PATCH_
	// for LoHook always LOHOOK_
	// for HiHook always HIHOOK_
	virtual int  __stdcall GetType() = 0;

	// returns true if the patch is applied and false, if not.
	virtual _bool_ __stdcall IsApplied() = 0;

	// Apply the patch
	// returns> = 0 if the patch / hook is applied successfully
	// (the return value is the sequence number of the patch in the sequence
	// patches applied around the given address, the larger the number,
	// the later the patch was applied)
	// returns -2 if the patch is already applied
	// The result of executing the method is commonly written to the log
	virtual _bool_ __stdcall Apply() = 0;

	// ApplyInsert applies a patch specifying the sequence number in the
	// sequences of patches applied to this address.
	// the return values ​​are the same as in Patch :: Apply
	// the ApplyInsert function, you can pass an argument to the value returned
	// Undo function to apply the patch to the same place it was before the cancel.
	virtual _bool_ __stdcall ApplyInsert(int zorder) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Undo method
	// Undo the patch (hook) (in case the patch is applied last - restores the erased code)
	// Returns the number> = 0 if the patch (hook) was canceled successfully
	// (the return value is the patch number in the sequence
	// patches applied to this address, the larger the number,
	// the later the patch was applied)
	// Returns -2 if the patch has already been canceled (not applied)
	// The result of executing the method is commonly written to the log
	virtual _bool_ __stdcall Undo() = 0;


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Destroy method
	// Destructor
	// Cancels and permanently destroys the patch / hook
	// returns always 1 (for compatibility with earlier versions of the library)
	// The result of the destruction is commonly written to the log
	virtual _bool_ __stdcall Destroy() = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// GetAppliedBefore method
	// returns the patch applied before the data
	// returns NULL if this patch is applied first
	virtual Patch* __stdcall GetAppliedBefore() = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// GetAppliedAfter method
	// returns the patch applied after the given
	// returns NULL if this patch is applied last
	virtual Patch* __stdcall GetAppliedAfter() = 0;

};


// Abstract class LoHook (inherited from Patch, that is, essentially low-hook is a patch)
// you can create an instance with
// using the methods of class PatcherInstance
class LoHook : public Patch
{
};


typedef int(__stdcall *_LoHookFunc_)(LoHook*, HookContext*);

// values ​​passed as the hooktype argument in PatcherInstance :: WriteHiHook and PatcherInstance :: CreateHiHook
#define CALL_ 0
#define SPLICE_ 1
#define FUNCPTR_ 2

// values ​​passed as the subtype argument in PatcherInstance :: WriteHiHook and PatcherInstance :: CreateHiHook
#define DIRECT_  0
#define EXTENDED_ 1
#define SAFE_  2

// values ​​passed as a calltype argument to PatcherInstance :: WriteHiHook and PatcherInstance :: CreateHiHook
#define ANY_  0
#define STDCALL_ 0
#define THISCALL_ 1
#define FASTCALL_ 2
#define CDECL_  3
#define FASTCALL1 1

// Abstract class HiHook (inherited from Patch, that is, essentially hi-hook is a patch)
// you can create an instance using methods from the class PatcherInstance
class HiHook : public Patch
{
public:
	// returns a pointer to the function (on the bridge to the function in the case of SPLICE_),
	// replaced by a hook
	// Attention! Calling a function for an unused hook, you can get
	// irrelevant (but working) value.
	virtual _ptr_ __stdcall GetDefaultFunc() = 0;

	// returns a pointer to the original function (on the bridge to the function in the case of SPLICE_),
	// replaced by a hook (hooks) at this address
	// (that is, it returns GetDefaultFunc () for the first hook applied to this address)
	// Attention! Calling a function for an unused hook, you can get
	// irrelevant (but working) value.
	virtual _ptr_ __stdcall GetOriginalFunc() = 0;

	// returns the return address to the original code
	// can be used inside the hook function
	// SPLICE_ EXTENDED_ or SAFE_ hook to find out where it came from
	// for SPLICE_ DIRECT_ hook function always returns 0 (ie for DIRECT_ hook possibility to find the return address through it - no)
	virtual _ptr_ __stdcall GetReturnAddress() = 0;


	// # ver 2.1
	// sets the value of user hook data
	virtual void __stdcall SetUserData(_dword_ data) = 0;
	// returns the value of the user hook data
	// if not specified by the user, then 0
	virtual _dword_ __stdcall GetUserData() = 0;
};


// Abstract class PatcherInstance
// create / get an instance using the CreateInstance and GetInstance methods of the Patcher class
// directly allows you to create / install patches and hooks in the code,
// adding them to the tree of all the patches / hooks created by the patcher_x86.dll library
class PatcherInstance
{
public:
	//////////////////////////////////////////////////////////////////////////////////////////
	// WriteByte method
	// write a one-byte number at address
	// (creates and applies DATA_ patch)
	// Returns the pointer to the patch
	virtual Patch* __stdcall WriteByte(_ptr_ address, int value) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////
	// WriteWord method
	// write a two-byte number at address
	// (creates and applies DATA_ patch)
	// Returns the pointer to the patch
	virtual Patch* __stdcall WriteWord(_ptr_ address, int value) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////
	// WriteDword method
	// write a four-byte number at address
	// (creates and applies DATA_ patch)
	// Returns the pointer to the patch
	virtual Patch* __stdcall WriteDword(_ptr_ address, int value) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////
	// WriteJmp method
	// writes jmp to opcode at address
	// (creates and applies a CODE_ patch)
	// Returns the pointer to the patch
	// the patch closes an integer number of opcodes,
	// i.e. The size of the patch> = 5, the difference is filled with NOPs.
	virtual Patch* __stdcall WriteJmp(_ptr_ address, _ptr_ to) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// WriteHexPatch method
	// writes to the address address the byte sequence,
	// defined hex_str
	// (creates and applies DATA_ patch)
	// Returns the pointer to the patch
	// hex_str - c-string can contain hexadecimal digits
	// 0123456789ABCDEF (uppercase only!) Other characters
	// when reading by the method hex_str ignored (skipped)
	// convenient to use as an argument to this method
	// copied using Binary copy in OllyDbg
	/* Example:
	Pi->WriteHexPatch(0x57b521, "6A 01 6A 00");
	*/
	virtual Patch* __stdcall WriteHexPatch(_ptr_ address, const char* hex_str) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteCodePatchVA
	// in the original form, the method is not supposed to be used,
	// see (below) the description of the wrapper method WriteCodePatch
	virtual Patch* __stdcall WriteCodePatchVA(_ptr_ address, char* format, _dword_* va_args) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteLoHook
	// creates an address low-level hook (CODE_ patch) and applies it
	// returns pointer to the hook
	// func - function called when the hook triggers
	// must have the form int __stdcall func (LoHook * h, HookContext * c);
	// in HookContext * c are passed for reading / changing
	// processor registers and return address
	// if func returns EXEC_DEFAULT, then
	// after the func is completed, the code is truncated.
	// if - SKIP_DEFAULT - the erased code is not executed
	//
	// ATTENTION!
	// the size of the memory that can be placed on the context stack
	// using c-> esp and c-> Push, is limited to 128 bytes.
	// if you need another restriction, use the WriteLoHookEx or CreateLoHookEx method.
	virtual LoHook* __stdcall WriteLoHook(_ptr_ address, _LoHookFunc_ func) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteHiHook
	// creates a high-level hook at address and applies it
	// returns pointer to the hook
	//
	// new_func - function replacing the original
	//
	// hooktype - hook type:
	// CALL_ - hook to the function call at address
	// the E8 and FF 15 opcodes are supported, otherwise the hook is not installed
	// and the information about this error is written to the log
	// SPLICE_ - hook directly to the FUNCTION itself at address
	// FUNCPTR_ - hook to the function in the pointer (rarely used, mostly for hooks in import tables)
	//
	// subtype - the subtype of the hook:
	// DIRECT_ - new_func has the same form as
	// original replaceable function
	// note: instead of __thiscall f (this)
	// you can use __fastcal f (this_)
	// instead of __thiscall f (this, ...) you can use
	// __fastcall f (this_, no_used_edx, ...)
	// EXTENDED_ - new_func function is passed the first stack argument
	// pointer to the HiHook instance and, in the case
	// conventions of the original __thiscall and __fastcall
	// register arguments are passed by stack second
	// So the function new_func should look like
	//? __stdcall new_func (HiHook * hook,?) For? ? Orig (?)
	//
	// ATTENTION! EXTENDED_ FASTCALL_ supports only functions with 2 or more arguments
	// for __fastcall with 1 argument, use EXTENDED_ FASTCALL_1 / EXTENDED_ THISCALL_
	//
	// SAFE_ is the same as EXTENDED_, but before calling (at the time of the call) GetDefaultFunc () is restored
	// The register values of the EAX, ECX(if not FASTCALL_ and not THISCALL_)
	// EDX (if not FASTCALL_), EBX, ESI, EDI, which were at the time of the call of the replaced function
	//
	//  In the vast majority of cases it is more convenient to use EXTENDED
	//  But DIRECT_ is executed faster because there is no bridge to the new replacement function
	//
	// Calltype - an agreement to call the original replacement f-tion:
	//  STDCALL_
	//  THISCALL_
	//  FASTCALL_
	//  CDECL_
	// need to specify the agreement correctly in order to EXTENDED_ hook correctly
	// built a bridge to a new replacement function
	//
	// CALL_, SPLICE_ hook is the CODE_ patch
	// FUNCPTR_ hook is a DATA_ patch
	//
	virtual HiHook* __stdcall WriteHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) = 0;
	//
	// @@@hooktype@@@
	// CALL_ : on CALL instruction
	// SPLICE_ : on start of subfunction
	//
	// @@@calltype@@@
	// STDCALL_ for __stdcall
	// THISCALL_ for __thiscall
	// FASTCALL_ for __fastcall
	// CDECL_ for __cdecl
	//
	// @@@subtype@@@
	// defaulted to EXTENDED_
	// if you wish to use another subtype, use regular virtual function
	HiHook* WriteHiHook(_ptr_ address, int hooktype, int calltype, void* new_func)
	{
		return WriteHiHook(address, hooktype, EXTENDED_, calltype, new_func);
	}
	// @@@calltype@@@
	// STDCALL_ for __stdcall
	// THISCALL_ for __thiscall
	// FASTCALL_ for __fastcall
	// CDECL_ for __cdecl
	//
	// Automatically sets subtype to EXTENDED_
	// Checks whether to use CALL_ or SPLICE_ hooktype
	// based on the bytes at address
	HiHook* WriteHiHook(_ptr_ address, int calltype, void* new_func)
	{
		if (*reinterpret_cast<_byte_*>(address) == 0xE8 || *reinterpret_cast<_word_*>(address) == 0x15FF)
			return WriteHiHook(address, CALL_, EXTENDED_, calltype, new_func);
		return WriteHiHook(address, SPLICE_, EXTENDED_, calltype, new_func);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Methods Create ...
	// create a patch / hook as well as the corresponding Write ... methods,
	// but do not use it
	// return pointer to patch / hook
	virtual Patch* __stdcall CreateBytePatch(_ptr_ address, int value) = 0;
	virtual Patch* __stdcall CreateWordPatch(_ptr_ address, int value) = 0;
	virtual Patch* __stdcall CreateDwordPatch(_ptr_ address, int value) = 0;
	virtual Patch* __stdcall CreateJmpPatch(_ptr_ address, _ptr_ to) = 0;
	virtual Patch* __stdcall CreateHexPatch(_ptr_ address, char* hex_str) = 0;
	virtual Patch* __stdcall CreateCodePatchVA(_ptr_ address, char* format, _dword_* va_args) = 0;
	virtual LoHook* __stdcall CreateLoHook(_ptr_ address, void* func) = 0;
	virtual HiHook* __stdcall CreateHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ApplyAll method
	// applies all patches / hooks created by this instance of PatcherInstance
	// always returns 1 (for compatibility with earlier versions of the library)
	// (see Patch :: Apply)
	virtual _bool_ __stdcall ApplyAll() = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// UndoAll Method
	// cancels all patches / hooks created by this instance of PatcherInstance
	// i.e. For each of the patches / hooks calls the Undo method
	// always returns 1 (for compatibility with earlier versions of the library)
	// (see Patch :: Undo)
	virtual _bool_ __stdcall UndoAll() = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DestroyAll Method
	// cancels and permanently destroys all patches / hooks created by this instance of PatcherInstance
	// i.e. For each of the patches / hooks calls the Destroy method
	// always returns 1 (for compatibility with earlier versions of the library)
	// (see Patch :: Destroy)
	virtual _bool_ __stdcall DestroyAll() = 0;

	// in the original form, the method is not supposed to be used,
	// see (below) the description of the wrapper method WriteDataPatch
	virtual Patch* __stdcall WriteDataPatchVA(_ptr_ address, char* format, _dword_* va_args);
	// in the original form, the method is not supposed to be used,
	// see (below) the description of the wrapper method WriteDataPatch
	virtual Patch* __stdcall CreateDataPatchVA(_ptr_ address, char* format, _dword_* va_args);


	// GetLastPatchAt method
	// returns NULL if no patch / hook has been applied in the vicinity of the address address,
	// created by this instance of PatcherInstance
	// otherwise returns the last applied patch / hook in the neighborhood of the address address,
	// created by this instance of PatcherInstance
	virtual Patch* __stdcall GetLastPatchAt(_ptr_ address) = 0;

	// UndoAllAt Method
	// cancels the patches applied by this instance of PatcherInstance
	// in the neighborhood of address
	// always returns 1 (for compatibility with earlier versions of the library)
	// (see Patch :: Undo)
	virtual _bool_ __stdcall UndoAllAt(_ptr_ address) = 0;

	// GetFirstPatchAt method
	// returns NULL if no patch / hook has been applied in the vicinity of the address address,
	// created by this instance of PatcherInstance
	// otherwise returns the first applied patch / hook in the neighborhood of the address address,
	// created by this instance of PatcherInstance
	virtual Patch* __stdcall GetFirstPatchAt(_ptr_ address) = 0;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Write Method
	// writes address data / code from memory to address data size size bytes
	// if is_code == 1, then a CODE_ patch is created and written, if 0 is a DATA patch.
	// Returns the pointer to the patch
	virtual Patch* __stdcall Write(_ptr_ address, _ptr_ data, _dword_ size, _bool_ is_code = 0) = 0;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CreatePatch method
	// creates a patch as well as the Write method,
	// but does not apply it
	// return pointer to patch
	virtual Patch* __stdcall CreatePatch(_ptr_ address, _ptr_ data, _dword_ size, _bool_ is_code = 0) = 0;


	// ## ver 2.1
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteLoHookEx
	// is similar to the WriteLoHook method, but has an additional argument
	// stack_delta - the size of the memory that can be placed in the context stack
	// using HookContext :: esp and HookContext :: Push inside func.
	//
	// Return a pointer to the LoHook hook
	virtual LoHook* __stdcall WriteLoHookEx(_ptr_ address, void* func, _dword_ stack_delta) = 0;
	// The CreateLoHookEx Method
	// creates a hook just like WriteLoHookEx,
	// but DO NOT apply it.
	// Return a pointer to the LoHook hook
	virtual LoHook* __stdcall CreateLoHookEx(_ptr_ address, void* func, _dword_ stack_delta) = 0;


	// in the original form, the method is not supposed to be used,
	// see (below) the description of the WriteHexHook shell method
	virtual LoHook* __stdcall WriteHexHookVA(_ptr_ address, _bool_ exec_default, char* hex_str, _dword_* va_args) = 0;
	// in the original form, the method is not supposed to be used,
	// see (below) the description of the CreateHexHook shell method
	virtual LoHook* __stdcall CreateHexHookVA(_ptr_ address, _bool_ exec_default, char* hex_str, _dword_* va_args) = 0;



	// the BlockAt method sets the block to a specific address (specifically to the specific address and not to the neighborhood)
	// for this instance of PatcherInstance
	// after which this instance of PatcherInstance can not apply
	// patches at this address
	virtual void __stdcall BlockAt(_ptr_ address) = 0;

	//## ver 2.6

	// the BlockAllExceptVA method sets the block to all addresses except those specified in va_args
	// as well as the BlockAt method operates with specific addresses and not neighborhoods
	// for this instance of PatcherInstance
	// after which this instance of PatcherInstance can not apply
	// patches for all addresses except those specified.
	// the list of addresses in va_args should end with 0 (zero)
	virtual void __stdcall BlockAllExceptVA(_dword_ *va_args) = 0;


	//## ver 4.0
	// in the original form, the method is not supposed to be used,
	// see (below) the description of the wrapper method WriteAsmPatch
	virtual Patch* __stdcall WriteAsmPatchVA(_ptr_ address, _dword_* va_args) = 0;

	// in the original form, the method is not supposed to be used,
	// see (below) the description of the CreateAsmPatch shell method
	virtual Patch* __stdcall CreateAsmPatchVA(_ptr_ address, _dword_* va_args) = 0;

	// in the original form, the method is not supposed to be used,
	// see (below) the description of the wrapper method WriteAsmHook
	virtual LoHook* __stdcall WriteAsmHookVA(_ptr_ address, _dword_* va_args) = 0;

	// in the original form, the method is not supposed to be used,
	// see (below) the description of the CreateAsmHook shell method
	virtual LoHook* __stdcall CreateAsmHookVA(_ptr_ address, _dword_* va_args) = 0;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// WriteAsmPatch writes a patch to the address address
	// returns pointer to patch
	// arguments ... are strings containing code in assembler
	// all the instructions recognized by OllyDbg 1.04 (up to and including MMX and amd 3DNow!) Are recognized
	// ATTENTION! Unlike OllyDbg, integers that do not have the prefix 0x or postfix h are read as decimal!
	// so do not forget to write the hex numbers explicitly
	// In one line there can be several instructions separated by a ';'
	// The assembler code can contain labels;
	// declaration of the label - label_name: (label name, colon),
	// use label_name (a name without a colon);
	// the maximum length of the label name is 39 characters, the name can contain letters, numbers, symbols '_' and '.';
	// the code can contain the pseudoinstruction times (writes the specified number of times the next instruction)
	// for example, the result "times 3 nop" will be the code 90 90 90
	// code can contain a pseudo-instruction _ExecCopy <address>, <size> (writes code from memory to <address> size <size>)
	// the code can contain pseudoinstructions db <number>, dw <number>, dd <number or label>.
	// The string can contain the character format% d. In this case, the line should be followed by the corresponding number of four-byte numbers (signed / unsigned / addresses / ...)
	// ATTENTION! The last argument (string) must be 0 (NULL)!
	// abstract example: WriteAsmPatch (0x112233, "begin: call% d", MyFunc, "jmp begin", "jne dword [% d]", 0xAABBCC, 0);
	inline Patch* WriteAsmPatch(_ptr_ address, ...)
	{
		return WriteAsmPatchVA(address, (_dword_*)((_ptr_)&address + 4));
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CreateAsmPatch method
	// creates a patch as well as the WriteCodePatch method,
	// but does not apply it
	// returns pointer to patch
	inline Patch* CreateAsmPatch(_ptr_ address, ...)
	{
		return CreateAsmPatchVA(address, (_dword_*)((_ptr_)&address + 4));
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	// WriteAsmHook writes to address address primitive hook
	// namely LoHook without calling a high-level function.
	// the body of the hook is written directly in the call to CreateHexHook or WriteHexHook
	// in the same way as the patch is written using WriteAsmPatch (see WriteAsmPatch)
	// Unlike the WriteAsmPatch method, the code here may or may not contain the _ExecDefault pseudo-command,
	// the code executes the code
	// ATTENTION! In the code there can not be more than one pseudo-command _ExecDefault
	// returns pointer to LoHook hook
	// ATTENTION! The last argument (string) must be 0 (NULL)!
	// abstract example: WriteAsmHook (0x112233, "cmp eax, 0; jne SkipDefault; _ExecDefault; jmp End; SkipDefault: mov ecx, 2; End: retn", 0);
	inline LoHook* WriteAsmHook(_ptr_ address, ...)
	{
		return WriteAsmHookVA(address, (_dword_*)((_ptr_)&address + 4));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method CreateAsmHook
	// creates a hook just like WriteAsmHook,
	// but DO NOT apply it.
	// Return a pointer to the LoHook hook
	inline LoHook* CreateAsmHook(_ptr_ address, ...)
	{
		return CreateAsmHookVA(address, (_dword_*)((_ptr_)&address + 4));
	}



	// WriteHexHook writes at address the most primitive hook
	// namely LoHook without calling a high-level function.
	// the body of the hook is written directly in the call to CreateHexHook or WriteHexHook
	// in the same way as the patch is written using WriteCodePatch (see WriteCodePatch)
	//
	// exec_default - whether to execute the hooked code after executing the hook body
	// returns pointer to LoHook hook
	inline LoHook* WriteHexHook(_ptr_ address, _bool_ exec_default, char* format, ...)
	{
		return WriteHexHookVA(address, exec_default, format, (_dword_*)((_ptr_)&format + 4));
	}
	// CreateHexHook method
	// creates a hook as well as WriteHexHook,
	// but DO NOT apply it.
	// Return a pointer to the LoHook hook
	inline LoHook* CreateHexHook(_ptr_ address, _bool_ exec_default, char* format, ...)
	{
		return CreateHexHookVA(address, exec_default, format, (_dword_*)((_ptr_)&format + 4));
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteCodePatch
	// writes to the address address the byte sequence,
	// defined format and ...
	// (creates and applies a CODE_ patch)
	// Returns the pointer to the patch
	// format - c-string can contain hexadecimal digits
	// 0123456789ABCDEF (uppercase only!),
	// as well as special format-characters (lower case!):
	// %b - (byte) writes a single-byte number from ...
	// %w - (word) writes a two-byte number from ...
	// %d - (dword) writes a four-byte number from ...
	// %j - writes jmp to the address from ...
	// %c - writes сall ...
	// %m - copies the code to the address ... the size ... (ie reads 2 arguments from ...)
	// copying occurs via MemCopyCodeEx (see description)
	// %% - writes a string with format characters from ...
	// %o - (offset) places the address offset in the argument from the argument
	// Complex code, relative to the beginning of the Complex code.
	// %n - write nop opcode, number equal to ... \
		// #0: - #9: - set the label (from 0 to 9) to which you can go with # 0 - # 9 \
		// #0 - #9 - write the address after the opcodes EB, 70 - 7F, E8, E9, 0F80 - 0F8F
	// corresponding label; After other opcodes nothing writes
	// ~b - takes from ... the absolute address and writes the relative offset before it
	// 1 byte in size (used for EB, 70 - 7F opcodes)
	// ~d - takes from ... the absolute address and writes the relative offset before it
	// 4 bytes in size (used for the E8, E9, 0F 80 - 0F 8F opcodes)
	// %. - does nothing (like any other character not declared above after%)
	// abstract example:
	// Patch * p = pi-> WriteCodePatch (address,
	// "#0: %%",
	// "B9 %d %%", this, // mov ecx, this //
	// "BA %d %%", this-> context, // mov edx, context //
	// "%c %%", func, // call func //
	// "83 F8 01 %%", // cmp eax, 1
	// "0F 85 #7 %%", // jne long to label 7 (if func returns 0)
	// "83 F8 02 %%", // cmp eax, 2
	// "0F 85 ~d %%", 0x445544, // jne long to 0x445544 (if func returns 0)
	// "EB #0 %%", // jmp short to label 0
	// "%m %%", address2, size, // exec code copy from address2
	// "#7: FF 25 %d %.", & Return_address); // jmp [& return_address]
	inline Patch* WriteCodePatch(_ptr_ address, char* format, ...)
	{
		return WriteCodePatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// The CreateCodePatch method
	// creates a patch as well as the WriteCodePatch method,
	// but does not apply it
	// returns pointer to patch
	inline Patch* CreateCodePatch(_ptr_ address, char* format, ...)
	{
		return CreateCodePatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteDataPatch
	// writes to the address address the byte sequence,
	// defined format and ...
	// (creates and applies DATA_ patch)
	// Returns the pointer to the patch
	// format - a c-string can contain hexadecimal digits
	// 0123456789ABCDEF (uppercase only!),
	// as well as special format-characters (lower case!):
	// %b - (byte) writes a single-byte number from ...
	// %w - (word) writes a two-byte number from ...
	// %d - (dword) writes a four-byte number from ...
	// %m - copies data to an address ... size ... (ie reads 2 arguments from ...)
	// %% - writes a string with format characters from ...
	// %o - (offset) places the address offset in the argument from the argument
	// Complex code, relative to the beginning of the Complex code.
	// %. - does nothing (like any other character not declared above after%)
	// abstract example:
	// Patch * p = pi-> WriteDataPatch (address,
	// "FF FF FF %d %%", var,
	// "%m %%", address2, size,
	// "AE %.");
	inline Patch* WriteDataPatch(_ptr_ address, char* format, ...)
	{
		return WriteDataPatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CreateDataPatch method
	// creates the patch as well as the WriteDataPatch method,
	// but does not apply it
	// returns pointer to patch
	inline Patch* CreateDataPatch(_ptr_ address, char* format, ...)
	{
		return CreateDataPatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
	}

	inline Patch* __stdcall WriteDword(_ptr_ address, const char* value)
	{
		return WriteDword(address, (int)value);
	}

};

// class Patcher
class Patcher
{
public:
	// îñíîâíûå ìåòîäû:

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// CreateInstance method
	// Creates an instance of the PatcherInstance class, which
	// directly allows you to create patches and hooks and
	// returns a pointer to this instance.
	// owner - the unique name of the PatcherInstance instance
	// the method returns NULL if an instance with the name owner is already created
	// if owner == NULL or owner == "" then
	// the PatcherInstance instance will be created with the module name from
	// the function was called.
	virtual PatcherInstance* __stdcall CreateInstance(const char* owner) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// GetInstance method
	// Returns a pointer to an instance of PatcherInstance
	// with the name owner.
	// the method returns NULL if
	// the instance named owner does not exist (was not created)
	// the module name can be passed as an argument.
	// Is used for :
	// - check if some mod is active, using patcher_x86.dll
	// - get access to all patches and hooks of some mod,
	// using patcher_x86.dll
	virtual PatcherInstance*  __stdcall GetInstance(const char* owner) = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// GetLastPatchAt method
	// returns NULL if no patch / hook is applied in the vicinity of the address address
	// otherwise returns the last applied patch / hook in the neighborhood of address
	// consistently walk through all the patches in a given neighborhood
	// using this method and Patch :: GetAppliedBefore
	virtual Patch* __stdcall GetLastPatchAt(_ptr_ address);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// UndoAllAt Method
	// cancels all patches / hooks in the neighborhood of address
	// always returns 1 (for compatibility with earlier versions of the library)
	virtual Patch* __stdcall UndoAllAt(_ptr_ address);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// SaveDump Method
	// saves to file named file_name
	// - number and names of all instances of PatcherInstance
	// - the number of all applied patches / hooks
	// - list of all applied patches and hooks with their installation addresses, sizes, global order of use, proprietors (PatcherInstance names)
	virtual void __stdcall SaveDump(const char* file_name) = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////// /
	// SaveLog method
	// saves to the file named file_name a log
	// if logging is disabled in the log, there will be 0 entries.
	// enable logging by creating in the library directory
	// the text file patcher_x86.ini with the contents: Logging = 1
	virtual void __stdcall SaveLog(const char* file_name) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// GetMaxPatchSize Method
	// The patcher_x86.dll library imposes some restrictions
	// to the maximum size of the patch,
	// which one can be recognized using the GetMaxPatchSize method
	// (at the moment this is 262144 bytes, i.e., dohrena :))
	virtual int __stdcall GetMaxPatchSize() = 0;

	// additional methods:

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Method WriteComplexDataVA
	// in the original form, the method is not supposed to be used,
	// see (below) the description of the wrapper method WriteComplexString
	virtual int __stdcall WriteComplexDataVA(_ptr_ address, char* format, _dword_* args) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// method GetOpcodeLength
	// so-called. Disassembler of the lengths of the opcodes
	// returns the length in bytes of the opcode at p_opcode
	// returns 0 if opcode is unknown
	virtual int __stdcall GetOpcodeLength(_ptr_ p_opcode) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// method MemCopyCode
	// copies the code from memory to src address in memory at dst
	// MemCopyCode always copies an integer number of opcodes with the size> = size. Be careful!
	// returns the size of the copied code.
	// differs by the action from a simple copy of the memory,
	// that correctly copies the ops E8 (call), E9 (jmp long), 0F80 - 0F8F (j ** long)
	// c relative addressing without knocking down addresses in them, if instructions
	// Forward outside the copied blocking.
	//
	virtual int __stdcall MemCopyCode(_ptr_ dst, _ptr_ src, _dword_ size) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// GetFirstPatchAt method
	// returns NULL if no patch / hook is applied in the vicinity of the address address
	// otherwise returns the first applied patch / hook in the neighborhood of address
	// consistently walk through all the patches in a given neighborhood
	// using this method and Patch :: GetAppliedAfter
	virtual Patch* __stdcall GetFirstPatchAt(_ptr_ address);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// method MemCopyCodeEx
	// copies the code from memory to src address in memory at dst
	// returns the size of the copied code.
	// differs from MemCopyCode in that,
	// that correctly copies the opcodes EB (jmp short), 70 - 7F (j ** short)
	// c relative addressing without knocking down addresses in them, if instructions
	// send outside the copied block (in this case they are replaced by
	// corresponding to E9 (jmp long), 0F80 - 0F8F (j ** long) opcodes.
	// Attention! Because of this, the size of the copied code can be significantly
	// more than copied.
	virtual int __stdcall MemCopyCodeEx(_ptr_ dst, _ptr_ src, _dword_ size) = 0;


	// ver 2.3
	// VarInit Method
	// initializes a "variable" named name and sets the value of "variable" to value
	// if a "variable" with this name already exists, then simply sets its value to value
	// returns a pointer to the "variable" if successful and NULL otherwise
	virtual Variable* __stdcall VarInit(const char* name, _dword_ value) = 0;
	// VarFind method
	// returns a pointer to a "variable" named name, if such was initialized
	// if not, it returns NULL
	virtual Variable* __stdcall VarFind(const char* name) = 0;


	// ver 2.6
	// Method PreCreateInstance
	// Creates a defective PatcherInstance with the specified name.
	// PatcherInstance created in this way can not create patches.
	// This incomplete instance is used to apply the PatcherInstance :: BlockAt and PatcherInstance :: BlockAllExceptVA methods
	// so that you can block addresses before this PatcherInstance is fully created using CreateInstance
	virtual PatcherInstance* __stdcall PreCreateInstance(const char* name) = 0;


	// ver 4.1
	// description in development ...
	virtual int __stdcall WriteAsmCodeVA(_ptr_ address, _dword_* args) = 0;
	virtual _ptr_ __stdcall CreateCodeBlockVA(_dword_* args) = 0;


	// the VarGetValue method returns the value of a "variable" named name
	// if the "variable" with this name was not initialized, it returns default_value
	template<typename ValueType>
	inline ValueType VarGetValue(const char* name, ValueType default_value)
	{
		if (sizeof(ValueType) > 4) return default_value;
		Variable* v = VarFind(name);
		if (v == NULL) return default_value;
		return (ValueType)v->GetValue();
	}

	// the VarValue method returns a reference to the value of the "variable" named name
	// if the "variable" with this name was not initialized, initializes it and sets the value to 0
	// attention, accessing the value of a variable by reference is not intrinsically safe
	template<typename ValueType>
	inline ValueType& VarValue(const char* name)
	{
		if (sizeof(ValueType) > 4) __asm{__asm int 3};

		Variable* v = VarFind(name);
		if (v == NULL) v = VarInit(name, 0);

		if (v == NULL) __asm{__asm int 3};

		return (ValueType&)*v->GetPValue();
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// method WriteComplexData
	// is a more convenient interface
	// method WriteComplexDataVA
	// this method is defined here and not in the library, because Its appearance
	// differs in C and Delphi
	// The method's functionality is almost the same as that of PatcherInstance :: WriteCodePatch
	// (see the description of this method)
	// that is, the method writes to the address address, the sequence of bytes,
	// defined by the arguments format and ...,
	// BUT! DOES NOT create an instance of the Patch class, with all that is implied (i.e., not allowing to undo, access to edit from another mode, etc.)
	// ATTENTION!
	// Use this method only for dynamically creating blocks
	// code, i.e. Write this method only in your memory,
	// a in the code of the program to be modified only with the help of
	// PatcherInstance :: WriteCodePatch
	//
	inline _ptr_ WriteComplexData(_ptr_ address, char* format, ...)
	{
		return WriteComplexDataVA(address, format, (_dword_*)((_ptr_)&format + 4));
	}

	inline HiHook* GetFirstHiHookAt(_ptr_ address)
	{
		Patch* p = GetFirstPatchAt(address);
		while (true)
		{
			if (p == 0) return 0;
			if (p->GetType() == HIHOOK_) return (HiHook*)p;
			p = p->GetAppliedAfter();
		}
	}

	inline HiHook* GetLastHiHookAt(_ptr_ address)
	{
		Patch* p = GetLastPatchAt(address);
		while (true)
		{
			if (p == 0) return 0;
			if (p->GetType() == HIHOOK_) return (HiHook*)p;
			p = p->GetAppliedBefore();
		}
	}
};

// restore the alignment of members of structures and classes
#pragma pack(pop)

#define NOMINMAX
#include <windows.h>
#undef NOMINMAX

#define CALL_0(return_type, func_type, address) ((return_type(func_type *)(void))address)()

//////////////////////////////////////////////////////////////////
// function GetPatcher
// loads the library and, by calling the only exported
// function _GetPatcherX86@0, returns a pointer to the Patcher object,
// through which the entire functionality of the library patcher_x86.dll is available
// return NULL on failure
// function is called 1 time, which is obvious from its definition
inline Patcher* GetPatcher()
{
	static int calls_count = 0;
	if (calls_count > 0)
		return NULL;
	calls_count++;
	HMODULE pl = LoadLibraryA("patcher_x86.dll");
	if (pl)
	{
		FARPROC f = GetProcAddress(pl, "_GetPatcherX86@0");
		if (f)
			return CALL_0(Patcher*, __stdcall, f);
	}
	return NULL;
}

#ifndef _LHF_
// * predefined macro for LoHook functions
// * LoHook *h and HookContext *c are pre-defined
// * e.g. _LHF_(MyFunction) {}
#define _LHF_(func) int __stdcall func(LoHook *h, HookContext *c)
#endif