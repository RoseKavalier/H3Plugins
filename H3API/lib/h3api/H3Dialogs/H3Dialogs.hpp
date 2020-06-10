//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3DIALOGS_HPP_
#define _H3DIALOGS_HPP_

#include "../H3_Base.hpp"
#include "../H3_String.hpp"
#include "../H3_BinaryItems.hpp"

namespace h3
{
	// * forward declarations
	_H3API_DECLARE_(H3Msg);
	_H3API_DECLARE_(H3MsgCustom);
	_H3API_DECLARE_(H3BaseDlg);
	_H3API_DECLARE_(H3TownAlignmentDlg);
	_H3API_DECLARE_(H3Dlg);
	_H3API_DECLARE_(H3DlgItem);
	_H3API_DECLARE_(H3DlgTransparentItem);
	_H3API_DECLARE_(H3DlgFrame);
	_H3API_DECLARE_(H3DlgDef);
	_H3API_DECLARE_(H3DlgDefButton);
	_H3API_DECLARE_(H3DlgScrollbar);
	_H3API_DECLARE_(H3DlgCaptionButton);
	_H3API_DECLARE_(H3DlgPcx);
	_H3API_DECLARE_(H3DlgPcx16);
	_H3API_DECLARE_(H3DlgEdit);
	_H3API_DECLARE_(H3DlgText);
	_H3API_DECLARE_(H3DlgTextPcx);
	_H3API_DECLARE_(H3DlgScrollableText);
	_H3API_DECLARE_(H3DlgTextScrollbar);
	_H3API_DECLARE_(H3DlgCustomButton);
	_H3API_DECLARE_(H3DlgHintBar);
	_H3API_DECLARE_(H3DlgBasePanel);

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
			MC_KeyDown       = 1,
			MC_KeyUp         = 2,
			MC_MouseOver     = 4,
			MC_LClickOutside = 8,
			MC_RClickOutside = 0x20,
			MC_KeyHeld       = 0x100,
			MC_MouseButton   = 0x200,
			MC_WheelButton   = 0x309,
			MC_MouseWheel    = 0x20A,
		};
		enum MessageSubtype
		{
			MS_EndDialog            = 0xA,
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
		_H3API_ H3DlgItem* ItemAtPosition(H3BaseDlg* dlg) const;
		_H3API_ INT32      KeyPressed()    const;
		_H3API_ BOOL       IsKeyPress()    const;
		_H3API_ BOOL       IsKeyDown()     const;
		_H3API_ BOOL       IsKeyHeld()     const;
		_H3API_ BOOL       IsMouseOver()   const;
		_H3API_ BOOL       IsWheelButton() const;
		_H3API_ BOOL       IsLeftClick()   const;
		_H3API_ BOOL       IsLeftDown()    const;
		_H3API_ BOOL       IsRightClick()  const;
		_H3API_ BOOL       ClickOutside()  const;
		_H3API_ INT32      CloseDialog();

		_H3API_ MessageFlag    GetFlag()   const;
		_H3API_ NH3VKey::eH3VK GetKey()    const;
		_H3API_ INT            GetX()      const;
		_H3API_ INT            GetY()      const;
		_H3API_ POINT          GetCoords() const;

		_H3API_ INT StopProcessing();
	};

	struct H3MsgCustom : public H3Msg
	{
		_H3API_ H3Dlg* GetDlg() const;
	};

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
		h3func dlgProc;
		h3func mouseMove;
		h3func rightClick;
		h3func clickRet;
		h3func _nullsub3;
		h3func closeDlg;

		_H3API_ H3DlgVTable();
	};

	// * cannot be used except as a pointer or reference
	struct H3BaseDlg : H3Allocator
	{
	protected:
		// * +0
		//H3DlgVTable* vtable;
		// +00
		_H3API_ virtual H3BaseDlg* vDestroy() = 0;
		// +04
		_H3API_ virtual INT vShow(INT zorder, BOOL8 draw) = 0;
		// +08
		_H3API_ virtual INT vHide(BOOL8 redrawScreen) = 0;
		// +0C
		_H3API_ virtual INT vPreProcess(H3Msg& msg) = 0;
		// +10
		// always seems to be nullsub
		_H3API_ virtual VOID vParentActivate_10(H3DlgItem* unknown) = 0;
		// +14
		_H3API_ virtual BOOL8 vRedraw(BOOL8 redrawScreen, INT32 minItemId, INT32 maxItemId) = 0;
		// +18
		_H3API_ virtual INT vShowAndRun(BOOL8 fadeIn) = 0;
		// +1C
		_H3API_ virtual INT vInitiateItems() = 0;
		// +20
		_H3API_ virtual INT vActivateItems(BOOL8 increase) = 0;
		// +24
		_H3API_ virtual INT vDialogProc(H3Msg& msg) = 0;
		// +28
		_H3API_ virtual BOOL8 vOnMouseMove(INT32 x, INT32 y) = 0;
		// +2C
		_H3API_ virtual BOOL8 vOnRightClick(INT32 id) = 0;
		// +30
		_H3API_ virtual BOOL8 vOnLeftClick(INT32 id, BOOL8& closeDialog) = 0;
		// +34
		// if a status bar is provided, short tip text for H3DlgItem under cursor will be shown
		_H3API_ virtual H3DlgTextPcx* vGetStatusBar() = 0;
		// +38
		_H3API_ virtual INT vEndDialogOnTimeExpired(H3Msg& msg) = 0;

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
		H3LoadedPcx16* pcx16;
		// * +48
		INT32 deactivatesCount;
		// * +4C
		INT32 lastHintShowed;
		// * +50
		INT32 messageCommand;
		// * +54
		INT32 messageSubtype;
		// * +58
		INT32 messageItemId;
		// * +5C
		BOOL8 networkGame;
		h3align _f_5D[3];
		h3unk _f_60[8];
		// normal dialog size is 0x68 total

		_H3API_ H3DlgItem* GetDlgItem(UINT16 id, h3func vtable) const;

	public:

		_H3API_ H3BaseDlg(INT x, INT y, INT w, INT h);

		_H3API_ INT32 GetWidth() const;
		_H3API_ INT32 GetHeight() const;
		_H3API_ INT32 GetX() const;
		_H3API_ INT32 GetY() const;
		_H3API_ BOOL  IsTopDialog() const;

		_H3API_ VOID  Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy); // redraw part of dialog
		_H3API_ VOID  Redraw(); // redraw whole dialog
		_H3API_ INT32 DefaultProc(H3Msg* msg);
		_H3API_ INT32 DefaultProc(H3Msg& msg);

		// * this is what gets shown on the screen
		// * it gets drawn over every time you refresh an item
		// * or draw a new item... good for temporary things
		_H3API_ H3LoadedPcx16* GetCurrentPcx();

		_H3API_ H3DlgItem* ItemAtPosition(H3Msg* msg);
		_H3API_ H3DlgItem* ItemAtPosition(H3Msg& msg);
		_H3API_ H3Vector<H3DlgItem*>& GetList();
		_H3API_ H3DlgItem* GetH3DlgItem(UINT16 id);

		_H3API_ VOID RedrawItem(UINT16 itemID);
		_H3API_ VOID EnableItem(UINT16 id, BOOL enable);
		_H3API_ VOID SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter);
		_H3API_ VOID SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter);
		_H3API_ VOID AdjustToPlayerColor(INT8 player, UINT16 itemId);
		_H3API_ H3DlgItem* AddItem(H3DlgItem* item);

		// * search and cast to ItemType
		// * e.g. Get<H3DlgDef>(1234)
		template<typename ItemType>
		ItemType* Get(UINT16 id);

		// * these DlgItem Get functions will confirm not only the id
		// * but also the type of the item through its virtual table
		// * because of this latter confirmation, it is possible that
		// * the result is nullptr, so you should always check the return
		_H3API_ H3DlgDef*             GetDef(UINT16 id) const;
		_H3API_ H3DlgPcx*             GetPcx(UINT16 id) const;
		_H3API_ H3DlgEdit*            GetEdit(UINT16 id) const;
		_H3API_ H3DlgText*            GetText(UINT16 id) const;
		_H3API_ H3DlgFrame*           GetFrame(UINT16 id) const;
		_H3API_ H3DlgPcx16*           GetPcx16(UINT16 id) const;
		_H3API_ H3DlgTextPcx*         GetTextPcx(UINT16 id) const;
		_H3API_ H3DlgDefButton*       GetDefButton(UINT16 id) const;
		_H3API_ H3DlgScrollbar*       GetScrollbar(UINT16 id) const;
		_H3API_ H3DlgTransparentItem* GetTransparent(UINT16 id) const;
		_H3API_ H3DlgCustomButton*    GetCustomButton(UINT16 id) const;
		_H3API_ H3DlgCaptionButton*   GetCaptionButton(UINT16 id) const;
		_H3API_ H3DlgScrollableText*  GetScrollabaleText(UINT16 id) const;

		// * dlgitem that is not visible but responds to commands
		_H3API_ H3DlgTransparentItem* CreateHidden(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id);

		_H3API_ H3DlgFrame*          CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color);
		_H3API_ H3DlgFrame*          CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color);
		_H3API_ H3DlgFrame*          CreateFrame(H3DlgItem* target, RGB565 color, INT id = 0, BOOL around_edge = false);
		_H3API_ H3DlgDef*            CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame,
			INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ H3DlgDef*            CreateDef(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group = 0,
			INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ H3DlgDefButton*      CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			INT32 frame, INT32 clickFrame, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
		_H3API_ H3DlgDefButton*      CreateButton(INT32 x, INT32 y, INT32 id, LPCSTR defName,
			INT32 frame = 0, INT32 clickFrame = 1, BOOL closeDialog = FALSE, INT32 hotkey = NULL);
		_H3API_ H3DlgDefButton*      CreateOKButton(INT32 x, INT32 y);
		_H3API_ H3DlgDefButton*      CreateSaveButton(INT32 x, INT32 y);
		_H3API_ H3DlgDefButton*      CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame = 0);
		_H3API_ H3DlgDefButton*      CreateOKButton(); // adjust for hintBar
		_H3API_ H3DlgDefButton*      CreateOK32Button(INT32 x, INT32 y); // height is 32
		_H3API_ H3DlgDefButton*      CreateCancelButton(); // adjust for hintBar
		_H3API_ H3DlgCaptionButton*  CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			LPCSTR text, LPCSTR font, INT32 frame, INT32 group = 0, BOOL closeDialog = FALSE, INT32 hotkey = NULL, INT32 color = 0);
		_H3API_ H3DlgCustomButton*   CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName,
			H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ H3DlgCustomButton*   CreateCustomButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc,
			INT32 frame, INT32 clickFrame);
		_H3API_ H3DlgCustomButton*   CreateCustomButton(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc,
			INT32 frame, INT32 clickFrame);
		_H3API_ H3DlgPcx*            CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ H3DlgPcx*            CreatePcx(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		_H3API_ H3DlgPcx*            CreateLineSeparator(INT32 x, INT32 y, INT32 width);
		_H3API_ H3DlgPcx16*          CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ H3DlgEdit*           CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text,
			LPCSTR fontName = NH3Dlg::Text::MEDIUM, INT32 color = NH3Dlg::TextColor::REGULAR,
			INT32 align = NH3Dlg::TextAlignment::MiddleCenter, LPCSTR pcxName = nullptr,
			INT32 id = 0, INT32 hasBorder = FALSE, INT32 borderX = 0, INT32 borderY = 0);
		_H3API_ H3DlgText*           CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
		_H3API_ H3DlgTextPcx*        CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			LPCSTR pcxName, INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
		_H3API_ H3DlgScrollableText* CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height,
			LPCSTR font, INT32 color, INT32 isBlue = FALSE);
		_H3API_ H3DlgScrollbar*      CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount,
			H3DlgScrollbar_proc scrollbarProc = nullptr, BOOL isBlue = FALSE, INT32 stepSize = 0, BOOL arrowsEnabled = TRUE);
	};

	// * Shows creature associated to current town
	struct H3TownAlignmentDlg : H3Allocator
	{
	private:
		// the same as H3BaseDlg but not needed...
		H3DlgVTable* m_vtable;
		h3align m_data[sizeof(H3BaseDlg) - 4];
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
		//======================================
		// original virtual functions
		// DO NOT OVERLOAD THESE!
		//======================================
		// +00
		_H3API_ virtual H3Dlg* vDestroy() override;
		// +04
		_H3API_ virtual INT vShow(INT zorder, BOOL8 draw) override;
		// +08
		_H3API_ virtual INT vHide(BOOL8 redrawScreen) override;
		// +0C
		_H3API_ virtual INT vPreProcess(H3Msg& msg) override;
		// +10
		// always seems to be nullsub
		_H3API_ virtual VOID vParentActivate_10(H3DlgItem* unknown) override;
		// +14
		_H3API_ virtual BOOL8 vRedraw(BOOL8 redrawScreen, INT32 minItemId, INT32 maxItemId) override;
		// +18
		_H3API_ virtual INT vShowAndRun(BOOL8 fadeIn) override;
		// +1C
		_H3API_ virtual INT vInitiateItems() override;
		// +20
		_H3API_ virtual INT vActivateItems(BOOL8 increase) override;
		//======================================
		// custom overload of original virtual function
		// OVERRIDE NOT RECOMMENDED!!
		//======================================
		// +24
		_H3API_ virtual INT vDialogProc(H3Msg & msg) override;
		//======================================
		// original virtual functions
		// DO NOT OVERLOAD THESE!
		//======================================
		// +28
		_H3API_ virtual BOOL8 vOnMouseMove(INT32 x, INT32 y) override;
		// +2C
		_H3API_ virtual BOOL8 vOnRightClick(INT32 id) override;
		// +30
		_H3API_ virtual BOOL8 vOnLeftClick(INT32 id, BOOL8& closeDialog) override;
		// +34
		// if a status bar is provided, short tip text for H3DlgItem under cursor will be shown
		_H3API_ virtual H3DlgTextPcx* vGetStatusBar() override;
		// +38
		_H3API_ virtual INT vEndDialogOnTimeExpired(H3Msg& msg) override;

	public:
		//======================================
		// custom virtual functions
		// FEEL FREE TO OVERLOAD THESE!
		//======================================

		// these remove the need to look at WindowManager to get clicked id
		// and occur within the message loop
		virtual _H3API_ VOID OnOK();
		virtual _H3API_ VOID OnCancel();
		virtual _H3API_ VOID OnClose(INT itemId);

		// * you can use this to add H3DlgItems to your dialog before running it
		// * return TRUE if you wish to run the dialog
		// * return FALSE if you wish to abort
		virtual _H3API_ BOOL OnCreate();

		// * BOOL override functions:
		// *	on TRUE will continue handling current message
		// *	on FALSE will not process current message further

		virtual _H3API_ BOOL DialogProc(H3Msg& msg);
		virtual _H3API_ BOOL OnLeftClick(INT itemId, H3Msg& msg);
		virtual _H3API_ BOOL OnLeftClickOutside();
		virtual _H3API_ BOOL OnRightClick(H3DlgItem* it);
		virtual _H3API_ BOOL OnRightClickOutside();
		// scroll down: -1, scroll up +1
		virtual _H3API_ BOOL OnMouseWheel(INT direction);
		virtual _H3API_ BOOL OnWheelButton(H3DlgItem* it);
		virtual _H3API_ BOOL OnMouseHover(INT32 x, INT32 y);
		virtual _H3API_ BOOL OnMouseHover(H3DlgItem* it);
		virtual _H3API_ BOOL OnKeyPress(NH3VKey::eH3VK key, H3Msg::MessageFlag flag);
		virtual _H3API_ BOOL OnKeyHeld(NH3VKey::eH3VK key, H3Msg::MessageFlag flag);

		// * this message gets sent from individual H3DlgItems
		// * that use customized virtual tables instead of default ones
		// * this hook occurs before the H3Msg is sent to vDialogProc()
		virtual _H3API_ BOOL OnNotify(H3DlgItem* it, H3Msg& msg);
	protected:
		////////////////////////////////////////////////////////////////////////
		// Custom Fields - not part of regular dialogs!
		////////////////////////////////////////////////////////////////////////
		BOOL           endDialog;
		H3LoadedPcx16* background;
		H3DlgHintBar*  hintBar;

		////////////////////////////////////////////////////////////////////////
		// Protected functions not meant to be used outside implementation
		////////////////////////////////////////////////////////////////////////
		_H3API_ INT CheckEnd(H3Msg& msg);

	public:
		////////////////////////////////////////////////////////////////////////
		// Constructor and destructor
		////////////////////////////////////////////////////////////////////////
		// * default constructor
		_H3API_ H3Dlg(int width, int height, int x = -1, int y = -1, BOOL statusBar = FALSE,
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
		_H3API_ VOID  Stop();
		_H3API_ VOID  RMB_Show();
		_H3API_ BOOL  AddBackground(INT32 x, INT32 y, INT32 w, INT32 h, BOOL frame, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);
		_H3API_ BOOL  AddBackground(BOOL frame, BOOL statusBar, INT32 colorIndex);
		_H3API_ BOOL  AddBackground(H3LoadedPcx* pcx);
		_H3API_ BOOL  AddBackground(H3LoadedPcx16* pcx);
		_H3API_ BOOL  AddBackground(H3LoadedPcx24* pcx);
		_H3API_ BOOL  AddBackground(H3LoadedDef* def, INT group = 0, INT frame = 0);

		_H3API_ BOOL Notify(H3DlgItem* it, H3Msg& msg);

		_H3API_ H3LoadedPcx16* GetBackgroundPcx() const;
		// * draws the background pcx only
		_H3API_ BOOL BackgroundRegion(INT32 xStart, INT32 yStart, INT32 w, INT32 h, BOOL is_blue = FALSE);
		// * draws the HDmod simple frames only
		_H3API_ BOOL SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPcx16* destination = nullptr);
		// * draws the outside frames only
		_H3API_ BOOL FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue = FALSE);

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
		h3unk _f_68[8];
		// * +70
		HDDlg_proc hdProc;
	public:
		_H3API_ INT CallHDProc(H3Msg& msg);
	};

	struct H3DlgItemVTable // 0x63BA24
	{
		h3func deref; // +0
		h3func init;  // +4
		h3func processCommand; // +8 used to redraw
		h3func _null1; // C
		h3func draw; // +10
		h3func getHeight;
		h3func getWidth;
		h3func showHint;
		h3func drawShadow; // +20
		h3func setEnabled;
		h3func getFocus;
		h3func loseFocus;
		h3func _null5; // +30
		h3func setText; // +34
		////////////////////////////////////////////////
		// not all H3DlgItems have the following:
		////////////////////////////////////////////////
		h3func setFocus; // H3DlgEdit has these // ScrollbarText has 3
		h3func processKey;
		h3func isDisallowedKey; // +40 disallowed key for H3DlgEdit, e.g. save game field 0x57D2F0
		h3func loadPcx16;
		h3func pcx16FromBuffer;
	};

	struct H3DlgItem : H3Allocator   // size 0x30
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

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x643CA0
		//=================================================
		// +[00]
		_H3API_ virtual H3DlgItem* vDestroy(BOOL8 deallocate) = 0;
		// +[04]
		_H3API_ virtual BOOL vInitiate(INT16 zorder, H3BaseDlg* parent) = 0;
		// +[08]
		_H3API_ virtual INT vProcessMsg(H3Msg& msg) = 0;
		// +[0C]
		// no action for most dlg items except H3DlgPcx
		_H3API_ virtual VOID vDrawPcx8(PWORD buffer, RGB565 color) = 0;
		// +[10]
		_H3API_ virtual VOID vDrawToWindow() = 0;
		// +[14]
		_H3API_ virtual INT vGetHeight() const = 0;
		// +[18]
		_H3API_ virtual INT vGetWidth() const = 0;
		// +[1C]
		_H3API_ virtual VOID vCallParent() const = 0;
		// +[20]
		_H3API_ virtual VOID vDarkenArea() const = 0;
		// +[24]
		_H3API_ virtual VOID vEnable(BOOL8 state) = 0;
		// +[28]
		_H3API_ virtual VOID vGetFocus() = 0;
		// +[2C]
		_H3API_ virtual VOID vLoseFocus() = 0;
		// +[30]
		_H3API_ virtual VOID vNullsub(INT unknown) const = 0;

		// * +4
		H3BaseDlg *parent;
		// * +8
		H3DlgItem *nextDlgItem;
		// * +C
		H3DlgItem *previousDlgItem;
		// * +10
		UINT16 id;
		// * +12
		INT16 zOrder;
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

		_H3API_ BOOL NotifyParent(H3Msg& msg);
		_H3API_ BOOL TranslateUnprocessedMessage(H3Msg& msg);

	public:
		_H3API_ VOID       EnableItem(BOOL enable);
		_H3API_ VOID       Enable();
		_H3API_ VOID       Disable();
		_H3API_ INT16      GetX() const;
		_H3API_ INT16      GetY() const;
		_H3API_ INT32      GetAbsoluteX() const;
		_H3API_ INT32      GetAbsoluteY() const;
		_H3API_ BOOL       IsEnabled() const;
		_H3API_ BOOL       IsActive() const;
		_H3API_ VOID       SetX(UINT16 x);
		_H3API_ VOID       SetY(UINT16 y);
		_H3API_ INT32      GetHeight() const;
		_H3API_ INT32      GetWidth() const;
		_H3API_ VOID       SetWidth(UINT16 w);
		_H3API_ VOID       SetHeight(UINT16 h);
		_H3API_ VOID       Draw(); // draw new contents through vTable
		_H3API_ VOID       Refresh(); // refresh screen through parent dlg
		_H3API_ H3DlgItem* Hide();
		_H3API_ VOID       HideDeactivate();
		_H3API_ VOID       ShowActivate();
		_H3API_ H3DlgItem* Show();
		_H3API_ VOID       Shade();
		_H3API_ VOID       UnShade();
		_H3API_ H3DlgItem* Activate();   // allows processing of H3Msg
		_H3API_ H3DlgItem* DeActivate(); // prevents processing of H3Msg
		_H3API_ BOOL       IsVisible() const;
		_H3API_ LPCSTR     GetHint() const;
		_H3API_ VOID       SetHint(LPCSTR msg);
		_H3API_ UINT16     GetID() const;
		_H3API_ VOID       ParentRedraw(); // redraw through parent
		_H3API_ VOID       ColorToPlayer(INT8 player);
		_H3API_ VOID       SendCommand(INT32 command, INT32 parameter);
		_H3API_ VOID       SetHints(LPCSTR shortTipText, LPCSTR rightClickHint, BOOL allocateMemory);
		_H3API_ VOID       DrawTempFrame(INT thickness, BYTE r, BYTE g, BYTE b) const;
		_H3API_ VOID       DrawTempFrame(INT thickness, const H3RGB888& color) const;

		_H3API_ H3BaseDlg* GetParent() const;
		_H3API_ H3DlgItem* GetNextItem() const;
		_H3API_ H3DlgItem* GetPreviousItem() const;

		template<typename ItemType>
		ItemType* Cast();

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

	struct H3DlgTransparentItem : H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BA24
		//=================================================
		// +[34]
		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0;
	public:
		_H3API_ static H3DlgTransparentItem* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id);
	};

	// * a 1-pixel wide rectangular frame with the color
	// * of your choice
	struct H3DlgFrame : public H3DlgItem // size 0x38
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BA5C
		//=================================================
		// +[34]
		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0;

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

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63EC48
		//=================================================
		// +[34]
		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0;

	protected:
		// * +30
		H3LoadedDef* loadedDef;
		// * +34
		INT32 defFrame;
		// * +38
		INT32 secondFrame; // seems unused
		// * +3C
		INT32 mirror;
		INT32 _f_40;
		// * +44
		INT16 closeDialog;
		h3align _f_46[2];
	public:

		_H3API_ static H3DlgDef* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ static H3DlgDef* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame = 0, INT32 group = 0, INT32 mirror = FALSE, BOOL closeDialog = FALSE);
		_H3API_ static H3DlgDef* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame = 0, INT32 group = 0);
		_H3API_ VOID  SetFrame(INT32 frame);
		_H3API_ INT32 GetFrame() const;
		_H3API_ INT32 ToggleFrame();
		_H3API_ INT32 GetClickFrame() const;
		_H3API_ VOID  SetClickFrame(INT32 clickFrame);
		_H3API_ VOID  ColorDefToPlayer(INT32 id);
		_H3API_ H3LoadedDef* GetDef();
	};

	struct H3DlgDefButton : public H3DlgItem // size 0x68 ~ although there is room for CustomProc, which is the same as H3DlgCustomButton, however it is not passed as an argument to the function
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BB54
		//=================================================
		// * +30
		H3LoadedDef* loadedDef;
		// * +34
		INT32 defFrame;
		// * +38
		INT32 defFrameOnClick;
		// * +3C
		INT32 mirror;
		INT32 _f_40;
		// * +44
		INT16 closeDialog;
		h3align _f_46[2];
		// * +48
		H3Vector<INT32> hotkeys; // ?
		// * +58
		H3String caption;

	public:
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 clickFrame);

		_H3API_ VOID  SetFrame(INT32 frame);
		_H3API_ INT   ToggleFrame();
		_H3API_ INT32 GetFrame() const;
		_H3API_ INT32 GetClickFrame() const;
		_H3API_ VOID  ColorDefToPlayer(INT32 id);
		_H3API_ VOID  SetClickFrame(INT32 clickFrame);
		_H3API_ H3LoadedDef* GetDef();
	};

	struct H3DlgCaptionButton : public H3DlgDefButton // size 0x70
	{
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BB88
		//=================================================

	protected:
		// * +68
		H3Font* loadedFont;
		// * +6C
		INT32 color;
	public:

		_H3API_ static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
		_H3API_ static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
	};

	struct H3DlgCustomButton : public H3DlgDefButton // size 0x6C
	{
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BBBC
		//=================================================

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
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BA94
		//=================================================
		// +[34]
		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0;

	protected:
		// * +30
		H3LoadedPcx* loadedPcx;
	public:
		_H3API_ static H3DlgPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ static H3DlgPcx* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		_H3API_ static H3DlgPcx* Create(INT32 x, INT32 y, LPCSTR pcxName);
		VOID SetPcx(H3LoadedPcx* pcx);
		VOID AdjustColor(INT player);
		H3LoadedPcx* GetPcx();
		H3LoadedPcx* GetPcx() const;
	};

	struct H3DlgPcx16 : public H3DlgItem
	{
	protected:
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BACC
		//=================================================
		// +[34]
		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0;
	protected:
		// * +30
		H3LoadedPcx16* loadedPcx16;
	public:
		_H3API_ static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ static H3DlgPcx16* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		_H3API_ static H3DlgPcx16* Create(INT32 x, INT32 y, LPCSTR pcxName);
		_H3API_ VOID SetPcx(H3LoadedPcx16* pcx16);
		_H3API_ H3LoadedPcx16* GetPcx();
		_H3API_ VOID SinkArea(INT32 x, INT32 y, INT32 w, INT32 h);
		_H3API_ VOID BevelArea(INT32 x, INT32 y, INT32 w, INT32 h);
		_H3API_ VOID SinkArea(H3DlgItem* it);
		_H3API_ VOID BevelArea(H3DlgItem* it);
	};

	struct H3DlgText : public H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x642DC0
		//=================================================
		// +[34]
		_H3API_ virtual VOID vSetText(LPCSTR text) const = 0;

	protected:
		// * +30
		H3String text;
		// * +40
		H3Font* font;
		// * +44
		INT32 color;
		// * +48
		INT32 bkColor;
		// * +4C
		INT32 align;
	public:
		_H3API_ static H3DlgText* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName = NH3Dlg::Text::SMALL, INT32 color = NH3Dlg::TextColor::REGULAR, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MiddleCenter, INT32 bkColor = 0);
		_H3API_ H3String& GetH3String();
		_H3API_ VOID SetText(LPCSTR text);
	};

	struct H3DlgEdit : public H3DlgText // size 0x70
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x642D50
		//=================================================
		// +[38]
		_H3API_ virtual VOID vSetFocus(BOOL8 focused) const = 0;
		// +[3C]
		_H3API_ virtual INT vProcessKey(H3Msg &msg) = 0;
		// +[40]
		_H3API_ virtual BOOL8 vIsTabEscEnter(H3Msg &msg) const = 0;
		// +[44]
		_H3API_ virtual VOID vLoadPcx16Special(BOOL8 redraw) const = 0;
		// +[48]
		_H3API_ virtual VOID vPcx16FromBuffer() const = 0;

	protected:
		// * +50
		H3LoadedPcx* loadedPcx;
		// * +54
		H3LoadedPcx16* loadedPcx16;
		// * +58
		UINT16 caretPos;
		// * +5A
		UINT16 maxLength;
		// * +5C
		UINT16 fieldSizeX;
		// * +5E
		UINT16 fieldSizeY;
		// * +60
		UINT16 fieldX;
		// * +62
		UINT16 fieldY;
		INT16 _f_64;
		INT16 hasBorder;
		INT16 _f_68;
		INT16 _f_6A;
		h3unk _f_6C;
		// * +6D
		BOOL8 focused;
		// * +6E
		BOOL8 autoRedraw;
		h3align _f_6F;
	public:
		_H3API_ static H3DlgEdit* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY);
		_H3API_ LPCSTR    GetText() const;
		_H3API_ H3String* GetString();
		_H3API_ VOID      SetText(LPCSTR text);
		_H3API_ VOID      DecreaseCaret();
		_H3API_ VOID      IncreaseCaret();
		_H3API_ UINT       GetCaret() const;
		_H3API_ BOOL      SetCaret(UINT pos);
		_H3API_ VOID      SetAutoredraw(BOOL on);
		_H3API_ VOID      SetFocus(BOOL on = TRUE);
	};

	struct H3DlgTextPcx : public H3DlgText
	{
	protected:
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x642DF8
		//=================================================

		// * +44
		H3LoadedPcx* loadedPcx;
	public:

		_H3API_ static H3DlgTextPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MiddleCenter);
		_H3API_ static H3DlgTextPcx* Create(INT32 x, INT32 y, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 align);
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

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BA24
		//=================================================
		// * +30
		LPCSTR font;
		// * +34
		H3Vector<H3String> textLines;
		// * +44
		H3Vector<H3DlgText*> textItems;
		// * +54
		H3DlgTextScrollbar* scrollBar;
		// * +58
		H3LoadedPcx16* canvas;
	public:
		_H3API_ static H3DlgScrollableText* Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR font, INT32 color, INT32 isBlue);
	};

	struct H3DlgScrollbar : public H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x641D60
		//=================================================
		// +[34]
		_H3API_ virtual VOID vSetTickCount(INT tick) const = 0;
		// +[38]
		_H3API_ virtual VOID vChangeTickPosition(INT change) = 0;
		// +[3C]
		_H3API_ virtual VOID vDecreaseTickPosition(INT change) = 0;
		// +[40]
		_H3API_ virtual VOID vScrollCallOwner() const = 0;

	protected:
		// * +30
		H3LoadedDef* loadedBtnDef;
		// * +34
		H3LoadedPcx* loadedPcx;
		// * +38
		INT32 previousTick;
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
		BOOL8 catchKeys;
		// * +5D
		BOOL8 focused;
		h3align _f_5E[2];
		h3unk _f_60[4];
		// * +64
		H3DlgScrollbar_proc callBack;

		VOID LoadButton(LPCSTR buttonName);

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
		_H3API_ H3LoadedPcx* GetPcx();
	};

	struct H3DlgTextScrollbar : public H3DlgScrollbar
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 00642CD8
		//=================================================
		// * +68
		H3DlgScrollableText* owner;

	public:

	};

	struct H3DlgBasePanel : H3Allocator
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0064235C
		//=================================================
		// * +[00]
		_H3API_ virtual H3DlgBasePanel* vDestroy(BOOL8 deallocate) = 0;
		// * +[04]
		_H3API_ virtual VOID        vFunc04(INT unknown) = 0;
		// * +[08]
		_H3API_ virtual VOID        vFunc08(INT unknown1, INT unknown2) = 0;
		// * +[0C]
		_H3API_ virtual VOID        vDrawToWindow() = 0;

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
		INT                  largestId;
		// * +2C
		INT                  smallestId;
		// * +30
		H3LoadedPcx16*       backupPcx;

		_H3API_ VOID BackupScreen();
		_H3API_ VOID RestoreBackupScreen();
	public:
		_H3API_ H3Vector<H3DlgItem*>& GetItems();

		_H3API_ H3DlgItem* AddItem(H3DlgItem* item);
		_H3API_ VOID Redraw();
		_H3API_ VOID Hide();
		_H3API_ VOID Show();
		_H3API_ VOID Move(INT xDest, INT yDest);
		_H3API_ VOID MoveRelative(INT xDelta, INT yDelta);

		_H3API_ INT32 GetWidth() const;
		_H3API_ INT32 GetHeight() const;
		_H3API_ INT32 GetX() const;
		_H3API_ INT32 GetY() const;
	};

	struct H3CombatBottomPanel : H3DlgBasePanel
	{
	protected:
		// * +34
		H3DlgTextPcx*      commentBar;
		// * +38
		H3DlgCustomButton* commentUp;
		// * +3C
		H3DlgCustomButton* commentDown;
	public:

	};

	struct H3CombatHeroPanel : H3DlgBasePanel
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

	struct H3CombatMonsterPanel : H3DlgBasePanel
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

		_H3API_ VOID ShowHint(LPCSTR hint, BOOL8 addToLog = FALSE);
		_H3API_ H3Vector<H3String*>& GetCombatText();
	};

	/////////////////////////////////////////////
	// Custom dialog functionality
	/////////////////////////////////////////////

	// * for any given dialog, you can add items that you would like to have
	// * a temporary frame on their edge when the cursor hovers over them
	class H3DlgHighlightable
	{
	protected:
		struct H3Highlighter
		{
			H3DlgItem* m_item;
			H3RGB888   m_highlight;
			UINT       m_thickness;
			_H3API_ H3Highlighter();
			_H3API_ H3Highlighter(H3DlgItem* item, const H3RGB888& color, UINT thickness);
			_H3API_ H3Highlighter(H3DlgItem* item, BYTE r, BYTE g, BYTE b, UINT thickness);
		};

		H3Vector<H3Highlighter> m_highlightableItems;
		mutable H3DlgItem* m_currentHighlight;
		_H3API_ BOOL UnhighlightSelection() const;
	public:
		_H3API_ H3DlgHighlightable();
		_H3API_ VOID AddItem(H3DlgItem* dlgItem, BYTE red, BYTE green, BYTE blue, UINT frameThickness);
		_H3API_ VOID AddItem(H3DlgItem* dlgItem, const H3RGB888& color, UINT frameThickness);
		_H3API_ BOOL HighlightItem(H3DlgItem* dlgItem) const;
		_H3API_ BOOL HighlightItem(const H3Msg& msg) const;
		_H3API_ VOID Clear();
	};

#pragma pack(pop)
}

#endif /* #define _H3DIALOGS_HPP_ */