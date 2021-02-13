#pragma once

#include <Plugin.hpp>
#include <H3API.hpp>

/**
 * Uncomment to show an error message when failing to link up with patcher_x86
 */
//#define SHOW_ERROR_MESSAGE_ON_FAIL

/**
 * @brief A derived Plugin that constructs itself
 */
class ShiftTogglePlugin : public Plugin
{
public:
	ShiftTogglePlugin() : Plugin(), m_shiftPressed(false)
	{
		Status status = Init("H3.ShiftToggle");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.ShiftToggle", status);
#endif
	}

	static ShiftTogglePlugin& GetPlugin();

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	int CheckShift(HookContext& c);
	int ChangeCursor(HookContext& c);
	int ShiftOff(HookContext& c);
	int DialogsTurnOffShift();
	int _HH_CheckShift(HiHook* h, h3::H3AdventureManager* This, h3::H3Msg* msg, int a3, int a4, int a5);

private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================
	bool m_shiftPressed;
};