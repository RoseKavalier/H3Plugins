#include "Hooks.h"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Third party handler
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class ImageLoaderPcx16
{
	int m_w;
	int m_h;
	int m_comp;
	stbi_uc *m_pixels;
	BOOL m_state;

	H3LoadedPCX16 *pcx16;

public:
	ImageLoaderPcx16(LPCSTR filepath);
	~ImageLoaderPcx16();
	BOOL Valid() { return m_state; }
	int Width() { return m_w; }
	int Height() { return m_h; }
	VOID Resize(int w, int h);
	H3LoadedPCX16* CreatePcx16(LPCSTR h3name);
	VOID RGB_to_BGR();
};

ImageLoaderPcx16::ImageLoaderPcx16(LPCSTR filepath)
{
	m_pixels = stbi_load(filepath, &m_w, &m_h, &m_comp, STBI_rgb);
	m_state = m_pixels != nullptr;
}

ImageLoaderPcx16::~ImageLoaderPcx16()
{
	if (m_pixels)
		stbi_image_free(m_pixels);
}

VOID ImageLoaderPcx16::Resize(int w, int h)
{
	unsigned char* output = nullptr;
	stbir_resize_uint8(m_pixels, m_w, m_h, 0, output, w, h, 0, STBI_rgb);
	if (output)
	{
		m_pixels = output;
		m_w = w;
		m_h = h;
	}
	else
	{
		stbi__g_failure_reason = "Could not resize image.";
		m_pixels = nullptr;
	}
}

H3LoadedPCX16 * ImageLoaderPcx16::CreatePcx16(LPCSTR h3name)
{
	H3LoadedPCX24 pcx24;
	pcx24.width = m_w;
	pcx24.height = m_h;
	pcx24.buffer = m_pixels;

	pcx16 = H3LoadedPCX16::Create(h3name, m_w, m_h);
	if (!pcx16)
	{
		stbi__g_failure_reason = "Could not create PCX16.";
		return nullptr;
	}

	// * use game assets to convert into pcx16 format
	pcx24.DrawToPcx16(0, 0, pcx16);

	pcx16->AddToBinaryTree();

	// * so that it stays in the binary tree after use
	pcx16->IncreaseReferences();

	return pcx16;
}

VOID ImageLoaderPcx16::RGB_to_BGR()
{
	stbi_uc * img = m_pixels;

	for (int j = 0; j < m_h; ++j)
		for (int i = 0; i < m_w; ++i)
		{
			stbi_uc b = img[2];
			img[2] = img[0];
			img[0] = b;

			img += STBI_rgb;
		}
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

using namespace H3Plugin::ImageLoader;

static class H3ImageLoaderInternal : public H3ImageLoader
{
	DWORD m_images_added;
public:
	// * the number of images added by the plugin so far
	virtual INT NumberAdded() override;

	// * returns the last error
	virtual LPCSTR GetLastError() override;

	// * DOES NOT SUPPORT TRANSPARENCY
	// * @filepath - the complete path to the image you are looking to load
	// * @h3name - the name to use within the H3 assets (to recuperate the image later)
	// * @width and @height are optional, but can be used to resize the image
	virtual H3LoadedPCX16* LoadImageToPcx16(LPCSTR filepath, LPCSTR h3name, INT width = -1, INT height = -1) override;


}InternalImageLoader;

H3Plugin::ImageLoader::H3ImageLoader * GetImageLoader_()
{
	return &InternalImageLoader;
}

INT H3ImageLoaderInternal::NumberAdded()
{
	return m_images_added;
}

LPCSTR H3ImageLoaderInternal::GetLastError()
{
	return stbi_failure_reason();
}

H3LoadedPCX16 * H3ImageLoaderInternal::LoadImageToPcx16(LPCSTR filepath, LPCSTR h3name, INT width, INT height)
{
	if (!filepath)
	{
		stbi__g_failure_reason = "No filepath provided.";
		return nullptr;
	}

	if (!h3name)
	{
		stbi__g_failure_reason = "No h3name provided.";
		return nullptr;
	}

	if (P_BinaryTree->FindItem(h3name))
	{
		stbi__g_failure_reason = "An asset already exists with the provided name.";
		return nullptr;
	}

	ImageLoaderPcx16 image(filepath);
	if (!image.Valid())
		return nullptr;

	int req_width = width > 0 ? width : image.Width();
	int req_height = height > 0 ? height : image.Height();

	// * no use making something too large
	req_width = std::min(req_width, gameWidth);
	req_height = std::min(req_height, gameHeight);

	if (req_width <= 0 || req_height <= 0)
	{
		stbi__g_failure_reason = "Invalid image size.";
		return nullptr;
	}

	if (req_width != image.Width() || req_height != image.Height())
	{
		image.Resize(req_width, req_height);
		if (!image.Valid())
			return nullptr;
	}

	// * swap blue and red for h3 format
	image.RGB_to_BGR();

	H3LoadedPCX16 *pcx = image.CreatePcx16(h3name);
	if (pcx)
		++m_images_added;
	return pcx;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

void Hooks_init(PatcherInstance *pi)
{
	// * nothing here!
}

