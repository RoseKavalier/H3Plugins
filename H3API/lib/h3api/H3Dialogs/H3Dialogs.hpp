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

#ifndef _H3DIALOGS_HPP_
#define _H3DIALOGS_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_String.hpp"
#include "../H3_BinaryItems.hpp"

namespace h3
{
	// * forward declarations

	struct  H3Msg;
	struct  H3MsgCustom;
	struct  H3BaseDlg;
	struct  H3Dlg;
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
	typedef INT32(__stdcall* H3Dlg_proc)(H3Dlg* dlg, H3Msg* msg);
	typedef INT32(__fastcall* H3DlgButton_proc)(H3MsgCustom* msg);
	typedef VOID(__fastcall* H3DlgScrollbar_proc)(INT32 click_id, H3Dlg* dlg);

#pragma pack(push, 1)
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
			ID_SAVE   = 30000,
			ID_OK     = 30725,
			ID_CANCEL = 30726,
		};

		enum MessageCommand
		{
			MC_MouseButton   = 0x200,
			MC_RClickOutside = 0x20,
			MC_LClickOutside = 8,
			MC_MouseOver     = 4,
			MC_KeyDown       = 1,
			MC_KeyUp         = 2,
			MC_WheelButton   = 0x309,
			MC_MouseWheel    = 0x20A,
		};
		enum MessageSubtype
		{
			MS_LButtonDown          = 0xC,
			MS_LButtonClick         = 0xD,
			MS_RButtonDown          = 0xE,
			MS_MouseWheelButtonDown = 0x207,
			MS_MouseWheelButtonUp   = 0x208,
		};
		enum MessageFlag
		{
			MF_Shift = 1,
			MF_Ctrl  = 4,
			MF_Alt   = 32,
		};

		VOID       SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2);
		VOID       SetCommand(INT32 cmd, INT32 param);
		H3DlgItem* ItemAtPosition(H3BaseDlg* dlg);
		INT32      KeyPressed()   const;
		BOOL       IsKeyPress()   const;
		BOOL       IsKeyDown()    const;
		BOOL       IsMouseOver()  const;
		BOOL       IsLeftClick()  const;
		BOOL       IsLeftDown()   const;
		BOOL       IsRightClick() const;
		BOOL       ClickOutside() const;
		INT32      CloseDialog();
	};
	
	struct H3MsgCustom : public H3Msg
	{
		H3Dlg* GetDlg() const;
	};

	// * actually __thiscall but declaration is not allowed
	// * so dummy int is inserted. Modeled after iFunction2 from WoG source
	static INT32 __fastcall H3DlgCustomProc(struct H3Dlg* dlg, int, H3Msg* msg);

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

		_H3API_ H3DlgVTable();
	};

	static H3DlgVTable CustomDlgVTable;

	struct H3BaseDlg
	{
	protected:
		// * +0
		H3DlgVTable* vtable;
		// * +4
		INT32 zOrder;
		// * +8
		H3Dlg* nextDialog;
		// * +C
		H3Dlg* lastDialog;
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
		H3DlgItem* lastItem;
		// * +2C
		H3DlgItem* firstItem;
		// * +30
		H3Vector<H3DlgItem*> dlgItems;
		// * +40
		INT32 focusedItemId;
		// * +44
		H3LoadedPCX16* pcx16;
		// * +48
		INT32 deactivatesCount;
		h3unk _f_4C[28]; // normal dialog size is 0x68 total	
	public:

		INT32 GetWidth() const;
		INT32 GetHeight() const;
		INT32 GetX() const;
		INT32 GetY() const;
		BOOL  IsTopDialog() const;

		VOID  Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy); // redraw part of dialog
		VOID  Redraw(); // redraw whole dialog
		INT32 DefaultProc(H3Msg* msg);

		// * this is what gets shown on the screen
		// * it gets drawn over every time you refresh an item
		// * or draw a new item... good for temporary things
		H3LoadedPCX16* GetCurrentPcx();

		H3DlgItem* ItemAtPosition(H3Msg* msg);
		H3Vector<H3DlgItem*>& GetList();
		H3DlgItem* GetH3DlgItem(UINT16 id);
		VOID RedrawItem(UINT16 itemID);
		VOID EnableItem(UINT16 id, BOOL enable);
		VOID SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter);
		VOID SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter);
		VOID AdjustToPlayerColor(INT8 player, UINT16 itemId);
		H3DlgItem* AddItem(H3DlgItem* item);

		H3DlgFrame* CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color);
		H3DlgFrame* CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color);
		H3DlgFrame* CreateFrame(H3DlgItem* target, RGB565 color, INT id = 0, BOOL around_edge = false);
		H3DlgDef* CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame,
			INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		H3DlgDef* CreateDef(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group = 0,
			INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		H3DlgDefButton* CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			INT32 frame, INT32 clickFrame, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
		H3DlgDefButton* CreateOKButton(INT32 x, INT32 y);
		H3DlgDefButton* CreateSaveButton(INT32 x, INT32 y);
		H3DlgDefButton* CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame = 0);
		H3DlgDefButton* CreateOKButton(); // adjust for hintBar
		H3DlgDefButton* CreateOK32Button(INT32 x, INT32 y); // height is 32
		H3DlgDefButton* CreateCancelButton(); // adjust for hintBar
		H3DlgCaptionButton* CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			LPCSTR text, LPCSTR font, INT32 frame, INT32 group = 0, BOOL closeDialog = FALSE, INT32 hotkey = NULL, INT32 color = 0);
		H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc,
			INT32 frame, INT32 clickFrame);
		H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc,
			INT32 frame, INT32 clickFrame);
		H3DlgPcx* CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		H3DlgPcx* CreateLineSeparator(INT32 x, INT32 y, INT32 width);
		H3DlgPcx16* CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		H3DlgEdit* CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text,
			LPCSTR fontName = NH3Dlg::Text::MEDIUM, INT32 color = NH3Dlg::TextColor::REGULAR,
			INT32 align = NH3Dlg::TextAlignment::MiddleCenter, LPCSTR pcxName = nullptr,
			INT32 id = 0, INT32 hasBorder = FALSE, INT32 borderX = 0, INT32 borderY = 0);
		H3DlgText* CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
		H3DlgTextPcx* CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			LPCSTR pcxName, INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
		H3DlgScrollableText* CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height,
			INT32 font, INT32 color, INT32 isBlue = FALSE);
		H3DlgScrollbar* CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount,
			H3DlgScrollbar_proc scrollbarProc = nullptr, BOOL isBlue = FALSE, INT32 stepSize = 0, BOOL arrowsEnabled = TRUE);
	};

	// * This removes the following warning when using enum
	// * warning C4482: nonstandard extension used: enum '...' used in qualified name
