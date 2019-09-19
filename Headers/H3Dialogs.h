//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/potmdehex/homm3tools                 //
//  Author: potmdehex and contributors                              //
//                                                                  //
//  Source: https://github.com/redxu/HoMM3_FA                       //
//  Author: redxu                                                   //
//                                                                  //
//  Source: https://github.com/openhomm/openhomm                    //
//  Author: Ershov Stanislav, Fomin Roman, Akulich Alexander        //
//                                                                  //
//  Source: https://github.com/GrayFace/wog                         //
//  Author: GrayFace and WoG team                                   //
//                                                                  //
//  Source: https://github.com/ethernidee/era                       //
//  Author: Berserker                                               //
//                                                                  //
//  Source: https://github.com/ethernidee/era-editor                //
//  Author: Grayface and Berserker                                  //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=3900      //
//  Author: Slava and GrayFace                                      //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=4583      //
//  Author: gamecreator                                             //
//                                                                  //
//  Thanks: patcher_x86 by baratorch and code therein               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3DIALOGS_H_
#define _H3DIALOGS_H_

#pragma once

#include "H3Base.h"
#include "H3Structures.h"
#include "H3Functions.h"
#include "H3BinaryItems.h"
#include "H3Constants.h"

#pragma pack(push, 1)

struct  H3Dlg;
struct  H3Msg;
struct  H3MsgCustom;
struct  H3DlgItem;
struct  H3DlgFrame;
struct  H3DlgDef;
struct  H3DlgDefButton;
struct  H3DlgScrollbar;
struct  H3DlgCaptionButton;
struct  H3DlgPcx;
struct  H3DlgPcx16;
struct  H3DlgEdit;
struct  H3DlgText;
struct  H3DlgTextPcx;
struct  H3DlgScrollableText;
struct  H3DlgCustomButton;
struct  H3DlgHintBar;
typedef INT32(__stdcall *H3Dlg_proc)(H3Dlg* dlg, H3Msg* msg);
typedef INT32(__fastcall *H3DlgButton_proc)(H3MsgCustom *msg);
typedef VOID(__fastcall *H3DlgScrollbar_proc)(INT32 click_id, H3Dlg* dlg);

struct H3Msg
{
	INT32 command;
	INT32 subtype;
	INT32 item_id;
	INT32 flags;
	INT32 x_abs;
	INT32 y_abs;
	INT32 parameter;
	INT32 flags2;

	enum ItemIDs
	{
		ID_SAVE = 30000,
		ID_OK = 30725,
		ID_CANCEL = 30726
	};

	enum MessageCommand
	{
		MC_MouseButton = 0x200,
		MC_RClickOutside = 0x20,
		MC_LClickOutside = 8,
		MC_MouseOver = 4,
		MC_KeyDown = 1,
		MC_KeyUp = 2,
		MC_WheelButton = 0x309,
		MC_MouseWheel = 0x20A
	};
	enum MessageSubtype
	{
		MS_LButtonDown = 0xC,
		MS_LButtonClick = 0xD,
		MS_RButtonDown = 0xE,
		MS_MouseWheelButtonDown = 0x207,
		MS_MouseWheelButtonUp = 0x208
	};
	enum MessageFlag
	{
		MF_Shift = 1,
		MF_Ctrl = 4,
		MF_Alt = 32
	};

	VOID      SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2);
	VOID      SetCommand(INT32 cmd, INT32 param);
	H3DlgItem *ItemAtPosition(H3Dlg *dlg);
	INT32     KeyPressed()   { return subtype; }
	BOOL      IsMouseOver()  { return command == MC_MouseOver; }
	BOOL      IsKeyPress()   { return command == MC_KeyUp; }
	BOOL      IsKeyDown()    { return command == MC_KeyDown; }
	BOOL      IsLeftClick()  { return (command == MC_MouseButton && subtype == MS_LButtonClick); }
	BOOL      IsLeftDown()   { return (command == MC_MouseButton && subtype == MS_LButtonDown);}
	BOOL      IsRightClick() { return (command == MC_MouseButton && subtype == MS_RButtonDown);	}
	INT32     CloseDialog()  { return STDCALL_1(INT32, 0x491640, this); }
	BOOL      ClickOutside() { return command == MC_RClickOutside || command == MC_LClickOutside; }
};

struct H3MsgCustom : public H3Msg
{
	H3Dlg * GetDlg() { return (H3Dlg*)flags2; }
};

// * actually __thiscall but declaration is not allowed
// * so dummy int is inserted. Modeled after iFunction2 from WoG source
static INT32 __fastcall H3DlgCustomProc(struct H3Dlg *dlg, int, H3Msg *msg);

struct H3DlgVTable
{
public: // copied from vTable at 0x63A6A8
	h3func     destroyDlg;
	h3func     showDlg;
	h3func     hideDlg;
	h3func     callProcessAction;
	h3func     _nullsub;
	h3func     redrawDlg;
	h3func     runDlg;
	h3func     initDlgItems;
	h3func     activateDlg;
	H3Dlg_proc dlgProc;
	h3func     mouseMove;
	h3func     rightClick;
	h3func     clickRet;
	h3func     _nullsub3;
	h3func     closeDlg;

	H3DlgVTable()
	{
		destroyDlg        = 0x41B040;
		showDlg           = 0x5FF0A0;
		hideDlg           = 0x5FF220;
		callProcessAction = 0x405610;
		_nullsub          = 0x49A230;
		redrawDlg         = 0x5FF5E0;
		runDlg            = 0x5FFA20;
		initDlgItems      = 0x5FFB30;
		activateDlg       = 0x5FFBB0;
		dlgProc           = (H3Dlg_proc)H3DlgCustomProc; // custom proc to show hint messages and call our own dlg proc, default 0x41B120.
		mouseMove         = 0x5FFCA0;
		rightClick        = 0x5FFD50;
		clickRet          = 0x5FFE90;
		_nullsub3         = 0x4842C0;
		closeDlg          = 0x41B0F0;
	}
	~H3DlgVTable() {}
};

static H3DlgVTable CustomDlgVTable;

// * This removes the following warning when using enum
// * warning C4482: nonstandard extension used: enum '...' used in qualified name
#pragma warning(push)
#pragma warning(disable : 4482)
struct H3Dlg
{
protected:
	// * +0
	H3DlgVTable *vtable;
	// * +4
	INT32 zOrder;
	// * +8
	H3Dlg *nextDialog;
	// * +C
	H3Dlg *lastDialog;
	// * +10
	INT32 flags;
	// * +14
	INT32 state;
	// * +18
	INT32 xDlg;
	// * +1C
	INT32 yDlg;
	// * +20
	INT32 widthDlg;
	// * +24
	INT32 heightDlg;
	// * +28
	struct H3DlgItem *lastItem;
	// * +2C
	struct H3DlgItem *firstItem;
	// * +30
	H3Vector<H3DlgItem*> dlgItems;
	// * +40
	INT32 focusedItemId;
	// * +44
	H3LoadedPCX16 *pcx16;
	// * +48
	INT32 deactivatesCount;
	h3unk _f_4C[28]; // normal dialog size is 0x68 total

	////////////////////////////////////////////////////////////////////////
	// Custom Fields - not part of regular dialogs!
	////////////////////////////////////////////////////////////////////////
	H3Dlg_proc customProc;
	H3DlgHintBar *hintBar;
	H3LoadedPCX16 *background;
private:

	// * to be deprecated in favor of AddBackground()
	BOOL OldDlgBackground(BOOL frame, BOOL statusBar, INT32 colorIndex);
	// * to be deprecated in favor of SimpleFrameRegion()
	BOOL OldSimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height);
	// * to be deprecated in favor of CreateBlackBox()
	H3DlgText* OldCreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height);

