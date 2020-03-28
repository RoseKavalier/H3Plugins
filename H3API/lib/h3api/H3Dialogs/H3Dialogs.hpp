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
	_H3_DECLARE_(H3Msg);
	_H3_DECLARE_(H3Msg);
	_H3_DECLARE_(H3MsgCustom);
	_H3_DECLARE_(H3BaseDlg);
	_H3_DECLARE_(H3TownAlignmentDlg);
	_H3_DECLARE_(H3Dlg);
	_H3_DECLARE_(H3DlgItem);
	_H3_DECLARE_(H3DlgFrame);
	_H3_DECLARE_(H3DlgDef);
	_H3_DECLARE_(H3DlgDefButton);
	_H3_DECLARE_(H3DlgScrollbar);
	_H3_DECLARE_(H3DlgCaptionButton);
	_H3_DECLARE_(H3DlgPcx);
	_H3_DECLARE_(H3DlgPcx16);
	_H3_DECLARE_(H3DlgEdit);
	_H3_DECLARE_(H3DlgText);
	_H3_DECLARE_(H3DlgTextPcx);
	_H3_DECLARE_(H3DlgScrollableText);
	_H3_DECLARE_(H3DlgCustomButton);
	_H3_DECLARE_(H3DlgHintBar);
	typedef INT32(__stdcall*  H3Dlg_proc)(H3Dlg*, H3Msg*);
	typedef INT32(__fastcall* H3DlgButton_proc)(H3MsgCustom*);
	typedef VOID (__fastcall* H3DlgScrollbar_proc)(INT32, H3Dlg*);

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
			MC_KeyHeld       = 0x100,
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

		_H3API_ VOID       SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2);
		_H3API_ VOID       SetCommand(INT32 cmd, INT32 param);
		_H3API_ H3DlgItem* ItemAtPosition(H3BaseDlg* dlg);
		_H3API_ INT32      KeyPressed()   const;
		_H3API_ BOOL       IsKeyPress()   const;
		_H3API_ BOOL       IsKeyDown()    const;
		_H3API_ BOOL       IsKeyHeld()    const;
		_H3API_ BOOL       IsMouseOver()  const;
		_H3API_ BOOL       IsWheelButton()  const;		
		_H3API_ BOOL       IsLeftClick()  const;
		_H3API_ BOOL       IsLeftDown()   const;
		_H3API_ BOOL       IsRightClick() const;
		_H3API_ BOOL       ClickOutside() const;
		_H3API_ INT32      CloseDialog();
	};
	
	struct H3MsgCustom : public H3Msg
	{
		_H3API_ H3Dlg* GetDlg() const;
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

		_H3API_ INT32 GetWidth() const;
		_H3API_ INT32 GetHeight() const;
		_H3API_ INT32 GetX() const;
		_H3API_ INT32 GetY() const;
		_H3API_ BOOL  IsTopDialog() const;

		_H3API_ VOID  Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy); // redraw part of dialog
		_H3API_ VOID  Redraw(); // redraw whole dialog
		_H3API_ INT32 DefaultProc(H3Msg* msg);

		// * this is what gets shown on the screen
		// * it gets drawn over every time you refresh an item
		// * or draw a new item... good for temporary things
		_H3API_ H3LoadedPCX16* GetCurrentPcx();

		_H3API_ H3DlgItem* ItemAtPosition(H3Msg* msg);
		_H3API_ H3Vector<H3DlgItem*>& GetList();
		_H3API_ H3DlgItem* GetH3DlgItem(UINT16 id);
		_H3API_ VOID RedrawItem(UINT16 itemID);
		_H3API_ VOID EnableItem(UINT16 id, BOOL enable);
		_H3API_ VOID SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter);
		_H3API_ VOID SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter);
		_H3API_ VOID AdjustToPlayerColor(INT8 player, UINT16 itemId);
		_H3API_ H3DlgItem* AddItem(H3DlgItem* item);

		// * dlgitem that is not visible but responds to commands
		_H3API_ H3DlgItem* CreateHidden(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id);

		_H3API_ H3DlgFrame* CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color);		
		_H3API_ H3DlgFrame* CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color);		
		_H3API_ H3DlgFrame* CreateFrame(H3DlgItem* target, RGB565 color, INT id = 0, BOOL around_edge = false);
		_H3API_ H3DlgDef* CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame,
			INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ H3DlgDef* CreateDef(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group = 0,
			INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ H3DlgDefButton* CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			INT32 frame, INT32 clickFrame, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
		_H3API_ H3DlgDefButton* CreateButton(INT32 x, INT32 y, INT32 id, LPCSTR defName,
			INT32 frame = 0, INT32 clickFrame = 1, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
		_H3API_ H3DlgDefButton* CreateOKButton(INT32 x, INT32 y);
		_H3API_ H3DlgDefButton* CreateSaveButton(INT32 x, INT32 y);
		_H3API_ H3DlgDefButton* CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame = 0);
		_H3API_ H3DlgDefButton* CreateOKButton(); // adjust for hintBar
		_H3API_ H3DlgDefButton* CreateOK32Button(INT32 x, INT32 y); // height is 32
		_H3API_ H3DlgDefButton* CreateCancelButton(); // adjust for hintBar
		_H3API_ H3DlgCaptionButton* CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			LPCSTR text, LPCSTR font, INT32 frame, INT32 group = 0, BOOL closeDialog = FALSE, INT32 hotkey = NULL, INT32 color = 0);
		_H3API_ H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc,
			INT32 frame, INT32 clickFrame);
		_H3API_ H3DlgCustomButton* CreateCustomButton(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc,
			INT32 frame, INT32 clickFrame);
		_H3API_ H3DlgPcx* CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ H3DlgPcx* CreatePcx(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		_H3API_ H3DlgPcx* CreateLineSeparator(INT32 x, INT32 y, INT32 width);
		_H3API_ H3DlgPcx16* CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ H3DlgEdit* CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text,
			LPCSTR fontName = NH3Dlg::Text::MEDIUM, INT32 color = NH3Dlg::TextColor::REGULAR,
			INT32 align = NH3Dlg::TextAlignment::MiddleCenter, LPCSTR pcxName = nullptr,
			INT32 id = 0, INT32 hasBorder = FALSE, INT32 borderX = 0, INT32 borderY = 0);
		_H3API_ H3DlgText* CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
		_H3API_ H3DlgTextPcx* CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			LPCSTR pcxName, INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
		_H3API_ H3DlgScrollableText* CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height,
			INT32 font, INT32 color, INT32 isBlue = FALSE);
		_H3API_ H3DlgScrollbar* CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount,
			H3DlgScrollbar_proc scrollbarProc = nullptr, BOOL isBlue = FALSE, INT32 stepSize = 0, BOOL arrowsEnabled = TRUE);
	};

	// * Shows creature associated to current town
	struct H3TownAlignmentDlg : protected H3BaseDlg
	{
	public:
		_H3API_ H3TownAlignmentDlg(int town);		
		_H3API_ ~H3TownAlignmentDlg();
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
		_H3API_ VOID  PlaceAtMouse();
		_H3API_ VOID  Start();
		_H3API_ VOID  RMB_Show();
		_H3API_ BOOL  AddBackground(INT32 x, INT32 y, INT32 w, INT32 h, BOOL frame, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);
		_H3API_ BOOL  AddBackground(BOOL frame, BOOL statusBar, INT32 colorIndex);
		_H3API_ BOOL  AddBackground(H3LoadedPCX* pcx);
		_H3API_ BOOL  AddBackground(H3LoadedPCX16* pcx);
		_H3API_ BOOL  AddBackground(H3LoadedPCX24* pcx);
		_H3API_ BOOL  AddBackground(H3LoadedDEF* def, INT group = 0, INT frame = 0);
		
		_H3API_ H3LoadedPCX16* GetBackgroundPcx() const;
		// * draws the background pcx only
		_H3API_ BOOL BackgroundRegion(INT32 xStart, INT32 yStart, INT32 w, INT32 h, BOOL is_blue = FALSE);
		// * draws the HDmod simple frames only
		_H3API_ BOOL SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPCX16* destination = nullptr);
		// * draws the outside frames only
		_H3API_ BOOL FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);
		_H3API_ H3Dlg_proc     GetProc();

		// Item functions		
		_H3API_ H3DlgHintBar* GetHintBar();
		_H3API_ BOOL CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height);
		_H3API_ H3DlgHintBar* CreateHint();
		_H3API_ H3DlgHintBar* CreateHint(INT32 x, INT32 y, INT32 width, INT32 height);
	};