#pragma warning(push)
#pragma warning(disable : 4482)
	struct H3Dlg : H3BaseDlg
	{
	protected:
	////////////////////////////////////////////////////////////////////////
	// Custom Fields - not part of regular dialogs!
	////////////////////////////////////////////////////////////////////////
		H3Dlg_proc customProc;
		H3DlgHintBar* hintBar;
		H3LoadedPCX16* background;

	public:
		////////////////////////////////////////////////////////////////////////
		// Constructor and destructor
		////////////////////////////////////////////////////////////////////////
		// * default constructor
		_H3API_ H3Dlg(int width, int height, int x = -1, int y = -1, BOOL statusBar = FALSE, H3Dlg_proc dlgProc = nullptr, 
			BOOL makeBackground = TRUE, INT32 colorIndex = IntAt(0x69CCF4));
		// * default destructor
		// * if you prefer to allocate your own dialogs, use this style:
		// * H3Dlg* MyDlg = new H3Dlg(.......);
		// * ...
		// * delete MyDlg;
		// * this will automatically call the destructor before deallocating memory
		_H3API_ ~H3Dlg();
		////////////////////////////////////////////////////////////////////////
		// Functions
		////////////////////////////////////////////////////////////////////////		
		VOID  PlaceAtMouse();
		VOID  Start();
		VOID  RMB_Show();
		BOOL  AddBackground(INT32 x, INT32 y, INT32 w, INT32 h, BOOL frame, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);
		BOOL  AddBackground(BOOL frame, BOOL statusBar, INT32 colorIndex);
		BOOL  AddBackground(H3LoadedPCX* pcx);
		BOOL  AddBackground(H3LoadedPCX16* pcx);
		BOOL  AddBackground(H3LoadedPCX24* pcx);
		BOOL  AddBackground(H3LoadedDEF* def, INT group = 0, INT frame = 0);		
				
		H3LoadedPCX16* GetBackgroundPcx() const;		
		// * draws the background pcx only
		BOOL BackgroundRegion(INT32 xStart, INT32 yStart, INT32 w, INT32 h, BOOL is_blue = FALSE);
		// * draws the HDmod simple frames only
		BOOL SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPCX16* destination = nullptr);
		// * draws the outside frames only
		BOOL FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);		
		H3Dlg_proc     GetProc();

		// Item functions		
		H3DlgHintBar* GetHintBar();	
		BOOL CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height);
		H3DlgHintBar* CreateHint();
	};
