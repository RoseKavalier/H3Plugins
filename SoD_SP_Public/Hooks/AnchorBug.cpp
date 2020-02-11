/*
 * Big thanks to kazmer for his help in understanding obstacles placement
 * And for his wonderful Battlefield Explorer for HoMM3 (highly recommended)
 * https://github.com/jtakacs/homm3_battlefields
 *
 * Summary: when placing Obstacles on the Battlefield, the game sets an "Anchor"
 * From where relative cells corresponding to this obstacle's shape are blocked.
 * However, the Anchor tile also receive a block flag.
 * This flag is required to correctly draw the obstacle on battlefield during combat.
 * The bug fixed by this plugin arises when the Anchor tile is not part of the obstacle's shape:
 * This flag is not normally visible, unless you try to cast Fire Wall, Force Field, Land Mine or Quicksand.
 * In these four cases, you will be unable to place anything on the Anchor tile...
 * Even though this hex is technically free - you can still move creatures there.
 * With this plugin, the Anchor is always part of the obstacle and the DEF is correctly placed.
 */

#include "AnchorBug.h"
#include "Global.h"
#include "SODSP_Files/Log.h"

using namespace h3;
using NH3Constants::COMBATSQUARE_WIDTH;
using NH3Constants::COMBATSQUARE_HEIGHT;

using SODSP::FEATURES::FOptions;

/*
 *
 * This hook moves the anchor of problematic obstacles within the obstacles themselves.
 * The hook is applied after obstacle placement algorithm has completed to ensure
 * original obstacle arrangement is maintained.
 *
 */
void __stdcall _HH_FixObstacleAnchorBug(HiHook *h, H3CombatManager *combat)
{
	LOG_HIHOOK;
	THISCALL_1(void, h->GetDefaultFunc(), combat);

	if (!F_Multiplayer() && FOptions.anchor)
	{
		for (auto& obstacle : combat->obstacleInfo)
		{
			int obstacle_id = obstacle.info - &P_DefObstacleInfo(0);
			UINT8 anchor_hex = obstacle.AnchorHex;
			int row_parity; // is the row odd or even?
			switch (obstacle_id)
			{
			case LocalObstacles::obbdt01: // offset at 1 exists
			case LocalObstacles::obdts04:
			case LocalObstacles::obdts15:
			case LocalObstacles::obdsm02:
			case LocalObstacles::obdss17:
			case LocalObstacles::obgrs01:
			case LocalObstacles::obgrs02:
			case LocalObstacles::obsns02:
			case LocalObstacles::obsns05:
			case LocalObstacles::obsns06:
			case LocalObstacles::obrgs03:
			case LocalObstacles::obbhs02:
			case LocalObstacles::obbhs11a:
			case LocalObstacles::obbhs12b:
			case LocalObstacles::obhgs02:
			case LocalObstacles::obefs03:
			case LocalObstacles::obefs04:
			case LocalObstacles::obcfs02:
			case LocalObstacles::oblps03:
			case LocalObstacles::obffs03:
			case LocalObstacles::obrls03:
			case LocalObstacles::obmcs01:
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex + 1].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obdts14: // offset at 2 exists
			case LocalObstacles::obsns09:
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex + 2].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obsns10: // 3;-13;-14;-15;-33;-49;-66
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex + 3].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obsws02: // -10;-11;-12;-13;-14;-15;-16
				row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex - 10 - row_parity].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obsws11b: // -13;-14;-15;-16;-30;-31;-32;-33
			case LocalObstacles::oblvs03: // -13;-14;-15;-30;-31;-32;-33
			case LocalObstacles::oblvs17: // -13;-14;-15;-16;-30;-31
			case LocalObstacles::oblvs22: // -13;-14;-15;-16;-31;-32;-33
				row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex - 13 - row_parity].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obrgs02: // -14;-15;-16;-32;-33
			case LocalObstacles::oblvs01: // -14;-32;-33
			case LocalObstacles::oblvs09: // -14;-15;-32;-33;-49;-50
				row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex - 14 - row_parity].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obdrk01: // -15, -16
			case LocalObstacles::obdsm01: // -15;-16;-32;-33;-48;-49
			case LocalObstacles::obrgs05: // -15;-16;-32
			case LocalObstacles::obbts04: // -15;-16;-33
				row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex - 15 - row_parity].obstacleBits |= 1; // add anchor flag
				break;
			case LocalObstacles::obsws13a: // -16;-17;-31;-32;-33;-34
			case LocalObstacles::obdrk03: // -16
			case LocalObstacles::obrgs04: // -16;-32;-33
				row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
				combat->squares[anchor_hex].obstacleBits &= ~1; // remove anchor flag
				combat->squares[anchor_hex - 16 - row_parity].obstacleBits |= 1; // add anchor flag
				break;
			default:
				break;
			}
		}
	}
}

/*
 *
 * Since anchors of certain obstacles were moved, this hook corrects their
 * placement at the time of drawing.
 *
 */
