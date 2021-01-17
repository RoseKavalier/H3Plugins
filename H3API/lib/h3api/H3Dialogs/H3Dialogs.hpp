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

#include "../H3_BinaryItems.hpp"
#include "../H3_Structures.hpp"

namespace h3
{
	// * forward declarations
	_H3API_DECLARE_(H3Msg);
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

	typedef INT32(__fastcall* H3DlgButton_proc)(H3Msg*);
	typedef VOID (__fastcall* H3DlgScrollbar_proc)(INT32, H3Dlg*);

#pragma pack(push, 4)
	struct H3Msg
	{
		typedef NH3VKey::eVirtualKeys eVirtualKeys;

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
			MC_KEY_DOWN       = 1,
			MC_KEY_UP         = 2,
			MC_MOUSE_OVER     = 4,
			MC_LCLICK_OUTSIDE = 8,
			MC_RCLICK_OUTSIDE = 0x20,
			MC_KEY_HELD       = 0x100,
			MC_MOUSE_BUTTON   = 0x200,
			MC_WHEEL_BUTTON   = 0x309,
			MC_MOUSE_WHEEL    = 0x20A,
		};

		enum MessageSubtype
		{
			MS_EndDialog            = 0xA,
			MS_LButtonDown          = 0xC,
			MS_LButtonClick         = 0xD,
			MS_RButtonDown          = 0xE,
			MS_MouseWheelButtonDown = 0x207,
			MS_MouseWheelButtonUp   = 0x208,

			MS_END_DIALOG              = 0xA,
			MS_LBUTTON_DOWN            = 0xC,
			MS_LBUTTON_CLICK           = 0xD,
			MS_RBUTTON_DOWN            = 0xE,
			MS_MOUSE_WHEEL_BUTTON_DOWN = 0x207,
			MS_MOUSE_WHEEL_BUTTON_UP   = 0x208,
		};

		enum MessageFlag
		{
			MF_SHIFT = 1,
			MF_CTRL  = 4,
			MF_ALT   = 32,
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
		_H3API_ NH3VKey::eVirtualKeys GetKey() const;
		_H3API_ INT            GetX()      const;
		_H3API_ INT            GetY()      const;
		_H3API_ POINT          GetCoords() const;
		/**
		 * @brief Get the parent dialog for some custom items when calling their custom proc.
		 *
		 * @return H3Dlg* owning dialog of the current item
		 */
		_H3API_ H3Dlg*         GetDlg() const;