public:
	////////////////////////////////////////////////////////////////////////
	// Constructor and destructor
	////////////////////////////////////////////////////////////////////////
	// * default constructor
	H3Dlg(int width, int heigh, int x = -1, int y = -1, BOOL statusBar = FALSE, H3Dlg_proc dlgProc = nullptr, BOOL makeBackground = TRUE, INT32 colorIndex = IntAt(0x69CCF4));
	// * default destructor
	// * if you prefer to allocate your own dialogs,
	// * change the last value to a 1 --- or use
	// * H3Dlg* MyDlg = new H3Dlg();
	// * ...
	// * delete MyDlg;
	// * this will automatically call the destructor before deallocating memory
	~H3Dlg() { THISCALL_2(VOID, vtable->destroyDlg, this, 0); }
	////////////////////////////////////////////////////////////////////////
	// Functions
	////////////////////////////////////////////////////////////////////////
	H3DlgItem* AddItem(H3DlgItem *item);
	// Dlg functions
	VOID           PlaceAtMouse();
	VOID           Start();
	VOID           RMB_Show() { THISCALL_1(VOID, 0x5F4B90, this); }
	BOOL           AddBackground(INT32 x, INT32 y, INT32 w, INT32 h, BOOL frame, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);
	BOOL           AddBackground(BOOL frame, BOOL statusBar, INT32 colorIndex);
	BOOL           AddBackground(H3LoadedPCX *pcx);
	BOOL           AddBackground(H3LoadedPCX16 *pcx);
	BOOL           AddBackground(H3LoadedPCX24 *pcx);
	BOOL           AddBackground(H3LoadedDEF *def, INT group = 0, INT frame = 0);
	VOID           Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy); // redraw part of dialog
	VOID           Redraw(); // redraw whole dialog
	INT32          DefaultProc(H3Msg *msg) { return THISCALL_2(INT32, 0x41B120, this, msg); }
	INT32          GetWidth()              { return widthDlg; }
	INT32          GetHeight()             { return heightDlg; }
	INT32          GetX()                  { return xDlg; }
	INT32          GetY()                  { return yDlg; }
	H3LoadedPCX16* GetBackgroundPcx()      { return background; }

	// * draws the background pcx only
	BOOL BackgroundRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, BOOL is_blue = FALSE);
	// * draws the HDmod simple frames only
	BOOL SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPCX16 *destination = nullptr);
	// * draws the outside frames only
	BOOL FrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);

	// *
	// * this is what gets shown on the screen
	// * it gets drawn over every time you refresh an item
	// * or draw a new item... good for temporary things
	H3LoadedPCX16* GetCurrentPcx()         { return pcx16; }
	H3Dlg_proc     GetProc()               { return customProc; }

	// Item functions
	H3DlgItem*			 ItemAtPosition(H3Msg *msg);
	H3Vector<H3DlgItem*>*GetList()    { return &dlgItems; }
	H3DlgHintBar*		 GetHintBar() { return hintBar; }
	H3DlgItem*			 GetH3DlgItem(UINT16 id);
	VOID                 RedrawItem(UINT16 itemID);
	VOID                 EnableItem(UINT16 id, BOOL enable);
	VOID                 SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter);
	VOID                 SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter);
	VOID                 AdjustToPlayerColor(INT8 player, UINT16 itemId);
	H3DlgFrame*          CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color);
	H3DlgFrame*          CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color);
	H3DlgFrame*          CreateFrame(H3DlgItem *target, RGB565 color, INT id = 0, BOOL around_edge = false);
	H3DlgDef*            CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	H3DlgDef*            CreateDef(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	H3DlgDefButton*      CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
	H3DlgDefButton*		 CreateOKButton(INT32 x, INT32 y);
	H3DlgDefButton*		 CreateSaveButton(INT32 x, INT32 y);
	H3DlgDefButton*		 CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame = 0);
	H3DlgDefButton*      CreateOKButton(); // adjust for hintBar
	H3DlgDefButton*      CreateOK32Button(INT32 x, INT32 y); // height is 32
	H3DlgDefButton*      CreateCancelButton(); // adjust for hintBar
	H3DlgCaptionButton*  CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group = 0, BOOL closeDialog = FALSE, INT32 hotkey = NULL, INT32 color = 0);
	H3DlgCustomButton*   CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	H3DlgCustomButton*   CreateCustomButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	H3DlgCustomButton*   CreateCustomButton(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	H3DlgPcx*            CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
	H3DlgPcx*            CreateLineSeparator(INT32 x, INT32 y, INT32 width);
	H3DlgPcx16*          CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
	H3DlgEdit*           CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName = NH3Dlg::Text::MEDIUM, INT32 color = NH3Dlg::TextColor::REGULAR, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, LPCSTR pcxName = nullptr, INT32 id = 0, INT32 hasBorder = FALSE, INT32 borderX = 0, INT32 borderY = 0);
	H3DlgText*           CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
	BOOL                 CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height);
	H3DlgHintBar*        CreateHint();
	H3DlgTextPcx*        CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
	H3DlgScrollableText* CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue = FALSE);
	H3DlgScrollbar*      CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc = nullptr, BOOL isBlue = FALSE, INT32 stepSize = 0, BOOL arrowsEnabled = TRUE);
};
#pragma warning(pop)

struct H3DlgPanel
{
	// * +0
	h3func *vTable;
	h3unk _f_04[8];
	// * +C
	INT32 width;
	// * +10
	INT32 height;
	// * +14
	H3Vector<H3DlgItem*> dlgItems;
	// * +24
	struct H3Dlg *parent;
	// * +28
	INT32 minId;
	// * +2C
	INT32 maxId;
	h3unk _f_30[4];

	// goes on ...
};

struct H3DlgItemVTable // 0x63BA24
{
	h3func deref;
	h3func init;
	h3func processCommand; // used to redraw
	h3func _null1;
	h3func draw;
	h3func getHeight;
	h3func getWidth;
	h3func showHint;
	h3func drawShadow;
	h3func setEnabled;
	h3func getFocus;
	h3func loseFocus;
	h3func _null5;
	h3func setText;
	////////////////////////////////////////////////
	// not all H3DlgItems have the following:
	////////////////////////////////////////////////
	h3func setFocus; // H3DlgEdit has these // ScrollbarText has 3
	h3func processKey;
	h3func isDisallowedKey; // +40 disallowed key for H3DlgEdit, e.g. save game field 0x57D2F0
	h3func loadPcx16;
	h3func pcx16FromBuffer;
};

struct H3DlgItem // size 0x30
{
protected:
	// * +0
	H3DlgItemVTable *vTable;
	// * +4
	H3Dlg *parent;
	// * +8
	H3DlgItem *previousDlgItem;
	// * +C
	H3DlgItem *nextDlgItem;
	// * +10
	UINT16 id;
	// * +12
	UINT16 zOrder;
	// * +14
	UINT16 flags;
	// * +16
	UINT16 state;
	// * +18
	INT16 xPos;
	// * +1A
	INT16 yPos;
	// * +1C
	UINT16 widthItem;
	// * +1E
	UINT16 heightItem;
	// * +20
	LPCSTR hint;
	// * +24
	LPCSTR rightClickHint;
	h3unk _f_28[4];
	// * +2C
	INT32 deactivatesCount;

