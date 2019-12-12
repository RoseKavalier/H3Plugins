//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3EXCEPTION_HPP_
#define _H3EXCEPTION_HPP_

#include "../H3_Core.hpp"
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
		void h3_trans_func(UINT code, EXCEPTION_POINTERS* ep);
		CHAR const OfferToLog[] = "\nWould you like to save this error to file ?";
		LPCSTR opDescription(const ULONG opcode);
		LPCSTR seDescription(const UINT& code);
		VOID information(H3String& error, _EXCEPTION_POINTERS* ep, UINT code = 0, bool log_error = true);
	}

	// * Catches std::exception and SEH errors
	// * when combined with H3SEHandler
	class H3Exception : public std::exception
	{
	public:
		H3Exception(LPCSTR message);
		// * creates an in-game dialog showing the error
		VOID ShowInGame();
		// * creates an in-game dialog showing the error
		BOOL ShowInGameLog();
		// * creates a out-of-game messagebox showing the error
		VOID ShowMessagebox();
		// * creates a out-of-game messagebox showing the error
		BOOL ShowMessageboxLog();
		// * logs error to specified path
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
		_H3API_ H3SEHandler();
		_H3API_ ~H3SEHandler();
	};

}

#endif /* #ifdef _CPPUNWIND */

#endif /* #define _H3EXCEPTION_HPP_ */