//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Exception.hpp"
#include "H3Exception.inl"
#include "../H3_Functions.hpp"

namespace h3
{
	_H3API_ void H3Internal::_h3TransFunction(UINT code, EXCEPTION_POINTERS* ep)
	{
		H3String error;
		// * change the last input to false if you do not wish to offer logging the SE error
		_exInformation(error, ep, code, true);
		throw H3Exception(error);
	}

	_H3API_ LPCSTR H3Internal::_opDescription(const ULONG opcode)
	{
		switch (opcode)
		{
		case 0:
			return "read";
		case 1:
			return "write";
		case 8:
			return "user-mode data execution prevention (DEP) violation";
		default:
			return "unknown";
		}
	}

	_H3API_ LPCSTR H3Internal::_seDescription(const UINT& code)
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

	_H3API_ VOID H3Internal::_exInformation(H3String& error, _EXCEPTION_POINTERS* ep, UINT code, bool log_error)
	{
		HMODULE hm;
		GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)(ep->ExceptionRecord->ExceptionAddress), &hm);

		IMAGE_DOS_HEADER* pDOSHeader = (IMAGE_DOS_HEADER*)hm;
		IMAGE_NT_HEADERS* pNTHeaders = (IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
		DWORD base_of_code = ((DWORD)hm + pNTHeaders->OptionalHeader.BaseOfCode);

		char module_name[MAX_PATH];
		DWORD mn_len = F_GetModuleFileNameA(hm, module_name, MAX_PATH);
		module_name[mn_len] = 0; // null terminate for XP

		// find short name of module
		PCHAR module_name_short = module_name + mn_len - 1;
		for (int i = mn_len - 1; i >= 0; --i, --module_name_short)
			if (*module_name_short == '\\')
			{
				++module_name_short;
				break;
			}

		error.Printf("SE %s at address offset 0x%08X inside %s.\n",
			_seDescription(code),
			(DWORD)ep->ExceptionRecord->ExceptionAddress - base_of_code,
			module_name_short);

		if (code == EXCEPTION_ACCESS_VIOLATION || code == EXCEPTION_IN_PAGE_ERROR)
		{
			error.PrintfAppend("Invalid operation: %s at address 0x%08X.\n",
				_opDescription(ep->ExceptionRecord->ExceptionInformation[0]),
				ep->ExceptionRecord->ExceptionInformation[1]);
		}

		if (code == EXCEPTION_IN_PAGE_ERROR) {
			error.PrintfAppend("Underlying NTSTATUS code that resulted in the exception %08X.\n",
				ep->ExceptionRecord->ExceptionInformation[2]);
		}

		PCONTEXT ctx = ep->ContextRecord;
		error.PrintfAppend("\nContext:\nEAX = 0x%08X\nECX = 0x%08X\nEDX = 0x%08X\nEBX = 0x%08X\nESP = 0x%08X\nEBP = 0x%08X\nESI = 0x%08X\nEDI = 0x%08X\nFlags = 0x%08X\n",
			ctx->Eax, ctx->Ecx, ctx->Edx, ctx->Ebx, ctx->Esp, ctx->Ebp, ctx->Esi, ctx->Edi, ctx->ContextFlags);

		if (log_error)
			error.AppendA(OfferToLog);
	}

	_H3API_ H3Exception::H3Exception(LPCSTR message) :
		exception(message)
	{
	}

	H3Exception::H3Exception(const H3String & message) :
		exception(message.String())
	{
	}

	_H3API_ VOID H3Exception::ShowInGame()
	{
		F_MessageBox(what());
	}

	_H3API_ BOOL H3Exception::ShowInGameLog()
	{
		return F_MessageBoxChoice(what());
	}

	_H3API_ VOID H3Exception::ShowMessagebox()
	{
		H3Error::ShowError(what());
	}

	_H3API_ BOOL H3Exception::ShowMessageboxLog()
	{
		return H3Error::ShowErrorChoice(what());
	}

	_H3API_ VOID H3Exception::LogError(LPCSTR path)
	{
		FILE* f = F_fopen(path, "wb+");
		if (!f)
			return;
		F_fwrite(what(), 1, strlen(what()) - sizeof(H3Internal::OfferToLog), f);
		F_fclose(f);
	}
	_H3API_ VOID H3Exception::LogError(const H3String & path)
	{
		LogError(path.String());
	}

	_H3API_ H3SEHandler::H3SEHandler() :
		m_oldTranslator(_set_se_translator(H3Internal::_h3TransFunction))
	{
	}

	_H3API_ H3SEHandler::~H3SEHandler()
	{
		_set_se_translator(m_oldTranslator);
	}

}