	// * private function, use SetText() of respective items
	// * if it's not there, it's not available!
	VOID _SetText(LPCSTR text);

public:
	static H3DlgItem* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags);

	VOID   EnableItem(BOOL enable) { THISCALL_2(VOID, vTable->setEnabled, this, enable); }
	VOID   Enable()                { EnableItem(TRUE); }
	VOID   Disable()               { EnableItem(FALSE); }
	INT16  GetX()                  { return xPos; }
	INT16  GetY()                  { return yPos; }
	BOOL   IsEnabled()             { return !(state & 0x20); }
	VOID   SetX(UINT16 x)          { xPos = x; }
	VOID   SetY(UINT16 y)          { yPos = y; }
	INT32  GetHeight()             { return heightItem; }
	INT32  GetWidth()              { return widthItem; }
	VOID   SetWidth(UINT16 w)      { widthItem = w; }
	VOID   SetHeight(UINT16 h)     { heightItem = h; }
	VOID   Draw(); // draw new contents through vTable
	VOID   Refresh(); // refresh screen through parent dlg
	VOID   Hide()                  { state &= ~4; }
	VOID   Show()                  { state |= 4; }
	VOID   Shade()                 { state |= 8; }
	VOID   UnShade()               { state &= ~8; }
	VOID   SetFocus(BOOL8 focus)   { THISCALL_2(VOID, vTable->setFocus, this, focus); }
	BOOL   IsVisible()             { return state & 4; }
	LPCSTR GetHint()               { return hint; }
	VOID   SetHint(LPCSTR msg)     { hint = msg; }
	UINT16 GetID()                 { return id; }
	VOID   ParentRedraw(); // redraw through parent
	VOID   ColorToPlayer(INT8 player);
	VOID   SendCommand(INT32 command, INT32 parameter);

	H3DlgFrame          *CastFrame()            { return (H3DlgFrame*)this; }
	H3DlgDef            *CastDef()              { return (H3DlgDef*)this; }
	H3DlgDefButton      *CastDefButton()        { return (H3DlgDefButton*)this; }
	H3DlgCaptionButton  *CastDefButtonCaption() { return (H3DlgCaptionButton*)this; }
	H3DlgCustomButton*  CastCustomButton()      { return (H3DlgCustomButton*)this; }
	H3DlgPcx*           CastPcx()               { return (H3DlgPcx*)this; }
	H3DlgPcx16          *CastPcx16()            { return (H3DlgPcx16*)this; }
	H3DlgEdit           *CastEdit()             { return (H3DlgEdit*)this; }
	H3DlgText           *CastText()             { return (H3DlgText*)this; }
	H3DlgTextPcx        *CastTextPcx()          { return (H3DlgTextPcx*)this; }
	H3DlgHintBar        *CastHintBar()          { return (H3DlgHintBar*)this; }
	H3DlgScrollableText *CastScrollText()       { return (H3DlgScrollableText*)this; }
	H3DlgScrollbar      *CastScrollbar()        { return (H3DlgScrollbar*)this; }
};

// * a 1-pixel wide rectangular frame with the color
// * of your choice
struct H3DlgFrame : public H3DlgItem // size 0x38
{
protected:
	// * +30
	// * RGB565 color
	H3RGB565 color565;
	h3unk _f_32[2];
	// * +34
	// * modifies hue within frame toward RGB565 color
	BOOL8 change_hue; // see 0x44FEB4
	h3unk _f_35[3];
public:
	static H3DlgFrame* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color);
	static H3DlgFrame* Create(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color);
	// * the around parameter will create the frame around the edge
	// * of the dialog item instead of covering some of its pixels
	static H3DlgFrame* Create(H3DlgItem *target, RGB565 color, INT id = 0, BOOL around_edge = false);

	VOID     ChangeColor(RGB565 color) { color565.SetBits(color); }
	VOID     HideHue()                 { change_hue = FALSE; }
	VOID     ShowHue()                 { change_hue = TRUE; }
	VOID     ToggleHue()               { change_hue = !change_hue; }
	H3RGB565 *GetColor()               { return &color565; }
};

struct H3DlgDef : public H3DlgItem // size 0x48
{
protected:
	// * +30
	struct H3LoadedDEF *loadedDef;
	// * +34
	INT32 defFrame;
	// * +38
	INT32 defFrameOnClick;
	// * +3C
	INT32 mirror;
	h3unk _f_40[4];
	// * +44
	INT16 closeDialog;
	h3unk _f_46[2];
public:
	static H3DlgDef* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	static H3DlgDef* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	static H3DlgDef* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame = 0, INT32 group = 0);
	VOID SetFrame(INT32 frame) { defFrame = frame; }
	INT ToggleFrame() { defFrame = !defFrame; defFrameOnClick = !defFrameOnClick; return defFrame; }
	INT32 GetFrame() { return defFrame; }
	VOID Copy(H3DlgDef* src);
	VOID ColorDefToPlayer(INT32 id);
	VOID SetClickFrame(INT32 clickFrame) { defFrameOnClick = clickFrame; }
};

struct H3DlgDefButton : public H3DlgDef // size 0x68 ~ although there is room for CustomProc, which is the same as H3DlgCustomButton, however it is not passed as an argument to the function
{
protected:
	// * +48
	H3Vector<INT32> hotkeys; // ?
	// * +58
	H3String caption;
	// customProc
public:
	static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
	static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
	static H3DlgDefButton* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 clickFrame);
};

struct H3DlgCaptionButton : public H3DlgDefButton // size 0x70
{
protected:
	// * +68
	INT32 loadedFont;
	// * +6C
	INT32 color;
public:
	VOID SetText(LPCSTR text) { _SetText(text); }
	static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
	static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
};

struct H3DlgCustomButton : public H3DlgDefButton // size 0x6C
{
protected:
	// * +68
	H3DlgButton_proc customButtonProc;
public:
	static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	static H3DlgCustomButton* Create(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);

	VOID ToggleFlag(BOOL & flag);
};

struct H3DlgPcx : public H3DlgItem
{
protected:
	// * +30
	struct H3LoadedPCX *loadedPcx;
public:
	static H3DlgPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
	static H3DlgPcx* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
	static H3DlgPcx* Create(INT32 x, INT32 y, LPCSTR pcxName);
	VOID Copy(H3DlgPcx* src);

	VOID AdjustColor(INT player) { THISCALL_2(VOID, 0x4501D0, this, player); }
};

struct H3DlgPcx16 : public H3DlgItem
{
protected:
	// * +30
	H3LoadedPCX16 *loadedPcx16;
public:
	static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
	static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
	static H3DlgPcx16* Create(INT32 x, INT32 y, LPCSTR pcxName);
	VOID SetPcx(H3LoadedPCX16* pcx16) { loadedPcx16 = pcx16; }
};

struct H3DlgEdit : public H3DlgItem // size 0x70
{
protected:
	// * +30
	H3String text;
	// * +40
	INT32 loadedFont;
	// * +44
	INT32 color;
	// * +48
	INT32 bkColor;
	// * +4C
	INT32 align;
	// * +50
	struct H3LoadedPCX *loadedPcx;
	// * +54
	struct H3LoadedPCX16 *loadedPcx16;
	// * +58
	INT16 caretPos;
	// * +5A
	INT16 maxLength;
	// * +5C
	INT16 fieldSizeX;
	// * +5E
	INT16 fieldSizeY;
	// * +60
	INT16 fieldX;
	// * +62
	INT16 fieldY;
	h3unk _f_64[4][2];
	h3unk _f_6C;
	// * +6D
	BOOL8 focused;
	// * +6E
	BOOL8 autoRedraw;
	h3unk _f_6F;
public:
	static H3DlgEdit* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY);
	LPCSTR   GetText()                { return text.String(); }
	H3String *GetString()             { return &text; }
	VOID     SetText(LPCSTR text)     { _SetText(text); }
	VOID     DecreaseCaret()          { caretPos--; }
	VOID     SetAutoredraw(BOOL on)   { autoRedraw = on; }
	VOID     SetFocus(BOOL on = TRUE) { THISCALL_2(VOID, vTable->setFocus, this, on); }
};

struct H3DlgText : public H3DlgItem
{
protected:
	// * +30
	H3String text;
	// * +34
	H3Font *font;
	// * +38
	INT32 color;
	// * +3C
	INT32 bkColor;
	// * +40
	INT32 align;
public:
	static H3DlgText* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName = NH3Dlg::Text::SMALL, INT32 color = NH3Dlg::TextColor::REGULAR, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
	H3String& GetH3String()        { return text; }
	VOID      SetText(LPCSTR text) { _SetText(text); }
};

struct H3DlgTextPcx : public H3DlgText
{
protected:
	// * +44
	struct H3LoadedPCX *loadedPcx;
public:
	static H3DlgTextPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
	static H3DlgTextPcx* Create(INT32 x, INT32 y, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 align);
};

struct H3DlgHintBar : public H3DlgTextPcx
{
	VOID   ShowHint(H3Msg *msg);
	VOID   ShowMessage(LPCSTR msg);
	static H3DlgHintBar * Create(H3Dlg * dlg);
};

struct H3DlgScrollableText : public H3DlgItem
{
protected:
	// * +30
	H3Font *font;
	// * +34
	INT32 linesCount;
	h3unk _f_38[12];
	// * +44
	H3Vector<UINT32> items; // never bothered to figure out the type
	// * +54
	H3DlgScrollbar *scrollBar;
	h3unk _f_58[4];
public:
	static H3DlgScrollableText* Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue);
};

