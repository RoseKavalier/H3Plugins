#pragma once
#define _H3API_PLUGINS_
#include <Plugin.hpp>
#include <H3API.hpp>

/**
 * Uncomment to show an error message when failing to link up with patcher_x86
 */
//#define SHOW_ERROR_MESSAGE_ON_FAIL

/**
 * @brief A derived Plugin that constructs itself
 */
class ImageLoaderPlugin : public Plugin
{
public:
	ImageLoaderPlugin() : Plugin()
	{
		Status status = Init("H3.ImageLoader");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.ImageLoader", status);
#endif
	}

	static ImageLoaderPlugin& GetPlugin();

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================


private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================

};