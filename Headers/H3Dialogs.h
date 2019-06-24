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

enum TextAlignment
{
	// left and top are default, value is 0
	TA_HCenter = 1,
	TA_HRight = 2,
	TA_VCenter = 4,
	TA_VBottom = 8,
	TA_BottomRight = 2 | 8,
	TA_BottomCenter = 1 | 8
};

#define TINY_TEXT		((PCHAR)0x660CB4)	// "tiny.fnt"
#define SMALL_TEXT		((PCHAR)0x65F2F8)	// "smalfont.fnt"
#define MEDIUM_TEXT		((PCHAR)0x65F2EC)	// "MedFont.fnt"
#define BIG_TEXT		((PCHAR)0x660B24)	// "bigfont.fnt"
#define VERDANA_TEXT	((PCHAR)0x6700B4)	// "Verd10B.fnt"

#define TEXT_SILVER 0
#define TEXT_REGULAR 1
#define TEXT_HIGHLIGHT 2
#define TEXT_GOLD 3
#define TEXT_WHITE 4
#define TEXT_GREEN 0x0D
#define TEXT_LIGHT_GREEN 0x0E
#define TEXT_DARK_GREEN 0x0F
#define TEXT_BLACK 0x17
#define TEXT_BLUE 0x18
#define TEXT_CYAN 0x1A
#define TEXT_RED 0x1B
#define TEXT_PURPLE 0x1C
#define TEXT_YELLOW 0x1D
#define TEXT_GRAY 0x36
#define TEXT_RED2 0x37
#define TEXT_BLUE2 0x38
#define TEXT_TAN 0x39
#define TEXT_DARK_GREEN2 0x3A
#define TEXT_ORANGE 0x3B
#define TEXT_PURPLE2 0x3C
#define TEXT_DARK_CYAN 0x3D
#define TEXT_PINK 0x3E
#define TEXT_GRAY2 0x3F
#define TEXT_YELLOW2 0x57
#define TEXT_DARK_YELLOW 0x58
#define TEXT_TAN2 0x59
#define TEXT_TAN3 0x5A
#define TEXT_TAN4 0x5B
#define TEXT_TAN5 0x5C
#define TEXT_CYAN2 0x67
#define TEXT_CYAN3 0x68
#define TEXT_CYAN4 0x69
#define TEXT_CYAN5 0x6A

#define DLGBOX				((PCHAR)0x66024C)
#define DIBOXBACK			((PCHAR)0x66025C)	// "diboxback.pcx" 256x256
#define ARTIFACT_DEF		((PCHAR)0x660214)	// "artifact.def" 44x44
#define CREATURE_SMALL		((PCHAR)0x660180)	// "CPRSMALL.def" 32x32
#define PSKILL_42			((PCHAR)0x679D9C)	// "PSKIL42.def" 42x42
#define RESOURCE_DEF		((PCHAR)0x660224)	// "resource.def" 32x32
#define RESOURCE_82			((PCHAR)0x660114)	// "resour82.def" 82x93
#define SPELLS_DEF			((PCHAR)0x660208)	// "spells.def"	78x65
#define SSKILL_44			((PCHAR)0x6601D0)	// "Secskill.def" 44x44
#define UN44_DEF			((PCHAR)0x679D90)	// "un44.def"	44x44
#define SPELL_SMALL			((PCHAR)0x6700A4)	// "spellint.def" 48x36
#define SCROLL_SMALL		"def.SpScrArt"		// from HDmod, 44x44
#define OVBUTN3				((PCHAR)0x6817C4)	// "OvButn3.def" 108x16
#define HERO_CADRE			((PCHAR)0x65F3DC)	// hpsyyy.pcx 48x32
#define LARGE_HERO_CADRE	((PCHAR)0x68C45C)	// TPTavSel.pcx 62x68 ~decal by -2
#define CREATURE_LARGE		((PCHAR)0x6700C0)	// TwCrPort.def 58x64
#define HERO_FRAME			"48x32bFr.bmp"		// darken an area for 48x32 def ~ from HDmod
#define BACKPACK_DEF		"bckpck.def"		// from HDmod 52x36
#define BIG_BACKPACK		"BkPack.bmp"		// from HDmod 369x369
#define CANCEL_BUTTON		((PCHAR)0x660B04)	// iCancel.def 64x30
#define CAST_SPELL			((PCHAR)0x66FFD4)	// icm005.def 48x36
#define ARTS_ICON			((PCHAR)0x683178)	// AltArt.def 64x32
#define MORALE_42			((PCHAR)0x68C6DC)	// IMRL42.def 42x38
#define LUCK_42				((PCHAR)0x68C6D0)	// ILCK42.def 42x38
#define CREST58				((PCHAR)0x6601FC)	// CREST58.def 58x64
#define TOWN_SMALL			((PCHAR)0x65F318)	// itpa.def 48x32
#define NO_VISION			((PCHAR)0x6885A0)	// SYSOPB8.def 46x32
#define ADVENTURE_CURSOR	((PCHAR)0x68164C)	// cradvntr.def 40x40
#define ALT_ART				((PCHAR)0x683178)	// AltArt.def 64x32
#define ON_OFF_CHECKBOX		((PCHAR)0x6700F0)	// sysopchk.def 32x24
#define OKAY_DEF			((PCHAR)0x670160)	// iOkay.def 64x30
#define OKAY32_DEF			((PCHAR)0x682374)	// iOkay32.def 66x32
#define OKAY6432_DEF		((PCHAR)0x65F470)	// iOk6432.def 64x32
#define BOX_64_30_PCX		((PCHAR)0x67016C)	// Box64x30.pcx
#define BOX_66_32_PCX		((PCHAR)0x682380)	// Box66x32.pcx
#define CANCEL_DEF			((PCHAR)0x660B04)	// "iCancel.def" 64x30
#define VIEW_CREATURE		((PCHAR)0x660134)	// iViewCr.def
#define VIEW_MAGNIFIER		((PCHAR)0x68C734)	// VWMag1.def 60x32
#define iSAVE_DEF			("ISAVE.DEF")		// iSave.def 64x32
#define BOX_64_32_PCX		((PCHAR)0x68C640)	// Box64x32.pcx
#define LINE_SEPARATOR		"stripe3d.bmp"		// from HDmod 800x2
#define HD_STATUSBAR_PCX	"HD_TStat.pcx"		// from HDmod 800x19
#define GAME_TYPE_DEF		((PCHAR)0x683568)	// 32x24