struct H3DlgScrollbar : public H3DlgItem
{
protected:
	// * +30
	struct H3LoadedDEF *loadedBtnDef;
	// * +34
	struct H3LoadedPCX *loadedPcx;
	h3unk _f_38[4];
	// * +3C
	INT32 tick;
	// * +40
	INT32 btnPosition;
	// * +44
	INT32 sizeFree;
	// * +48
	INT32 ticksCount;
	// * +4C
	INT32 sizeMax;
	// * +50
	INT32 bigStepSize;
	// * +54
	INT32 btnSize2;
	h3unk _f_58[4];
	// * +5C
	INT32 catchKeys;
	h3unk _f_60[4];
	// * +64
	H3DlgScrollbar_proc callBack;

public:
	static H3DlgScrollbar* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled);
	INT32 GetTick()              { return tick; }
	VOID  SetTick(INT32 index)   { tick = index; }
	VOID  SetBigStep(INT32 step) { bigStepSize = step; } // used for pageup, pagedown
	VOID  SetButtonPosition()    { btnPosition = sizeFree * tick / (ticksCount - 1) + btnSize2; }
	BOOL  IsHorizontal()         { return widthItem > heightItem; }
	INT32 GetRightButtonX()      { return parent->GetX() + xPos + sizeMax - btnSize2; } // for horizontal scrollbar only!
	INT32 GetHorizontalY()       { return parent->GetY() + yPos; }
	INT32 GetBackgroundWidth()   { return sizeMax - 2 * btnSize2; }
	INT32 GetBackgroundX()       { return parent->GetX() + xPos + btnSize2; }
	INT32 GetSliderX()           { return parent->GetX() + xPos + btnPosition; }
};

#pragma pack(pop)

// * Member functions

inline H3DlgItem * H3Dlg::AddItem(H3DlgItem * item)
{
	dlgItems += item;
	return THISCALL_3(H3DlgItem*, 0x5FF270, this, item, -1); // LoadItem
}

inline H3DlgItem * H3Dlg::ItemAtPosition(H3Msg * msg)
{
	return THISCALL_3(H3DlgItem*, 0x5FF9A0, this, msg->x_abs, msg->y_abs);
}

inline H3DlgItem * H3Dlg::GetH3DlgItem(UINT16 id)
{
	return THISCALL_2(H3DlgItem*, 0x5FF5B0, this, id);
}

inline VOID H3Dlg::EnableItem(UINT16 id, BOOL enable)
{
	H3DlgItem *it = GetH3DlgItem(id);
	if (it)
		it->EnableItem(enable);
}

inline VOID H3Dlg::SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter)
{
	THISCALL_5(VOID, 0x5FF400, this, 0x200, command, itemID, parameter);
}

inline VOID H3Dlg::SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter)
{
	H3Msg msg;
	msg.SetCommand(0x200, command, itemID, 0, 0, 0, parameter, 0);
	THISCALL_2(VOID, 0x5FF3A0, this, &msg);
}

inline VOID H3Dlg::AdjustToPlayerColor(INT8 player, UINT16 itemId)
{
	if (H3DlgItem *it = GetH3DlgItem(itemId))
		it->ColorToPlayer(player);
}

inline H3DlgFrame * H3Dlg::CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color)
{
	H3DlgFrame *frame = H3DlgFrame::Create(x, y, width, height, id, color);
	if (frame)
		AddItem(frame);
	return frame;
}

inline H3DlgFrame * H3Dlg::CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color)
{
	H3DlgFrame *frame = H3DlgFrame::Create(x, y, width, height, 0, color);
	if (frame)
		AddItem(frame);
	return frame;
}

inline H3DlgFrame * H3Dlg::CreateFrame(H3DlgItem * target, RGB565 color, INT id, BOOL around_edge)
{
	H3DlgFrame *frame = H3DlgFrame::Create(target, color, id, around_edge);
	if (frame)
		AddItem(frame);
	return frame;
}

inline H3DlgDef * H3Dlg::CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *def = H3DlgDef::Create(x, y, width, height, id, defName, frame, group, mirror, closeDialog);
	if (def)
		AddItem(def);
	return def;
}

inline H3DlgDef * H3Dlg::CreateDef(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *def = H3DlgDef::Create(x, y, id, defName, frame, group, mirror, closeDialog);
	if (def)
		AddItem(def);
	return def;
}

inline H3DlgDefButton * H3Dlg::CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
{
	H3DlgDefButton *but = H3DlgDefButton::Create(x, y, width, height, id, defName, frame, clickFrame, closeDialog, hotkey);
	if (but)
		AddItem(but);
	return but;
}

inline H3DlgDefButton * H3Dlg::CreateOKButton(INT32 x, INT32 y)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, H3Msg::ID_OK, NH3Dlg::Assets::OKAY_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
	if (button)
	{
		AddItem(H3DlgPcx::Create(x - 1, y - 1, NH3Dlg::Assets::BOX_64_30_PCX));
		AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateSaveButton(INT32 x, INT32 y)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, H3Msg::ID_SAVE, NH3Dlg::Assets::iSAVE_DEF, 0, 1, FALSE, NH3VKey::H3VK_S);
	if (button)
	{
		AddItem(H3DlgPcx::Create(x - 1, y - 1, NH3Dlg::Assets::BOX_64_32_PCX));
		AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, id, NH3Dlg::Assets::ON_OFF_CHECKBOX, frame, clickFrame, 0, 0);
	if (button)
		AddItem(button);
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateOKButton()
{

	H3DlgDefButton *button = H3DlgDefButton::Create(25, heightDlg - 50, H3Msg::ID_OK, NH3Dlg::Assets::OKAY_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
	if (button)
	{
		AddItem(H3DlgPcx::Create(25 - 1, heightDlg - 50 - 1, NH3Dlg::Assets::BOX_64_30_PCX));
		AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateOK32Button(INT32 x, INT32 y)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, H3Msg::ID_OK, NH3Dlg::Assets::OKAY32_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
	if (button)
	{
		AddItem(H3DlgPcx::Create(x - 1, y - 1, NH3Dlg::Assets::BOX_66_32_PCX));
		AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateCancelButton()
{
	H3DlgDefButton *button = H3DlgDefButton::Create(widthDlg - 25 - 64, heightDlg - 50, H3Msg::ID_CANCEL, NH3Dlg::Assets::CANCEL_DEF, 0, 1, TRUE, NH3VKey::H3VK_ESCAPE);
	if (button)
	{
		AddItem(H3DlgPcx::Create(widthDlg - 25 - 1 - 64, heightDlg - 50 - 1, NH3Dlg::Assets::BOX_64_30_PCX));
		AddItem(button);
	}
	return button;
}

inline H3DlgCaptionButton * H3Dlg::CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
{
	H3DlgCaptionButton *but = H3DlgCaptionButton::Create(x, y, width, height, id, defName, text, font, frame, group, closeDialog, hotkey, color);
	if (but)
		AddItem(but);
	return but;
}

inline H3DlgCustomButton * H3Dlg::CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *but = H3DlgCustomButton::Create(x, y, width, height, id, defName, customProc, frame, clickFrame);
	if (but)
		AddItem(but);
	return but;
}

inline H3DlgCustomButton * H3Dlg::CreateCustomButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *but = H3DlgCustomButton::Create(x, y, id, defName, customProc, frame, clickFrame);
	if (but)
		AddItem(but);
	return but;
}

inline H3DlgCustomButton * H3Dlg::CreateCustomButton(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	return CreateCustomButton(x, y, 0, defName, customProc, frame, clickFrame);
}

inline H3DlgPcx * H3Dlg::CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
{
	H3DlgPcx *pcx = H3DlgPcx::Create(x, y, width, height, id, pcxName);
	if (pcx)
		AddItem(pcx);
	return pcx;
}

inline H3DlgPcx * H3Dlg::CreateLineSeparator(INT32 x, INT32 y, INT32 width)
{
	return CreatePcx(x, y, width, 2, 0, NH3Dlg::HDassets::LINE_SEPARATOR);
}

inline H3DlgPcx16 * H3Dlg::CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
{
	H3DlgPcx16 *pcx = H3DlgPcx16::Create(x, y, width, height, id, pcxName);
	if (pcx)
		AddItem(pcx);
	return pcx;
}

inline H3DlgEdit * H3Dlg::CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY)
{
	H3DlgEdit *ed = H3DlgEdit::Create(x, y, width, height, maxLength, text, fontName, color, align, pcxName, id, hasBorder, borderX, borderY);
	if (ed)
		AddItem(ed);
	return ed;
}

inline H3DlgText * H3Dlg::CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, INT32 color, INT32 id, INT32 align, INT32 bkColor)
{
	H3DlgText *tx = H3DlgText::Create(x, y, width, height, text, fontName, color, id, align, bkColor);
	if (tx)
		AddItem(tx);
	return tx;
}

