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
class AssetLoaderPlugin : public Plugin
{
public:
	AssetLoaderPlugin() : Plugin()
	{
		Status status = Init("H3.AssetLoader");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.AssetLoader", status);
#endif
	}

	static AssetLoaderPlugin& GetPlugin();

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	h3::H3String m_errorMessage;

	h3::H3LoadedPcx* LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name);
	h3::H3WavFile* LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name);
	h3::H3LoadedDef* LoadDefFromFile(LPCSTR const filePath, LPCSTR const h3name);
	int DefFromFile(HookContext& c);
private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================
	LPCSTR m_defPath;
	LoHook* m_defHook;

	bool ValidateParameters(LPCSTR const filepath, LPCSTR const h3name);
	PUINT8 GetFileBuffer(LPCSTR const filepath, DWORD& fileSize);

	static constexpr CHAR MissingPath[]      = "Path not provided.";
	static constexpr CHAR MissingFileName[]  = "File name not provided.";
	static constexpr CHAR ErrorReadingFile[] = "Could not read file at provided path.";
	static constexpr CHAR MemoryAllocation[] = "Could not allocate memory.";
	static constexpr CHAR AlreadyExists[]    = "An asset already exists with the provided name.";
};