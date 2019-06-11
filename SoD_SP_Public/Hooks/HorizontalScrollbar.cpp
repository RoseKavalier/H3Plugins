/*
 *
 * H3 Code has GUI assets and code to handle horizontal scrollbars,
 * however none were ever used. The scrollbar drawing function does not
 * consider the orientation of the scrollbar and always assumes it is vertical
 * which draws garbage on the screen.
 *
 */

#include "HorizontalScrollbar.h"

static H3DlgScrollbar *hSlider; // static variable to correct horizontal scrollbar drawing with hotkeys

/*
 *
 * Splice at start of drawing function. If the slider is horizontal,
 * it is stored and used as trigger to correctly draw the slider later on.
 *
 */
void __stdcall _HH_HrztlScrollbarHotkey(HiHook *h, H3DlgScrollbar* slider, int a1, int a2, int a3, int a4, int a5)
{
	LOG_HIHOOK;
	if (slider->IsHorizontal())
		hSlider = slider;

	THISCALL_6(void, h->GetDefaultFunc(), slider, a1, a2, a3, a4, a5);

	hSlider = NULL; // always reset
	LOG_HIHOOK;
}

/*
 *
 * If drawing a horizontal scrollbar, correct the position of the rightmost arrow button.
 *
 */
void __stdcall _HH_HScrollbarRight(HiHook *h, H3LoadedDEF *This, int a1, int a2, int a3, int a4, int a5, int a6, int dest_x, int dest_y, int a9, int a10, int a11, int a12)
{
	LOG_HIHOOK;
	int new_dest_x = dest_x;
	int new_dest_y = dest_y;

	if (H3DlgScrollbar *scroll = hSlider) // pressed right arrow key on horizontal slider
	{
		new_dest_x = scroll->GetRightButtonX();
		new_dest_y = scroll->GetHorizontalY();
	}

	THISCALL_13(void, h->GetDefaultFunc(), This, a1, a2, a3, a4, a5, a6, new_dest_x, new_dest_y, a9, a10, a11, a12);
	LOG_HIHOOK;
}

/*
 *
 * If drawing a horizontal scrollbar, correct the orientation (position and dimensions)
 * of the scrollbar's black background.
 *
 */
void __stdcall _HH_HScrollBarBackground(HiHook *h, H3LoadedPCX *This, int a1, int a2, int width, int height, int a5, int x_pos, int y_pos, int a8)
{
	LOG_HIHOOK;
	int new_height = height;
	int new_width = width;
	int new_dest_x = x_pos;
	int new_dest_y = y_pos;
	if (H3DlgScrollbar *scroll = hSlider)
	{
		new_height = scroll->GetHeight();
		new_width = scroll->GetBackgroundWidth();
		new_dest_x = scroll->GetBackgroundX();
		new_dest_y = scroll->GetHorizontalY();
	}

	THISCALL_9(void, h->GetDefaultFunc(), This, a1, a2, new_width, new_height, a5, new_dest_x, new_dest_y, a8);
	LOG_HIHOOK;
}

/*
 *
 * If drawing a horizontal scrollbar, correct the position of the slider thumb.
 *
 */
void __stdcall _HH_HScrollbarThumb(HiHook *h, H3LoadedDEF *This, int a1, int a2, int a3, int a4, int a5, int a6, int dest_x, int dest_y, int a9, int a10, int a11, int a12)
{
	LOG_HIHOOK;
	int new_dest_x = dest_x;
	int new_dest_y = dest_y;

	if (H3DlgScrollbar *scroll = hSlider)
	{
		new_dest_x = scroll->GetSliderX();
		new_dest_y = scroll->GetHorizontalY();
	}

	THISCALL_13(void, h->GetDefaultFunc(), This, a1, a2, a3, a4, a5, a6, new_dest_x, new_dest_y, a9, a10, a11, a12);
	LOG_HIHOOK;
}

void horizontalScrollbar_init(PatcherInstance * pi)
{
	pi->WriteHiHook(0x596520, SPLICE_, THISCALL_, _HH_HrztlScrollbarHotkey);	// if horizontal, store scrollbar item
	pi->WriteHiHook(0x5965C3, CALL_, THISCALL_, _HH_HScrollbarRight);		// correctly draw right button
	pi->WriteHiHook(0x596606, CALL_, THISCALL_, _HH_HScrollBarBackground);	// correctly draw black background
	pi->WriteHiHook(0x596655, CALL_, THISCALL_, _HH_HScrollbarThumb);		// correctly draw slider thumb
}