inline BOOL H3Dlg::CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height)
{
	if (!background)
		return FALSE;

	background->FillRectangle(x, y, width, height, 0, 0, 0);
	return TRUE;
}

inline H3DlgText * H3Dlg::OldCreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height)
{
	H3DlgText *t = H3DlgText::Create(x, y, width, height, h3_NullString, NH3Dlg::Text::MEDIUM, 0, 0, 0, 9 + NH3Dlg::TextColor::BLACK);
	if (t)
		AddItem(t);
	return t;
}

inline H3DlgHintBar * H3Dlg::CreateHint()
{
	H3DlgHintBar *h = H3DlgHintBar::Create(this);
	if (h)
		AddItem(h);
	return h;
}

inline H3DlgTextPcx * H3Dlg::CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id, INT32 align)
{
	H3DlgTextPcx *tx = H3DlgTextPcx::Create(x, y, width, height, text, fontName, pcxName, color, id, align);
	if (tx)
		AddItem(tx);
	return tx;
}

inline H3DlgScrollableText * H3Dlg::CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue)
{
	H3DlgScrollableText *sc = H3DlgScrollableText::Create(text, x, y, width, height, font, color, isBlue);
	if (sc)
		AddItem(sc);
	return sc;
}

inline H3DlgScrollbar * H3Dlg::CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled)
{
	H3DlgScrollbar *sc = H3DlgScrollbar::Create(x, y, width, height, id, ticksCount, scrollbarProc, isBlue, stepSize, arrowsEnabled);
	if (sc)
		AddItem(sc);
	return sc;
}

inline VOID H3Dlg::PlaceAtMouse()
{
	int x, y;
	F_GetCursorPosition(x, y);

	// adjust x & y to make certain the dialog will fit
	x = min(x, gameWidth - widthDlg - 200); // 200 is width of adventure bar on right
	y = min(y, gameHeight - heightDlg - 48); // 48 is height of resource bar on bottom
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;

	xDlg = x;
	yDlg = y;
}

inline VOID H3Dlg::Start()
{
	H3MouseManager *mmgr = H3Pointers::MouseManager();
	INT32 mouseType = mmgr->GetType();
	INT32 mouseFrame = mmgr->GetFrame();
	mmgr->DefaultCursor();

	THISCALL_2(VOID, vtable->runDlg, this, 0); // run H3Dlg

	mmgr->SetCursor(mouseType, mouseFrame); // restore previous cursor
}

inline BOOL H3Dlg::OldDlgBackground(BOOL frame, BOOL statusBar, INT32 colorIndex)
{
	INT32 w = widthDlg;
	INT32 h = heightDlg;

	if (frame && (w < 64 || h < 64))
		return FALSE;

	INT32 x, y, _w, _h;
	INT32 dh;
	y = 0;
	H3DlgPcx *bg = H3DlgPcx::Create(0, 0, min(w, 256), min(h, 256), 0, NH3Dlg::Assets::DIBOXBACK); // template background to copy
	if (!bg)
		return FALSE;
	_h = h;
	////////////////////
	// make background first
	////////////////////
	while (_h > 0) // vertical pass second
	{
		x = 0;
		dh = min(256, _h);
		_w = w; // reset variable to dialog width
		while (_w > 0) // horizontal pass first
		{
			H3DlgPcx *bg2 = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
			if (!bg2)
			{
				F_delete(bg);
				return FALSE;
			}
			bg2->Copy(bg); // copy contents
			bg2->SetX(x); // update position
			bg2->SetY(y);
			bg2->SetWidth(min(_w, 256)); // update dimensions
			bg2->SetHeight(dh);
			AddItem(bg2);
			x += 256;
			_w -= 256;
		}
		y += 256; // go to next horizontal pass
		_h -= 256;
	}

	F_delete(bg); // no longer needed

	if (!frame)
		return TRUE;

	enum eBackgroundFrames
	{
		BF_tl,
		BF_tr,
		BF_bl,
		BF_br,
		BF_ml,
		BF_mr,
		BF_tm,
		BF_bm,
		BF_blstat,
		BF_brstat,
		BF_bmstat
	};

	////////////////////
	////////////////////
	// now make frame
	////////////////////
	////////////////////

	// definitions
	H3DlgDef *def, *def2;
	INT8 f_bl, f_br, f_bm;
	if (statusBar)
	{
		f_bl = BF_blstat;
		f_br = BF_brstat;
		f_bm = BF_bmstat;
	}
	else
	{
		f_bl = BF_bl;
		f_br = BF_br;
		f_bm = BF_bm;
	}

	////////////////////
	// start with top left, as base - don't place yet
	////////////////////
	H3DlgDef *baseDef = H3DlgDef::Create(0, 0, NH3Dlg::Assets::DLGBOX, BF_tl);
	if (!baseDef)
		return FALSE;

	////////////////////
	// do middle sides
	////////////////////
	x = w - 64 - 64; // corners are written after

	while (x > 0)
	{
		def = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
		if (!def)
			return FALSE;
		def->Copy(baseDef);
		def->SetX(x);
		def->SetFrame(BF_tm);
		AddItem(def);

		def2 = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
		if (!def2)
			return FALSE;
		def2->Copy(def);
		def2->SetY(h - 64);
		def2->SetFrame(f_bm);
		AddItem(def2);

		x -= 64;
	}

	////////////////////
	// do vertical sides ~ defs can only match their whole size
	////////////////////
	// start from bottom and move up
	y = h - 64 - 64;

	while (y >= 0)
	{
		def = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
		if (!def)
			return FALSE;
		def->Copy(baseDef);
		def->SetY(y);
		def->SetFrame(BF_ml);
		AddItem(def);

		def2 = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
		if (!def2)
			return FALSE;
		def2->Copy(def);
		def2->SetX(w - 64);
		def2->SetFrame(BF_mr);
		AddItem(def2);

		y -= 64;
	}

	////////////////////
	// All corners
	////////////////////
	// top left
	AddItem(baseDef);

	////////////////////
	// now top right
	////////////////////
	def = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
	if (!def)
		return FALSE;
	def->Copy(baseDef);
	def->SetX(w - 64);
	def->SetFrame(BF_tr);
	AddItem(def);

	////////////////////
	// bottom left
	////////////////////
	def = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
	if (!def)
		return FALSE;
	def->Copy(baseDef);
	def->SetY(h - 64);
	def->SetFrame(f_bl);
	AddItem(def);

	////////////////////
	// bottom right
	////////////////////
	def = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
	if (!def)
		return FALSE;
	def->Copy(baseDef);
	def->SetX(w - 64);
	def->SetY(h - 64);
	def->SetFrame(f_br);
	AddItem(def);

	def->ColorDefToPlayer(colorIndex);
	return TRUE;
}

inline BOOL H3Dlg::AddBackground(INT32 x, INT32 y, INT32 w, INT32 h, BOOL frame, BOOL statusBar, INT32 colorIndex, BOOL is_blue)
{
	if (this->background)
		return FALSE;

	if (frame && (w < 64 || h < 64))
		return FALSE;

	H3LoadedPCX16 *pcx = H3LoadedPCX16::Create(h3_NullString, widthDlg, heightDlg);
	if (!pcx)
		return FALSE;

	// * the actual dialog background
	// * made with no pcx name as we want to insert our own
	// * otherwise h3 tries to load the named pcx
	H3DlgPcx16* bg = H3DlgPcx16::Create(x, y, w, h, 0, nullptr);
	if (!bg)
	{
		pcx->Destroy();
		return FALSE;
	}

	// * stored for further use
	this->background = pcx;

	BackgroundRegion(x, y, w, h, is_blue);
	if (frame)
		FrameRegion(x, y, w, h, statusBar, colorIndex, is_blue);

	bg->SetPcx(pcx);
	AddItem(bg);
	return TRUE;
}

