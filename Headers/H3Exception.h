//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3EXCEPTION_H_
#define _H3EXCEPTION_H_

#pragma once

#include "H3Base.h"
#include "H3Varia.h"
#include <eh.h>
#include <exception>
#include <Psapi.h>

// * Only available if stack unwinding is enabled (enable C++ exceptions).
// * you should use /EHa compiler flag when using this file
#ifdef _CPPUNWIND

// * forward declaration
namespace NH3Error
{
	inline void h3_trans_func(UINT code, EXCEPTION_POINTERS* ep);
}

// * Catches std::exception and SEH errors
// * when combined with H3SEHandler
class H3Exception : public std::exception
{
public:
	H3Exception(LPCSTR message) : exception(message)
	{}
	H3Exception(const H3String &str) : exception(str.String())
	{}
	// * creates an in-game dialog showing the error
	VOID ShowInGame() { F_MessageBox(what()); }
	// * creates an in-game dialog showing the error
	BOOL ShowInGameLog() { return F_MessageBoxChoice(what()); }
	// * creates a out-of-game messagebox showing the error
	VOID ShowMessagebox() { H3Error::ShowError(what()); }
	// * creates a out-of-game messagebox showing the error
	BOOL ShowMessageboxLog() { return H3Error::ShowErrorChoice(what()); }
	//TODO add logging options to external file...
	VOID LogError(const H3String &path) { LogError(path.String()); }
	VOID LogError(LPCSTR path);

};

// * create a H3SEHandler object on the stack where you want to use try{} catch{}
// * to receive the error code, use the what() exception member function
// * e.g. this snippet would show an error in-game without crashing the game
// * H3SEHandler seh;
// * try
// * {
// *     some stuff that can create an error...
// * }
// * catch (H3Exception& e)
// * {
// *	e.ShowInGame();
// * }
class H3SEHandler
{
	const _se_translator_function old_SE_translator;
public:
	H3SEHandler()
		: old_SE_translator{ _set_se_translator(NH3Error::h3_trans_func) }
	{}
	~H3SEHandler()
	{
		_set_se_translator(old_SE_translator);
	}
};

#pragma region helper class
namespace NH3Error
{
	// * based on https://stackoverflow.com/a/13642727
	class H3SEInfo
	{
	public:
		static LPCSTR opDescription(const ULONG opcode)
		{
			switch (opcode)
			{
			case 0: return "read";
			case 1: return "write";
			case 8: return "user-mode data execution prevention (DEP) violation";
			default: return "unknown";
			}
		}

		static LPCSTR seDescription(const UINT& code)
		{
			switch (code)
			{
			case EXCEPTION_ACCESS_VIOLATION:
				return "EXCEPTION_ACCESS_VIOLATION [0xC0000005]";
			case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
				return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED [0xC000008C]";
			case EXCEPTION_BREAKPOINT:
				return "EXCEPTION_BREAKPOINT [0x80000003]";
			case EXCEPTION_DATATYPE_MISALIGNMENT:
				return "EXCEPTION_DATATYPE_MISALIGNMENT [0x80000002]";
			case EXCEPTION_FLT_DENORMAL_OPERAND:
				return "EXCEPTION_FLT_DENORMAL_OPERAND [0xC000008D]";
			case EXCEPTION_FLT_DIVIDE_BY_ZERO:
				return "EXCEPTION_FLT_DIVIDE_BY_ZERO [0xC000008E]";
			case EXCEPTION_FLT_INEXACT_RESULT:
				return "EXCEPTION_FLT_INEXACT_RESULT [0xC000008F]";
			case EXCEPTION_FLT_INVALID_OPERATION:
				return "EXCEPTION_FLT_INVALID_OPERATION [0xC0000090]";
			case EXCEPTION_FLT_OVERFLOW:
				return "EXCEPTION_FLT_OVERFLOW [0xC0000091]";
			case EXCEPTION_FLT_STACK_CHECK:
				return "EXCEPTION_FLT_STACK_CHECK [0xC0000092]";
			case EXCEPTION_FLT_UNDERFLOW:
				return "EXCEPTION_FLT_UNDERFLOW [0xC0000093]";
			case EXCEPTION_ILLEGAL_INSTRUCTION:
				return "EXCEPTION_ILLEGAL_INSTRUCTION [0xC000001D]";
			case EXCEPTION_IN_PAGE_ERROR:
				return "EXCEPTION_IN_PAGE_ERROR [0xC0000006]";
			case EXCEPTION_INT_DIVIDE_BY_ZERO:
				return "EXCEPTION_FLT_DIVIDE_BY_ZERO [0xC000008E]";
			case EXCEPTION_INT_OVERFLOW:
				return "EXCEPTION_INT_OVERFLOW [0xC0000095]";
			case EXCEPTION_INVALID_DISPOSITION:
				return "EXCEPTION_INVALID_DISPOSITION [0xC0000026]";
			case EXCEPTION_NONCONTINUABLE_EXCEPTION:
				return "EXCEPTION_NONCONTINUABLE_EXCEPTION [0xC0000025]";
			case EXCEPTION_PRIV_INSTRUCTION:
				return "EXCEPTION_PRIV_INSTRUCTION [0xC0000096]";
			case EXCEPTION_SINGLE_STEP:
				return "EXCEPTION_SINGLE_STEP [0x80000004]";
			case EXCEPTION_STACK_OVERFLOW:
				return "EXCEPTION_STACK_OVERFLOW [0xC00000FD]";
			case EXCEPTION_INVALID_HANDLE:
				return "EXCEPTION_INVALID_HANDLE [0xC0000008]";
			case EXCEPTION_GUARD_PAGE:
				return "EXCEPTION_GUARD_PAGE [0x80000001]";
			default:
				return "UNKNOWN EXCEPTION";
			}
		}

