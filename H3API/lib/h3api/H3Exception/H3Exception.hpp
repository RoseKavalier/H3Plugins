//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3EXCEPTION_HPP_
#define _H3EXCEPTION_HPP_

#include "../H3_Base.hpp"

#ifdef _CPPUNWIND
#include "../H3_String.hpp"
#include <eh.h>
#include <exception>
#include <Psapi.h>

namespace h3
{
	// * Only available if stack unwinding is enabled (enable C++ exceptions).
	// * you should use /EHa compiler flag when using this file
	namespace NH3Error
	{
		CHAR const OfferToLog[] = "\nWould you like to save this error to file ?";
		_H3API_ void   h3_trans_func(UINT code, EXCEPTION_POINTERS* ep);
		_H3API_ LPCSTR opDescription(const ULONG opcode);
		_H3API_ LPCSTR seDescription(const UINT& code);
		_H3API_ VOID   information(H3String& error, _EXCEPTION_POINTERS* ep, UINT code = 0, bool log_error = true);
	}

	// * Catches std::exception and SEH errors
	// * when combined with H3SEHandler
	class H3Exception : public std::exception
	{
	public:
		_H3API_ H3Exception(LPCSTR message);
		_H3API_ H3Exception(const H3String& message);
		// * creates an in-game dialog showing the error
		_H3API_ VOID ShowInGame();
		// * creates an in-game dialog showing the error
		_H3API_ BOOL ShowInGameLog();
		// * creates a out-of-game messagebox showing the error
		_H3API_ VOID ShowMessagebox();
		// * creates a out-of-game messagebox showing the error
		_H3API_ BOOL ShowMessageboxLog();
		// * logs error to specified path
		_H3API_ VOID LogError(LPCSTR path);
		_H3API_ VOID LogError(const H3String& path);
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
		_H3API_ H3SEHandler();
		_H3API_ ~H3SEHandler();
	};

}

#endif /* #ifdef _CPPUNWIND */

#endif /* #define _H3EXCEPTION_HPP_ */