#pragma pack(push, 1)

struct H3Dlg;
struct H3Msg;
struct H3DlgItem;
struct H3DlgDef;
struct H3DlgDefButton;
struct H3DlgScrollbar;
struct H3DlgCaptionButton;
struct H3DlgPcx;
struct H3DlgPcx16;
struct H3DlgEdit;
struct H3DlgText;
struct H3DlgTextPcx;
struct H3DlgScrollableText;
struct H3DlgCustomButton;
struct H3DlgHintBar;
typedef INT32(__stdcall *H3Dlg_proc)(H3Dlg* dlg, H3Msg* msg);
typedef INT32(__thiscall *H3DlgButton_proc)(struct H3Msg *msg);
typedef void(__fastcall *H3DlgScrollbar_proc)(INT32 click_id, H3Dlg* dlg);

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

	void SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2);
	void SetCommand(INT32 cmd, INT32 param);
	H3DlgItem *ItemAtPosition(H3Dlg *dlg);
	INT32 KeyPressed() { return subtype; }
	BOOL IsMouseOver() { return command == MC_MouseOver; }
	BOOL IsKeyPress() { return command == MC_KeyUp; }
	BOOL IsKeyDown() { return command == MC_KeyDown; }
	BOOL IsLeftClick() { return (command == MC_MouseButton && subtype == MS_LButtonClick); }
	BOOL IsLeftDown() { return (command == MC_MouseButton && subtype == MS_LButtonDown);}
	BOOL IsRightClick() { return (command == MC_MouseButton && subtype == MS_RButtonDown);	}
	INT32 CloseDialog() { return STDCALL_1(INT32, 0x491640, this); }
	BOOL ClickOutside() { return command == MC_RClickOutside || command == MC_LClickOutside; }
};

// * actually __thiscall but declaration is not allowed
// * so dummy int is inserted. Modeled after iFunction2 from WoG source
static INT32 __fastcall H3DlgCustomProc(struct H3Dlg *dlg, int, H3Msg *msg);

struct H3DlgVTable
{
public: // copied from vTable at 0x63A6A8
	h3func destroyDlg;
	h3func showDlg;
	h3func hideDlg;
	h3func callProcessAction;
	h3func _nullsub;
	h3func redrawDlg;
	h3func runDlg;
	h3func initDlgItems;
	h3func activateDlg;
	H3Dlg_proc dlgProc;
	h3func mouseMove;
	h3func rightClick;
	h3func clickRet;
	h3func _nullsub3;
	h3func closeDlg;

	H3DlgVTable()
	{
		destroyDlg = 0x41B040;
		showDlg = 0x5FF0A0;
		hideDlg = 0x5FF220;
		callProcessAction = 0x405610;
		_nullsub = 0x49A230;
		redrawDlg = 0x5FF5E0;
		runDlg = 0x5FFA20;
		initDlgItems = 0x5FFB30;
		activateDlg = 0x5FFBB0;
		dlgProc = (H3Dlg_proc)H3DlgCustomProc; // custom proc to show hint messages and call our own dlg proc, default 0x41B120.
		mouseMove = 0x5FFCA0;
		rightClick = 0x5FFD50;
		clickRet = 0x5FFE90;
		_nullsub3 = 0x4842C0;
		closeDlg = 0x41B0F0;
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
	struct H3LoadedPCX16 *pcx16;
	// * +48
	INT32 deactivatesCount;
	h3unk _f_4C[28]; // normal dialog size is 0x68 total

	////////////////////////////////////////////////////////////////////////
	// Custom Fields - not part of regular dialogs!
	////////////////////////////////////////////////////////////////////////
	H3Dlg_proc customProc;
	H3DlgHintBar *hintBar;
public:
	////////////////////////////////////////////////////////////////////////
	// Constructor and destructor
	////////////////////////////////////////////////////////////////////////
	H3Dlg(int width = 0, int height = 0, int x = -1, int y = -1); // default constructor
	H3Dlg(int width, int heigh, int x = -1, int y = -1, BOOL statusBar = FALSE, H3Dlg_proc dlgProc = NULL, INT32 colorIndex = IntAt(0x69CCF4)); // extended constructor
	~H3Dlg() { THISCALL_2(void, vtable->destroyDlg, this, 0); } // default destructor
	////////////////////////////////////////////////////////////////////////
	// Functions
	////////////////////////////////////////////////////////////////////////
	H3DlgItem* AddItem(H3DlgItem *item);
	// Dlg functions
	void PlaceAtMouse();
	void Start();
	void RMB_Show() { THISCALL_1(void, 0x5F4B90, this); }
	BOOL DlgBackground(BOOL frame, BOOL statusBar, INT32 colorIndex);
	BOOL SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height);
	void Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy); // redraw part of dialog
	void Redraw(); // redraw whole dialog
	INT32 DefaultProc(H3Msg *msg) { return THISCALL_2(INT32, 0x41B120, this, msg); }
	INT32 GetWidth() { return widthDlg; }
	INT32 GetHeight() { return heightDlg; }
	INT32 GetX() { return xDlg; }
	INT32 GetY() { return yDlg; }

	H3Dlg_proc GetProc() { return customProc; }

	// Item functions
	H3DlgItem * ItemAtPosition(H3Msg *msg);
	H3Vector<H3DlgItem*> *GetList() { return &dlgItems; }
	H3DlgHintBar *GetHintBar() { return hintBar; }
	H3DlgItem *GetH3DlgItem(UINT16 id);
	void RedrawItem(UINT16 itemID);
	void EnableItem(UINT16 id, BOOL enable);
	void SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter);
	void SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter);
	void AdjustToPlayerColor(INT8 player, UINT16 itemId);
	H3DlgDef* CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	H3DlgDef* CreateDef(INT32 x, INT32 y, INT32 id, PCHAR defName, INT32 frame, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	H3DlgDefButton* CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
	H3DlgDefButton * CreateOKButton(INT32 x, INT32 y);
	H3DlgDefButton * CreateSaveButton(INT32 x, INT32 y);
	H3DlgDefButton * CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame = 0);
	H3DlgDefButton* CreateOKButton(); // adjust for hintBar
	H3DlgDefButton* CreateOK32Button(INT32 x, INT32 y); // height is 32
	H3DlgDefButton* CreateCancelButton(); // adjust for hintBar
	H3DlgCaptionButton* CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, PCHAR text, PCHAR font, INT32 frame, INT32 group = 0, BOOL closeDialog = FALSE, INT32 hotkey = NULL, INT32 color = 0);
	H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	H3DlgPcx* CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName);
	H3DlgPcx* CreateLineSeparator(INT32 x, INT32 y, INT32 width);
	H3DlgPcx16* CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName);
	H3DlgEdit* CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, PCHAR text, PCHAR fontName = MEDIUM_TEXT, INT32 color = TEXT_REGULAR, INT32 align = TextAlignment::TA_HCenter | TextAlignment::TA_VCenter, PCHAR pcxName = NULL, INT32 id = 0, INT32 hasBorder = FALSE, INT32 borderX = 0, INT32 borderY = 0);
	H3DlgText* CreateText(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, INT32 color, INT32 id, INT32 align = TextAlignment::TA_HCenter | TextAlignment::TA_VCenter, INT32 bkColor = 0);
	H3DlgText* CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height);
	H3DlgHintBar* CreateHint();
	H3DlgTextPcx* CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, PCHAR pcxName, INT32 color, INT32 id, INT32 align = TextAlignment::TA_HCenter | TextAlignment::TA_VCenter);
	H3DlgScrollableText* CreateScrollableText(PCHAR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue = FALSE);
	H3DlgScrollbar* CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc = NULL, BOOL isBlue = FALSE, INT32 stepSize = 0, BOOL arrowsEnabled = TRUE);
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
	h3func isTabEscEnter;
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
	PCHAR hint;
	// * +24
	PCHAR rightClickHint;
	h3unk _f_28[4];
	// * +2C
	INT32 deactivatesCount;