		static VOID information(H3String &error, _EXCEPTION_POINTERS* ep, bool has_exception_code = false, UINT code = 0, bool log_error = true)
		{
			HMODULE hm;
			GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)(ep->ExceptionRecord->ExceptionAddress), &hm);
			char module_name[MAX_PATH];

			IMAGE_DOS_HEADER* pDOSHeader = (IMAGE_DOS_HEADER*)hm;
			IMAGE_NT_HEADERS* pNTHeaders = (IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
			DWORD base_of_code = ((DWORD)hm + pNTHeaders->OptionalHeader.BaseOfCode);

			DWORD mn_len = GetModuleFileNameA(hm, module_name, MAX_PATH);
			// null terminate for XP
			module_name[mn_len] = 0;

			// find short name of module
			PCHAR module_name_short = module_name + mn_len - 1;
			for (int i = mn_len - 1; i >= 0; --i, --module_name_short)
				if (*module_name_short == '\\')
				{
					++module_name_short;
					break;
				}

			CHAR buffer[512];

			error += "SE ";
			if (has_exception_code)
				error += seDescription(code);
			error += " at address offset 0x";
			// address offset of error
			int len = sprintf_s(buffer, sizeof(buffer), "%08X", (DWORD)ep->ExceptionRecord->ExceptionAddress - base_of_code);
			error.Append(buffer, len);
			error += " inside ";
			error += module_name_short;
			error += ".\n";

			if (has_exception_code && (code == EXCEPTION_ACCESS_VIOLATION || code == EXCEPTION_IN_PAGE_ERROR))
			{
				error += "Invalid operation: ";
				error += opDescription(ep->ExceptionRecord->ExceptionInformation[0]);
				error += " at address 0x";

				len = sprintf_s(buffer, sizeof(buffer), "%08X\n", ep->ExceptionRecord->ExceptionInformation[1]);
				error.Append(buffer, len);
			}

			if (has_exception_code && code == EXCEPTION_IN_PAGE_ERROR) {
				error += "Underlying NTSTATUS code that resulted in the exception ";
				len = sprintf_s(buffer, sizeof(buffer), "%08X\n", ep->ExceptionRecord->ExceptionInformation[2]);
				error.Append(buffer, len);
			}

			error += "Context:\n";
			PCONTEXT ctx = ep->ContextRecord;
			len = sprintf_s(buffer, sizeof(buffer),
				"EAX = 0x%08X\nECX = 0x%08X\nEDX = 0x%08X\nEBX = 0x%08X\nESP = 0x%08X\nEBP = 0x%08X\nESI = 0x%08X\nEDI = 0x%08X\nFlags = 0x%08X\n",
				ctx->Eax, ctx->Ecx, ctx->Edx, ctx->Ebx, ctx->Esp, ctx->Ebp, ctx->Esi, ctx->Edi, ctx->ContextFlags);
			error.Append(buffer, len);

			if (log_error)
				error += "\nWould you like to save this error to file?";
		}
	};

	inline void h3_trans_func(UINT code, EXCEPTION_POINTERS* ep)
	{
		H3String error;
		// * change the last input to false if you do not wish to offer logging the SE error
		H3SEInfo::information(error, ep, true, code, true);
		throw H3Exception(error);
	}
}
#pragma endregion

inline VOID H3Exception::LogError(LPCSTR path)
{
	FILE *f = fopen(path, "wb+");
	if (!f)
		return;
	fwrite(what(), 1, strlen(what()), f);
	fclose(f);
}

#endif /* #ifdef _CPPUNWIND */

#endif /* #define _H3EXCEPTION_H_ */