#pragma warning(pop)

	// * follows HDmod's dlg format
	// * some member functions are made private to disallow their use
	// * WARNING! this structure should only be used to hook existing dialogs
	struct HDDlg : H3BaseDlg
	{
		typedef INT32(__stdcall* HDDlg_proc)(HDDlg*, H3Msg*);
	protected:
		h3unk _f_6C;
		// * +70
		HDDlg_proc hdProc;	
	public:
		INT CallHDProc(H3Msg& msg) { return hdProc(this, &msg); }
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
		H3BaseDlg *parent;
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
		// * +28
		BOOL8 hintsAreAllocated;
		h3unk _f_29[3];
		// * +2C
		INT32 deactivatesCount;

		// * private function, use SetText() of respective items
		// * if it's not there, it's not available!
		VOID _SetText(LPCSTR text);

	public:
		static H3DlgItem* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags);

		VOID   EnableItem(BOOL enable);
		VOID   Enable();
		VOID   Disable();
		INT16  GetX() const;
		INT16  GetY() const;
		BOOL   IsEnabled() const;
		VOID   SetX(UINT16 x);
		VOID   SetY(UINT16 y);
		INT32  GetHeight() const;
		INT32  GetWidth() const;
		VOID   SetWidth(UINT16 w);
		VOID   SetHeight(UINT16 h);
		VOID   Draw(); // draw new contents through vTable
		VOID   Refresh(); // refresh screen through parent dlg
		VOID   Hide();
		VOID   Show();
		VOID   Shade();
		VOID   UnShade();
		VOID   SetFocus(BOOL8 focus);
		BOOL   IsVisible() const;
		LPCSTR GetHint() const;
		VOID   SetHint(LPCSTR msg);
		UINT16 GetID() const;
		VOID   ParentRedraw(); // redraw through parent
		VOID   ColorToPlayer(INT8 player);
		VOID   SendCommand(INT32 command, INT32 parameter);
		VOID   SetHints(LPCSTR shortTipText, LPCSTR rightClickHint, BOOL allocateMemory);

		H3DlgFrame*          CastFrame();
		H3DlgDef *           CastDef();
		H3DlgDefButton*      CastDefButton();
		H3DlgCaptionButton*  CastDefButtonCaption();
		H3DlgCustomButton*   CastCustomButton();
		H3DlgPcx*            CastPcx();
		H3DlgPcx16*          CastPcx16();
		H3DlgEdit*           CastEdit();
		H3DlgText*           CastText();
		H3DlgTextPcx*        CastTextPcx();
		H3DlgHintBar*        CastHintBar();
		H3DlgScrollableText* CastScrollText();
		H3DlgScrollbar*      CastScrollbar();
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
		static H3DlgFrame* Create(H3DlgItem* target, RGB565 color, INT id = 0, BOOL around_edge = false);

		VOID     ChangeColor(RGB565 color);
		VOID     HideHue();
		VOID     ShowHue();
		VOID     ToggleHue();
		H3RGB565* GetColor();
	};

	struct H3DlgDef : public H3DlgItem // size 0x48
	{
	protected:
		// * +30
		struct H3LoadedDEF* loadedDef;
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
		VOID  SetFrame(INT32 frame);
		INT   ToggleFrame();
		INT32 GetFrame() const;
		VOID  ColorDefToPlayer(INT32 id);
		VOID  SetClickFrame(INT32 clickFrame);
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
		H3Font* loadedFont;
		// * +6C
		INT32 color;
	public:
		VOID SetText(LPCSTR text);
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
		VOID ToggleFlag(BOOL& flag);
	};

	struct H3DlgPcx : public H3DlgItem
	{
	protected:
		// * +30
		H3LoadedPCX* loadedPcx;
	public:
		static H3DlgPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		static H3DlgPcx* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		static H3DlgPcx* Create(INT32 x, INT32 y, LPCSTR pcxName);		
		VOID SetPcx(H3LoadedPCX* pcx);
		VOID AdjustColor(INT player);
		H3LoadedPCX* GetPcx();
		H3LoadedPCX* GetPcx() const;
	};

	struct H3DlgPcx16 : public H3DlgItem
	{
	protected:
		// * +30
		H3LoadedPCX16* loadedPcx16;
	public:
		static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		static H3DlgPcx16* Create(INT32 x, INT32 y, LPCSTR pcxName);
		VOID SetPcx(H3LoadedPCX16* pcx16);
		H3LoadedPCX16* GetPcx();
		VOID SinkArea(INT32 x, INT32 y, INT32 w, INT32 h);
		VOID BevelArea(INT32 x, INT32 y, INT32 w, INT32 h);
		VOID SinkArea(H3DlgItem* it);
		VOID BevelArea(H3DlgItem* it);
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
		struct H3LoadedPCX* loadedPcx;
		// * +54
		struct H3LoadedPCX16* loadedPcx16;
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
		LPCSTR   GetText() const;
		H3String* GetString();
		VOID     SetText(LPCSTR text);
		VOID     DecreaseCaret();
		VOID     SetAutoredraw(BOOL on);
		VOID     SetFocus(BOOL on = TRUE);
	};

	struct H3DlgText : public H3DlgItem
	{
	protected:
		// * +30
		H3String text;
		// * +34
		H3Font* font;
		// * +38
		INT32 color;
		// * +3C
		INT32 bkColor;
		// * +40
		INT32 align;
	public:
		static H3DlgText* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName = NH3Dlg::Text::SMALL, INT32 color = NH3Dlg::TextColor::REGULAR, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
		H3String& GetH3String();
		VOID SetText(LPCSTR text);
	};

	struct H3DlgTextPcx : public H3DlgText
	{
	protected:
		// * +44
		struct H3LoadedPCX* loadedPcx;
	public:
		static H3DlgTextPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
		static H3DlgTextPcx* Create(INT32 x, INT32 y, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 align);
	};

	struct H3DlgHintBar : public H3DlgTextPcx
	{
		VOID   ShowHint(H3Msg* msg);
		VOID   ShowMessage(LPCSTR msg);
		static H3DlgHintBar* Create(H3Dlg* dlg);
	};

	struct H3DlgScrollableText : public H3DlgItem
	{
	protected:
		// * +30
		H3Font* font;
		// * +34
		INT32 linesCount;
		h3unk _f_38[12];
		// * +44
		H3Vector<UINT32> items; // never bothered to figure out the type
		// * +54
		H3DlgScrollbar* scrollBar;
		h3unk _f_58[4];
	public:
		static H3DlgScrollableText* Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue);
	};

	struct H3DlgScrollbar : public H3DlgItem
	{
	protected:
		// * +30
		H3LoadedDEF* loadedBtnDef;
		// * +34
		H3LoadedPCX* loadedPcx;
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
		INT32 GetTick() const;
		VOID  SetTick(INT32 index);
		VOID  SetBigStep(INT32 step);
		VOID  SetButtonPosition();
		BOOL  IsHorizontal() const;
		INT32 GetRightButtonX() const; // for horizontal scrollbar only!
		INT32 GetHorizontalY() const;
		INT32 GetBackgroundWidth() const;
		INT32 GetBackgroundX() const;
		INT32 GetSliderX() const;
	};

	struct H3DlgPanel
	{
	protected:
		h3func*              vTable;
		// * +4
		INT                  x;
		// * +8
		INT                  y;
		// * +C
		INT                  width;
		// * +10
		INT                  height;
		// * +14
		H3Vector<H3DlgItem*> items;
		// * +24
		H3BaseDlg*           parent;
		// * +28
		INT                  smallestId;
		// * +2C
		INT                  largestId;
		h3unk                _f_30[4];
	public:
		H3Vector<H3DlgItem*>& GetItems();
	};

	struct H3CombatBottomPanel : H3DlgPanel
	{
	protected:
		// * +34
		H3DlgTextPcx*      commentBar;
		// * +38
		H3DlgCustomButton* commentUp;
		// * +3C
		H3DlgCustomButton* commentDown;
	public:
		void AddComment(LPCSTR text);
	};

	struct H3CombatHeroPanel : H3DlgPanel
	{
	protected:
		// * +34
		H3DlgPcx*  background;
		// * +38
		H3DlgPcx*  hero;
		// * +3C
		H3DlgText* attack;
		// * +40
		H3DlgText* defense;
		// * +44
		H3DlgText* power;
		// * +48
		H3DlgText* knowledge;
		// * +4C
		H3DlgDef*  morale;
		// * +50
		H3DlgDef*  luck;
		// * +54
		H3DlgText* spellPoints;
		// * +58
		BOOL8      needsRedraw;
		h3align    _f_59[3];
	public:
	};

	struct H3CombatMonsterPanel : H3DlgPanel
	{
	protected:
		// * +34
		H3DlgPcx*  background;
		// * +38
		H3DlgDef*  creature;
		// * +3C
		H3DlgText* attack;		
		// * +40
		H3DlgText* defense;
		// * +44
		H3DlgText* damage;		
		// * +48
		H3DlgText* health;
		// * +4C
		H3DlgDef*  morale;		
		// * +50
		H3DlgDef*  luck;
		// * +54
		H3DlgText* numberAlive;
		// * +58
		H3DlgDef*  spells[3];
		// * +64
		H3DlgText* noActiveSpell;
		// * +68
		BOOL8      needsRedraw;
		h3align    _f_69[3];
		// * +6C
		// 1 or 2 ?
		INT        type;
	public:

	};
	
	/////////////////////////////////////////////
	// Specific dialogs from the game
	/////////////////////////////////////////////

	struct H3CombatDlg : H3BaseDlg
	{
	protected:
		h3unk _f_68[4];
		// * +6C
		UINT lastAnimTime;
	public:
		// * +70
		H3CombatBottomPanel*  bottomPanel;
		// * +74
		H3CombatHeroPanel*    leftHeroPopup;
		// * +78
		H3CombatHeroPanel*    rightHeroPopup;
		// * +7C
		H3CombatMonsterPanel* leftMonsterPopup;
		// * +80
		H3CombatMonsterPanel* rightMonsterPopup;
		// * +84
		H3CombatMonsterPanel* bottomleftMonsterPopup;
		// * +88
		H3CombatMonsterPanel* bottomRightMonsterPopup;
	};
#pragma pack(pop)
}

#endif /* #define _H3DIALOGS_HPP_ */