public:
	static H3DlgItem* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags);
	void EnableItem(BOOL enable) { THISCALL_2(void, vTable->setEnabled, this, enable); }
	void Enable() { EnableItem(TRUE); }
	void Disable() { EnableItem(FALSE); }
	void SetX(UINT16 x) { xPos = x; }
	void SetY(UINT16 y) { yPos = y; }
	INT32 GetHeight() { return heightItem; }
	INT32 GetWidth() { return widthItem; }
	void SetWidth(UINT16 w) { widthItem = w; }
	void SetHeight(UINT16 h) { heightItem = h; }
	void Draw(); // draw new contents through vTable
	void Refresh(); // refresh screen through parent dlg
	void Hide() { state &= ~4; }
	void Show() { state |= 4; }
	void Shade() { state |= 8; }
	void UnShade() { state &= ~8; }
	void SetFocus(BOOL8 focus) { THISCALL_2(void, vTable->setFocus, this, focus); }
	BOOL IsVisible() { return state & 4; }
	PCHAR GetHint() { return hint; }
	void SetHint(PCHAR msg) { hint = msg; }
	UINT16 GetID() { return id; }
	void ParentRedraw(); // redraw through parent
	void ColorToPlayer(INT8 player);
	void SendCommand(INT32 command, INT32 parameter);
	void SetText(char *text);

	H3DlgDef *CastDef() { return (H3DlgDef*)this; }
	H3DlgDefButton *CastDefButton() { return (H3DlgDefButton*)this; }
	H3DlgCaptionButton *CastDefButtonCaption() { return (H3DlgCaptionButton*)this; }
	H3DlgCustomButton* CastCustomButton() { return (H3DlgCustomButton*)this; }
	H3DlgPcx* CastPcx() { return (H3DlgPcx*)this; }
	H3DlgPcx16 *CastPcx16() { return (H3DlgPcx16*)this; }
	H3DlgEdit *CastEdit() { return (H3DlgEdit*)this; }
	H3DlgText *CastText() { return (H3DlgText*)this; }
	H3DlgTextPcx *CastTextPcx() { return (H3DlgTextPcx*)this; }
	H3DlgHintBar *CastHintBar() { return (H3DlgHintBar*)this; }
	H3DlgScrollableText *CastScrollText() { return (H3DlgScrollableText*)this; }
	H3DlgScrollbar *CastScrollbar() { return (H3DlgScrollbar*)this; }
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
	static H3DlgDef* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	static H3DlgDef* Create(INT32 x, INT32 y, INT32 id, PCHAR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
	static H3DlgDef* Create(INT32 x, INT32 y, PCHAR defName, INT32 frame = 0, INT32 group = 0);
	void SetFrame(INT32 frame) { defFrame = frame; }
	void ToggleFrame() { defFrame = !defFrame; defFrameOnClick = !defFrameOnClick; }
	void Copy(H3DlgDef* src);
	void ColorDefToPlayer(INT32 id);
	void SetClickFrame(INT32 clickFrame) { defFrameOnClick = clickFrame; }
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
	static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
	static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 id, PCHAR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
	static H3DlgDefButton* Create(INT32 x, INT32 y, PCHAR defName, INT32 frame, INT32 clickFrame);
};