#pragma warning(pop)

	// * follows HDmod's dlg format	
	// * WARNING! this structure should only be used to hook existing dialogs
	struct HDDlg : H3BaseDlg
	{
		typedef INT32(__stdcall* HDDlg_proc)(HDDlg*, H3Msg*);
	protected:
		h3unk _f_6C;
		// * +70
		HDDlg_proc hdProc;	
	public:
		_H3API_ INT CallHDProc(H3Msg& msg);
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
		enum eVTables
		{
			VT_DLGITEM          = 0x63BA24,
			VT_DLGFRAME         = 0x63BA5C,
			VT_DLGPCX           = 0x63BA94,
			VT_DLGPCX16         = 0x63BACC,
			VT_DLGDEFBUTTON     = 0x63BB54,
			VT_DLGCAPTIONBUTTON = 0x63BB88,
			VT_DLGCUSTOMBUTTOM  = 0x63BBBC,

			VT_EDITTEXT2        = 0x63EBF4,

			VT_DLGDEF           = 0x63EC48,
			VT_DLGSCROLLBAR     = 0x641D60,
			
			//VT_DEFScrollsmt     = 0x642CD8,

			VT_DLGSCROLLTEXT    = 0x642D1C,
			VT_DLGEDIT          = 0x642D50,
			VT_DLGTEXT          = 0x642DC0,
			VT_DLGTEXTPCX       = 0x642DF8,			
		};

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
		_H3API_ VOID _SetText(LPCSTR text);

	public:
		_H3API_ static H3DlgItem* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags);

		_H3API_ VOID   EnableItem(BOOL enable);
		_H3API_ VOID   Enable();
		_H3API_ VOID   Disable();
		_H3API_ INT16  GetX() const;
		_H3API_ INT16  GetY() const;
		_H3API_ BOOL   IsEnabled() const;
		_H3API_ VOID   SetX(UINT16 x);
		_H3API_ VOID   SetY(UINT16 y);
		_H3API_ INT32  GetHeight() const;
		_H3API_ INT32  GetWidth() const;
		_H3API_ VOID   SetWidth(UINT16 w);
		_H3API_ VOID   SetHeight(UINT16 h);
		_H3API_ VOID   Draw(); // draw new contents through vTable
		_H3API_ VOID   Refresh(); // refresh screen through parent dlg
		_H3API_ VOID   Hide();
		_H3API_ VOID   Show();
		_H3API_ VOID   Shade();
		_H3API_ VOID   UnShade();
		_H3API_ VOID   SetFocus(BOOL8 focus);
		_H3API_ BOOL   IsVisible() const;
		_H3API_ LPCSTR GetHint() const;
		_H3API_ VOID   SetHint(LPCSTR msg);
		_H3API_ UINT16 GetID() const;
		_H3API_ VOID   ParentRedraw(); // redraw through parent
		_H3API_ VOID   ColorToPlayer(INT8 player);
		_H3API_ VOID   SendCommand(INT32 command, INT32 parameter);
		_H3API_ VOID   SetHints(LPCSTR shortTipText, LPCSTR rightClickHint, BOOL allocateMemory);

		_H3API_ H3DlgFrame*          CastFrame();
		_H3API_ H3DlgDef *           CastDef();
		_H3API_ H3DlgDefButton*      CastDefButton();
		_H3API_ H3DlgCaptionButton*  CastDefButtonCaption();
		_H3API_ H3DlgCustomButton*   CastCustomButton();
		_H3API_ H3DlgPcx*            CastPcx();
		_H3API_ H3DlgPcx16*          CastPcx16();
		_H3API_ H3DlgEdit*           CastEdit();
		_H3API_ H3DlgText*           CastText();
		_H3API_ H3DlgTextPcx*        CastTextPcx();
		_H3API_ H3DlgHintBar*        CastHintBar();
		_H3API_ H3DlgScrollableText* CastScrollText();
		_H3API_ H3DlgScrollbar*      CastScrollbar();
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
		_H3API_ static H3DlgFrame* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color);
		_H3API_ static H3DlgFrame* Create(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color);
		// * the around parameter will create the frame around the edge
		// * of the dialog item instead of covering some of its pixels
		_H3API_ static H3DlgFrame* Create(H3DlgItem* target, RGB565 color, INT id = 0, BOOL around_edge = false);

		_H3API_ VOID      ChangeColor(RGB565 color);
		_H3API_ VOID      HideHue();
		_H3API_ VOID      ShowHue();
		_H3API_ VOID      ToggleHue();
		_H3API_ H3RGB565* GetColor();
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
		_H3API_ static H3DlgDef* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ static H3DlgDef* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ static H3DlgDef* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame = 0, INT32 group = 0);
		_H3API_ VOID  SetFrame(INT32 frame);
		_H3API_ INT   ToggleFrame();
		_H3API_ INT32 GetFrame() const;
		_H3API_ VOID  ColorDefToPlayer(INT32 id);
		_H3API_ VOID  SetClickFrame(INT32 clickFrame);
		_H3API_ H3LoadedDEF* GetDef();
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
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 clickFrame);
	};

	struct H3DlgCaptionButton : public H3DlgDefButton // size 0x70
	{
	protected:
		// * +68
		H3Font* loadedFont;
		// * +6C
		INT32 color;
	public:
		_H3API_ VOID SetText(LPCSTR text);
		_H3API_ static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
		_H3API_ static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
	};

	struct H3DlgCustomButton : public H3DlgDefButton // size 0x6C
	{
	protected:
		// * +68
		H3DlgButton_proc customButtonProc;
	public:
		_H3API_ static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ static H3DlgCustomButton* Create(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ VOID ToggleFlag(BOOL& flag);
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
		_H3API_ static H3DlgEdit* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY);
		_H3API_ LPCSTR    GetText() const;
		_H3API_ H3String* GetString();
		_H3API_ VOID      SetText(LPCSTR text);
		_H3API_ VOID      DecreaseCaret();
		_H3API_ VOID      IncreaseCaret();
		_H3API_ INT       GetCaret() const;
		_H3API_ BOOL      SetCaret(INT pos);
		_H3API_ VOID      SetAutoredraw(BOOL on);
		_H3API_ VOID      SetFocus(BOOL on = TRUE);
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
		_H3API_ VOID   ShowHint(H3Msg* msg);
		_H3API_ VOID   ShowMessage(LPCSTR msg);
		_H3API_ static H3DlgHintBar* Create(H3Dlg* dlg);
		_H3API_ static H3DlgHintBar* Create(H3Dlg* dlg, INT32 x, INT32 y, INT32 w, INT32 h);
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
		H3Vector<h3unk*> items; // never bothered to figure out the type
		// * +54
		H3DlgScrollbar* scrollBar;
		h3unk _f_58[4];
	public:
		_H3API_ static H3DlgScrollableText* Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue);
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
		_H3API_ static H3DlgScrollbar* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled);
		_H3API_ INT32 GetTick() const;
		_H3API_ VOID  SetTick(INT32 index);
		_H3API_ VOID  SetBigStep(INT32 step);
		_H3API_ VOID  SetButtonPosition();
		_H3API_ BOOL  IsHorizontal() const;
		_H3API_ INT32 GetRightButtonX() const; // for horizontal scrollbar only!
		_H3API_ INT32 GetHorizontalY() const;
		_H3API_ INT32 GetBackgroundWidth() const;
		_H3API_ INT32 GetBackgroundX() const;
		_H3API_ INT32 GetSliderX() const;
		_H3API_ H3LoadedPCX* GetPcx();
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
		_H3API_ H3Vector<H3DlgItem*>& GetItems();
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
		_H3API_ void AddComment(LPCSTR text);
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