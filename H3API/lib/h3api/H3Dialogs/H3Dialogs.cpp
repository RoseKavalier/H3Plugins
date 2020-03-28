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

#include "H3Dialogs.hpp"
#include "../H3_Functions.hpp"
#include "../H3_Structures.hpp"

namespace h3
{
	_H3API_ VOID H3Msg::SetCommand(INT32 _command, INT32 _subtype, INT32 _item_id, INT32 _flags, INT32 x, INT32 y, INT32 param, INT32 _flags2)
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
	_H3API_ VOID H3Msg::SetCommand(INT32 cmd, INT32 param)
	{
		SetCommand(0x200, cmd, 0, 0, 0, 0, param, 0);
	}
	_H3API_ H3DlgItem* H3Msg::ItemAtPosition(H3BaseDlg* dlg)
	{
		return THISCALL_3(H3DlgItem*, 0x5FF9A0, dlg, x_abs, y_abs);
	}
	_H3API_ INT32 H3Msg::KeyPressed() const
	{
		return subtype;
	}
	_H3API_ BOOL H3Msg::IsKeyPress() const
	{
		return command == int(MessageCommand::MC_KeyUp);
	}
	_H3API_ BOOL H3Msg::IsKeyDown() const
	{
		return command == int(MessageCommand::MC_KeyDown);
	}
	_H3API_ BOOL H3Msg::IsKeyHeld() const
	{
		return command == int(MessageCommand::MC_KeyHeld);
	}
	_H3API_ BOOL H3Msg::IsMouseOver() const
	{
		return command == int(MessageCommand::MC_MouseOver);
	}
	_H3API_ BOOL H3Msg::IsWheelButton() const
	{
		return command == int(MessageCommand::MC_WheelButton) && subtype == int(MessageSubtype::MS_MouseWheelButtonDown);
	}
	_H3API_ BOOL H3Msg::IsLeftClick() const
	{
		return (command == int(MessageCommand::MC_MouseButton) && subtype == int(MessageSubtype::MS_LButtonClick));
	}
	_H3API_ BOOL H3Msg::IsLeftDown() const
	{
		return (command == int(MessageCommand::MC_MouseButton) && subtype == int(MessageSubtype::MS_LButtonDown));
	}
	_H3API_ BOOL H3Msg::IsRightClick() const
	{
		return (command == int(MessageCommand::MC_MouseButton) && subtype == int(MessageSubtype::MS_RButtonDown));
	}
	_H3API_ BOOL H3Msg::ClickOutside() const
	{
		return command == int(MessageCommand::MC_RClickOutside) || command == int(MessageCommand::MC_LClickOutside);
	}
	_H3API_ INT32 H3Msg::CloseDialog()
	{
		return STDCALL_1(INT32, 0x491640, this);
	}
	_H3API_ H3Dlg* H3MsgCustom::GetDlg() const
	{
		return reinterpret_cast<H3Dlg*>(flags2);
	}
	_H3API_ H3DlgVTable::H3DlgVTable() :
		destroyDlg(0x41B040),
		showDlg(0x5FF0A0),
		hideDlg(0x5FF220),
		callProcessAction(0x405610),
		_nullsub(0x49A230),
		redrawDlg(0x5FF5E0),
		runDlg(0x5FFA20),
		initDlgItems(0x5FFB30),
		activateDlg(0x5FFBB0),
		dlgProc(reinterpret_cast<H3Dlg_proc>(H3DlgCustomProc)), // custom proc to show hint messages and call our own dlg proc), default 0x41B120.
		mouseMove(0x5FFCA0),
		rightClick(0x5FFD50),
		clickRet(0x5FFE90),
		_nullsub3(0x4842C0),
		closeDlg(0x41B0F0)
	{
	}
	_H3API_ H3Dlg::H3Dlg(int width, int height, int x, int y, BOOL statusBar, H3Dlg_proc dlgProc, BOOL makeBackground, INT32 colorIndex)
	{
		THISCALL_6(H3Dlg*, 0x41AFA0, this, x == -1 ? (H3Internal::_gameWidth() - width) / 2 : x, y == -1 ? (H3Internal::_gameHeight() - height) / 2 : y, width, height, 0x12);
		vtable = &CustomDlgVTable;
		background = nullptr;
		if (makeBackground)
			AddBackground(TRUE, statusBar, colorIndex);
		customProc = dlgProc;
		H3DlgHintBar* hint = nullptr;
		if (statusBar)
			hint = CreateHint();
		hintBar = hint;
	}
	_H3API_ H3Dlg::~H3Dlg()
	{
		THISCALL_2(VOID, vtable->destroyDlg, this, 0);
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
		H3MouseManager* mmgr = H3Internal::MouseManager();
		INT32 mouseType = mmgr->GetType();
		INT32 mouseFrame = mmgr->GetFrame();
		mmgr->DefaultCursor();
		THISCALL_2(VOID, vtable->runDlg, this, 0); // run H3Dlg
		mmgr->SetCursor(mouseType, mouseFrame); // restore previous cursor
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

		H3LoadedPCX16* pcx = H3LoadedPCX16::Create(h3_NullString, widthDlg, heightDlg);
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
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedPCX* pcx)
	{
		if (!pcx || background)
			return FALSE;
		background = H3LoadedPCX16::Create(h3_NullString, pcx->width, pcx->height);
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
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedPCX16* pcx)
	{
		if (!pcx || background)
			return FALSE;
		background = H3LoadedPCX16::Create(h3_NullString, pcx->width, pcx->height);
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
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedPCX24* pcx)
	{
		if (!pcx || background)
			return FALSE;

		background = H3LoadedPCX16::Create(h3_NullString, pcx->width, pcx->height);
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
	_H3API_ BOOL H3Dlg::AddBackground(H3LoadedDEF* def, INT group, INT frame)
	{
		if (background || !def || def->groupsCount < group || !def->activeGroups[group])
			return FALSE;
		H3DefGroup* grp = def->groups[group];
		if (grp->count < frame)
			return FALSE;

		H3DefFrame* fr = grp->frames[frame];

		background = H3LoadedPCX16::Create(h3_NullString, fr->frameWidth, fr->frameHeight);
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
	
	_H3API_ VOID H3BaseDlg::Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy)
	{
		H3Internal::WindowManager()->H3Redraw(xDlg + x, yDlg + y, dx, dy);
	}
	_H3API_ VOID H3BaseDlg::Redraw()
	{
		THISCALL_4(VOID, vtable->redrawDlg, this, TRUE, -65535, 65535);
	}
	_H3API_ INT32 H3BaseDlg::DefaultProc(H3Msg* msg)
	{
		return THISCALL_2(INT32, 0x41B120, this, msg);
	}
	_H3API_ INT32 H3BaseDlg::GetWidth() const
	{
		return widthDlg;
	}
	_H3API_ INT32 H3BaseDlg::GetHeight() const
	{
		return heightDlg;
	}
	_H3API_ INT32 H3BaseDlg::GetX() const
	{
		return xDlg;
	}
	_H3API_ INT32 H3BaseDlg::GetY() const
	{
		return yDlg;
	}
	_H3API_ BOOL H3BaseDlg::IsTopDialog() const
	{
		return nextDialog == nullptr;
	}
	_H3API_ H3DlgItem* H3BaseDlg::AddItem(H3DlgItem* item)
	{
		dlgItems += item;
		return THISCALL_3(H3DlgItem*, 0x5FF270, this, item, -1); // LoadItem
	}
	_H3API_ H3DlgItem * H3BaseDlg::CreateHidden(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id)
	{
		H3DlgItem* it = H3DlgItem::Create(x, y, width, height, id, 0);
		if (it)
			AddItem(it);
		return it;
	}
	_H3API_ H3LoadedPCX16* H3Dlg::GetBackgroundPcx() const
	{
		return background;
	}
	_H3API_ BOOL H3Dlg::BackgroundRegion(INT32 xStart, INT32 yStart, INT32 w, INT32 h, BOOL is_blue)
	{
		if (!background || w <= 0 || h <= 0)
			return FALSE;
		return background->BackgroundRegion(xStart, yStart, w, h, is_blue);
	}
	_H3API_ BOOL H3Dlg::SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height, H3LoadedPCX16* destination)
	{
		H3LoadedPCX16* target = destination ? destination : background;
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
	_H3API_ H3LoadedPCX16* H3BaseDlg::GetCurrentPcx()
	{
		return pcx16;
	}
	_H3API_ H3Dlg_proc H3Dlg::GetProc()
	{
		return customProc;
	}
	_H3API_ H3DlgItem* H3BaseDlg::ItemAtPosition(H3Msg* msg)
	{
		return THISCALL_3(H3DlgItem*, 0x5FF9A0, this, msg->x_abs, msg->y_abs);
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
			H3LoadedDEF* def = but->GetDef();
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
			H3LoadedPCX* p = pcx->GetPcx();
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
	_H3API_ H3DlgScrollableText* H3BaseDlg::CreateScrollableText(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue)
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
	_H3API_ VOID H3DlgItem::_SetText(LPCSTR text)
	{
		THISCALL_2(VOID, vTable->setText, this, text);
	}
	_H3API_ H3DlgItem* H3DlgItem::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, INT32 flags)
	{
		H3DlgItem* d = (H3DlgItem*)F_malloc(sizeof(H3DlgItem));
		if (d)
			THISCALL_7(H3DlgItem*, 0x44FBE0, d, x, y, width, height, id, flags);
		return d;
	}
	_H3API_ VOID H3DlgItem::EnableItem(BOOL enable)
	{
		THISCALL_2(VOID, vTable->setEnabled, this, enable);
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
	_H3API_ BOOL H3DlgItem::IsEnabled() const
	{
		return !(state & 0x20);
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
		THISCALL_1(VOID, vTable->draw, this);
	}
	_H3API_ VOID H3DlgItem::Refresh()
	{
		parent->Redraw(xPos, yPos, widthItem, heightItem);
	}
	_H3API_ VOID H3DlgItem::Hide()
	{
		state &= ~4;
	}
	_H3API_ VOID H3DlgItem::Show()
	{
		state |= 4;
	}
	_H3API_ VOID H3DlgItem::Shade()
	{
		state |= 8;
	}
	_H3API_ VOID H3DlgItem::UnShade()
	{
		state &= ~8;
	}
	_H3API_ VOID H3DlgItem::SetFocus(BOOL8 focus)
	{
		THISCALL_2(VOID, vTable->setFocus, this, focus);
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
		change_hue = FALSE;
	}
	_H3API_ VOID H3DlgFrame::ShowHue()
	{
		change_hue = TRUE;
	}
	_H3API_ VOID H3DlgFrame::ToggleHue()
	{
		change_hue = !change_hue;
	}
	_H3API_ H3RGB565* H3DlgFrame::GetColor()
	{
		return &color565;
	}
	_H3API_ H3DlgDef* H3DlgDef::Create(INT32 x, INT32 y, INT32 width, INT32 height, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
	{
		H3DlgDef* d = (H3DlgDef*)F_malloc(sizeof(H3DlgDef));
		if (d)
			THISCALL_12(H3DlgDef*, 0x4EA800, d, x, y, width, height, id, defName, frame, group, mirror, closeDialog, 0x10);
		return d;
	}
	_H3API_ H3DlgDef* H3DlgDef::Create(INT32 x, INT32 y, INT32 id, LPCSTR defName, INT32 frame, INT32 group, INT32 mirror, BOOL closeDialog)
	{
		H3DlgDef* d = Create(x, y, 0, 0, id, defName, frame, group, mirror, closeDialog);
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
	_H3API_ INT H3DlgDef::ToggleFrame()
	{
		defFrame = !defFrame; defFrameOnClick = !defFrameOnClick; return defFrame;
	}
	_H3API_ INT32 H3DlgDef::GetFrame() const
	{
		return defFrame;
	}
	_H3API_ VOID H3DlgDef::ColorDefToPlayer(INT32 id)
	{
		loadedDef->ColorToPlayer(id);
	}
	_H3API_ VOID H3DlgDef::SetClickFrame(INT32 clickFrame)
	{
		defFrameOnClick = clickFrame;
	}
	_H3API_ H3LoadedDEF * H3DlgDef::GetDef()
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
	_H3API_ VOID H3DlgCaptionButton::SetText(LPCSTR text)
	{
		_SetText(text);
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
	_H3API_ VOID H3DlgPcx::SetPcx(H3LoadedPCX* pcx)
	{
		loadedPcx = pcx;
	}
	_H3API_ VOID H3DlgPcx::AdjustColor(INT player)
	{
		THISCALL_2(VOID, 0x4501D0, this, player);
	}
	_H3API_ H3LoadedPCX* H3DlgPcx::GetPcx()
	{
		return loadedPcx;
	}
	_H3API_ H3LoadedPCX* H3DlgPcx::GetPcx() const
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
	_H3API_ VOID H3DlgPcx16::SetPcx(H3LoadedPCX16* pcx16)
	{
		loadedPcx16 = pcx16;
	}
	_H3API_ H3LoadedPCX16* H3DlgPcx16::GetPcx()
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
		_SetText(text);
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
	_H3API_ INT H3DlgEdit::GetCaret() const
	{
		return caretPos;
	}
	_H3API_ BOOL H3DlgEdit::SetCaret(INT pos)
	{
		if (pos < 0 || pos == caretPos || pos > text.Length())
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
		THISCALL_2(VOID, vTable->setFocus, this, on);
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
		_SetText(text);
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
		if (msg->command == int(H3Msg::MessageCommand::MC_MouseOver))
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
	_H3API_ H3DlgScrollableText* H3DlgScrollableText::Create(LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, INT32 font, INT32 color, INT32 isBlue)
	{
		H3DlgScrollableText* s = (H3DlgScrollableText*)F_malloc(sizeof(H3DlgScrollableText));
		if (s)
			THISCALL_9(H3DlgScrollableText*, 0x5BA360, s, text, x, y, width, height, font, color, isBlue);
		return s;
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
	_H3API_ H3LoadedPCX * H3DlgScrollbar::GetPcx()
	{
		return loadedPcx;
	}
	_H3API_ INT32 __fastcall H3DlgCustomProc(H3Dlg* dlg, int, H3Msg* msg)
	{
		if (H3DlgHintBar* hint = dlg->GetHintBar())
			hint->ShowHint(msg);
		if (H3Dlg_proc cProc = dlg->GetProc())
			return STDCALL_2(INT32, cProc, dlg, msg);
		return dlg->DefaultProc(msg);
	}
	_H3API_ void H3CombatBottomPanel::AddComment(LPCSTR text)
	{
		THISCALL_2(void, vTable[1], this, text);
	}
	_H3API_ H3Vector<H3DlgItem*>& H3DlgPanel::GetItems()
	{
		return items;
	}
	_H3API_ INT HDDlg::CallHDProc(H3Msg & msg)
	{
		return hdProc(this, &msg);
	}
	_H3API_ H3TownAlignmentDlg::H3TownAlignmentDlg(int town)
	{
		THISCALL_2(H3TownAlignmentDlg&, 0x5761A0, this, 1);
		int frame = 2 * town + 2;
		DefLoader def(NH3Dlg::Assets::TOWN_SMALL);
		THISCALL_4(BOOL8, 0x5761C0, this, def.Get(), frame, town);
		THISCALL_2(VOID, vtable->runDlg, this, 0);
	}	
	_H3API_ H3TownAlignmentDlg::~H3TownAlignmentDlg()
	{
		THISCALL_1(VOID, 0x48FA10, this);
	}
}