struct H3DlgCaptionButton : public H3DlgDefButton // size 0x70
{
protected:
	// * +68
	INT32 loadedFont;
	// * +6C
	INT32 color;
public:
	static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, PCHAR text, PCHAR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
	static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 id, PCHAR defName, PCHAR text, PCHAR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
};

struct H3DlgCustomButton : public H3DlgDefButton // size 0x6C
{
protected:
	// * +68
	H3DlgButton_proc customButtonProc;
public:
	static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
	static H3DlgCustomButton* Create(INT32 x, INT32 y, PCHAR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
};

struct H3DlgPcx : public H3DlgItem
{
protected:
	// * +30
	struct H3LoadedPCX *loadedPcx;
public:
	static H3DlgPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName);
	static H3DlgPcx* Create(INT32 x, INT32 y, INT32 id, PCHAR pcxName);
	static H3DlgPcx* Create(INT32 x, INT32 y, PCHAR pcxName);
	void Copy(H3DlgPcx* src);

	void AdjustColor(INT player) { THISCALL_2(void, 0x4501D0, this, player); }
};

struct H3DlgPcx16 : public H3DlgItem
{
protected:
	// * +30
	H3LoadedPCX16 *loadedPcx16;
public:
	static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName);
	static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 id, PCHAR pcxName);
	static H3DlgPcx16* Create(INT32 x, INT32 y, PCHAR pcxName);
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
	static H3DlgEdit* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, PCHAR text, PCHAR fontName, INT32 color, INT32 align, PCHAR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY);
	PCHAR GetText() { return text.String(); }
	H3String *GetString() { return &text; }
	void DecreaseCaret() { caretPos--; }
	void SetAutoredraw(BOOL on) { autoRedraw = on; }
	void SetFocus(BOOL on = TRUE) { THISCALL_2(void, vTable->setFocus, this, on); }
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
	static H3DlgText* Create(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName = SMALL_TEXT, INT32 color = TEXT_REGULAR, INT32 id = 0, INT32 align = TA_HCenter | TA_VCenter, INT32 bkColor = 0);
	H3String & GetH3String() { return text; }
};

struct H3DlgTextPcx : public H3DlgText
{
protected:
	// * +44
	struct H3LoadedPCX *loadedPcx;
public:
	static H3DlgTextPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, PCHAR pcxName, INT32 color, INT32 id = 0, INT32 align = TA_HCenter | TA_VCenter);
	static H3DlgTextPcx* Create(INT32 x, INT32 y, PCHAR text, PCHAR fontName, PCHAR pcxName, INT32 color, INT32 align);
};


struct H3DlgHintBar : public H3DlgTextPcx
{
	void ShowHint(H3Msg *msg);
	void ShowMessage(PCHAR msg);
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
	static H3DlgScrollableText* Create(PCHAR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue);
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
	INT32 GetTick() { return tick; }
	void SetTick(INT32 index) { tick = index; }
	void SetBigStep(INT32 step) { bigStepSize = step; } // used for pageup, pagedown
	void SetButtonPosition() { btnPosition = sizeFree * tick / (ticksCount - 1) + btnSize2; }
	BOOL IsHorizontal() { return widthItem > heightItem; }
	INT32 GetRightButtonX() { return parent->GetX() + xPos + sizeMax - btnSize2; } // for horizontal scrollbar only!
	INT32 GetHorizontalY() { return parent->GetY() + yPos; }
	INT32 GetBackgroundWidth() { return sizeMax - 2 * btnSize2; }
	INT32 GetBackgroundX() { return parent->GetX() + xPos + btnSize2; }
	INT32 GetSliderX() { return parent->GetX() + xPos + btnPosition; }
};

#pragma pack(pop)

// * Member functions

inline H3DlgItem * H3Dlg::AddItem(H3DlgItem * item)
{
	//dlgItems.AddSize4(item);
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

inline void H3Dlg::EnableItem(UINT16 id, BOOL enable)
{
	H3DlgItem *it = GetH3DlgItem(id);
	if (it)
		it->EnableItem(enable);
}

inline void H3Dlg::SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter)
{
	THISCALL_5(void, 0x5FF400, this, 0x200, command, itemID, parameter);
}

inline void H3Dlg::SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter)
{
	H3Msg msg;
	msg.SetCommand(0x200, command, itemID, 0, 0, 0, parameter, 0);
	THISCALL_2(void, 0x5FF3A0, this, &msg);
}

inline void H3Dlg::AdjustToPlayerColor(INT8 player, UINT16 itemId)
{
	if (H3DlgItem *it = GetH3DlgItem(itemId))
		it->ColorToPlayer(player);
}

inline H3DlgDef * H3Dlg::CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *def = H3DlgDef::Create(x, y, width, height, id, defName, frame, group, mirror, closeDialog);
	if (def)
		AddItem(def);
	return def;
}

inline H3DlgDef * H3Dlg::CreateDef(INT32 x, INT32 y, INT32 id, PCHAR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *def = H3DlgDef::Create(x, y, id, defName, frame, group, mirror, closeDialog);
	if (def)
		AddItem(def);
	return def;
}

inline H3DlgDefButton * H3Dlg::CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
{
	H3DlgDefButton *but = H3DlgDefButton::Create(x, y, width, height, id, defName, frame, clickFrame, closeDialog, hotkey);
	if (but)
		AddItem(but);
	return but;
}