inline BOOL H3Dlg::AddBackground(BOOL frame, BOOL statusBar, INT32 colorIndex)
{
	return AddBackground(0, 0, widthDlg, heightDlg, frame, statusBar, colorIndex);
}

inline BOOL H3Dlg::AddBackground(H3LoadedPCX * pcx)
{
	if (!pcx || background)
		return FALSE;
	background = H3LoadedPCX16::Create(h3_NullString, pcx->width, pcx->height);
	if (!background)
		return FALSE;

	pcx->DrawToPcx16(0, 0, pcx->width, pcx->height, background, 0, 0, FALSE);

	return TRUE;
}

inline BOOL H3Dlg::AddBackground(H3LoadedPCX16 * pcx)
{
	if (!pcx || background)
		return FALSE;
	background = H3LoadedPCX16::Create(h3_NullString, pcx->width, pcx->height);
	if (!background)
		return FALSE;

	pcx->DrawToPcx16(0, 0, FALSE, background);

	return TRUE;
}

inline BOOL H3Dlg::AddBackground(H3LoadedPCX24 * pcx)
{
	if (!pcx || background)
		return FALSE;

	background = H3LoadedPCX16::Create(h3_NullString, pcx->width, pcx->height);
	if (!background)
		return FALSE;

	pcx->DrawToPcx16(0, 0, background);

	return TRUE;
}

inline BOOL H3Dlg::AddBackground(H3LoadedDEF * def, INT group, INT frame)
{
	if (background || !def || def->groupsCount < group || !def->activeGroups[group])
		return FALSE;
	H3DefGroup* grp = def->groups[group];
	if (grp->count < frame)
		return FALSE;

	H3DefFrame *fr = grp->frames[frame];

	background = H3LoadedPCX16::Create(h3_NullString, fr->frameWidth, fr->frameHeight);
	if (!background)
		return FALSE;

	fr->DrawToPcx16(0, 0, fr->frameWidth, fr->frameHeight, background, 0, 0, def->palette565);

	return TRUE;
}

inline BOOL H3Dlg::OldSimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height)
{
	INT32 xEnd, yEnd, dX, dY;
	dX = _width;
	dY = _height;
	xEnd = xStart + _width;
	yEnd = yStart + _height;
	if (dX < 4 || dY < 4)
		return FALSE;

	H3DlgPcx *up, *down, *left, *right, *pcx;

	up = H3DlgPcx::Create(xStart, yStart, NH3Dlg::HDassets::FRAME_U);
	down = H3DlgPcx::Create(xStart, yEnd - 4, NH3Dlg::HDassets::FRAME_D);
	left = H3DlgPcx::Create(xStart, yStart, NH3Dlg::HDassets::FRAME_L);
	right = H3DlgPcx::Create(xEnd - 4, yStart, NH3Dlg::HDassets::FRAME_R);

	if (!up || !down || !left || !right)
	{
		F_delete(up);
		F_delete(down);
		F_delete(left);
		F_delete(right);
		return FALSE;
	}

	////////////////////
	// do horizontal sides
	////////////////////
	while (dX >= 4)
	{
		dX -= 4;
		pcx = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
		if (pcx)
		{
			pcx->Copy(up);
			pcx->SetX(xStart + dX);
			AddItem(pcx);
		}
		pcx = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
		if (pcx)
		{
			pcx->Copy(down);
			pcx->SetX(xStart + dX);
			AddItem(pcx);
		}
	}

	////////////////////
	// do vertical sides
	////////////////////
	while (dY >= 4)
	{
		dY -= 4;
		pcx = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
		if (pcx)
		{
			pcx->Copy(left);
			pcx->SetY(yStart + dY);
			AddItem(pcx);
		}
		pcx = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
		if (pcx)
		{
			pcx->Copy(right);
			pcx->SetY(yStart + dY);
			AddItem(pcx);
		}
	}

	F_delete(up);
	F_delete(down);
	F_delete(left);
	F_delete(right);

	////////////////////
	// Add corners
	////////////////////
	AddItem(H3DlgPcx::Create(xStart, yStart, NH3Dlg::HDassets::FRAME_LU));
	AddItem(H3DlgPcx::Create(xStart, yEnd - 4, NH3Dlg::HDassets::FRAME_LD));
	AddItem(H3DlgPcx::Create(xEnd - 4, yStart, NH3Dlg::HDassets::FRAME_RU));
	AddItem(H3DlgPcx::Create(xEnd - 4, yEnd - 4, NH3Dlg::HDassets::FRAME_RD));

	return TRUE;
}

inline BOOL H3Dlg::BackgroundRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL is_blue)
{
	if (!background || w <= 0 || h <= 0)
		return FALSE;

	H3LoadedPCX* back = H3LoadedPCX::Load(is_blue ? NH3Dlg::HDassets::DLGBLUEBACK : NH3Dlg::Assets::DIBOXBACK);
	if (!back)
		return FALSE;

	int _x, _y, _w, _h, dh;
	_y = y;
	_h = h;

	// * add background region
	while (_h > 0)
	{
		_x = x;
		dh = min(256, _h);
		_w = w;
		while (_w > 0)
		{
			back->DrawToPcx16(0, 0, min(_w, 256), dh, background, _x, _y, FALSE);
			_x += 256;
			_w -= 256;
		}
		_y += 256;
		_h -= 256;
	}
	back->Dereference();

	return TRUE;
}

inline BOOL H3Dlg::SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPCX16 *destination)
{
	H3LoadedPCX16* target = destination ? destination : background;

	if (!target)
		return FALSE;

	INT32 xEnd, yEnd, dX, dY;
	dX = _width;
	dY = _height;
	xEnd = xStart + _width;
	yEnd = yStart + _height;
	if (dX < 4 || dY < 4)
		return FALSE;

	// * helper struct
	struct HDFrames
	{
		enum
		{
			up,
			down,
			left,
			right,
			tl,
			tr,
			bl,
			br
		};

		H3LoadedPCX *frames[8];
		H3LoadedPCX16 *tgt;
		HDFrames(H3LoadedPCX16* bg) :
			tgt(bg)
		{
			frames[up]    = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_U);
			frames[down]  = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_D);
			frames[left]  = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_L);
			frames[right] = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_R);
			frames[tl]    = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_LU);
			frames[tr]    = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_RU);
			frames[bl]    = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_LD);
			frames[br]    = H3LoadedPCX::Load(NH3Dlg::HDassets::FRAME_RD);
		}
		BOOL AllLoaded()
		{
			for (int i = 0; i < 8; ++i)
				if (frames[i] == nullptr)
					return FALSE;
			return TRUE;
		}

		~HDFrames()
		{
			for (int i = 0; i < 8; ++i)
				if (frames[i])
					frames[i]->Dereference();
		}

		VOID Draw(INT x, INT y, INT frame)
		{
			frames[frame]->DrawToPcx16(0, 0, 4, 4, tgt, x, y, FALSE);
		}
	};

	HDFrames frames(target);
	if (!frames.AllLoaded())
		return FALSE;

	////////////////////////////////////////
	// do horizontal sides - bottom to top
	////////////////////////////////////////
	while (dX >= 4)
	{
		dX -= 4;
		frames.Draw(xStart + dX, yStart,   frames.up);
		frames.Draw(xStart + dX, yEnd - 4, frames.down);
	}

	////////////////////////////////////////
	// do vertical sides - right to left
	////////////////////////////////////////
	while (dY >= 4)
	{
		dY -= 4;
		frames.Draw(xStart,   yStart + dY, frames.left);
		frames.Draw(xEnd - 4, yStart + dY, frames.right);
	}

	////////////////////
	// Add corners
	////////////////////
	frames.Draw(xStart,   yStart,   frames.tl);
	frames.Draw(xStart,   yEnd - 4, frames.bl);
	frames.Draw(xEnd - 4, yStart,   frames.tr);
	frames.Draw(xEnd - 4, yEnd - 4, frames.br);

	return TRUE;
}

