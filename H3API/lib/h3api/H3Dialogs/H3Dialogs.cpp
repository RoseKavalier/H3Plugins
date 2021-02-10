//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Dialogs.hpp"
#include "H3Dialogs.inl"
#include "../H3_Functions.hpp"

namespace h3
{
	_H3API_ VOID H3Msg::SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2)
	{
		command   = _command;
		subtype   = _subtype;
		item_id   = _item_id;
		flags     = _flags;
		x_abs     = x;
		y_abs     = y;
		parameter = param;
		flags2    = _flags2;
	}
	_H3API_ VOID H3Msg::SetCommand(INT32 cmd, INT32 param)
	{
		SetCommand(0x200, cmd, 0, 0, 0, 0, param, 0);
	}
	_H3API_ H3DlgItem* H3Msg::ItemAtPosition(H3BaseDlg* dlg) const
	{
		return THISCALL_3(H3DlgItem*, 0x5FF9A0, dlg, x_abs, y_abs);
	}
	_H3API_ INT32 H3Msg::KeyPressed() const
	{
		return subtype;
	}
	_H3API_ BOOL H3Msg::IsKeyPress() const
	{
		return command == int(MessageCommand::MC_KEY_UP);
	}
	_H3API_ BOOL H3Msg::IsKeyDown() const
	{
		return command == int(MessageCommand::MC_KEY_DOWN);
	}
	_H3API_ BOOL H3Msg::IsKeyHeld() const
	{
		return command == int(MessageCommand::MC_KEY_HELD);
	}
	_H3API_ BOOL H3Msg::IsMouseOver() const
	{
		return command == int(MessageCommand::MC_MOUSE_OVER);
	}
	_H3API_ BOOL H3Msg::IsWheelButton() const
	{
		return command == int(MessageCommand::MC_WHEEL_BUTTON) && subtype == int(MessageSubtype::MS_MOUSE_WHEEL_BUTTON_DOWN);
	}
	_H3API_ BOOL H3Msg::IsLeftClick() const
	{
		return (command == int(MessageCommand::MC_MOUSE_BUTTON) && subtype == int(MessageSubtype::MS_LBUTTON_CLICK));
	}
	_H3API_ BOOL H3Msg::IsLeftDown() const
	{
		return (command == int(MessageCommand::MC_MOUSE_BUTTON) && subtype == int(MessageSubtype::MS_LBUTTON_DOWN));
	}
	_H3API_ BOOL H3Msg::IsRightClick() const
	{
		return (command == int(MessageCommand::MC_MOUSE_BUTTON) && subtype == int(MessageSubtype::MS_RBUTTON_DOWN));
	}
	_H3API_ BOOL H3Msg::ClickOutside() const
	{
		return command == int(MessageCommand::MC_RCLICK_OUTSIDE) || command == int(MessageCommand::MC_LCLICK_OUTSIDE);
	}
	_H3API_ INT32 H3Msg::CloseDialog()
	{
		return STDCALL_1(INT32, 0x491640, this);
	}
	_H3API_ H3Msg::MessageFlag H3Msg::GetFlag() const
	{
		return MessageFlag(flags);
	}
	_H3API_ NH3VKey::eVirtualKeys H3Msg::GetKey() const
	{
		return NH3VKey::eVirtualKeys(subtype);
	}
	_H3API_ INT H3Msg::GetX() const
	{
		return x_abs;
	}
	_H3API_ INT H3Msg::GetY() const
	{
		return y_abs;
	}
	_H3API_ POINT H3Msg::GetCoords() const
	{
		POINT pt;
		pt.x = x_abs;
		pt.y = y_abs;
		return pt;
	}
	_H3API_ H3Dlg* H3Msg::GetDlg() const
	{
		return reinterpret_cast<H3Dlg*>(flags2);
	}
	_H3API_ INT H3Msg::StopProcessing()
	{
		command = 0;
		subtype = 0;
		return 2;
	}

	_H3API_ INT H3Dlg::CheckEnd(H3Msg & msg)
	{
		if (endDialog)
			return msg.CloseDialog();
		return 0;
	}
	_H3API_ H3Dlg::H3Dlg(int width, int height, int x, int y, BOOL statusBar, BOOL makeBackground, INT32 colorIndex) :
		H3BaseDlg(x, y, width, height), endDialog(FALSE), background(nullptr), hintBar(nullptr)
	{
		STDCALL_0(VOID, 0x597AA0); // stop video animation
		if (x == -1)
			xDlg = (H3Internal::_gameWidth() - width) >> 1;
		if (y == -1)
			yDlg = (H3Internal::_gameHeight() - height) >> 1;

		if (makeBackground)
			AddBackground(TRUE, statusBar, colorIndex);
		if (statusBar)
			hintBar = CreateHint();
	}
	_H3API_ H3Dlg::~H3Dlg()
	{
		vDestroy();
		STDCALL_0(VOID, 0x597B50); // resume video animation
	}
	_H3API_ VOID H3Dlg::PlaceAtMouse()
	{
		int x, y;
		F_GetCursorPosition(x, y);

		// adjust x & y to make certain the dialog will fit
		x = std::min(x, H3Internal::_gameWidth() - widthDlg - 200); // 200 is width of adventure bar on right
		y = std::min(y, H3Internal::_gameHeight() - heightDlg - 48); // 48 is height of resource bar on bottom
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;

		xDlg = x;
		yDlg = y;
	}
	_H3API_ VOID H3Dlg::Start()
	{
		if (!OnCreate())
			return;

		H3MouseManager* mmgr = H3Internal::_mouseManager();
		const INT32 mouseType = mmgr->GetType();
		const INT32 mouseFrame = mmgr->GetFrame();
		mmgr->DefaultCursor();
		vShowAndRun(FALSE);
		mmgr->SetCursor(mouseFrame, mouseType); // restore previous cursor
	}
	_H3API_ VOID H3Dlg::Stop()
	{
		endDialog = TRUE;
	}
	_H3API_ VOID H3Dlg::RMB_Show()
	{
		THISCALL_1(VOID, 0x5F4B90, this);
	}
	_H3API_ BOOL H3Dlg::AddBackground(INT32 x, INT32 y, INT32 w, INT32 h, BOOL frame, BOOL statusBar, INT32 colorIndex, BOOL is_blue)
	{
		if (this->background)
			return FALSE;

		if (frame && (w < 64 || h < 64))
			return FALSE;

		H3LoadedPcx16* pcx = H3LoadedPcx16::Create(h3_NullString, widthDlg, heightDlg);
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
	_H3API_ BOOL H3Dlg::AddBackground(BOOL frame, BOOL statusBar, INT32 colorIndex)
	{
		return AddBackground(0, 0, widthDlg, heightDlg, frame, statusBar, colorIndex);
	}
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedPcx* pcx)
	{
		if (!pcx || background)
			return FALSE;
		background = H3LoadedPcx16::Create(h3_NullString, pcx->width, pcx->height);
		if (!background)
			return FALSE;

		pcx->DrawToPcx16(0, 0, pcx->width, pcx->height, background, 0, 0, FALSE);

		H3DlgPcx16* bg = H3DlgPcx16::Create(0, 0, pcx->width, pcx->height, 0, nullptr);
		if (!bg)
		{
			background->Destroy();
			background = nullptr;
			return FALSE;
		}
		bg->SetPcx(background);
		AddItem(bg);

		return TRUE;
	}
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedPcx16* pcx)
	{
		if (!pcx || background)
			return FALSE;
		background = H3LoadedPcx16::Create(h3_NullString, pcx->width, pcx->height);
		if (!background)
			return FALSE;

		pcx->DrawToPcx16(0, 0, FALSE, background);

		H3DlgPcx16* bg = H3DlgPcx16::Create(0, 0, pcx->width, pcx->height, 0, nullptr);
		if (!bg)
		{
			background->Destroy();
			background = nullptr;
			return FALSE;
		}
		bg->SetPcx(background);
		AddItem(bg);

		return TRUE;
	}
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedPcx24* pcx)
	{
		if (!pcx || background)
			return FALSE;

		background = H3LoadedPcx16::Create(h3_NullString, pcx->width, pcx->height);
		if (!background)
			return FALSE;

		pcx->DrawToPcx16(0, 0, background);

		H3DlgPcx16* bg = H3DlgPcx16::Create(0, 0, pcx->width, pcx->height, 0, nullptr);
		if (!bg)
		{
			background->Destroy();
			background = nullptr;
			return FALSE;
		}
		bg->SetPcx(background);
		AddItem(bg);

		return TRUE;
	}
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedDef* def, INT group, INT frame)
	{
		if (background || !def || def->groupsCount < group || !def->activeGroups[group])
			return FALSE;
		H3DefGroup* grp = def->groups[group];
		if (grp->count < frame)
			return FALSE;

		H3DefFrame* fr = grp->frames[frame];

		background = H3LoadedPcx16::Create(h3_NullString, fr->frameWidth, fr->frameHeight);
		if (!background)
			return FALSE;

		fr->DrawToPcx16(0, 0, fr->frameWidth, fr->frameHeight, background, 0, 0, def->palette565);

		H3DlgPcx16* bg = H3DlgPcx16::Create(0, 0, fr->frameWidth, fr->frameHeight, 0, nullptr);
		if (!bg)
		{
			background->Destroy();
			background = nullptr;
			return FALSE;
		}
		bg->SetPcx(background);
		AddItem(bg);

		return TRUE;
	}

	_H3API_ BOOL H3Dlg::Notify(H3DlgItem * it, H3Msg & msg)
	{
		return OnNotify(it, msg);
	}

	_H3API_ VOID H3BaseDlg::Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy)
	{
		H3Internal::_windowManager()->H3Redraw(xDlg + x, yDlg + y, dx, dy);
	}
	_H3API_ VOID H3BaseDlg::Redraw()
	{
		vRedraw(TRUE, -65535, 65535);
	}
	_H3API_ INT32 H3BaseDlg::DefaultProc(H3Msg* msg)
	{
		return DefaultProc(*msg);
	}
	_H3API_ INT32 H3BaseDlg::DefaultProc(H3Msg& msg)
	{
		return THISCALL_2(INT32, 0x41B120, this, &msg);
	}
	_H3API_ H3Dlg* H3Dlg::vDestroy()
	{
		THISCALL_1(VOID, 0x41B080, this);
		return this;
	}

	_H3API_ INT H3Dlg::vShow(INT zorder, BOOL8 draw)
	{
		return THISCALL_3(INT, 0x5FF0A0, this, zorder, draw);
	}

	_H3API_ INT H3Dlg::vHide(BOOL8 redrawScreen)
	{
		return THISCALL_2(INT, 0x5FF220, this, redrawScreen);
	}

	_H3API_ INT H3Dlg::vPreProcess(H3Msg & msg)
	{
		return vDialogProc(msg);
	}

	_H3API_ VOID H3Dlg::vParentActivate_10(H3DlgItem* unknown)
	{
	}

	_H3API_ BOOL8 H3Dlg::vRedraw(BOOL8 redrawScreen, INT32 minItemId, INT32 maxItemId)
	{
		return THISCALL_4(BOOL8, 0x5FF5E0, this, redrawScreen, minItemId, maxItemId);
	}

	_H3API_ INT H3Dlg::vShowAndRun(BOOL8 fadeIn)
	{
		return THISCALL_2(INT, 0x5FFA20, this, fadeIn);
	}

	_H3API_ INT H3Dlg::vInitiateItems()
	{
		return THISCALL_1(INT, 0x5FFB30, this);
	}

	_H3API_ INT H3Dlg::vActivateItems(BOOL8 increase)
	{
		return THISCALL_2(INT, 0x5FFBB0, this, increase);
	}

	_H3API_ BOOL8 H3Dlg::vOnMouseMove(INT32 x, INT32 y)
	{
		return THISCALL_3(BOOL8, 0x5FFCA0, this, x, y);
	}

	_H3API_ BOOL8 H3Dlg::vOnRightClick(INT32 id)
	{
		return THISCALL_2(BOOL8, 0x5FFD50, this, id);
	}

	_H3API_ BOOL8 H3Dlg::vOnLeftClick(INT32 id, BOOL8 & closeDialog)
	{
		closeDialog = FALSE;
		return FALSE; // same as original function 0x5FFE90
	}

	_H3API_ H3DlgTextPcx* H3Dlg::vGetStatusBar()
	{
		return nullptr; // same as original 0x4842C0
	}

	_H3API_ INT H3Dlg::vEndDialogOnTimeExpired(H3Msg & msg)
	{
		return THISCALL_2(INT, 0x41B0F0, this, &msg);
	}

	_H3API_ H3DlgItem * H3BaseDlg::getDlgItem(UINT16 id, h3func vtable) const
	{
		H3DlgItem* it = firstItem;
		if (it == nullptr)
			return it;
		do
		{
			if ((it->GetID() == id) && (*reinterpret_cast<h3func*>(it) == vtable))
				break;
		} while (it = it->GetNextItem());

		return it;
	}

	_H3API_ H3BaseDlg::H3BaseDlg(INT x, INT y, INT w, INT h) :
		H3BasicDlg(x, y, w, h), lastHintShowed(-1),
		messageCommand(512), messageSubtype(10), messageItemId(30721), networkGame(FALSE)
	{
		struct unkNetwork
		{
			h3unk _f_00[240];
			BYTE* data;
		};
		if (IntAt(0x69959C))
		{
			unkNetwork* net = *(unkNetwork**)0x69D858;
			if (net->data)
			{
				if (net->data[4])
					networkGame = TRUE;
				net->data[4] = 1;
			}
		}
	}

	_H3API_ INT32 H3BasicDlg::GetWidth() const
	{
		return widthDlg;
	}
	_H3API_ INT32 H3BasicDlg::GetHeight() const
	{
		return heightDlg;
	}
	_H3API_ INT32 H3BasicDlg::GetX() const
	{
		return xDlg;
	}
	_H3API_ INT32 H3BasicDlg::GetY() const
	{
		return yDlg;
	}
	_H3API_ BOOL H3BasicDlg::IsTopDialog() const
	{
		return nextDialog == nullptr;
	}
	_H3API_ H3DlgItem* H3BasicDlg::AddItem(H3DlgItem* item, BOOL initiate /*= TRUE*/)
	{
		dlgItems += item;
		if (initiate)
			return THISCALL_3(H3DlgItem*, 0x5FF270, this, item, -1); // LoadItem
		else
			return item;
	}

	_H3API_ H3DlgDef* H3BaseDlg::GetDef(UINT16 id) const
	{
		return reinterpret_cast<H3DlgDef*>(getDlgItem(id, H3DlgItem::VT_DLGDEF));
	}

	_H3API_ H3DlgPcx * H3BaseDlg::GetPcx(UINT16 id) const
	{
		return reinterpret_cast<H3DlgPcx*>(getDlgItem(id, H3DlgItem::VT_DLGPCX));
	}

	_H3API_ H3DlgEdit * H3BaseDlg::GetEdit(UINT16 id) const
	{
		return reinterpret_cast<H3DlgEdit*>(getDlgItem(id, H3DlgItem::VT_DLGEDIT));
	}

	_H3API_ H3DlgText * H3BaseDlg::GetText(UINT16 id) const
	{
		return reinterpret_cast<H3DlgText*>(getDlgItem(id, H3DlgItem::VT_DLGTEXT));
	}

	_H3API_ H3DlgFrame * H3BaseDlg::GetFrame(UINT16 id) const
	{
		return reinterpret_cast<H3DlgFrame*>(getDlgItem(id, H3DlgItem::VT_DLGFRAME));
	}

	_H3API_ H3DlgPcx16 * H3BaseDlg::GetPcx16(UINT16 id) const
	{
		return reinterpret_cast<H3DlgPcx16*>(getDlgItem(id, H3DlgItem::VT_DLGPCX16));
	}

	_H3API_ H3DlgTextPcx * H3BaseDlg::GetTextPcx(UINT16 id) const
	{
		return reinterpret_cast<H3DlgTextPcx*>(getDlgItem(id, H3DlgItem::VT_DLGTEXTPCX));
	}

	_H3API_ H3DlgDefButton * H3BaseDlg::GetDefButton(UINT16 id) const
	{
		return reinterpret_cast<H3DlgDefButton*>(getDlgItem(id, H3DlgItem::VT_DLGDEFBUTTON));
	}

	_H3API_ H3DlgScrollbar * H3BaseDlg::GetScrollbar(UINT16 id) const
	{
		return reinterpret_cast<H3DlgScrollbar*>(getDlgItem(id, H3DlgItem::VT_DLGSCROLLBAR));
	}

	_H3API_ H3DlgTransparentItem * H3BaseDlg::GetTransparent(UINT16 id) const
	{
		return reinterpret_cast<H3DlgTransparentItem*>(getDlgItem(id, H3DlgItem::VT_DLGITEM));
	}

	_H3API_ H3DlgCustomButton * H3BaseDlg::GetCustomButton(UINT16 id) const
	{
		return reinterpret_cast<H3DlgCustomButton*>(getDlgItem(id, H3DlgItem::VT_DLGCUSTOMBUTTOM));
	}

	_H3API_ H3DlgCaptionButton * H3BaseDlg::GetCaptionButton(UINT16 id) const
	{
		return reinterpret_cast<H3DlgCaptionButton*>(getDlgItem(id, H3DlgItem::VT_DLGCAPTIONBUTTON));
	}

	_H3API_ H3DlgScrollableText * H3BaseDlg::GetScrollabaleText(UINT16 id) const
	{
		return reinterpret_cast<H3DlgScrollableText*>(getDlgItem(id, H3DlgItem::VT_DLGSCROLLTEXT));
	}

	_H3API_ H3DlgTransparentItem * H3BaseDlg::CreateHidden(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id)
	{
		H3DlgTransparentItem* it = H3DlgTransparentItem::Create(x, y, width, height, id);
		if (it)
			AddItem(it);
		return it;
	}
	_H3API_ H3LoadedPcx16* H3Dlg::GetBackgroundPcx() const
	{
		return background;
	}
	_H3API_ BOOL H3Dlg::BackgroundRegion(INT32 xStart, INT32 yStart, INT32 w, INT32 h, BOOL is_blue)
	{
		if (!background || w <= 0 || h <= 0)
			return FALSE;
		return background->BackgroundRegion(xStart, yStart, w, h, is_blue);
	}
	_H3API_ BOOL H3Dlg::SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPcx16* destination)
	{
		H3LoadedPcx16* target = destination ? destination : background;
		if (!target)
			return FALSE;
		return target->SimpleFrameRegion(xStart, yStart, _width, _height);
	}
	_H3API_ BOOL H3Dlg::FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue)
	{
		if (!background)
			return FALSE;
		if (w < 64 || h < 64)
			return FALSE;
		return background->FrameRegion(x, y, w, h, statusBar, colorIndex, is_blue);
	}
	_H3API_ H3LoadedPcx16* H3BaseDlg::GetCurrentPcx()
	{
		return pcx16;
	}
	_H3API_ H3DlgItem* H3BaseDlg::ItemAtPosition(H3Msg* msg)
	{
		return ItemAtPosition(*msg);
	}
	_H3API_ H3DlgItem* H3BaseDlg::ItemAtPosition(H3Msg& msg)
	{
		return THISCALL_3(H3DlgItem*, 0x5FF9A0, this, msg.x_abs, msg.y_abs);
	}
	_H3API_ H3Vector<H3DlgItem*>& H3BaseDlg::GetList()
	{
		return dlgItems;
	}
	_H3API_ H3DlgHintBar* H3Dlg::GetHintBar()
	{
		return hintBar;
	}
	_H3API_ H3DlgItem* H3BaseDlg::GetH3DlgItem(UINT16 id)
	{
		return THISCALL_2(H3DlgItem*, 0x5FF5B0, this, id);
	}
	_H3API_ VOID H3BaseDlg::RedrawItem(UINT16 itemID)
	{
		if (H3DlgItem* it = GetH3DlgItem(itemID))
			it->Refresh();
	}
	_H3API_ VOID H3BaseDlg::EnableItem(UINT16 id, BOOL enable)
	{
		H3DlgItem* it = GetH3DlgItem(id);
		if (it)
			it->EnableItem(enable);
	}
	_H3API_ VOID H3BaseDlg::SendCommandToItem(INT32 command, UINT16 itemID, UINT32 parameter)
	{
		THISCALL_5(VOID, 0x5FF400, this, 0x200, command, itemID, parameter);
	}
	_H3API_ VOID H3BaseDlg::SendCommandToAllItems(INT32 command, INT32 itemID, INT32 parameter)
	{
		H3Msg msg;
		msg.SetCommand(0x200, command, itemID, 0, 0, 0, parameter, 0);
		THISCALL_2(VOID, 0x5FF3A0, this, &msg);
	}
	_H3API_ VOID H3BaseDlg::AdjustToPlayerColor(INT8 player, UINT16 itemId)
	{
		if (H3DlgItem* it = GetH3DlgItem(itemId))
			it->ColorToPlayer(player);
	}
	_H3API_ H3DlgFrame* H3BaseDlg::CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color)
	{
		H3DlgFrame* frame = H3DlgFrame::Create(x, y, width, height, id, color);
		if (frame)
			AddItem(frame);
		return frame;
	}
	_H3API_ H3DlgFrame* H3BaseDlg::CreateFrame(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color)
	{
		H3DlgFrame* frame = H3DlgFrame::Create(x, y, width, height, 0, color);
		if (frame)
			AddItem(frame);
		return frame;
	}
	_H3API_ H3DlgFrame* H3BaseDlg::CreateFrame(H3DlgItem* target, RGB565 color, INT id, BOOL around_edge)
	{
		H3DlgFrame* frame = H3DlgFrame::Create(target, color, id, around_edge);
		if (frame)
			AddItem(frame);
		return frame;
	}
	_H3API_ H3DlgDef* H3BaseDlg::CreateDef(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
	{
		H3DlgDef* def = H3DlgDef::Create(x, y, width, height, id, defName, frame, group, mirror, closeDialog);
		if (def)
			AddItem(def);
		return def;
	}
	_H3API_ H3DlgDef* H3BaseDlg::CreateDef(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
	{
		H3DlgDef* def = H3DlgDef::Create(x, y, id, defName, frame, group, mirror, closeDialog);
		if (def)
			AddItem(def);
		return def;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
	{
		H3DlgDefButton* but = H3DlgDefButton::Create(x, y, width, height, id, defName, frame, clickFrame, closeDialog, hotkey);
		if (but)
			AddItem(but);
		return but;
	}
	_H3API_ H3DlgDefButton * H3BaseDlg::CreateButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
	{
		H3DlgDefButton* but = CreateButton(x, y, 0, 0, id, defName, frame, clickFrame, closeDialog, hotkey);
		if (but)
		{
			H3LoadedDef* def = but->GetDef();
			if (def)
			{
				but->SetWidth(def->widthDEF);
				but->SetHeight(def->heightDEF);
			}
		}
		return but;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateOKButton(INT32 x, INT32 y)
	{
		H3DlgDefButton* button = H3DlgDefButton::Create(x, y, int(H3Msg::ItemIDs::ID_OK), NH3Dlg::Assets::OKAY_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
		if (button)
		{
			AddItem(H3DlgPcx::Create(x - 1, y - 1, NH3Dlg::Assets::BOX_64_30_PCX));
			AddItem(button);
		}
		return button;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateSaveButton(INT32 x, INT32 y)
	{
		H3DlgDefButton* button = H3DlgDefButton::Create(x, y, int(H3Msg::ItemIDs::ID_SAVE), NH3Dlg::Assets::iSAVE_DEF, 0, 1, FALSE, NH3VKey::H3VK_S);
		if (button)
		{
			AddItem(H3DlgPcx::Create(x - 1, y - 1, NH3Dlg::Assets::BOX_64_32_PCX));
			AddItem(button);
		}
		return button;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateOnOffCheckbox(INT32 x, INT32 y, INT32 id, INT32 frame, INT32 clickFrame)
	{
		H3DlgDefButton* button = H3DlgDefButton::Create(x, y, id, NH3Dlg::Assets::ON_OFF_CHECKBOX, frame, clickFrame, 0, 0);
		if (button)
			AddItem(button);
		return button;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateOKButton()
	{
		H3DlgDefButton* button = H3DlgDefButton::Create(25, heightDlg - 50, int(H3Msg::ItemIDs::ID_OK), NH3Dlg::Assets::OKAY_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
		if (button)
		{
			AddItem(H3DlgPcx::Create(25 - 1, heightDlg - 50 - 1, NH3Dlg::Assets::BOX_64_30_PCX));
			AddItem(button);
		}
		return button;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateOK32Button(INT32 x, INT32 y)
	{
		H3DlgDefButton* button = H3DlgDefButton::Create(x, y, int(H3Msg::ItemIDs::ID_OK), NH3Dlg::Assets::OKAY32_DEF, 0, 1, TRUE, NH3VKey::H3VK_ENTER);
		if (button)
		{
			AddItem(H3DlgPcx::Create(x - 1, y - 1, NH3Dlg::Assets::BOX_66_32_PCX));
			AddItem(button);
		}
		return button;
	}
	_H3API_ H3DlgDefButton* H3BaseDlg::CreateCancelButton()
	{
		H3DlgDefButton* button = H3DlgDefButton::Create(widthDlg - 25 - 64, heightDlg - 50, int(H3Msg::ItemIDs::ID_CANCEL), NH3Dlg::Assets::CANCEL_DEF, 0, 1, TRUE, NH3VKey::H3VK_ESCAPE);
		if (button)
		{
			AddItem(H3DlgPcx::Create(widthDlg - 25 - 1 - 64, heightDlg - 50 - 1, NH3Dlg::Assets::BOX_64_30_PCX));
			AddItem(button);
		}
		return button;
	}
	_H3API_ H3DlgCaptionButton* H3BaseDlg::CreateCaptionButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
	{
		H3DlgCaptionButton* but = H3DlgCaptionButton::Create(x, y, width, height, id, defName, text, font, frame, group, closeDialog, hotkey, color);
		if (but)
			AddItem(but);
		return but;
	}
	_H3API_ H3DlgCustomButton* H3BaseDlg::CreateCustomButton(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
	{
		H3DlgCustomButton* but = H3DlgCustomButton::Create(x, y, width, height, id, defName, customProc, frame, clickFrame);
		if (but)
			AddItem(but);
		return but;
	}
	_H3API_ H3DlgCustomButton* H3BaseDlg::CreateCustomButton(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
	{
		H3DlgCustomButton* but = H3DlgCustomButton::Create(x, y, id, defName, customProc, frame, clickFrame);
		if (but)
			AddItem(but);
		return but;
	}
	_H3API_ H3DlgCustomButton* H3BaseDlg::CreateCustomButton(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
	{
		return CreateCustomButton(x, y, 0, defName, customProc, frame, clickFrame);
	}
	_H3API_ H3DlgPcx* H3BaseDlg::CreatePcx(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx* pcx = H3DlgPcx::Create(x, y, width, height, id, pcxName);
		if (pcx)
			AddItem(pcx);
		return pcx;
	}
	_H3API_ H3DlgPcx * H3BaseDlg::CreatePcx(INT32 x, INT32 y, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx* pcx = CreatePcx(x, y, 0, 0, id, pcxName);
		if (pcx && pcx->GetPcx())
		{
			H3LoadedPcx* p = pcx->GetPcx();
			pcx->SetWidth(p->width);
			pcx->SetHeight(p->height);
		}
		return pcx;
	}
	_H3API_ H3DlgPcx* H3BaseDlg::CreateLineSeparator(INT32 x, INT32 y, INT32 width)
	{
		return CreatePcx(x, y, width, 2, 0, NH3Dlg::HDassets::LINE_SEPARATOR);
	}
	_H3API_ H3DlgPcx16* H3BaseDlg::CreatePcx16(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx16* pcx = H3DlgPcx16::Create(x, y, width, height, id, pcxName);
		if (pcx)
			AddItem(pcx);
		return pcx;
	}
	_H3API_ H3DlgEdit* H3BaseDlg::CreateEdit(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY)
	{
		H3DlgEdit* ed = H3DlgEdit::Create(x, y, width, height, maxLength, text, fontName, color, align, pcxName, id, hasBorder, borderX, borderY);
		if (ed)
			AddItem(ed);
		return ed;
	}
	_H3API_ H3DlgText* H3BaseDlg::CreateText(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, INT32 color, INT32 id, INT32 align, INT32 bkColor)
	{
		H3DlgText* tx = H3DlgText::Create(x, y, width, height, text, fontName, color, id, align, bkColor);
		if (tx)
			AddItem(tx);
		return tx;
	}
	_H3API_ BOOL H3Dlg::CreateBlackBox(INT32 x, INT32 y, INT32 width, INT32 height)
	{
		if (!background)
			return FALSE;

		background->FillRectangle(x, y, width, height, 0, 0, 0);
		return TRUE;
	}
	_H3API_ H3DlgHintBar* H3Dlg::CreateHint()
	{
		H3DlgHintBar* h = H3DlgHintBar::Create(this);
		if (h)
			AddItem(h);
		return h;
	}
	_H3API_ H3DlgHintBar * H3Dlg::CreateHint(INT32 x, INT32 y, INT32 width, INT32 height)
	{
		H3DlgHintBar* h = H3DlgHintBar::Create(this, x, y, width, height);
		if (h)
			AddItem(h);
		return h;
	}
	_H3API_ H3DlgTextPcx* H3BaseDlg::CreateTextPcx(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id, INT32 align)
	{
		H3DlgTextPcx* tx = H3DlgTextPcx::Create(x, y, width, height, text, fontName, pcxName, color, id, align);
		if (tx)
			AddItem(tx);
		return tx;
	}
	_H3API_ H3DlgScrollableText* H3BaseDlg::CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR font, INT32 color, INT32 isBlue)
	{
		H3DlgScrollableText* sc = H3DlgScrollableText::Create(text, x, y, width, height, font, color, isBlue);
		if (sc)
			AddItem(sc);
		return sc;
	}
	_H3API_ H3DlgScrollbar* H3BaseDlg::CreateScrollbar(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled)
	{
		H3DlgScrollbar* sc = H3DlgScrollbar::Create(x, y, width, height, id, ticksCount, scrollbarProc, isBlue, stepSize, arrowsEnabled);
		if (sc)
			AddItem(sc);
		return sc;
	}

	_H3API_ H3DlgTransparentItem* H3DlgTransparentItem::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id)
	{
		H3DlgTransparentItem* d = (H3DlgTransparentItem*)F_malloc(sizeof(H3DlgTransparentItem));
		if (d)
			THISCALL_7(H3DlgTransparentItem*, 0x44FBE0, d, x, y, width, height, id, 1);
		return d;
	}

	_H3API_ BOOL H3DlgItem::NotifyParent(H3Msg & msg)
	{
		return reinterpret_cast<H3Dlg*>(parent)->Notify(this, msg);
	}
	_H3API_ BOOL H3DlgItem::TranslateUnprocessedMessage(H3Msg & msg)
	{
		switch (msg.command)
		{
		case H3Msg::MC_WHEEL_BUTTON:
			if (msg.subtype != H3Msg::MS_MOUSE_WHEEL_BUTTON_DOWN || msg.subtype != H3Msg::MS_MOUSE_WHEEL_BUTTON_UP)
				break;
			/* fall through */
		case H3Msg::MC_MOUSE_WHEEL:
		{
			if (deactivatesCount > 0)
				break;
			if (!IsActive())
				break;
			const int x = msg.GetX() - parent->GetX();
			const int y = msg.GetY() - parent->GetY();
			if ((x < GetX()) || (y < GetY()) || (x >= GetX() + GetWidth()) || (y >= GetY() + GetHeight()))
				break;
			return NotifyParent(msg);
		}
		default:
			break;
		}
		return FALSE;
	}

	_H3API_ VOID H3DlgItem::EnableItem(BOOL enable)
	{
		vEnable(enable);
	}
	_H3API_ VOID H3DlgItem::Enable()
	{
		EnableItem(TRUE);
	}
	_H3API_ VOID H3DlgItem::Disable()
	{
		EnableItem(FALSE);
	}
	_H3API_ INT16 H3DlgItem::GetX() const
	{
		return xPos;
	}
	_H3API_ INT16 H3DlgItem::GetY() const
	{
		return yPos;
	}
	_H3API_ INT32 H3DlgItem::GetAbsoluteX() const
	{
		return xPos + parent->GetX();
	}
	_H3API_ INT32 H3DlgItem::GetAbsoluteY() const
	{
		return yPos + parent->GetY();
	}
	_H3API_ BOOL H3DlgItem::IsEnabled() const
	{
		return !(state & 0x20);
	}
	_H3API_ BOOL H3DlgItem::IsActive() const
	{
		return state & 2;
	}
	_H3API_ VOID H3DlgItem::SetX(UINT16 x)
	{
		xPos = x;
	}
	_H3API_ VOID H3DlgItem::SetY(UINT16 y)
	{
		yPos = y;
	}
	_H3API_ INT32 H3DlgItem::GetHeight() const
	{
		return heightItem;
	}
	_H3API_ INT32 H3DlgItem::GetWidth() const
	{
		return widthItem;
	}
	_H3API_ VOID H3DlgItem::SetWidth(UINT16 w)
	{
		widthItem = w;
	}
	_H3API_ VOID H3DlgItem::SetHeight(UINT16 h)
	{
		heightItem = h;
	}
	_H3API_ VOID H3DlgItem::Draw()
	{
		vDrawToWindow();
	}
	_H3API_ VOID H3DlgItem::Refresh()
	{
		parent->Redraw(xPos, yPos, widthItem, heightItem);
	}
	_H3API_ H3DlgItem * H3DlgItem::Hide()
	{
		state &= ~4;
		return this;
	}
	_H3API_ VOID H3DlgItem::HideDeactivate()
	{
		state &= ~6;
	}
	_H3API_ VOID H3DlgItem::ShowActivate()
	{
		state |= 6;
	}
	_H3API_ H3DlgItem * H3DlgItem::Show()
	{
		state |= 4;
		return this;
	}
	_H3API_ VOID H3DlgItem::Shade()
	{
		state |= 8;
	}
	_H3API_ VOID H3DlgItem::UnShade()
	{
		state &= ~8;
	}
	_H3API_ H3DlgItem * H3DlgItem::Activate()
	{
		state |= 2;
		return this;
	}
	_H3API_ H3DlgItem * H3DlgItem::DeActivate()
	{
		state &= ~2;
		return this;
	}
	_H3API_ BOOL H3DlgItem::IsVisible() const
	{
		return state & 4;
	}
	_H3API_ LPCSTR H3DlgItem::GetHint() const
	{
		return hint;
	}
	_H3API_ VOID H3DlgItem::SetHint(LPCSTR msg)
	{
		hint = msg;
	}
	_H3API_ UINT16 H3DlgItem::GetID() const
	{
		return id;
	}
	_H3API_ VOID H3DlgItem::ParentRedraw()
	{
		parent->Redraw(xPos, yPos, widthItem, heightItem);
	}
	_H3API_ VOID H3DlgItem::ColorToPlayer(INT8 player)
	{
		THISCALL_2(VOID, 0x4501D0, this, player);
	}
	_H3API_ VOID H3DlgItem::SendCommand(INT32 command, INT32 parameter)
	{
		THISCALL_3(VOID, 0x5FED80, this, command, parameter);
	}
	_H3API_ VOID H3DlgItem::SetHints(LPCSTR shortTipText, LPCSTR rightClickHint, BOOL allocateMemory)
	{
		THISCALL_4(void, 0x5FEE00, this, shortTipText, rightClickHint, allocateMemory);
	}
	_H3API_ VOID H3DlgItem::DrawTempFrame(INT thickness, BYTE r, BYTE g, BYTE b) const
	{
		H3LoadedPcx16* pcx = H3Internal::_windowManager()->GetDrawBuffer();
		if (!pcx)
			return;
		pcx->DrawThickFrame(GetAbsoluteX(), GetAbsoluteY(), GetWidth(), GetHeight(), thickness, r, g, b);
	}
	_H3API_ VOID H3DlgItem::DrawTempFrame(INT thickness, const H3RGB888 & color) const
	{
		DrawTempFrame(thickness, color.r, color.g, color.b);
	}
	_H3API_ H3BaseDlg * H3DlgItem::GetParent() const
	{
		return parent;
	}
	_H3API_ H3DlgItem * H3DlgItem::GetNextItem() const
	{
		return nextDlgItem;
	}
	_H3API_ H3DlgItem * H3DlgItem::GetPreviousItem() const
	{
		return previousDlgItem;
	}
	_H3API_ H3DlgFrame* H3DlgItem::CastFrame()
	{
		return (H3DlgFrame*)this;
	}
	_H3API_ H3DlgDef* H3DlgItem::CastDef()
	{
		return (H3DlgDef*)this;
	}
	_H3API_ H3DlgDefButton* H3DlgItem::CastDefButton()
	{
		return (H3DlgDefButton*)this;
	}
	_H3API_ H3DlgCaptionButton* H3DlgItem::CastDefButtonCaption()
	{
		return (H3DlgCaptionButton*)this;
	}
	_H3API_ H3DlgCustomButton* H3DlgItem::CastCustomButton()
	{
		return (H3DlgCustomButton*)this;
	}
	_H3API_ H3DlgPcx* H3DlgItem::CastPcx()
	{
		return (H3DlgPcx*)this;
	}
	_H3API_ H3DlgPcx16* H3DlgItem::CastPcx16()
	{
		return (H3DlgPcx16*)this;
	}
	_H3API_ H3DlgEdit* H3DlgItem::CastEdit()
	{
		return (H3DlgEdit*)this;
	}
	_H3API_ H3DlgText* H3DlgItem::CastText()
	{
		return (H3DlgText*)this;
	}
	_H3API_ H3DlgTextPcx* H3DlgItem::CastTextPcx()
	{
		return (H3DlgTextPcx*)this;
	}
	_H3API_ H3DlgHintBar* H3DlgItem::CastHintBar()
	{
		return (H3DlgHintBar*)this;
	}
	_H3API_ H3DlgScrollableText* H3DlgItem::CastScrollText()
	{
		return (H3DlgScrollableText*)this;
	}
	_H3API_ H3DlgScrollbar* H3DlgItem::CastScrollbar()
	{
		return (H3DlgScrollbar*)this;
	}
	_H3API_ H3DlgFrame* H3DlgFrame::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, RGB565 color)
	{
		H3DlgFrame* f = (H3DlgFrame*)F_malloc(sizeof(H3DlgFrame));
		if (f)
			THISCALL_8(H3DlgFrame*, 0x44FE00, f, x, y, width, height, id, color, 0x400);
		return f;
	}
	_H3API_ H3DlgFrame* H3DlgFrame::Create(INT32 x, INT32 y, INT32 width, INT32 height, RGB565 color)
	{
		return Create(x, y, width, height, 0, color);
	}
	_H3API_ H3DlgFrame* H3DlgFrame::Create(H3DlgItem* target, RGB565 color, INT id, BOOL around_edge)
	{
		if (!target)
			return nullptr;
		if (around_edge)
			return Create(target->GetX() - 1, target->GetY() - 1, target->GetWidth() + 2, target->GetHeight() + 2, id, color);
		else
			return Create(target->GetX(), target->GetY(), target->GetWidth(), target->GetHeight(), id, color);
	}
	_H3API_ VOID H3DlgFrame::ChangeColor(RGB565 color)
	{
		color565.SetBits(color);
	}
	_H3API_ VOID H3DlgFrame::HideHue()
	{
		changeHue = FALSE;
	}
	_H3API_ VOID H3DlgFrame::ShowHue()
	{
		changeHue = TRUE;
	}
	_H3API_ VOID H3DlgFrame::ToggleHue()
	{
		changeHue = !changeHue;
	}
	_H3API_ H3RGB565* H3DlgFrame::GetColor()
	{
		return &color565;
	}
	_H3API_ H3DlgDef* H3DlgDef::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 secondFrame, INT32 mirror, BOOL closeDialog)
	{
		H3DlgDef* d = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
		if (d)
			THISCALL_12(H3DlgDef*, 0x4EA800, d, x, y, width, height, id, defName, frame, secondFrame, mirror, closeDialog, 0x10);
		return d;
	}
	_H3API_ H3DlgDef* H3DlgDef::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 secondFrame, INT32 mirror, BOOL closeDialog)
	{
		H3DlgDef* d = Create(x, y, 0, 0, id, defName, frame, secondFrame, mirror, closeDialog);
		if (d && d->loadedDef)
		{
			d->widthItem = d->loadedDef->widthDEF;
			d->heightItem = d->loadedDef->heightDEF;
		}
		return d;
	}
	_H3API_ H3DlgDef* H3DlgDef::Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 group)
	{
		H3DlgDef* d = Create(x, y, 0, 0, 0, defName, frame, group, 0, 0);
		if (d && d->loadedDef)
		{
			d->widthItem = d->loadedDef->widthDEF;
			d->heightItem = d->loadedDef->heightDEF;
		}
		return d;
	}
	_H3API_ VOID H3DlgDef::SetFrame(INT32 frame)
	{
		defFrame = frame;
	}
	_H3API_ INT H3DlgDefButton::ToggleFrame()
	{
		defFrame = !defFrame; defFrameOnClick = !defFrameOnClick; return defFrame;
	}
	_H3API_ INT32 H3DlgDefButton::GetFrame() const
	{
		return defFrame;
	}
	_H3API_ INT32 H3DlgDefButton::GetClickFrame() const
	{
		return defFrameOnClick;
	}
	_H3API_ VOID H3DlgDefButton::ColorDefToPlayer(INT32 id)
	{
		loadedDef->ColorToPlayer(id);
	}
	_H3API_ INT32 H3DlgDef::GetFrame() const
	{
		return defFrame;
	}
	_H3API_ INT32 H3DlgDef::ToggleFrame()
	{
		std::swap(defFrame, secondFrame);
		return defFrame;
	}
	_H3API_ INT32 H3DlgDef::GetClickFrame() const
	{
		return secondFrame;
	}
	_H3API_ VOID H3DlgDef::SetClickFrame(INT32 clickFrame)
	{
		secondFrame = clickFrame;
	}
	_H3API_ VOID H3DlgDef::ColorDefToPlayer(INT32 id)
	{
		loadedDef->ColorToPlayer(id);
	}
	_H3API_	VOID H3DlgDefButton::SetFrame(INT32 frame)
	{
		defFrame = frame;
	}
	_H3API_ VOID H3DlgDefButton::SetClickFrame(INT32 clickFrame)
	{
		defFrameOnClick = clickFrame;
	}
	_H3API_ H3LoadedDef * H3DlgDefButton::GetDef()
	{
		return loadedDef;
	}
	_H3API_ VOID H3DlgDefButton::AddHotkey(INT32 key)
	{
		hotkeys.Add(key);
	}
	_H3API_ H3LoadedDef * H3DlgDef::GetDef()
	{
		return loadedDef;
	}
	_H3API_ H3DlgDefButton* H3DlgDefButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
	{
		H3DlgDefButton* b = (H3DlgDefButton*)F_malloc(sizeof(H3DlgDefButton));
		if (b)
			THISCALL_12(H3DlgDefButton*, 0x455BD0, b, x, y, width, height, id, defName, frame, clickFrame, closeDialog, hotkey, 2);
		return b;
	}
	_H3API_ H3DlgDefButton* H3DlgDefButton::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 clickFrame, BOOL closeDialog, INT32 hotkey)
	{
		H3DlgDefButton* b = Create(x, y, 0, 0, id, defName, frame, clickFrame, closeDialog, hotkey);
		if (b && b->loadedDef)
		{
			b->widthItem = b->loadedDef->widthDEF;
			b->heightItem = b->loadedDef->heightDEF;
		}
		return b;
	}
	_H3API_ H3DlgDefButton* H3DlgDefButton::Create(INT32 x, INT32 y, LPCSTR defName, INT32 frame, INT32 clickFrame)
	{
		return Create(x, y, 0, defName, frame, clickFrame, 0, 0);
	}

	_H3API_ H3DlgCaptionButton* H3DlgCaptionButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
	{
		H3DlgCaptionButton* b = (H3DlgCaptionButton*)F_malloc(sizeof(H3DlgCaptionButton));
		if (b)
			THISCALL_15(H3DlgCaptionButton*, 0x456730, b, x, y, width, height, id, defName, text, font, frame, group, closeDialog, hotkey, 2, color);
		return b;
	}
	_H3API_ H3DlgCaptionButton* H3DlgCaptionButton::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, LPCSTR text, LPCSTR font, INT32 frame, INT32 group, BOOL closeDialog, INT32 hotkey, INT32 color)
	{
		H3DlgCaptionButton* b = Create(x, y, 0, 0, id, defName, text, font, frame, group, closeDialog, hotkey, color);
		if (b && b->loadedDef)
		{
			b->widthItem = b->loadedDef->widthDEF;
			b->heightItem = b->loadedDef->heightDEF;
		}
		return b;
	}

	_H3API_ H3DlgCustomButton* H3DlgCustomButton::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
	{
		H3DlgCustomButton* b = (H3DlgCustomButton*)F_malloc(sizeof(H3DlgCustomButton));
		if (b)
			THISCALL_10(H3DlgCustomButton*, 0x456A10, b, x, y, width, height, id, defName, customProc, frame, clickFrame);
		return b;
	}
	_H3API_ H3DlgCustomButton* H3DlgCustomButton::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
	{
		H3DlgCustomButton* b = Create(x, y, 0, 0, id, defName, customProc, frame, clickFrame);
		if (b && b->loadedDef)
		{
			b->widthItem = b->loadedDef->widthDEF;
			b->heightItem = b->loadedDef->heightDEF;
		}
		return b;
	}
	_H3API_ H3DlgCustomButton* H3DlgCustomButton::Create(INT32 x, INT32 y, LPCSTR defName, H3DlgButton_proc customProc, INT32 frame, INT32 clickFrame)
	{
		return Create(x, y, 0, defName, customProc, frame, clickFrame);
	}
	_H3API_ VOID H3DlgCustomButton::ToggleFlag(BOOL& flag)
	{
		defFrame = !defFrame;
		defFrameOnClick = !defFrameOnClick;
		flag = !flag;
		Draw();
		Refresh();
	}
	_H3API_ H3DlgPcx* H3DlgPcx::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx* p = (H3DlgPcx*)F_malloc(sizeof(H3DlgPcx));
		if (p)
			THISCALL_8(H3DlgPcx*, 0x44FFA0, p, x, y, width, height, id, pcxName, 0x800);
		return p;
	}
	_H3API_ H3DlgPcx* H3DlgPcx::Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx* p = Create(x, y, 0, 0, id, pcxName);
		if (p && p->loadedPcx)
		{
			p->widthItem = p->loadedPcx->width;
			p->heightItem = p->loadedPcx->height;
		}
		return p;
	}
	_H3API_ H3DlgPcx* H3DlgPcx::Create(INT32 x, INT32 y, LPCSTR pcxName)
	{
		return Create(x, y, 0, pcxName);
	}
	_H3API_ VOID H3DlgPcx::SetPcx(H3LoadedPcx* pcx)
	{
		loadedPcx = pcx;
	}
	_H3API_ VOID H3DlgPcx::AdjustColor(INT player)
	{
		THISCALL_2(VOID, 0x4501D0, this, player);
	}
	_H3API_ H3LoadedPcx* H3DlgPcx::GetPcx()
	{
		return loadedPcx;
	}
	_H3API_ H3LoadedPcx* H3DlgPcx::GetPcx() const
	{
		return loadedPcx;
	}

	_H3API_ H3DlgPcx16* H3DlgPcx16::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx16* p = (H3DlgPcx16*)F_malloc(sizeof(H3DlgPcx16));
		if (p)
			THISCALL_8(H3DlgPcx16*, 0x450340, p, x, y, width, height, id, pcxName, 0x800);
		return p;
	}
	_H3API_ H3DlgPcx16* H3DlgPcx16::Create(INT32 x, INT32 y, INT32 id, LPCSTR pcxName)
	{
		H3DlgPcx16* p = Create(x, y, 0, 0, id, pcxName);
		if (p && p->loadedPcx16)
		{
			p->widthItem = p->loadedPcx16->width;
			p->heightItem = p->loadedPcx16->height;
		}
		return p;
	}
	_H3API_ H3DlgPcx16* H3DlgPcx16::Create(INT32 x, INT32 y, LPCSTR pcxName)
	{
		return Create(x, y, 0, 0, 0, pcxName);
	}
	_H3API_ VOID H3DlgPcx16::SetPcx(H3LoadedPcx16* pcx16)
	{
		loadedPcx16 = pcx16;
	}
	_H3API_ H3LoadedPcx16* H3DlgPcx16::GetPcx()
	{
		return loadedPcx16;
	}
	_H3API_ VOID H3DlgPcx16::SinkArea(INT32 x, INT32 y, INT32 w, INT32 h)
	{
		loadedPcx16->SinkArea(x, y, w, h);
	}
	_H3API_ VOID H3DlgPcx16::BevelArea(INT32 x, INT32 y, INT32 w, INT32 h)
	{
		loadedPcx16->BevelArea(x, y, w, h);
	}
	_H3API_ VOID H3DlgPcx16::SinkArea(H3DlgItem* it)
	{
		SinkArea(it->GetX() - 1, it->GetY() - 1, it->GetWidth() + 2, it->GetHeight() + 2);
	}
	_H3API_ VOID H3DlgPcx16::BevelArea(H3DlgItem* it)
	{
		BevelArea(it->GetX() - 1, it->GetY() - 1, it->GetWidth() + 2, it->GetHeight() + 2);
	}

	_H3API_ H3DlgEdit* H3DlgEdit::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 maxLength, LPCSTR text, LPCSTR fontName, INT32 color, INT32 align, LPCSTR pcxName, INT32 id, INT32 hasBorder, INT32 borderX, INT32 borderY)
	{
		H3DlgEdit* e = (H3DlgEdit*)F_malloc(sizeof(H3DlgEdit));
		if (e)
			THISCALL_17(H3DlgEdit*, 0x5BACD0, e, x, y, width, height, maxLength, text, fontName, color, align, pcxName, 0, id, 0, hasBorder, borderX, borderY);
		return e;
	}
	_H3API_ LPCSTR H3DlgEdit::GetText() const
	{
		return text.String();
	}
	_H3API_ H3String* H3DlgEdit::GetString()
	{
		return &text;
	}
	_H3API_ VOID H3DlgEdit::SetText(LPCSTR text)
	{
		vSetText(text);
	}
	_H3API_ VOID H3DlgEdit::DecreaseCaret()
	{
		if (caretPos > 0)
			--caretPos;
	}
	_H3API_ VOID H3DlgEdit::IncreaseCaret()
	{
		if (caretPos < text.Length())
			++caretPos;
	}
	_H3API_ UINT H3DlgEdit::GetCaret() const
	{
		return caretPos;
	}
	_H3API_ BOOL H3DlgEdit::SetCaret(UINT pos)
	{
		if (pos == caretPos || pos > text.Length())
			return FALSE;
		caretPos = pos;
		return TRUE;
	}
	_H3API_ VOID H3DlgEdit::SetAutoredraw(BOOL on)
	{
		autoRedraw = on;
	}
	_H3API_ VOID H3DlgEdit::SetFocus(BOOL on)
	{
		vSetFocus(on);
	}

	_H3API_ H3DlgText* H3DlgText::Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, INT32 color, INT32 id, INT32 align, INT32 bkColor)
	{
		H3DlgText* t = (H3DlgText*)F_malloc(sizeof(H3DlgText));
		if (t)
			THISCALL_12(H3DlgText*, 0x5BC6A0, t, x, y, width, height, text, fontName, color, id, align, bkColor, 8);
		return t;
	}
	_H3API_ H3String& H3DlgText::GetH3String()
	{
		return text;
	}
	_H3API_ VOID H3DlgText::SetText(LPCSTR text)
	{
		vSetText(text);
	}

	_H3API_ H3DlgTextPcx* H3DlgTextPcx::Create(INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 id, INT32 align)
	{
		H3DlgTextPcx* t = (H3DlgTextPcx*)F_malloc(sizeof(H3DlgTextPcx));
		if (t)
			THISCALL_12(H3DlgTextPcx*, 0x5BCB70, t, x, y, width, height, text, fontName, pcxName, color, id, align, 8);
		return t;
	}
	_H3API_ H3DlgTextPcx* H3DlgTextPcx::Create(INT32 x, INT32 y, LPCSTR text, LPCSTR fontName, LPCSTR pcxName, INT32 color, INT32 align)
	{
		H3DlgTextPcx* t = Create(x, y, 0, 0, text, fontName, pcxName, color, 0, align);
		if (t && t->loadedPcx)
		{
			t->widthItem = t->loadedPcx->width;
			t->heightItem = t->loadedPcx->height;
		}
		return t;
	}
	_H3API_ VOID H3DlgHintBar::ShowHint(H3Msg* msg)
	{
		if (msg->command == int(H3Msg::MessageCommand::MC_MOUSE_OVER))
		{
			H3DlgItem* di = msg->ItemAtPosition(parent);
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
	_H3API_ VOID H3DlgHintBar::ShowMessage(LPCSTR msg)
	{
		SetText(msg);
		Draw();
		Refresh();
	}
	_H3API_ H3DlgHintBar* H3DlgHintBar::Create(H3Dlg* dlg)
	{
		return (H3DlgHintBar*)H3DlgTextPcx::Create(8, dlg->GetHeight() - 26, dlg->GetWidth() - 16, 19, h3_NullString, NH3Dlg::Text::SMALL, NH3Dlg::HDassets::HD_STATUSBAR_PCX, NH3Dlg::TextColor::REGULAR);
	}
	_H3API_ H3DlgHintBar * H3DlgHintBar::Create(H3Dlg * dlg, INT32 x, INT32 y, INT32 w, INT32 h)
	{
		return (H3DlgHintBar*)H3DlgTextPcx::Create(x, y, w, h, h3_NullString, NH3Dlg::Text::SMALL, NH3Dlg::HDassets::HD_STATUSBAR_PCX, NH3Dlg::TextColor::REGULAR);
	}

	_H3API_ H3DlgScrollableText* H3DlgScrollableText::Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, LPCSTR font, INT32 color, INT32 isBlue)
	{
		H3DlgScrollableText* s = (H3DlgScrollableText*)F_malloc(sizeof(H3DlgScrollableText));
		if (s)
			THISCALL_9(H3DlgScrollableText*, 0x5BA360, s, text, x, y, width, height, font, color, isBlue);
		return s;
	}
	_H3API_ VOID H3DlgScrollbar::loadButton(LPCSTR buttonName)
	{
		THISCALL_2(VOID, 0x596340, this, buttonName);
	}

	_H3API_ H3DlgScrollbar* H3DlgScrollbar::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 ticksCount, H3DlgScrollbar_proc scrollbarProc, BOOL isBlue, INT32 stepSize, BOOL arrowsEnabled)
	{
		H3DlgScrollbar* s = (H3DlgScrollbar*)F_malloc(sizeof(H3DlgScrollbar));
		if (s)
			THISCALL_11(H3DlgScrollbar*, 0x5963C0, s, x, y, width, height, id, ticksCount, scrollbarProc, isBlue, stepSize, arrowsEnabled);
		return s;
	}
	_H3API_ INT32 H3DlgScrollbar::GetTick() const
	{
		return tick;
	}
	_H3API_ VOID H3DlgScrollbar::SetTick(INT32 index)
	{
		tick = index;
	}
	_H3API_ VOID H3DlgScrollbar::SetBigStep(INT32 step)
	{
		bigStepSize = step;
	}
	_H3API_ VOID H3DlgScrollbar::SetButtonPosition()
	{
		btnPosition = sizeFree * tick / (ticksCount - 1) + btnSize2;
	}
	_H3API_ BOOL H3DlgScrollbar::IsHorizontal() const
	{
		return widthItem > heightItem;
	}
	_H3API_ INT32 H3DlgScrollbar::GetRightButtonX() const
	{
		return parent->GetX() + xPos + sizeMax - btnSize2;
	}
	_H3API_ INT32 H3DlgScrollbar::GetHorizontalY() const
	{
		return parent->GetY() + yPos;
	}
	_H3API_ INT32 H3DlgScrollbar::GetBackgroundWidth() const
	{
		return sizeMax - 2 * btnSize2;
	}
	_H3API_ INT32 H3DlgScrollbar::GetBackgroundX() const
	{
		return parent->GetX() + xPos + btnSize2;
	}
	_H3API_ INT32 H3DlgScrollbar::GetSliderX() const
	{
		return parent->GetX() + xPos + btnPosition;
	}
	_H3API_ H3LoadedPcx * H3DlgScrollbar::GetPcx()
	{
		return loadedPcx;
	}

	_H3API_ VOID H3DlgBasePanel::backupScreen()
	{
		THISCALL_1(VOID, 0x5AA870, this);
	}
	_H3API_ VOID H3DlgBasePanel::restoreBackupScreen()
	{
		THISCALL_1(VOID, 0x5AA920, this);
	}

	_H3API_ H3Vector<H3DlgItem*>& H3DlgBasePanel::GetItems()
	{
		return items;
	}
	_H3API_ H3DlgItem* H3DlgBasePanel::AddItem(H3DlgItem * item)
	{
		// H3DlgBasePanel items are hidden by default
		// use Show() when needed.
		item->HideDeactivate();
		items += item;
		return THISCALL_3(H3DlgItem*, 0x5AA7B0, this, item, -1);
	}
	_H3API_ VOID H3DlgBasePanel::Redraw()
	{
		//THISCALL_4(VOID, 0x5AA800, this, TRUE, -65535, 65535);

		for (H3DlgItem** i = items.begin(); i != items.end(); ++i)
		{
			H3DlgItem* it = *i;
			if (it->IsVisible())
				it->Draw();
		}

		H3Internal::_windowManager()->H3Redraw(x + parent->GetX(), y + parent->GetY(), width, height);
	}
	_H3API_ VOID H3DlgBasePanel::Hide()
	{
		for (H3DlgItem** it = items.begin(); it != items.end(); ++it)
			(*it)->HideDeactivate();
		restoreBackupScreen();
	}
	_H3API_ VOID H3DlgBasePanel::Show()
	{
		// if backup pcx exists, panel is already shown
		if (backupPcx)
			return;
		backupScreen();
		for (H3DlgItem** it = items.begin(); it != items.end(); ++it)
			(*it)->ShowActivate();
		Redraw();
	}
	_H3API_ VOID H3DlgBasePanel::Move(INT xDest, INT yDest)
	{
		if (items.IsEmpty())
			return;

		const BOOL shown = backupPcx != nullptr;
		if (shown)
			Hide();

		const int dx = xDest - x;
		const int dy = yDest - y;
		x = xDest;
		y = yDest;

		for (H3DlgItem** i = items.begin(); i != items.end(); ++i)
		{
			H3DlgItem* it = *i;
			it->SetX(it->GetX() + dx);
			it->SetY(it->GetY() + dy);
		}

		if (shown)
			Show();
	}
	_H3API_ VOID H3DlgBasePanel::MoveRelative(INT xDest, INT yDest)
	{
		xDest -= parent->GetX();
		yDest -= parent->GetY();
		Move(xDest, yDest);
	}

	_H3API_ INT32 H3DlgBasePanel::GetWidth() const
	{
		return width;
	}
	_H3API_ INT32 H3DlgBasePanel::GetHeight() const
	{
		return height;
	}
	_H3API_ INT32 H3DlgBasePanel::GetX() const
	{
		return x;
	}
	_H3API_ INT32 H3DlgBasePanel::GetY() const
	{
		return y;
	}
	_H3API_ INT HDDlg::CallHDProc(const H3Msg & msg)
	{
		return hdProc(this, msg);
	}

	_H3API_ H3TownAlignmentDlg::H3TownAlignmentDlg(int town)
	{
		THISCALL_2(H3TownAlignmentDlg&, 0x5761A0, this, 1);
		int frame = 2 * town + 2;
		H3DefLoader def(NH3Dlg::Assets::TOWN_SMALL);
		THISCALL_4(BOOL8, 0x5761C0, this, def.Get(), frame, town);
		THISCALL_2(VOID, m_vtable->runDlg, this, 0);
	}
	_H3API_ H3TownAlignmentDlg::~H3TownAlignmentDlg()
	{
		THISCALL_1(VOID, 0x48FA10, this);
	}
	_H3API_ INT H3Dlg::vDialogProc(H3Msg & msg)
	{
		H3DlgItem* it = nullptr;

		switch (msg.command)
		{
		case H3Msg::MessageCommand::MC_KEY_UP:
			if (OnKeyPress(msg.GetKey(), msg.GetFlag()))
				break;
			return CheckEnd(msg);
		case H3Msg::MessageCommand::MC_MOUSE_OVER:
			if (!OnMouseHover(msg.GetX(), msg.GetY()))
				return CheckEnd(msg);
			it = ItemAtPosition(msg);
			if (!it)
				break;

			if (hintBar && it->GetHint())
				hintBar->ShowMessage(it->GetHint());

			if (OnMouseHover(it))
				break;
			return CheckEnd(msg);
		case H3Msg::MessageCommand::MC_LCLICK_OUTSIDE:
			if (OnLeftClickOutside())
				break;
			return CheckEnd(msg);
		case H3Msg::MessageCommand::MC_RCLICK_OUTSIDE:
			if (OnRightClickOutside())
				break;
			return CheckEnd(msg);
		case H3Msg::MessageCommand::MC_KEY_HELD:
			if (OnKeyHeld(msg.GetKey(), msg.GetFlag()))
				break;
			return CheckEnd(msg);
		case H3Msg::MessageCommand::MC_MOUSE_BUTTON:
			switch (msg.subtype)
			{
			case H3Msg::MessageSubtype::MS_END_DIALOG:
				switch (msg.item_id)
				{
				case H3Msg::ItemIDs::ID_OK:
					OnOK();
					break;
				case H3Msg::ItemIDs::ID_CANCEL:
					OnCancel();
					break;
				default:
					OnClose(msg.item_id);
					break;
				}
				break;
			case H3Msg::MessageSubtype::MS_LBUTTON_CLICK:
				if (OnLeftClick(msg.item_id, msg))
					break;
				return CheckEnd(msg);
			case H3Msg::MessageSubtype::MS_RBUTTON_DOWN:
				it = ItemAtPosition(msg);
				if (!it)
					break;
				if (OnRightClick(it))
					break;
				return CheckEnd(msg);
			default:
				break;
			}
			break;
		case H3Msg::MessageCommand::MC_MOUSE_WHEEL:
			if (OnMouseWheel(msg.subtype))
				break;
			return CheckEnd(msg);
		case H3Msg::MessageCommand::MC_WHEEL_BUTTON:
			if (msg.subtype == H3Msg::MessageSubtype::MS_MOUSE_WHEEL_BUTTON_DOWN)
			{
				it = ItemAtPosition(msg);
				if (!it)
					break;
				if (OnWheelButton(it))
					break;
				return CheckEnd(msg);
			}
			break;
		default:
			break;
		}

		if (endDialog)
			return msg.CloseDialog();

		if (DialogProc(msg))
			return DefaultProc(msg);

		return CheckEnd(msg);
	}
	_H3API_ VOID H3Dlg::OnOK()
	{
	}
	_H3API_ VOID H3Dlg::OnCancel()
	{
	}
	_H3API_ VOID H3Dlg::OnClose(INT itemId)
	{
	}
	_H3API_ BOOL H3Dlg::OnNotify(H3DlgItem * it, H3Msg & msg)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::DialogProc(H3Msg & msg)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnLeftClick(INT itemId, H3Msg& msg)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnLeftClickOutside()
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnRightClick(H3DlgItem* it)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnRightClickOutside()
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnMouseWheel(INT direction)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnWheelButton(H3DlgItem* it)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnMouseHover(INT32 x, INT32 y)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnMouseHover(H3DlgItem* it)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnKeyPress(NH3VKey::eVirtualKeys key, H3Msg::MessageFlag flag)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnKeyHeld(NH3VKey::eVirtualKeys key, H3Msg::MessageFlag flag)
	{
		return TRUE;
	}
	_H3API_ BOOL H3Dlg::OnCreate()
	{
		return TRUE;
	}

	_H3API_ VOID H3CombatDlg::ShowHint(LPCSTR hint, BOOL8 addToLog)
	{
		THISCALL_4(VOID, 0x4729D0, this, hint, addToLog, 0);
	}
	_H3API_ H3Vector<H3String*>& H3CombatDlg::GetCombatText()
	{
		return *reinterpret_cast<H3Vector<H3String*>*>(PBYTE(this) + 0x54);
	}

	_H3API_ BOOL H3DlgHighlightable::unhighlightSelection() const
	{
		if (m_currentHighlight)
		{
			m_currentHighlight->Draw();
			m_currentHighlight->Refresh();
			m_currentHighlight = nullptr;
			return TRUE;
		}
		return FALSE;
	}
	_H3API_ H3DlgHighlightable::H3DlgHighlightable() :
		m_currentHighlight()
	{
	}
	_H3API_ VOID H3DlgHighlightable::AddItem(H3DlgItem * dlgItem, BYTE red, BYTE green, BYTE blue, UINT frameThickness)
	{
		AddItem(dlgItem, H3ARGB888(red, green, blue), frameThickness);
	}
	_H3API_ VOID H3DlgHighlightable::AddItem(H3DlgItem * dlgItem, const H3ARGB888 & color, UINT frameThickness)
	{
		H3Highlighter highlight(dlgItem, color, frameThickness);
		m_highlightableItems += highlight;
	}
	_H3API_ BOOL H3DlgHighlightable::HighlightItem(H3DlgItem * dlgItem) const
	{
		if (!dlgItem)
			return unhighlightSelection();
		else
		{
			if (dlgItem == m_currentHighlight)
				return FALSE;
			unhighlightSelection();
			for (H3Highlighter* it = m_highlightableItems.begin(); it != m_highlightableItems.end(); ++it)
			{
				if (it->m_item == dlgItem)
				{
					it->m_item->DrawTempFrame(it->m_thickness, it->m_highlight);
					it->m_item->Refresh();
					m_currentHighlight = it->m_item;
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	_H3API_ BOOL H3DlgHighlightable::HighlightItem(const H3Msg& msg) const
	{
		if (m_highlightableItems.IsEmpty())
			return FALSE;
		if (!msg.IsMouseOver())
			return FALSE;
		return HighlightItem(msg.ItemAtPosition(m_highlightableItems[0].m_item->GetParent()));
	}
	_H3API_ VOID H3DlgHighlightable::Clear()
	{
		m_currentHighlight = nullptr;
		m_highlightableItems.RemoveAll();
	}
	H3DlgHighlightable::H3Highlighter::H3Highlighter() :
		m_item(), m_highlight(), m_thickness()
	{
	}
	_H3API_ H3DlgHighlightable::H3Highlighter::H3Highlighter(H3DlgItem* item, const H3ARGB888& color, UINT thickness) :
		m_item(item), m_highlight(color), m_thickness(thickness)
	{
	}
	_H3API_ H3DlgHighlightable::H3Highlighter::H3Highlighter(H3DlgItem* item, BYTE r, BYTE g, BYTE b, UINT thickness) :
		m_item(item), m_highlight(r, g, b), m_thickness(thickness)
	{
	}

	_H3API_ H3BasicDlg::H3BasicDlg(INT x, INT y, INT w, INT h) :
		zOrder(-1), nextDialog(nullptr), lastDialog(nullptr), flags(0x12), state(0),
		xDlg(x), yDlg(y), widthDlg(w), heightDlg(h), lastItem(nullptr), firstItem(nullptr),
		focusedItemId(-1), pcx16(nullptr), deactivatesCount(0)
	{
	}

	_H3API_ H3MapInformation& H3SelectScenarioDialog::CurrentMap()
	{
		return mapsInformation[selectedMapIndex];
	}

	_H3API_ VOID H3SelectScenarioDialog::UpdateForSelectedScenario(INT32 index, BOOL8 redraw)
	{
		THISCALL_3(VOID, 0x5857D0, this, index, redraw);
	}

	_H3API_ VOID H3SelectScenarioDialog::Redraw()
	{
		THISCALL_1(VOID, 0x584820, this);
	}

}