inline H3DlgDefButton * H3Dlg::CreateOKButton(INT32 x, INT32 y)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, H3Msg::ID_OK, OKAY_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
	if (button)
	{
		this->AddItem(H3DlgPcx::Create(x - 1, y - 1, BOX_64_30_PCX));
		this->AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateSaveButton(INT32 x, INT32 y)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, H3Msg::ID_SAVE, (PCHAR)iSAVE_DEF, 0, 1, FALSE, NH3VKey::H3VK_S);
	if (button)
	{
		AddItem(H3DlgPcx::Create(x - 1, y - 1, BOX_64_32_PCX));
		AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, id, ON_OFF_CHECKBOX, frame, clickFrame, 0, 0);
	if (button)
		AddItem(button);
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateOKButton()
{

	H3DlgDefButton *button = H3DlgDefButton::Create(25, this->heightDlg - 50, H3Msg::ID_OK, OKAY_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
	if (button)
	{
		this->AddItem(H3DlgPcx::Create(25 - 1, this->heightDlg - 50 - 1, BOX_64_30_PCX));
		this->AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateOK32Button(INT32 x, INT32 y)
{
	H3DlgDefButton *button = H3DlgDefButton::Create(x, y, H3Msg::ID_OK, OKAY32_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
	if (button)
	{
		this->AddItem(H3DlgPcx::Create(x - 1, y - 1, BOX_66_32_PCX));
		this->AddItem(button);
	}
	return button;
}

inline H3DlgDefButton * H3Dlg::CreateCancelButton()
{
	H3DlgDefButton *button = H3DlgDefButton::Create(this->widthDlg - 25 - 64, this->heightDlg - 50, H3Msg::ID_CANCEL, CANCEL_DEF, 0, 1, TRUE, NH3VKey::H3VK_ESCAPE);
	if (button)
	{
		this->AddItem(H3DlgPcx::Create(this->widthDlg - 25 - 1 - 64, this->heightDlg - 50 - 1, BOX_64_30_PCX));
		this->AddItem(button);
	}
	return button;
}

inline H3DlgCaptionButton * H3Dlg::CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, PCHAR text, PCHAR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
{
	H3DlgCaptionButton *but = H3DlgCaptionButton::Create(x, y, width, height, id, defName, text, font, frame, group, closeDialog, hotkey, color);
	if (but)
		AddItem(but);
	return but;
}

typedef int(__thiscall *H3DlgButton_proc)(struct H3Msg *msg);
inline H3DlgCustomButton * H3Dlg::CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *but = H3DlgCustomButton::Create(x, y, width, height, id, defName, customProc, frame, clickFrame);
	if (but)
		AddItem(but);
	return but;
}

inline H3DlgPcx * H3Dlg::CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName)
{
	H3DlgPcx *pcx = H3DlgPcx::Create(x, y, width, height, id, pcxName);
	if (pcx)
		AddItem(pcx);
	return pcx;
}

inline H3DlgPcx * H3Dlg::CreateLineSeparator(INT32 x, INT32 y, INT32 width)
{
	return CreatePcx(x, y, width, 2, 0, (PCHAR)LINE_SEPARATOR);
}

inline H3DlgPcx16 * H3Dlg::CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName)
{
	H3DlgPcx16 *pcx = H3DlgPcx16::Create(x, y, width, height, id, pcxName);
	if (pcx)
		AddItem(pcx);
	return pcx;
}

inline H3DlgEdit * H3Dlg::CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, PCHAR text, PCHAR fontName, INT32 color, INT32 align, PCHAR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY)
{
	H3DlgEdit *ed = H3DlgEdit::Create(x, y, width, height, maxLength, text, fontName, color, align, pcxName, id, hasBorder, borderX, borderY);
	if (ed)
		AddItem(ed);
	return ed;
}

inline H3DlgText * H3Dlg::CreateText(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, INT32 color, INT32 id, INT32 align, INT32 bkColor)
{
	H3DlgText *tx = H3DlgText::Create(x, y, width, height, text, fontName, color, id, align, bkColor);
	if (tx)
		AddItem(tx);
	return tx;
}

inline H3DlgText * H3Dlg::CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height)
{
	H3DlgText *t = H3DlgText::Create(x, y, width, height, h3_NullString, MEDIUM_TEXT, 0, 0, 0, 9 + TEXT_BLACK);
	if (t)
		this->AddItem(t);
	return t;
}

inline H3DlgHintBar * H3Dlg::CreateHint()
{
	H3DlgHintBar *h = H3DlgHintBar::Create(this);
	if (h)
		AddItem(h);
	return h;
}

inline H3DlgTextPcx * H3Dlg::CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, PCHAR pcxName, INT32 color, INT32 id, INT32 align)
{
	H3DlgTextPcx *tx = H3DlgTextPcx::Create(x, y, width, height, text, fontName, pcxName, color, id, align);
	if (tx)
		AddItem(tx);
	return tx;
}

inline H3DlgScrollableText * H3Dlg::CreateScrollableText(PCHAR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue)
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

inline void H3Dlg::PlaceAtMouse()
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

inline void H3Dlg::Start()
{
	H3MouseManager *mmgr = P_MouseMgr;
	INT32 mouseType = mmgr->GetType();
	INT32 mouseFrame = mmgr->GetFrame();
	mmgr->DefaultCursor();

	THISCALL_2(void, vtable->runDlg, this, 0); // run H3Dlg

	mmgr->SetCursor(mouseType, mouseFrame); // restore previous cursor
}