inline BOOL H3Dlg::FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue)
{
	enum eBackgroundFrames
	{
		BF_tl,
		BF_tr,
		BF_bl,
		BF_br,
		BF_ml,
		BF_mr,
		BF_tm,
		BF_bm,
		BF_blstat,
		BF_brstat,
		BF_bmstat
	};

	if (!background)
		return FALSE;

	if (w < 64 || h < 64)
		return FALSE;

	H3LoadedDEF* box = H3LoadedDEF::Load(is_blue ? NH3Dlg::HDassets::DLGBLUEBOX : NH3Dlg::Assets::DLGBOX);
	if (!box)
		return FALSE;

	INT f_bl, f_br, f_bm;
	if (statusBar)
	{
		f_bl = BF_blstat;
		f_br = BF_brstat;
		f_bm = BF_bmstat;
	}
	else
	{
		f_bl = BF_bl;
		f_br = BF_br;
		f_bm = BF_bm;
	}

	// * copying to this local palette prevents recoloration of def for others
	H3Palette565 pal565, *pal;
	if (!is_blue)
	{
		F_memcpy(&pal565, box->palette565, sizeof(pal565));
		pal565.ColorToPlayer(colorIndex);
		pal = &pal565;
	}
	else
		pal = box->palette565;

	// * add horizontal bars
	int _w = w - 64 - 64;
	H3DefFrame *tm = box->GetGroupFrame(0, eBackgroundFrames::BF_tm);
	H3DefFrame *bm = box->GetGroupFrame(0, f_bm);
	while (_w > 0)
	{
		tm->DrawToPcx16(0, 0, 64, 64, background, x + _w, y, pal);
		bm->DrawToPcx16(0, 0, 64, 64, background, x + _w, y + h - 64, pal);
		_w -= 64;
	}

	// * add vertical bars
	int _h = h - 64 - 64;
	H3DefFrame *ml = box->GetGroupFrame(0, eBackgroundFrames::BF_ml);
	H3DefFrame *mr = box->GetGroupFrame(0, eBackgroundFrames::BF_mr);
	while (_h > 0)
	{
		ml->DrawToPcx16(0, 0, 64, 64, background, x, y + _h, pal);
		mr->DrawToPcx16(0, 0, 64, 64, background, x + w - 64, y + _h, pal);
		_h -= 64;
	}

	// * add four corners
	box->GetGroupFrame(0, eBackgroundFrames::BF_tl)->DrawToPcx16(0, 0, 64, 64, background, x, y, pal);
	box->GetGroupFrame(0, eBackgroundFrames::BF_tr)->DrawToPcx16(0, 0, 64, 64, background, x + w - 64, y, pal);
	box->GetGroupFrame(0, f_bl)->DrawToPcx16(0, 0, 64, 64, background, x, y + h - 64, pal);
	box->GetGroupFrame(0, f_br)->DrawToPcx16(0, 0, 64, 64, background, x + w - 64, y + h - 64, pal);

	box->Dereference();
	return TRUE;

}

inline VOID H3Dlg::Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy)
{
	H3Pointers::WindowManager()->H3Redraw(xDlg + x, yDlg + y, dx, dy);
}

inline VOID H3Dlg::Redraw()
{
	THISCALL_4(VOID, vtable->redrawDlg, this, TRUE, -65535, 65535);
}

inline VOID H3Dlg::RedrawItem(UINT16 itemID)
{
	if (H3DlgItem *it = GetH3DlgItem(itemID))
		it->Refresh();
}

inline H3DlgItem * H3DlgItem::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags)
{
	H3DlgItem *d = (H3DlgItem*)F_malloc(sizeof(H3DlgItem));
	if (d)
		THISCALL_7(H3DlgItem*, 0x5FE900, d, x, y, width, height, id, flags);
	return d;
}

inline VOID H3DlgItem::ParentRedraw()
{
	parent->Redraw(xPos, yPos, widthItem, heightItem);
}

inline VOID H3DlgItem::Draw()
{
	THISCALL_1(VOID, vTable->draw, this);
}

inline VOID H3DlgItem::Refresh()
{
	parent->Redraw(xPos, yPos, widthItem, heightItem);
}

inline VOID H3DlgItem::ColorToPlayer(INT8 player) // for PCX
{
	THISCALL_2(VOID, 0x4501D0, this, player);
}

inline VOID H3DlgItem::SendCommand(INT32 command, INT32 parameter)
{
	THISCALL_3(VOID, 0x5FED80, this, command, parameter);
}

inline VOID H3DlgItem::_SetText(LPCSTR text)
{
	THISCALL_2(VOID, vTable->setText, this, text);
}

inline H3DlgFrame * H3DlgFrame::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color)
{
	H3DlgFrame *f = (H3DlgFrame*)F_malloc(sizeof(H3DlgFrame));
	if (f)
		THISCALL_8(H3DlgFrame*, 0x44FE00, f, x, y, width, height, id, color, 0x400);
	return f;
}

inline H3DlgFrame * H3DlgFrame::Create(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color)
{
	return Create(x, y, width, height, 0, color);
}

inline H3DlgFrame * H3DlgFrame::Create(H3DlgItem * target, RGB565 color, INT id, BOOL around_edge)
{
	if (!target)
		return nullptr;
	if (around_edge)
		return Create(target->GetX() - 1, target->GetY() - 1, target->GetWidth() + 2, target->GetHeight() + 2, id, color);
	else
		return Create(target->GetX(), target->GetY(), target->GetWidth(), target->GetHeight(), id, color);
}

inline H3DlgDef * H3DlgDef::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *d = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
	if (d)
		THISCALL_12(H3DlgDef*, 0x4EA800, d, x, y, width, height, id, defName, frame, group, mirror, closeDialog, 0x10);
	return d;
}

inline H3DlgDef * H3DlgDef::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *d = Create(x, y, 0, 0, id, defName, frame, group, mirror, closeDialog);
	if (d && d->loadedDef)
	{
		d->widthItem = d->loadedDef->widthDEF;
		d->heightItem = d->loadedDef->heightDEF;
	}
	return d;
}

inline H3DlgDef * H3DlgDef::Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 group)
{
	H3DlgDef *d = Create(x, y, 0, 0, 0, defName, frame, group, 0, 0);
	if (d && d->loadedDef)
	{
		d->widthItem = d->loadedDef->widthDEF;
		d->heightItem = d->loadedDef->heightDEF;
	}
	return d;
}

inline VOID H3DlgDef::Copy(H3DlgDef * src)
{
	F_memcpy(this, src, sizeof(H3DlgDef));
}

inline VOID H3DlgDef::ColorDefToPlayer(INT32 id)
{
	loadedDef->ColorToPlayer(id);
}

inline H3DlgPcx * H3DlgPcx::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
{
	H3DlgPcx *p = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
	if (p)
		THISCALL_8(H3DlgPcx*, 0x44FFA0, p, x, y, width, height, id, pcxName, 0x800);
	return p;
}

inline H3DlgPcx * H3DlgPcx::Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName)
{
	H3DlgPcx *p = Create(x, y, 0, 0, id, pcxName);
	if (p && p->loadedPcx)
	{
		p->widthItem = p->loadedPcx->width;
		p->heightItem = p->loadedPcx->height;
	}
	return p;
}

inline H3DlgPcx * H3DlgPcx::Create(INT32 x, INT32 y, LPCSTR pcxName)
{
	return Create(x, y, 0, pcxName);
}

inline VOID H3DlgPcx::Copy(H3DlgPcx * src)
{
	F_memcpy(this, src, sizeof(H3DlgPcx));
}

inline H3DlgDefButton * H3DlgDefButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
{
	H3DlgDefButton *b = (H3DlgDefButton*)F_malloc(sizeof(H3DlgDefButton));
	if (b)
		THISCALL_12(H3DlgDefButton*, 0x455BD0, b, x, y, width, height, id, defName, frame, clickFrame, closeDialog, hotkey, 2);
	return b;
}

