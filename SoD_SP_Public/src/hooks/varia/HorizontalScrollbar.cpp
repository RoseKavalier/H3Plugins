/*
 *
 * H3 Code has GUI assets and code to handle horizontal scrollbars,
 * however none were ever used. The scrollbar drawing function does not
 * consider the orientation of the scrollbar and always assumes it is vertical
 * which draws garbage on the screen.
 *
 */

#include "HorizontalScrollbar.hpp"
#include <H3API.hpp>
#include "sodsp/Log.hpp"

using namespace h3;

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

	hSlider = nullptr; // always reset
}

/*
 *
 * If drawing a horizontal scrollbar, correct the position of the rightmost arrow button.
 *
 */
void __stdcall _HH_HScrollbarRight(HiHook *h, H3LoadedDef *This, int a1, int a2, int a3, int a4, int a5, int a6, int dest_x, int dest_y, int a9, int a10, int a11, int a12)
{
	LOG_HIHOOK;

	if (H3DlgScrollbar *scroll = hSlider) // pressed right arrow key on horizontal slider
	{
		dest_x = scroll->GetRightButtonX();
		dest_y = scroll->GetHorizontalY();
	}

	THISCALL_13(void, h->GetDefaultFunc(), This, a1, a2, a3, a4, a5, a6, dest_x, dest_y, a9, a10, a11, a12);
}

/*
 *
 * If drawing a horizontal scrollbar, correct the orientation (position and dimensions)
 * of the scrollbar's black background.
 *
 */
void __stdcall _HH_HScrollBarBackground(HiHook *h, H3LoadedPcx *This, int a1, int a2, int width, int height, int a5, int x_pos, int y_pos, int a8)
{
	LOG_HIHOOK;

	if (H3DlgScrollbar *scroll = hSlider)
	{
		height = scroll->GetHeight();
		width  = scroll->GetBackgroundWidth();
		x_pos  = scroll->GetBackgroundX();
		y_pos  = scroll->GetHorizontalY();
	}

	THISCALL_9(void, h->GetDefaultFunc(), This, a1, a2, width, height, a5, x_pos, y_pos, a8);
}

/*
 *
 * If drawing a horizontal scrollbar, correct the position of the slider thumb.
 *
 */
void __stdcall _HH_HScrollbarThumb(HiHook *h, H3LoadedDef *This, int a1, int a2, int a3, int a4, int a5, int a6, int dest_x, int dest_y, int a9, int a10, int a11, int a12)
{
	LOG_HIHOOK;

	if (H3DlgScrollbar *scroll = hSlider)
	{
		dest_x = scroll->GetSliderX();
		dest_y = scroll->GetHorizontalY();
	}

	THISCALL_13(void, h->GetDefaultFunc(), This, a1, a2, a3, a4, a5, a6, dest_x, dest_y, a9, a10, a11, a12);
}

void horizontalScrollbar_init(PatcherInstance * pi)
{
	pi->WriteHiHook(0x596520, SPLICE_, THISCALL_, _HH_HrztlScrollbarHotkey); // if horizontal, store scrollbar item
	pi->WriteHiHook(0x5965C3, CALL_,   THISCALL_, _HH_HScrollbarRight);		 // correctly draw right button
	pi->WriteHiHook(0x596606, CALL_,   THISCALL_, _HH_HScrollBarBackground); // correctly draw black background
	pi->WriteHiHook(0x596655, CALL_,   THISCALL_, _HH_HScrollbarThumb);		 // correctly draw slider thumb
}