inline BOOL H3Dlg::DlgBackground(BOOL frame, BOOL statusBar, INT32 colorIndex)
{
	INT32 w = this->widthDlg;
	INT32 h = this->heightDlg;

	if (frame && (w < 64 || h < 64))
		return FALSE;

	INT32 x, y, _w, _h;
	INT32 dh;
	y = 0;
	H3DlgPcx *bg = H3DlgPcx::Create(0, 0, min(w, 256), min(h, 256), 0, DIBOXBACK); // template background to copy
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
			H3DlgPcx *bg2 = h3_new(H3DlgPcx, 1);
			if (!bg2)
			{
				h3_delete(bg);
				return FALSE;
			}
			bg2->Copy(bg); // copy contents
			bg2->SetX(x); // update position
			bg2->SetY(y);
			bg2->SetWidth(min(_w, 256)); // update dimensions
			bg2->SetHeight(dh);
			this->AddItem(bg2);
			x += 256;
			_w -= 256;
		}
		y += 256; // go to next horizontal pass
		_h -= 256;
	}

	h3_delete(bg); // no longer needed

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
	H3DlgDef *baseDef = H3DlgDef::Create(0, 0, DLGBOX, BF_tl);
	if (!baseDef)
		return FALSE;

	////////////////////
	// do middle sides
	////////////////////
	x = w - 64 - 64; // corners are written after

	while (x > 0)
	{
		def = h3_new(H3DlgDef, 1);
		if (!def)
			return FALSE;
		def->Copy(baseDef);
		def->SetX(x);
		def->SetFrame(BF_tm);
		this->AddItem(def);

		def2 = h3_new(H3DlgDef, 1);
		if (!def2)
			return FALSE;
		def2->Copy(def);
		def2->SetY(h - 64);
		def2->SetFrame(f_bm);
		this->AddItem(def2);

		x -= 64;
	}

	////////////////////
	// do vertical sides ~ defs can only match their whole size
	////////////////////
	// start from bottom and move up
	y = h - 64 - 64;

	while (y >= 0)
	{
		def = h3_new(H3DlgDef, 1);
		if (!def)
			return FALSE;
		def->Copy(baseDef);
		def->SetY(y);
		def->SetFrame(BF_ml);
		this->AddItem(def);

		def2 = h3_new(H3DlgDef, 1);
		if (!def2)
			return FALSE;
		def2->Copy(def);
		def2->SetX(w - 64);
		def2->SetFrame(BF_mr);
		this->AddItem(def2);

		y -= 64;
	}

	////////////////////
	// All corners
	////////////////////
	// top left
	this->AddItem(baseDef);

	////////////////////
	// now top right
	////////////////////
	def = h3_new(H3DlgDef, 1);
	if (!def)
		return FALSE;
	def->Copy(baseDef);
	def->SetX(w - 64);
	def->SetFrame(BF_tr);
	this->AddItem(def);

	////////////////////
	// bottom left
	////////////////////
	def = h3_new(H3DlgDef, 1);
	if (!def)
		return FALSE;
	def->Copy(baseDef);
	def->SetY(h - 64);
	def->SetFrame(f_bl);
	this->AddItem(def);

	////////////////////
	// bottom right
	////////////////////
	def = h3_new(H3DlgDef, 1);
	if (!def)
		return FALSE;
	def->Copy(baseDef);
	def->SetX(w - 64);
	def->SetY(h - 64);
	def->SetFrame(f_br);
	this->AddItem(def);

	def->ColorDefToPlayer(colorIndex);
	return TRUE;
}

inline BOOL H3Dlg::SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height)
{
	INT32 xEnd, yEnd, dX, dY;
	dX = _width;
	dY = _height;
	xEnd = xStart + _width;
	yEnd = yStart + _height;
	if (dX < 4 || dY < 4)
		return FALSE;

	H3DlgPcx *up, *down, *left, *right, *pcx;

	up = H3DlgPcx::Create(xStart, yStart, (PCHAR)"hd_fr_u.bmp");
	down = H3DlgPcx::Create(xStart, yEnd - 4, (PCHAR)"hd_fr_d.bmp");
	left = H3DlgPcx::Create(xStart, yStart, (PCHAR)"hd_fr_l.bmp");
	right = H3DlgPcx::Create(xEnd - 4, yStart, (PCHAR)"hd_fr_r.bmp");

	if (!up || !down || !left || !right)
	{
		h3_delete(up);
		h3_delete(down);
		h3_delete(left);
		h3_delete(right);
		return FALSE;
	}

	////////////////////
	// do horizontal sides
	////////////////////
	while (dX >= 4)
	{
		dX -= 4;
		pcx = h3_new(H3DlgPcx, 1);
		if (pcx)
		{
			pcx->Copy(up);
			pcx->SetX(xStart + dX);
			AddItem(pcx);
		}
		pcx = h3_new(H3DlgPcx, 1);
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
		pcx = h3_new(H3DlgPcx, 1);
		if (pcx)
		{
			pcx->Copy(left);
			pcx->SetY(yStart + dY);
			AddItem(pcx);
		}
		pcx = h3_new(H3DlgPcx, 1);
		if (pcx)
		{
			pcx->Copy(right);
			pcx->SetY(yStart + dY);
			AddItem(pcx);
		}
	}

	h3_delete(up);
	h3_delete(down);
	h3_delete(left);
	h3_delete(right);

	////////////////////
	// Add corners
	////////////////////
	this->AddItem(H3DlgPcx::Create(xStart, yStart, (PCHAR)"hd_fr_lu.bmp"));
	this->AddItem(H3DlgPcx::Create(xStart, yEnd - 4, (PCHAR)"hd_fr_ld.bmp"));
	this->AddItem(H3DlgPcx::Create(xEnd - 4, yStart, (PCHAR)"hd_fr_ru.bmp"));
	this->AddItem(H3DlgPcx::Create(xEnd - 4, yEnd - 4, (PCHAR)"hd_fr_rd.bmp"));

	return TRUE;
}

inline void H3Dlg::Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy)
{
	P_WindowMgr->H3Redraw(xDlg + x, yDlg + y, dx, dy);
}

inline void H3Dlg::Redraw()
{
	THISCALL_4(void, vtable->redrawDlg, this, TRUE, -65535, 65535);
}

inline void H3Dlg::RedrawItem(UINT16 itemID)
{
	if (H3DlgItem *it = GetH3DlgItem(itemID))
		it->Refresh();
}

inline H3DlgItem * H3DlgItem::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags)
{
	H3DlgItem *d = h3_new(H3DlgItem, 1);
	if (d)
		THISCALL_7(H3DlgItem*, 0x5FE900, d, x, y, width, height, id, flags);
	return d;
}

