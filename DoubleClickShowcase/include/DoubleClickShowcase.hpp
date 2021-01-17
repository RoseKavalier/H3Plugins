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
class DoubleClickShowcasePlugin : public Plugin
{
public:
	DoubleClickShowcasePlugin() : Plugin()
	{
		Status status = Init("H3.DoubleClickShowcase");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.DoubleClickShowcase", status);
#endif
	}

	static DoubleClickShowcasePlugin& GetPlugin();

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	int __stdcall _HH_CheckDoubleClick(HiHook* h, h3::H3InputManager* This, int* a2);

private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================
	static constexpr INT MT_DOUBLE_CLICK = 0x80;
	bool m_doubleClicked;
};