inline H3DlgDefButton * H3DlgDefButton::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
{
	H3DlgDefButton *b = Create(x, y, 0, 0, id, defName, frame, clickFrame, closeDialog, hotkey);
	if (b && b->loadedDef)
	{
		b->widthItem = b->loadedDef->widthDEF;
		b->heightItem = b->loadedDef->heightDEF;
	}
	return b;
}

inline H3DlgDefButton * H3DlgDefButton::Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 clickFrame)
{
	return Create(x, y, 0, defName, frame, clickFrame, 0, 0);
}

inline H3DlgCaptionButton * H3DlgCaptionButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
{
	H3DlgCaptionButton *b = (H3DlgCaptionButton*)F_malloc(sizeof(H3DlgCaptionButton));
	if (b)
		THISCALL_15(H3DlgCaptionButton*, 0x456730, b, x, y, width, height, id, defName, text, font, frame, group, closeDialog, hotkey, 2, color);
	return b;
}

inline H3DlgCaptionButton * H3DlgCaptionButton::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
{
	H3DlgCaptionButton *b = Create(x, y, 0, 0, id, defName, text, font, frame, group, closeDialog, hotkey, color);
	if (b && b->loadedDef)
	{
		b->widthItem = b->loadedDef->widthDEF;
		b->heightItem = b->loadedDef->heightDEF;
	}
	return b;
}

inline H3DlgPcx16 * H3DlgPcx16::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
{
	H3DlgPcx16 *p = (H3DlgPcx16*)F_malloc(sizeof(H3DlgPcx16));
	if (p)
		THISCALL_8(H3DlgPcx16*, 0x450340, p, x, y, width, height, id, pcxName, 0x800);
	return p;
}

inline H3DlgPcx16 * H3DlgPcx16::Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName)
{
	H3DlgPcx16 *p = Create(x, y, 0, 0, id, pcxName);
	if (p && p->loadedPcx16)
	{
		p->widthItem = p->loadedPcx16->width;
		p->heightItem = p->loadedPcx16->height;
	}
	return p;
}

inline H3DlgPcx16 * H3DlgPcx16::Create(INT32 x, INT32 y, LPCSTR pcxName)
{
	return Create(x, y, 0, 0, 0, pcxName);
}

inline H3DlgText * H3DlgText::Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, INT32 color, INT32 id, INT32 align, INT32 bkColor)
{
	H3DlgText *t = (H3DlgText*)F_malloc(sizeof(H3DlgText));
	if (t)
		THISCALL_12(H3DlgText*, 0x5BC6A0, t, x, y, width, height, text, fontName, color, id, align, bkColor, 8);
	return t;
}

inline H3DlgTextPcx * H3DlgTextPcx::Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id, INT32 align)
{
	H3DlgTextPcx *t = (H3DlgTextPcx*)F_malloc(sizeof(H3DlgTextPcx));
	if (t)
		THISCALL_12(H3DlgTextPcx*, 0x5BCB70, t, x, y, width, height, text, fontName, pcxName, color, id, align, 8);
	return t;
}

inline H3DlgTextPcx * H3DlgTextPcx::Create(INT32 x, INT32 y, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 align)
{
	H3DlgTextPcx *t = Create(x, y, 0, 0, text, fontName, pcxName, color, 0, align);
	if (t && t->loadedPcx)
	{
		t->widthItem = t->loadedPcx->width;
		t->heightItem = t->loadedPcx->height;
	}
	return t;
}

inline H3DlgScrollableText * H3DlgScrollableText::Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue)
{
	H3DlgScrollableText *s = (H3DlgScrollableText*)F_malloc(sizeof(H3DlgScrollableText));
	if (s)
		THISCALL_9(H3DlgScrollableText*, 0x5BA360, s, text, x, y, width, height, font, color, isBlue);
	return s;
}

inline H3DlgScrollbar * H3DlgScrollbar::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled)
{
	H3DlgScrollbar *s = (H3DlgScrollbar*)F_malloc(sizeof(H3DlgScrollbar));
	if (s)
		THISCALL_11(H3DlgScrollbar*, 0x5963C0, s, x, y, width, height, id, ticksCount, scrollbarProc, isBlue, stepSize, arrowsEnabled);
	return s;
}

inline H3DlgCustomButton * H3DlgCustomButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *b = (H3DlgCustomButton*)F_malloc(sizeof(H3DlgCustomButton));
	if (b)
		THISCALL_10(H3DlgCustomButton*, 0x456A10, b, x, y, width, height, id, defName, customProc, frame, clickFrame);
	return b;
}

inline H3DlgCustomButton * H3DlgCustomButton::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *b = Create(x, y, 0, 0, id, defName, customProc, frame, clickFrame);
	if (b && b->loadedDef)
	{
		b->widthItem = b->loadedDef->widthDEF;
		b->heightItem = b->loadedDef->heightDEF;
	}
	return b;
}

inline H3DlgCustomButton * H3DlgCustomButton::Create(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	return Create(x, y, 0, defName, customProc, frame, clickFrame);
}

inline VOID H3DlgCustomButton::ToggleFlag(BOOL & flag)
{
	defFrame = !defFrame;
	defFrameOnClick = !defFrameOnClick;
	flag = !flag;
	Draw();
	Refresh();
}


inline H3DlgEdit * H3DlgEdit::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY)
{
	H3DlgEdit *e = (H3DlgEdit*)F_malloc(sizeof(H3DlgEdit));
	if (e)
		THISCALL_17(H3DlgEdit*, 0x5BACD0, e, x, y, width, height, maxLength, text, fontName, color, align, pcxName, 0, id, 0, hasBorder, borderX, borderY);
	return e;
}

inline VOID H3Msg::SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2)
{
	command = _command;
	subtype = _subtype;
	item_id = _item_id;
	flags = _flags;
	x_abs = x;
	y_abs = y;
	parameter = param;
	flags2 = _flags2;
}

inline VOID H3Msg::SetCommand(INT32 cmd, INT32 param)
{
	SetCommand(0x200, cmd, 0, 0, 0, 0, param, 0);
}

inline H3DlgItem * H3Msg::ItemAtPosition(H3Dlg * dlg)
{
	return THISCALL_3(H3DlgItem*, 0x5FF9A0, dlg, x_abs, y_abs);
}

inline VOID H3DlgHintBar::ShowHint(H3Msg *msg)
{
	H3DlgItem *di;
	if (msg->command == H3Msg::MC_MouseOver)
	{
		di = msg->ItemAtPosition(parent);
		if (di)
		{
			if (di->GetHint())
				SetText(di->GetHint());
			else
				SetText(h3_NullString);
			Draw();
			Refresh();
		}
	}
}

inline VOID H3DlgHintBar::ShowMessage(LPCSTR msg)
{
	SetText(msg);
	Draw();
	Refresh();
}

inline H3DlgHintBar * H3DlgHintBar::Create(H3Dlg * dlg)
{
	return (H3DlgHintBar*)H3DlgTextPcx::Create(8, dlg->GetHeight() - 26, dlg->GetWidth() - 16, 19, h3_NullString, NH3Dlg::Text::SMALL, NH3Dlg::HDassets::HD_STATUSBAR_PCX, NH3Dlg::TextColor::REGULAR);
}

inline H3Dlg::H3Dlg(int width, int height, int x, int y, BOOL statusBar, H3Dlg_proc dlgProc, BOOL makeBackground, INT32 colorIndex)
{
	THISCALL_6(H3Dlg*, 0x41AFA0, this, x == -1 ? (gameWidth - width) / 2 : x, y == -1 ? (gameHeight - height) / 2 : y, width, height, 0x12);
	vtable = &CustomDlgVTable;
	background = nullptr;
	if (makeBackground)
		AddBackground(TRUE, statusBar, colorIndex);
	customProc = dlgProc;
	H3DlgHintBar *hint = nullptr;
	if (statusBar)
		hint = CreateHint();
	hintBar = hint;
}

INT32 __fastcall H3DlgCustomProc(H3Dlg * dlg, int, H3Msg * msg)
{
	if (H3DlgHintBar * hint = dlg->GetHintBar())
		hint->ShowHint(msg);
	if (H3Dlg_proc cProc = dlg->GetProc())
		return STDCALL_2(INT32, cProc, dlg, msg);
	else
		return dlg->DefaultProc(msg);
}

#endif /* #define _H3DIALOGS_H_ */