inline void H3DlgItem::ParentRedraw()
{
	parent->Redraw(xPos, yPos, widthItem, heightItem);
}

inline void H3DlgItem::Draw()
{
	THISCALL_1(void, vTable->draw, this);
}

inline void H3DlgItem::Refresh()
{
	parent->Redraw(xPos, yPos, widthItem, heightItem);
}

inline void H3DlgItem::ColorToPlayer(INT8 player) // for PCX
{
	THISCALL_2(void, 0x4501D0, this, player);
}

inline void H3DlgItem::SendCommand(INT32 command, INT32 parameter)
{
	THISCALL_3(void, 0x5FED80, this, command, parameter);
}

inline void H3DlgItem::SetText(char * text)
{
	THISCALL_2(void, vTable->setText, this, text);
}

inline H3DlgDef * H3DlgDef::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *d = h3_new(H3DlgDef, 1);
	if (d)
		THISCALL_12(H3DlgDef*, 0x4EA800, d, x, y, width, height, id, defName, frame, group, mirror, closeDialog, 0x10);
	return d;
}

inline H3DlgDef * H3DlgDef::Create(INT32 x, INT32 y, INT32 id, PCHAR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
{
	H3DlgDef *d = Create(x, y, 0, 0, id, defName, frame, group, mirror, closeDialog);
	if (d && d->loadedDef)
	{
		d->widthItem = d->loadedDef->widthDEF;
		d->heightItem = d->loadedDef->heightDEF;
	}
	return d;
}

inline H3DlgDef * H3DlgDef::Create(INT32 x, INT32 y, PCHAR defName, INT32 frame, INT32 group)
{
	H3DlgDef *d = Create(x, y, 0, 0, 0, defName, frame, group, 0, 0);
	if (d && d->loadedDef)
	{
		d->widthItem = d->loadedDef->widthDEF;
		d->heightItem = d->loadedDef->heightDEF;
	}
	return d;
}

inline void H3DlgDef::Copy(H3DlgDef * src)
{
	h3_memcpy(this, src, sizeof(H3DlgDef));
}

inline void H3DlgDef::ColorDefToPlayer(INT32 id)
{
	loadedDef->ColorToPlayer(id);
}

inline H3DlgPcx * H3DlgPcx::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName)
{
	H3DlgPcx *p = h3_new(H3DlgPcx, 1);
	if (p)
		THISCALL_8(H3DlgPcx*, 0x44FFA0, p, x, y, width, height, id, pcxName, 0x800);
	return p;
}

inline H3DlgPcx * H3DlgPcx::Create(INT32 x, INT32 y, INT32 id, PCHAR pcxName)
{
	H3DlgPcx *p = Create(x, y, 0, 0, id, pcxName);
	if (p && p->loadedPcx)
	{
		p->widthItem = p->loadedPcx->width;
		p->heightItem = p->loadedPcx->height;
	}
	return p;
}

inline H3DlgPcx * H3DlgPcx::Create(INT32 x, INT32 y, PCHAR pcxName)
{
	return Create(x, y, 0, pcxName);
}

inline void H3DlgPcx::Copy(H3DlgPcx * src)
{
	h3_memcpy(this, src, sizeof(H3DlgPcx));
}

inline H3DlgDefButton * H3DlgDefButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
{
	H3DlgDefButton *b = h3_new(H3DlgDefButton, 1);
	if (b)
		THISCALL_12(H3DlgDefButton*, 0x455BD0, b, x, y, width, height, id, defName, frame, clickFrame, closeDialog, hotkey, 2);
	return b;
}