_LHF_(RepositionAnchorDef)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.anchor)
	{
		H3CombatSquare *hex;
		if (h->GetAddress() == 0x494523) // previously missing
			hex = (H3CombatSquare*)(c->edi - 0x1C);
		else
			hex = (H3CombatSquare*)(c->edi - 0x14); // first fix
		H3CombatManager *combat = (H3CombatManager*)c->esi;
		if (hex->obstacleBits == 3) // anchor & local obstacle
		{
			int obstacle_number = hex->obstacleIndex;
			H3Obstacle *obstacle = &combat->obstacleInfo[obstacle_number];
			int obstacle_id = obstacle->info - &P_DefObstacleInfo(0);
			switch (obstacle_id)
			{
			case LocalObstacles::obbdt01: // offset at 1 exists
			case LocalObstacles::obdts04:
			case LocalObstacles::obdts15:
			case LocalObstacles::obdsm02:
			case LocalObstacles::obdss17:
			case LocalObstacles::obgrs01:
			case LocalObstacles::obgrs02:
			case LocalObstacles::obsns02:
			case LocalObstacles::obsns05:
			case LocalObstacles::obsns06:
			case LocalObstacles::obrgs03:
			case LocalObstacles::obbhs02:
			case LocalObstacles::obbhs11a:
			case LocalObstacles::obbhs12b:
			case LocalObstacles::obhgs02:
			case LocalObstacles::obefs03:
			case LocalObstacles::obefs04:
			case LocalObstacles::obcfs02:
			case LocalObstacles::oblps03:
			case LocalObstacles::obffs03:
			case LocalObstacles::obrls03:
			case LocalObstacles::obmcs01:
				c->eax -= COMBATSQUARE_WIDTH; // move X left
				break;
			case LocalObstacles::obdts14: // 2, -15, -16
			case LocalObstacles::obsns09: // 2;3;4;5;-13;-14;-15;-16
				c->eax -= 2 * COMBATSQUARE_WIDTH;
				break;
			case LocalObstacles::obsns10: // 3;-13;-14;-15;-33;-49;-66
				c->eax -= 3 * COMBATSQUARE_WIDTH;
				break;
			case LocalObstacles::obsws02: // -10;-11;-12;-13;-14;-15;-16
				c->eax -= (int)(6.5 * COMBATSQUARE_WIDTH); // move by 6.5 hex left  (-16 - -10 - 0.5)
				c->edx += COMBATSQUARE_HEIGHT; // lower row by 1
				break;
			case LocalObstacles::obsws11b: // -13;-14;-15;-16;-30;-31;-32;-33
			case LocalObstacles::oblvs03: // -13;-14;-15;-30;-31;-32;-33
			case LocalObstacles::oblvs17: // -13;-14;-15;-16;-30;-31
			case LocalObstacles::oblvs22: // -13;-14;-15;-16;-31;-32;-33
				c->eax -= (int)(3.5 * COMBATSQUARE_WIDTH); // move by 3.5 hex left (-16 - -13 - 0.5)
				c->edx += COMBATSQUARE_HEIGHT; // lower row by 1
				break;
			case LocalObstacles::obrgs02: // -14;-15;-16;-32;-33
			case LocalObstacles::oblvs01: // -14;-32;-33
			case LocalObstacles::oblvs09: // -14;-15;-32;-33;-49;-50
				c->eax -= (int)(2.5 * COMBATSQUARE_WIDTH); // move by 2.5 hex left (-16 - -14 - 0.5)
				c->edx += COMBATSQUARE_HEIGHT; // lower row by 1
				break;
			case LocalObstacles::obdrk01: // -15, -16
			case LocalObstacles::obdsm01: // -15;-16;-32;-33;-48;-49
			case LocalObstacles::obrgs05: // -15;-16;-32
			case LocalObstacles::obbts04: // -15;-16;-33
				c->eax -= (int)(1.5 * COMBATSQUARE_WIDTH); // move by 1.5 hex left (-16 - -15 - 0.5)
				c->edx += COMBATSQUARE_HEIGHT; // lower row by 1
				break;
			case LocalObstacles::obsws13a: // -16;-17;-31;-32;-33;-34
			case LocalObstacles::obdrk03: // -16
			case LocalObstacles::obrgs04: // -16;-32;-33
				c->eax -= (int)(0.5 * COMBATSQUARE_WIDTH); // move by 0.5 hex left (-16 - -16 - 0.5)
				c->edx += COMBATSQUARE_HEIGHT; // lower row by 1
				break;
			default:
				break;
			}
		}
	}

	return EXEC_DEFAULT;
}

void anchorbug_init(PatcherInstance * pi)
{
	pi->WriteHiHook(0x465E70, SPLICE_, THISCALL_, _HH_FixObstacleAnchorBug);
	pi->WriteLoHook(0x4941FE, RepositionAnchorDef);
	pi->WriteLoHook(0x494523, RepositionAnchorDef);
}