		_H3API_ INT StopProcessing();
	};
	_H3API_ASSERT_SIZE_(H3Msg, 0x20);

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
	};

	/**
	 * @brief A minimal dialog class without proc, ctor 5FEFB0, vtable 643CD4
	 *
	 */
	struct H3BasicDlg : H3Allocator
	{
	protected:
		_H3API_ virtual H3BaseDlg* vDestroy() = 0;                                               /**< @ brief [v00]*/
		_H3API_ virtual INT vShow(INT zorder, BOOL8 draw) = 0;                                   /**< @ brief [v04]*/
		_H3API_ virtual INT vHide(BOOL8 redrawScreen) = 0;                                       /**< @ brief [v08]*/
		_H3API_ virtual INT vPreProcess(H3Msg& msg) = 0;                                         /**< @ brief [v0C]*/
		_H3API_ virtual VOID vParentActivate_10(H3DlgItem* unknown) = 0;                         /**< @ brief [v10] always seems to be nullsub*/
		_H3API_ virtual BOOL8 vRedraw(BOOL8 redrawScreen, INT32 minItemId, INT32 maxItemId) = 0; /**< @ brief [v14]*/
		_H3API_ virtual INT vShowAndRun(BOOL8 fadeIn) = 0;                                       /**< @ brief [v18]*/
		_H3API_ virtual INT vInitiateItems() = 0;                                                /**< @ brief [v1C]*/
		_H3API_ virtual INT vActivateItems(BOOL8 increase) = 0;                                  /**< @ brief [v20]*/

		INT32                zOrder;           /**< @ brief [04]*/
		H3Dlg*               nextDialog;       /**< @ brief [08]*/
		H3Dlg*               lastDialog;       /**< @ brief [0C]*/
		INT32                flags;            /**< @ brief [10]*/
		INT32                state;            /**< @ brief [14]*/
		INT32                xDlg;             /**< @ brief [18]*/
		INT32                yDlg;             /**< @ brief [1C]*/
		INT32                widthDlg;         /**< @ brief [20]*/
		INT32                heightDlg;        /**< @ brief [24]*/
		H3DlgItem*           lastItem;         /**< @ brief [28]*/
		H3DlgItem*           firstItem;        /**< @ brief [2C]*/
		H3Vector<H3DlgItem*> dlgItems;         /**< @ brief [30]*/
		INT32                focusedItemId;    /**< @ brief [40]*/
		H3LoadedPcx16*       pcx16;            /**< @ brief [44]*/
		INT32                deactivatesCount; /**< @ brief [48]*/
	public:
		_H3API_ H3BasicDlg(INT x, INT y, INT w, INT h);
		_H3API_ INT32 GetWidth() const;
		_H3API_ INT32 GetHeight() const;
		_H3API_ INT32 GetX() const;
		_H3API_ INT32 GetY() const;
		_H3API_ BOOL  IsTopDialog() const;

		_H3API_ H3DlgItem* AddItem(H3DlgItem* item, BOOL initiate = TRUE);
	};

	/**
	 * @brief cannot be used except as a pointer or reference
	 *
	 */
	struct H3BaseDlg : H3BasicDlg
	{
	protected:
		_H3API_ virtual INT vDialogProc(H3Msg& msg) = 0;                                         /**< @ brief [v24]*/
		_H3API_ virtual BOOL8 vOnMouseMove(INT32 x, INT32 y) = 0;                                /**< @ brief [v28]*/
		_H3API_ virtual BOOL8 vOnRightClick(INT32 id) = 0;                                       /**< @ brief [v2C]*/
		/**
		 * @brief [v30] if a status bar is provided, short tip text for H3DlgItem under cursor will be shown
		*/
		_H3API_ virtual BOOL8 vOnLeftClick(INT32 id, BOOL8& closeDialog) = 0;
		_H3API_ virtual H3DlgTextPcx* vGetStatusBar() = 0;                                       /**< @ brief [v34]*/
		_H3API_ virtual INT vEndDialogOnTimeExpired(H3Msg& msg) = 0;                             /**< @ brief [v38]*/

		INT32                lastHintShowed;   /**< @ brief [4C]*/
		INT32                messageCommand;   /**< @ brief [50]*/
		INT32                messageSubtype;   /**< @ brief [54]*/
		INT32                messageItemId;    /**< @ brief [58]*/
		BOOL8                networkGame;      /**< @ brief [5C]*/
		h3unk32              _f_60[2];         /**< @ brief [60]*/

		_H3API_ H3DlgItem* getDlgItem(UINT16 id, h3func vtable) const;

	public:

		_H3API_ H3BaseDlg(INT x, INT y, INT w, INT h);

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
			INT32 align = NH3Dlg::TextAlignment::MIDDLE_CENTER, LPCSTR pcxName = nullptr,
			INT32 id = 0, INT32 hasBorder = FALSE, INT32 borderX = 0, INT32 borderY = 0);
		_H3API_ H3DlgText*           CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MIDDLE_CENTER, INT32 bkColor = 0);
		_H3API_ H3DlgTextPcx*        CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName,
			LPCSTR pcxName, INT32 color, INT32 id, INT32 align = NH3Dlg::TextAlignment::MIDDLE_CENTER);
		_H3API_ H3DlgScrollableText* CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height,
			LPCSTR font, INT32 color, INT32 isBlue = FALSE);
		_H3API_ H3DlgScrollbar*      CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount,
			H3DlgScrollbar_proc scrollbarProc = nullptr, BOOL isBlue = FALSE, INT32 stepSize = 0, BOOL arrowsEnabled = TRUE);
	};
	_H3API_ASSERT_SIZE_(H3BaseDlg, 0x68);

	/**
	 * @brief Shows creatures associated to current town
	 *
	 */
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

		_H3API_ virtual H3Dlg* vDestroy() override;                                                   /**< @ brief [v00]*/
		_H3API_ virtual INT vShow(INT zorder, BOOL8 draw) override;                                   /**< @ brief [v04]*/
		_H3API_ virtual INT vHide(BOOL8 redrawScreen) override;                                       /**< @ brief [v08]*/
		_H3API_ virtual INT vPreProcess(H3Msg& msg) override;                                         /**< @ brief [v0C]*/
		_H3API_ virtual VOID vParentActivate_10(H3DlgItem* unknown) override;                         /**< @ brief [v10] always seems to be nullsub*/
		_H3API_ virtual BOOL8 vRedraw(BOOL8 redrawScreen, INT32 minItemId, INT32 maxItemId) override; /**< @ brief [v14]*/
		_H3API_ virtual INT vShowAndRun(BOOL8 fadeIn) override;                                       /**< @ brief [v18]*/
		_H3API_ virtual INT vInitiateItems() override;                                                /**< @ brief [v1C]*/
		_H3API_ virtual INT vActivateItems(BOOL8 increase) override;                                  /**< @ brief [v20]*/
		//======================================
		// custom overload of original virtual function
		// OVERRIDE NOT RECOMMENDED!!
		//======================================

		_H3API_ virtual INT vDialogProc(H3Msg & msg) override; /**< @ brief [v24]*/
		//======================================
		// original virtual functions
		// DO NOT OVERLOAD THESE!
		//======================================

		_H3API_ virtual BOOL8 vOnMouseMove(INT32 x, INT32 y) override;             /**< @ brief [v28]*/
		_H3API_ virtual BOOL8 vOnRightClick(INT32 id) override;                    /**< @ brief [v2C]*/
		_H3API_ virtual BOOL8 vOnLeftClick(INT32 id, BOOL8& closeDialog) override; /**< @ brief [v30]*/
		_H3API_ virtual H3DlgTextPcx* vGetStatusBar() override;                    /**< @ brief [v34]*/
		_H3API_ virtual INT vEndDialogOnTimeExpired(H3Msg& msg) override;          /**< @ brief [v38]*/

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
		virtual _H3API_ BOOL OnKeyPress(NH3VKey::eVirtualKeys key, H3Msg::MessageFlag flag);
		virtual _H3API_ BOOL OnKeyHeld(NH3VKey::eVirtualKeys key, H3Msg::MessageFlag flag);

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

	/**
	 * @brief follows HDmod's dlg format
	 * WARNING! this structure should only be used to hook existing dialogs
	 */
	struct HDDlg : H3BaseDlg
	{
		typedef INT32(__stdcall* HDDlg_proc)(HDDlg*, const H3Msg&);
	protected:
		h3unk _f_68[8];
		// * +70
		HDDlg_proc hdProc;
	public:
		_H3API_ INT CallHDProc(const H3Msg& msg);
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

			VT_DLGSCROLLTEXT    = 0x642D1C,
			VT_DLGEDIT          = 0x642D50,
			VT_DLGTEXT          = 0x642DC0,
			VT_DLGTEXTPCX       = 0x642DF8,
		};

	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x643CA0
		//=================================================

		_H3API_ virtual H3DlgItem* vDestroy(BOOL8 deallocate) = 0;           /**< @ brief [v00]*/
		_H3API_ virtual BOOL vInitiate(INT16 zorder, H3BaseDlg* parent) = 0; /**< @ brief [v04]*/
		_H3API_ virtual INT vProcessMsg(H3Msg& msg) = 0;                     /**< @ brief [v08]*/
		_H3API_ virtual VOID vDrawPcx8(PWORD buffer, RGB565 color) = 0;      /**< @ brief [v0C] no action except H3DlgPcx*/
		_H3API_ virtual VOID vDrawToWindow() = 0;                            /**< @ brief [v10]*/
		_H3API_ virtual INT vGetHeight() const = 0;                          /**< @ brief [v14]*/
		_H3API_ virtual INT vGetWidth() const = 0;                           /**< @ brief [v18]*/
		_H3API_ virtual VOID vCallParent() const = 0;                        /**< @ brief [v1C]*/
		_H3API_ virtual VOID vDarkenArea() const = 0;                        /**< @ brief [v20]*/
		_H3API_ virtual VOID vEnable(BOOL8 state) = 0;                       /**< @ brief [v24]*/
		_H3API_ virtual VOID vGetFocus() = 0;                                /**< @ brief [v28]*/
		_H3API_ virtual VOID vLoseFocus() = 0;                               /**< @ brief [v2C]*/
		_H3API_ virtual VOID vNullsub(INT unknown) const = 0;                /**< @ brief [v30]*/

		H3BaseDlg *parent;           /**< @ brief [04]*/
		H3DlgItem *nextDlgItem;      /**< @ brief [08]*/
		H3DlgItem *previousDlgItem;  /**< @ brief [0C]*/
		UINT16    id;                /**< @ brief [10]*/
		INT16     zOrder;            /**< @ brief [12]*/
		UINT16    flags;             /**< @ brief [14]*/
		UINT16    state;             /**< @ brief [16]*/
		INT16     xPos;              /**< @ brief [18]*/
		INT16     yPos;              /**< @ brief [1A]*/
		UINT16    widthItem;         /**< @ brief [1C]*/
		UINT16    heightItem;        /**< @ brief [1E]*/
		LPCSTR    hint;              /**< @ brief [20]*/
		LPCSTR    rightClickHint;    /**< @ brief [24]*/
		BOOL8     hintsAreAllocated; /**< @ brief [28]*/
		INT32     deactivatesCount;  /**< @ brief [2C]*/

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
	_H3API_ASSERT_SIZE_(H3DlgItem, 0x30);

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
	struct H3DlgFrame : public H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BA5C
		//=================================================

		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0; /**< @ brief [v34]*/

	protected:
		H3RGB565 color565; /**< @ brief [30] RGB565 color*/
		h3align _f_32[2];
		BOOL8 changeHue;   /**< @ brief [34] modifies hue within frame toward RGB565 color, see 0x44FEB4*/
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
	_H3API_ASSERT_SIZE_(H3DlgFrame, 0x38);

	struct H3DlgDef : public H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63EC48
		//=================================================

		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0; /**< @ brief [v34]*/

	protected:
		H3LoadedDef* loadedDef;   /**< @ brief [30]*/
		INT32        defFrame;    /**< @ brief [34]*/
		INT32        secondFrame; /**< @ brief [38] seems unused*/
		INT32        mirror;      /**< @ brief [3C]*/
		INT32        _f_40;       /**< @ brief [40]*/
		INT16        closeDialog; /**< @ brief [44]*/
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
	_H3API_ASSERT_SIZE_(H3DlgDef, 0x48);

	struct H3DlgDefButton : public H3DlgItem // size 0x68 ~ although there is room for CustomProc, which is the same as H3DlgCustomButton, however it is not passed as an argument to the function
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BB54
		//=================================================

		H3LoadedDef*    loadedDef;       /**< @brief [30]*/
		INT32           defFrame;        /**< @brief [34]*/
		INT32           defFrameOnClick; /**< @brief [38]*/
		INT32           mirror;          /**< @brief [3C]*/
		h3unk32         _f_40;           /**< @brief [40]*/
		INT16           closeDialog;     /**< @brief [44]*/
		H3Vector<INT32> hotkeys;         /**< @brief [48] more than one hotkey can be associated*/
		H3String        caption;         /**< @brief [58]*/

	public:
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey);
		_H3API_ static H3DlgDefButton* Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 clickFrame);

		_H3API_ VOID  AddHotkey(INT32 key);
		_H3API_ VOID  SetFrame(INT32 frame);
		_H3API_ INT   ToggleFrame();
		_H3API_ INT32 GetFrame() const;
		_H3API_ INT32 GetClickFrame() const;
		_H3API_ VOID  ColorDefToPlayer(INT32 id);
		_H3API_ VOID  SetClickFrame(INT32 clickFrame);
		_H3API_ H3LoadedDef* GetDef();
	};
	_H3API_ASSERT_SIZE_(H3DlgDefButton, 0x68);

	struct H3DlgCaptionButton : public H3DlgDefButton
	{
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BB88
		//=================================================

	protected:
		H3Font* loadedFont; /**< @brief [68]*/
		INT32   color;      /**< @brief [6C]*/
	public:

		_H3API_ static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
		_H3API_ static H3DlgCaptionButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 a13, INT32 color);
	};
	_H3API_ASSERT_SIZE_(H3DlgCaptionButton, 0x70);

	struct H3DlgCustomButton : public H3DlgDefButton
	{
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BBBC
		//=================================================

	protected:
		H3DlgButton_proc customButtonProc; /**< @brief [68]*/
	public:

		_H3API_ static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ static H3DlgCustomButton* Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ static H3DlgCustomButton* Create(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame);
		_H3API_ VOID ToggleFlag(BOOL& flag);
	};
	_H3API_ASSERT_SIZE_(H3DlgCustomButton, 0x6C);

	struct H3DlgPcx : public H3DlgItem
	{
	protected:
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BA94
		//=================================================

		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0; /**< @brief [v34]*/

	protected:
		H3LoadedPcx* loadedPcx; /**< @brief [30]*/
	public:
		_H3API_ static H3DlgPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName);
		_H3API_ static H3DlgPcx* Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName);
		_H3API_ static H3DlgPcx* Create(INT32 x, INT32 y, LPCSTR pcxName);
		VOID SetPcx(H3LoadedPcx* pcx);
		VOID AdjustColor(INT player);
		H3LoadedPcx* GetPcx();
		H3LoadedPcx* GetPcx() const;
	};
	_H3API_ASSERT_SIZE_(H3DlgPcx, 0x34);

	struct H3DlgPcx16 : public H3DlgItem
	{
	protected:
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x63BACC
		//=================================================

		_H3API_ virtual BOOL8 vNullSub2(INT unk1, INT unk2) = 0; /**< @brief [v34]*/
	protected:
		H3LoadedPcx16* loadedPcx16; /**< @brief [30]*/
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
	_H3API_ASSERT_SIZE_(H3DlgPcx16, 0x34);

	struct H3DlgText : public H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x642DC0
		//=================================================

		_H3API_ virtual VOID vSetText(LPCSTR text) const = 0; /**< @brief [v34]*/

	protected:
		H3String text;    /**< @brief [30]*/
		H3Font*  font;    /**< @brief [40]*/
		INT32    color;   /**< @brief [44]*/
		INT32    bkColor; /**< @brief [48]*/
		INT32    align;   /**< @brief [4C]*/
	public:
		_H3API_ static H3DlgText* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName = NH3Dlg::Text::SMALL,
			INT32 color = NH3Dlg::TextColor::REGULAR, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MIDDLE_CENTER, INT32 bkColor = 0);
		_H3API_ H3String& GetH3String();
		_H3API_ VOID SetText(LPCSTR text);
	};
	_H3API_ASSERT_SIZE_(H3DlgText, 0x50);

	struct H3DlgEdit : public H3DlgText
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x642D50
		//=================================================

		_H3API_ virtual VOID vSetFocus(BOOL8 focused) const = 0;        /**< @brief [v38]*/
		_H3API_ virtual INT vProcessKey(H3Msg &msg) = 0;                /**< @brief [v3C]*/
		_H3API_ virtual BOOL8 vIsTabEscEnter(H3Msg &msg) const = 0;     /**< @brief [v40]*/
		_H3API_ virtual VOID vLoadPcx16Special(BOOL8 redraw) const = 0; /**< @brief [v44]*/
		_H3API_ virtual VOID vPcx16FromBuffer() const = 0;              /**< @brief [v48]*/

	protected:
		H3LoadedPcx*   loadedPcx;   /**< @brief [50]*/
		H3LoadedPcx16* loadedPcx16; /**< @brief [54]*/
		UINT16         caretPos;    /**< @brief [58]*/
		UINT16         maxLength;   /**< @brief [5A]*/
		UINT16         fieldSizeX;  /**< @brief [5C]*/
		UINT16         fieldSizeY;  /**< @brief [5E]*/
		UINT16         fieldX;      /**< @brief [60]*/
		UINT16         fieldY;      /**< @brief [62]*/
		INT16          _f_64;       /**< @brief [64]*/
		INT16          hasBorder;   /**< @brief [66]*/
		INT16          _f_68;       /**< @brief [68]*/
		INT16          _f_6A;       /**< @brief [6A]*/
		h3unk          _f_6C;       /**< @brief [6C]*/
		BOOL8          focused;     /**< @brief [6D]*/
		BOOL8          autoRedraw;  /**< @brief [6E]*/
	public:
		_H3API_ static H3DlgEdit* Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY);
		_H3API_ LPCSTR    GetText() const;
		_H3API_ H3String* GetString();
		_H3API_ VOID      SetText(LPCSTR text);
		_H3API_ VOID      DecreaseCaret();
		_H3API_ VOID      IncreaseCaret();
		_H3API_ UINT      GetCaret() const;
		_H3API_ BOOL      SetCaret(UINT pos);
		_H3API_ VOID      SetAutoredraw(BOOL on);
		_H3API_ VOID      SetFocus(BOOL on = TRUE);
	};
	_H3API_ASSERT_SIZE_(H3DlgEdit, 0x70);

	struct H3ScreenlogEdit : H3DlgEdit
	{
		BOOL8 enteringText; /**< @brief [70]*/
	};
	_H3API_ASSERT_SIZE_(H3ScreenlogEdit, 0x74);

	struct H3DlgTextPcx : public H3DlgText
	{
	protected:
		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x642DF8
		//=================================================

		// * +50
		H3LoadedPcx* loadedPcx;
	public:

		_H3API_ static H3DlgTextPcx* Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName,
			INT32 color, INT32 id = 0, INT32 align = NH3Dlg::TextAlignment::MIDDLE_CENTER);
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

		LPCSTR               font;      /**< @brief [30]*/
		H3Vector<H3String>   textLines; /**< @brief [34]*/
		H3Vector<H3DlgText*> textItems; /**< @brief [44]*/
		H3DlgTextScrollbar*  scrollBar; /**< @brief [54]*/
		H3LoadedPcx16*       canvas;    /**< @brief [58]*/
	public:
		_H3API_ static H3DlgScrollableText* Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR font, INT32 color, INT32 isBlue);
	};

	struct H3DlgScrollbar : public H3DlgItem
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0x641D60
		//=================================================

		_H3API_ virtual VOID vSetTickCount(INT tick) const = 0;     /**< @brief [v34]*/
		_H3API_ virtual VOID vChangeTickPosition(INT change) = 0;   /**< @brief [v38]*/
		_H3API_ virtual VOID vDecreaseTickPosition(INT change) = 0; /**< @brief [v3C]*/
		_H3API_ virtual VOID vScrollCallOwner() const = 0;          /**< @brief [v40]*/

	protected:
		H3LoadedDef*        loadedBtnDef; /**< @brief [30]*/
		H3LoadedPcx*        loadedPcx;    /**< @brief [34]*/
		INT32               previousTick; /**< @brief [38]*/
		INT32               tick;         /**< @brief [3C]*/
		INT32               btnPosition;  /**< @brief [40]*/
		INT32               sizeFree;     /**< @brief [44]*/
		INT32               ticksCount;   /**< @brief [48]*/
		INT32               sizeMax;      /**< @brief [4C]*/
		INT32               bigStepSize;  /**< @brief [50]*/
		INT32               btnSize2;     /**< @brief [54]*/
		h3unk32             _f_58;        /**< @brief [58]*/
		BOOL8               catchKeys;    /**< @brief [5C]*/
		BOOL8               focused;      /**< @brief [5D]*/
		h3unk32             _f_60;        /**< @brief [60]*/
		H3DlgScrollbar_proc callBack;     /**< @brief [64]*/

		VOID loadButton(LPCSTR buttonName);

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

		H3DlgScrollableText* owner; /**< @brief [68]*/

	public:

	};

	struct H3DlgBasePanel : H3Allocator
	{
	protected:

		//=================================================
		// VIRTUAL TABLE ORIGINAL FUNCTIONS 0064235C
		//=================================================

		_H3API_ virtual H3DlgBasePanel* vDestroy(BOOL8 deallocate) = 0;          /**< @brief [v00]*/
		_H3API_ virtual VOID            vFunc04(INT unknown) = 0;                /**< @brief [v04]*/
		_H3API_ virtual VOID            vFunc08(INT unknown1, INT unknown2) = 0; /**< @brief [v08]*/
		_H3API_ virtual VOID            vDrawToWindow() = 0;                     /**< @brief [v0C]*/

		INT                  x;          /**< @brief [04]*/
		INT                  y;          /**< @brief [08]*/
		INT                  width;      /**< @brief [0C]*/
		INT                  height;     /**< @brief [10]*/
		H3Vector<H3DlgItem*> items;      /**< @brief [14]*/
		H3BaseDlg*           parent;     /**< @brief [24]*/
		INT                  largestId;  /**< @brief [28]*/
		INT                  smallestId; /**< @brief [2C]*/
		H3LoadedPcx16*       backupPcx;  /**< @brief [30]*/

		_H3API_ VOID backupScreen();
		_H3API_ VOID restoreBackupScreen();
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
			H3ARGB888  m_highlight;
			UINT       m_thickness;
			_H3API_ H3Highlighter();
			_H3API_ H3Highlighter(H3DlgItem* item, const H3ARGB888& color, UINT thickness);
			_H3API_ H3Highlighter(H3DlgItem* item, BYTE r, BYTE g, BYTE b, UINT thickness);
		};

		H3Vector<H3Highlighter> m_highlightableItems;
		mutable H3DlgItem* m_currentHighlight;
		_H3API_ BOOL unhighlightSelection() const;
	public:
		_H3API_ H3DlgHighlightable();
		_H3API_ VOID AddItem(H3DlgItem* dlgItem, BYTE red, BYTE green, BYTE blue, UINT frameThickness);
		_H3API_ VOID AddItem(H3DlgItem* dlgItem, const H3ARGB888& color, UINT frameThickness);
		_H3API_ BOOL HighlightItem(H3DlgItem* dlgItem) const;
		_H3API_ BOOL HighlightItem(const H3Msg& msg) const;
		_H3API_ VOID Clear();
	};

	/////////////////////////////////////////////
	// Specific dialogs from the game
	/////////////////////////////////////////////

	struct H3CombatBottomPanel : H3DlgBasePanel
	{
	protected:
		H3DlgTextPcx*      commentBar;  /**< @brief [34]*/
		H3DlgCustomButton* commentUp;   /**< @brief [38]*/
		H3DlgCustomButton* commentDown; /**< @brief [3C]*/
	public:

	};

	struct H3CombatHeroPanel : H3DlgBasePanel
	{
	protected:
		H3DlgPcx*  background;  /**< @brief [34]*/
		H3DlgPcx*  hero;        /**< @brief [38]*/
		H3DlgText* attack;      /**< @brief [3C]*/
		H3DlgText* defense;     /**< @brief [40]*/
		H3DlgText* power;       /**< @brief [44]*/
		H3DlgText* knowledge;   /**< @brief [48]*/
		H3DlgDef*  morale;      /**< @brief [4C]*/
		H3DlgDef*  luck;        /**< @brief [50]*/
		H3DlgText* spellPoints; /**< @brief [54]*/
		BOOL8      needsRedraw; /**< @brief [58]*/
	public:
	};
	_H3API_ASSERT_SIZE_(H3CombatHeroPanel, 0x5C);

	struct H3CombatMonsterPanel : H3DlgBasePanel
	{
	protected:
		H3DlgPcx*  background;    /**< @brief [34]*/
		H3DlgDef*  creature;      /**< @brief [38]*/
		H3DlgText* attack;        /**< @brief [3C]*/
		H3DlgText* defense;       /**< @brief [40]*/
		H3DlgText* damage;        /**< @brief [44]*/
		H3DlgText* health;        /**< @brief [48]*/
		H3DlgDef*  morale;        /**< @brief [4C]*/
		H3DlgDef*  luck;          /**< @brief [50]*/
		H3DlgText* numberAlive;   /**< @brief [54]*/
		H3DlgDef*  spells[3];     /**< @brief [58]*/
		H3DlgText* noActiveSpell; /**< @brief [64]*/
		BOOL8      needsRedraw;   /**< @brief [68]*/
		INT        type;          /**< @brief [6C] 1 or 2 ?*/
	public:

	};
	_H3API_ASSERT_SIZE_(H3CombatMonsterPanel, 0x70);

	struct H3CombatDlg : H3BaseDlg
	{
	protected:
		h3unk32               _f_68;                   /**< @brief [68]*/
		UINT                  lastAnimTime;            /**< @brief [6C]*/
	public:
		H3CombatBottomPanel*  bottomPanel;             /**< @brief [70]*/
		H3CombatHeroPanel*    leftHeroPopup;           /**< @brief [74]*/
		H3CombatHeroPanel*    rightHeroPopup;          /**< @brief [78]*/
		H3CombatMonsterPanel* leftMonsterPopup;        /**< @brief [7C]*/
		H3CombatMonsterPanel* rightMonsterPopup;       /**< @brief [80]*/
		H3CombatMonsterPanel* bottomleftMonsterPopup;  /**< @brief [84]*/
		H3CombatMonsterPanel* bottomRightMonsterPopup; /**< @brief [88]*/

		_H3API_ VOID ShowHint(LPCSTR hint, BOOL8 addToLog = FALSE);
		_H3API_ H3Vector<H3String*>& GetCombatText();
	};

	struct H3MonsterInfoDlg : H3BaseDlg
	{
		INT32         morale;          /**< @brief [68]*/
		H3String      moraleModifiers; /**< @brief [6C]*/
		INT32         luck;			   /**< @brief [7C]*/
		H3String      luckModifiers;   /**< @brief [80]*/
		h3unk8        _f_90[32];	   /**< @brief [90]*/
		H3DlgTextPcx* varBackPcx;	   /**< @brief [B0]*/
		H3DlgDef*     animation;	   /**< @brief [B4]*/
	};
	_H3API_ASSERT_SIZE_(H3MonsterInfoDlg, 0xB8);

	struct H3TownDialog : H3BasicDlg
	{
		INT32      townIndex;            /**< @brief [4C]*/
		RGB565*    drawBuffer;           /**< @brief [50]*/
		H3DlgDef*  creaturePortraits[8]; /**< @brief [54] 8th slot for summoning portal creatures*/
		H3DlgText* creaturesText[8];     /**< @brief [74] 8th slot for summoning portal creatures*/
		INT32      creatureTypes[8];     /**< @brief [94] 8th slot for summoning portal creatures*/
	};
	_H3API_ASSERT_SIZE_(H3TownDialog, 0xB4);

	struct H3SelectScenarioDialog : H3BaseDlg
	{
		h3unk32                    _f_68;						 /**< @brief [0068]*/
		H3LoadedDef*               scselcDef;					 /**< @brief [006C]*/
		H3LoadedDef*               scnrvictDef;					 /**< @brief [0070]*/
		H3LoadedDef*               scnrlossDef;					 /**< @brief [0074]*/
		H3LoadedDef*               itpaDef;						 /**< @brief [0078]*/
		H3LoadedDef*               scnrstarDef;					 /**< @brief [007C]*/
		H3LoadedDef*               un44Def;						 /**< @brief [0080]*/
		h3unk32                    _f_84;						 /**< @brief [0084]*/
		H3LoadedPcx*               playerFlagsPcx[8];			 /**< @brief [0088]*/
		H3LoadedPcx*               playerInfoBarPcx[8];			 /**< @brief [00A8]*/
		H3LoadedPcx*               heroSmallPortraitsPcx[163];	 /**< @brief [00C8]*/
		H3LoadedPcx*               hpsrandPcx;					 /**< @brief [0354]*/
		h3unk8                     _f_358[4];					 /**< @brief [0358]*/
		H3LoadedPcx*               hpsrand0Pcx;					 /**< @brief [035C]*/
		H3LoadedPcx*               hpsrand1Pcx;					 /**< @brief [0360]*/
		h3unk32                    _f_364;						 /**< @brief [0364]*/
		H3LoadedPcx*               hpsrand6Pcx;					 /**< @brief [0368]*/
		h3unk8                     _f_36C;						 /**< @brief [036C]*/
		UINT32                     mapListNumberTop;			 /**< @brief [0370]*/
		UINT32                     selectedMapIndex;     		 /**< @brief [0374]*/
		UINT32                     turnDuration;				 /**< @brief [0378]*/
		BOOL8                      mapSelectShown;				 /**< @brief [037C]*/
		BOOL8                      mapListShown;				 /**< @brief [037D]*/
		BOOL8                      rmgSettingsShown;			 /**< @brief [037E]*/
		h3unk8                     _f_37F;						 /**< @brief [037F]*/
		H3DlgEdit*                 edit380;						 /**< @brief [0380]*/
		h3unk32                    _f_384;						 /**< @brief [0384]*/
		h3unk32                    _f_388;						 /**< @brief [0388]*/
		H3MapInformation           mapInfo;						 /**< @brief [038C]*/
		H3Vector<H3MapInformation> vector1030;					 /**< @brief [1030]*/
		H3Vector<H3MapInformation> vector1040;					 /**< @brief [1040]*/
		H3Vector<H3MapInformation> mapsInformation;				 /**< @brief [1050]*/
		H3MapInformation*          mapsInfoPtr;					 /**< @brief [1060]*/
		H3MapDlgPlayer             mapPlayersHuman[8];			 /**< @brief [1064]*/
		H3MapDlgPlayer             mapPlayersComputer[8];		 /**< @brief [1444]*/
		h3unk32                    _f_1824;						 /**< @brief [1824]*/
		h3unk32                    _f_1828;						 /**< @brief [1828]*/
		h3unk32                    _f_182C;						 /**< @brief [182C]*/
		h3unk32                    _f_1830;						 /**< @brief [1830]*/
		h3unk8                     _f_1834;						 /**< @brief [1834]*/
		H3DlgScrollbar*            scrollBar1838;				 /**< @brief [1838]*/
		H3DlgScrollbar*            scrollBar183C;				 /**< @brief [183C]*/
		H3DlgScrollbar*            turnDurationScroll;			 /**< @brief [1840]*/
		h3unk32                    _f_1844;						 /**< @brief [1844]*/
		H3DlgText*                 text1848;					 /**< @brief [1848]*/
		H3DlgText*                 text184C;					 /**< @brief [184C]*/
		H3DlgText*                 text1850;					 /**< @brief [1850]*/
		BOOL8                      newMapSelected;   			 /**< @brief [1854]*/
		H3DlgEdit*                 edit1858;					 /**< @brief [1858]*/
		h3unk32                    _f_185C;						 /**< @brief [185C]*/
		h3unk32                    _f_1860;						 /**< @brief [1860]*/
		h3unk8                     _f_1864;						 /**< @brief [1864]*/
		h3unk8                     _f_1865;						 /**< @brief [1865]*/
		H3DlgDefButton*            button1868;					 /**< @brief [1868]*/
		h3unk8                     _f_186C;                      /**< @brief [186C]*/
		H3LoadedPcx16*             extendedPcx;                  /**< @brief [1870] derived with an extra byte + 2 ints*/
		CHAR                       gameVersionName[20];          /**< @brief [1874] read from VersionInfo*/
		h3func*                    newGameCampaignVtable;		 /**< @brief [1888] start or another class*/
		h3unk8                     _f_188C[8];					 /**< @brief [188C]*/
		h3unk8                     _f_1894;  					 /**< @brief [1894]*/
		INT32                      gameVersion;					 /**< @brief [1898]*/
		h3unk32                    _f_189C;  					 /**< @brief [189C]*/
		UINT32                     mapDimension;				 /**< @brief [18A0]*/
		INT32                      numberLevels;				 /**< @brief [18A4]*/
		INT32                      numberPlayersSelected;		 /**< @brief [18A8]*/
		h3unk32                    _f_18AC;						 /**< @brief [18AC]*/
		INT32                      computerPlayersOnlySelected;	 /**< @brief [18B0]*/
		h3unk32                    _f_18B4;						 /**< @brief [18B4]*/
		INT32                      waterContentSelected;		 /**< @brief [18B8]*/
		INT32                      monsterStrengthSelected;		 /**< @brief [18BC]*/
		H3DlgDefButton*            humanComputerButtons[9];      /**< @brief [18C0]*/
		H3DlgDefButton*            humanComputerTeamsButtons[9]; /**< @brief [18E4]*/
		H3DlgDefButton*            computerOnlyButtons[9];		 /**< @brief [1908]*/
		H3DlgDefButton*            computerOnlyTeams[8];		 /**< @brief [192C]*/
		H3DlgDefButton*            waterContentButtons[4];		 /**< @brief [194C]*/
		H3DlgDefButton*            monsterStrengthButtons[4];	 /**< @brief [195C]*/
		H3DlgScrollableText*       textScroll;				     /**< @brief [196C]*/

		_H3API_ H3MapInformation& CurrentMap();
		_H3API_ VOID UpdateForSelectedScenario(INT32 index, BOOL8 redraw);
		_H3API_ VOID Redraw();
	};
	_H3API_ASSERT_SIZE_(H3SelectScenarioDialog, 0x1970);

#pragma pack(pop)
}

#endif /* #define _H3DIALOGS_HPP_ */