inline H3DlgDefButton * H3DlgDefButton::Create(INT32 x, INT32 y, INT32 id, PCHAR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
{
	H3DlgDefButton *b = Create(x, y, 0, 0, id, defName, frame, clickFrame, closeDialog, hotkey);
	if (b && b->loadedDef)
	{
		b->widthItem = b->loadedDef->widthDEF;
		b->heightItem = b->loadedDef->heightDEF;
	}
	return b;
}

inline H3DlgDefButton * H3DlgDefButton::Create(INT32 x, INT32 y, PCHAR defName, INT32 frame, INT32 clickFrame)
{
	return Create(x, y, 0, defName, frame, clickFrame, 0, 0);
}

inline H3DlgCaptionButton * H3DlgCaptionButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, PCHAR text, PCHAR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
{
	H3DlgCaptionButton *b = h3_new(H3DlgCaptionButton, 1);
	if (b)
		THISCALL_15(H3DlgCaptionButton*, 0x456730, b, x, y, width, height, id, defName, text, font, frame, group, closeDialog, hotkey, 2, color);
	return b;
}

inline H3DlgCaptionButton * H3DlgCaptionButton::Create(INT32 x, INT32 y, INT32 id, PCHAR defName, PCHAR text, PCHAR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
{
	H3DlgCaptionButton *b = Create(x, y, 0, 0, id, defName, text, font, frame, group, closeDialog, hotkey, color);
	if (b && b->loadedDef)
	{
		b->widthItem = b->loadedDef->widthDEF;
		b->heightItem = b->loadedDef->heightDEF;
	}
	return b;
}

inline H3DlgPcx16 * H3DlgPcx16::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR pcxName)
{
	H3DlgPcx16 *p = h3_new(H3DlgPcx16, 1);
	if (p)
		THISCALL_8(H3DlgPcx16*, 0x450340, p, x, y, width, height, id, pcxName, 0x800);
	return p;
}

inline H3DlgPcx16 * H3DlgPcx16::Create(INT32 x, INT32 y, INT32 id, PCHAR pcxName)
{
	H3DlgPcx16 *p = Create(x, y, 0, 0, id, pcxName);
	if (p && p->loadedPcx16)
	{
		p->widthItem = p->loadedPcx16->width;
		p->heightItem = p->loadedPcx16->height;
	}
	return p;
}

inline H3DlgPcx16 * H3DlgPcx16::Create(INT32 x, INT32 y, PCHAR pcxName)
{
	return Create(x, y, 0, 0, 0, pcxName);
}

inline H3DlgText * H3DlgText::Create(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, INT32 color, INT32 id, INT32 align, INT32 bkColor)
{
	H3DlgText *t = h3_new(H3DlgText, 1);
	if (t)
		THISCALL_12(H3DlgText*, 0x5BC6A0, t, x, y, width, height, text, fontName, color, id, align, bkColor, 8);
	return t;
}

inline H3DlgTextPcx * H3DlgTextPcx::Create(INT32 x, INT32 y, INT32 width, INT32 height, PCHAR text, PCHAR fontName, PCHAR pcxName, INT32 color, INT32 id, INT32 align)
{
	H3DlgTextPcx *t = h3_new(H3DlgTextPcx, 1);
	if (t)
		THISCALL_12(H3DlgTextPcx*, 0x5BCB70, t, x, y, width, height, text, fontName, pcxName, color, id, align, 8);
	return t;
}

inline H3DlgTextPcx * H3DlgTextPcx::Create(INT32 x, INT32 y, PCHAR text, PCHAR fontName, PCHAR pcxName, INT32 color, INT32 align)
{
	H3DlgTextPcx *t = Create(x, y, 0, 0, text, fontName, pcxName, color, 0, align);
	if (t && t->loadedPcx)
	{
		t->widthItem = t->loadedPcx->width;
		t->heightItem = t->loadedPcx->height;
	}
	return t;
}

inline H3DlgScrollableText * H3DlgScrollableText::Create(PCHAR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue)
{
	H3DlgScrollableText *s = h3_new(H3DlgScrollableText, 1);
	if (s)
		THISCALL_9(H3DlgScrollableText*, 0x5BA360, s, text, x, y, width, height, font, color, isBlue);
	return s;
}

inline H3DlgScrollbar * H3DlgScrollbar::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled)
{
	H3DlgScrollbar *s = h3_new(H3DlgScrollbar, 1);
	if (s)
		THISCALL_11(H3DlgScrollbar*, 0x5963C0, s, x, y, width, height, id, ticksCount, scrollbarProc, isBlue, stepSize, arrowsEnabled);
	return s;
}

inline H3DlgCustomButton * H3DlgCustomButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, PCHAR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *b = h3_new(H3DlgCustomButton, 1);
	if (b)
		THISCALL_10(H3DlgCustomButton*, 0x456A10, b, x, y, width, height, id, defName, customProc, frame, clickFrame);
	return b;
}

inline H3DlgCustomButton * H3DlgCustomButton::Create(INT32 x, INT32 y, PCHAR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
{
	H3DlgCustomButton *b = Create(x, y, 0, 0, 0, defName, customProc, frame, clickFrame);
	if (b && b->loadedDef)
	{
		b->widthItem = b->loadedDef->widthDEF;
		b->heightItem = b->loadedDef->heightDEF;
	}
	return b;
}

inline H3DlgEdit * H3DlgEdit::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, PCHAR text, PCHAR fontName, INT32 color, INT32 align, PCHAR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY)
{
	H3DlgEdit *e = h3_new(H3DlgEdit, 1);
	if (e)
		THISCALL_17(H3DlgEdit*, 0x5BACD0, e, x, y, width, height, maxLength, text, fontName, color, align, pcxName, 0, id, 0, hasBorder, borderX, borderY);
	return e;
}

inline void H3Msg::SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2)
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

inline void H3Msg::SetCommand(INT32 cmd, INT32 param)
{
	SetCommand(0x200, cmd, 0, 0, 0, 0, param, 0);
}

inline H3DlgItem * H3Msg::ItemAtPosition(H3Dlg * dlg)
{
	return THISCALL_3(H3DlgItem*, 0x5FF9A0, dlg, x_abs, y_abs);
}

inline void H3DlgHintBar::ShowHint(H3Msg *msg)
{
	H3DlgItem *di;
	if (msg->command == H3Msg::MC_MouseOver)
	{
		di = msg->ItemAtPosition(parent);
		if (di)
		{
			if (di->GetHint())
				this->SetText(di->GetHint());
			else
				this->SetText(h3_NullString);
			this->Draw();
			this->Refresh();
		}
	}
}

inline void H3DlgHintBar::ShowMessage(PCHAR msg)
{
	this->SetText(msg);
	this->Draw();
	this->Refresh();
}

inline H3DlgHintBar * H3DlgHintBar::Create(H3Dlg * dlg)
{
	return (H3DlgHintBar*)H3DlgTextPcx::Create(8, dlg->GetHeight() - 26, dlg->GetWidth() - 16, 19, h3_NullString, SMALL_TEXT, (PCHAR)HD_STATUSBAR_PCX, TEXT_REGULAR);
}

inline H3Dlg::H3Dlg(int width, int height, int x, int y)
{
	THISCALL_6(H3Dlg*, 0x41AFA0, this, x == -1 ? (gameWidth - width) / 2 : x, y == -1 ? (gameHeight - height) / 2 : y, width, height, 0x12);
	vtable = &CustomDlgVTable;
	customProc = NULL;
	hintBar = 0;
}

inline H3Dlg::H3Dlg(int width, int height, int x, int y, BOOL statusBar, H3Dlg_proc dlgProc, INT32 colorIndex)
{
	THISCALL_6(H3Dlg*, 0x41AFA0, this, x == -1 ? (gameWidth - width) / 2 : x, y == -1 ? (gameHeight - height) / 2 : y, width, height, 0x12);
	vtable = &CustomDlgVTable;
	this->DlgBackground(TRUE, statusBar, colorIndex);
	customProc = dlgProc;
	H3DlgHintBar *hint = NULL;
	if (statusBar)
		hint = this->CreateHint();
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