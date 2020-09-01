//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3MAPITEMS_HPP_
#define _H3MAPITEMS_HPP_

#include "../H3_Base.hpp"

namespace h3
{
	/**
	 * @brief data for wandering monsters on adventure map
	 *
	 */
	struct MapMonster
	{
		unsigned  count           : 12; /**< @brief [00] max 4095 creatures*/
		  signed  aggression      : 5;  /**< @brief [12] for diplomacy*/
		unsigned  noRun           : 1;  /**< @brief [17] monsters cannot run option*/
		unsigned  noGrowth        : 1;  /**< @brief [18] monsters cannot grow option*/
		unsigned  setupIndex      : 8;  /**< @brief [19] up to 256 individual messages/prizes*/
		unsigned  growthRemainder : 4;  /**< @brief [27] remainder of the division by 10 for growth*/
		unsigned  hasSetup        : 1;  /**< @brief [31] monster has a custom setup*/
	};
	/**
	 * @brief data for wandering monsters on adventure map, as of SoD_SP 1.18
	 *
	 */
	struct SODSP_MapMonster
	{
		unsigned  count      : 12; /**< @brief [00] max 4095 creatures*/
		  signed  aggression : 5;  /**< @brief [12] for diplomacy*/
		unsigned  noRun      : 1;  /**< @brief [17] monsters cannot run option*/
		unsigned  noGrowth   : 1;  /**< @brief [18] monsters cannot grow option*/
		/**
		 * @brief [19] up to 4096 individual messages/prizes
		 * Extra growth is handled using the same game logic, just not stored
		 */
		unsigned  setupIndex : 12;
		unsigned  hasSetup   : 1;  /**< @brief [31] monster has a custom setup*/
	};
	/**
	 * @brief data for artifact on the map
	 *
	 */
	struct MapArtifact
	{
		/**
		 * @brief [00] RoE-style artifact pickup requirements
		 * 0 - free selection
		 * 1 - for 2000 gold
		 * 2 - wisdom is required
		 * 3 - leadership is required
		 * 4 - 2500 gold and 3 wood
		 * 5 - 3000 gold and 5 wood
		 * 6 - fight is triggered
		 */
		unsigned type     : 4;
		unsigned _u1      : 15;
		unsigned id       : 12; /**< @brief [19] index of custom setup, up to 4096*/
		unsigned hasSetup : 1;  /**< @brief [31] monster has a custom setup*/
	};
	/**
	 * @brief data for spell scroll on the map
	 *
	 */
	struct MapScroll
	{
		unsigned  type     : 8; /**< @brief [00] spell id*/
		unsigned _u1       : 11;
		unsigned  id       : 12; /**< @brief [19] index of custom setup, up to 4096*/
		unsigned  hasSetup : 1;  /**< @brief [31] scroll has a custom setup*/
	};
	/**
	 * @brief data for scholar on adventure map
	 *
	 */
	struct MapScholar
	{
		unsigned  type   : 3;  /**< @brief [00] 0 Primary, 1 Secondary, 2 Spell*/
		unsigned  pSkill : 3;  /**< @brief [03] 0..3 primary skill id*/
		unsigned  sSkill : 7;  /**< @brief [06] 0..27 secondary skill id*/
		unsigned  spell  : 10; /**< @brief [13] 0..69 spell id*/
		unsigned _u1     : 9;
	};
	/**
	 * @brief data for event and Pandora's Box on adventure map
	 * in the case of Pandora's Boxes, only the \p id field is used
	 */
	struct MapEvent
	{
		unsigned  id        : 10; /**< @brief [00] 0..1023 custom setups*/
		unsigned  enabled   : 8;  /**< @brief [10] which players can activate it?*/
		unsigned  aiEnabled : 1;  /**< @brief [18] can AI activate it?*/
		unsigned  oneVisit  : 1;  /**< @brief [19] cancel after 1 visit*/
		unsigned _u1        : 12; /**< @brief [20] ?unused? ==> could be used to expand number of uniques*/
	};
	/**
	 * @brief data for treasure chest on adventure map
	 *
	 */
	struct MapTreasureChest
	{
		unsigned artifactID  : 10; /**< @brief [00] 0..1023 artifact IDs*/
		unsigned hasArtifact : 1;  /**< @brief [10] whether this chest contains an artifact*/
		unsigned bonus       : 4;  /**< @brief [11] 2..4 multiply by 500 to get gold amount, -500 to get experience*/
		unsigned _u1         : 17; /**< @brief [15]*/
	};
	/**
	 * @brief data for resource on adventure map
	 *
	 */
	struct MapResource
	{
		unsigned value      : 19; /**< @brief [00] up to 524,287*/
		unsigned setupIndex : 12; /**< @brief [19] index of custom setup for guardians and message*/
		unsigned hasSetup   : 1;  /**< @brief [31] resource has a custom setup*/
	};
	/**
	 * @brief data for sea chest on adventure map
	 *
	 */
	struct MapSeaChest
	{
		unsigned level      : 2;  /**< @brief [00] 0 empty, 1 1500 gold, 2 1000 gold & artifact*/
		unsigned _u1        : 1;  /**< @brief [02]*/
		unsigned artifactID : 10; /**< @brief [03] 0..1023 artifact IDs*/
		unsigned _u2        : 19; /**< @brief [13]*/
	};
	/**
	 * @brief data for warrior's tomb on adventure map
	 *
	 */
	struct MapWarriorsTomb
	{
		unsigned  hasArt     : 1; /**< @brief [00] does the tomb contains an artifact*/
		unsigned _u1         : 4; /**< @brief [01] */
		unsigned  visited    : 8; /**< @brief [05] which players have come by*/
		unsigned  artifactID : 10;/**< @brief [13] 0..1023 artifact IDs */
		unsigned _u2         : 9; /**< @brief [23] */
	};
	/**
	 * @brief data for tree of knowledge on adventure map
	 *
	 */
	struct MapTreeOfKnowledge
	{
		unsigned  id      : 5;  /**< @brief [00] 0..31 individual IDs*/
		unsigned  visited : 8;  /**< @brief [05] which players have come by*/
		unsigned  type    : 2;  /**< @brief [13] cost: 0 free, 1 2000 gold, 2 10 gems*/
		unsigned _u1      : 17; /**< @brief [15]*/
	};
	/**
	 * @brief data for campfire on adventure map
	 *
	 */
	struct MapCampfire
	{
		unsigned  resType  : 4;  /**< @brief [00] 0..5 resource type*/
		unsigned  resValue : 28; /**< @brief [04] 4..6 number of resources. Multiply by 100 for gold value*/
	};
	/**
	 * @brief data for lean to on adventure map
	 *
	 */
	struct MapLeanTo
	{
		unsigned  id       : 5;  /**< @brief [00] 0..31 individual IDs*/
		unsigned _u1       : 1;  /**< @brief [05]*/
		unsigned  resValue : 4;  /**< @brief [06] 1..5 resource amount, 0 if taken*/
		unsigned  resType  : 4;  /**< @brief [10] 0..6 resource type, no gold*/
		unsigned _u2       : 18; /**< @brief [14]*/
	};
	/**
	 * @brief data for witch's hut on adventure map
	 *
	 */
	struct MapWitchHut
	{
		unsigned _u1      : 5;  /**< @brief [00]*/
		signed    visited : 8;  /**< @brief [05] which players have come by*/
		signed    sSkill  : 7;  /**< @brief [13] 0..27 secondary skill id*/
		unsigned _u2      : 12; /**< @brief [20]*/
	};
	/**
	 * @brief data for learning stone on adventure map
	 *
	 */
	struct MapLearningStone
	{
		int id; /**< @brief [00] heroes can only visit 32 learning stones*/
	};
	/**
	 * @brief data for wagon on adventure map
	 *
	 */
	struct MapWagon
	{
		unsigned  resValue    : 5;  /**< @brief [00] 2..5 amount of resources*/
		signed    visited     : 8;  /**< @brief [05] which players have come by*/
		unsigned  hasBonus    : 1;  /**< @brief [13] whether the wagon contains anything at all*/
		unsigned  hasArtifact : 1;  /**< @brief [14] does wagon contain an artifact*/
		unsigned  artifactID  : 10; /**< @brief [15] 0..1023 artifact ID*/
		unsigned  resType     : 4;  /**< @brief [25] 0..6 resource type, never gold*/
		unsigned _u3          : 3;  /**< @brief [29]*/
	};
	/**
	 * @brief data for corpse on adventure map
	 *
	 */
	struct MapCorpse
	{
		unsigned  id          : 5;  /**< @brief [00] 0..31 corpse index*/
		unsigned _u1          : 1;  /**< @brief [05]*/
		unsigned  artifactID  : 10; /**< @brief [06] 0..1023 artifact ID*/
		unsigned  hasArtifact : 1;  /**< @brief [16] whether the Corpse contains an artifact*/
		unsigned _u2          : 15; /**< @brief [17]*/
	};
	/**
	 * @brief creature generators type 1 and 4 (2&3 don't exist)
	 *
	 */
	struct MapGenerator
	{
		int id; /**< @brief [00] setup index*/
	};
	/**
	 * @brief data for magic spring on adventure map
	 *
	 */
	struct MapMagicSpring
	{
		unsigned  id   : 5;  /**< @brief [00] 0..31 Magic Spring index*/
		unsigned _u1   : 1;  /**< @brief [05]*/
		unsigned  used : 1;  /**< @brief [06] did a hero already visit this week*/
		unsigned _u2   : 25; /**< @brief [07]*/
	};
	/**
	 * @brief data for water mill on adventure map
	 *
	 */
	struct MapWaterMill
	{
		unsigned  bonus   : 5;  /**< @brief [00] 0..2 multiply by 500 to get gold amount*/
		unsigned  visited : 8;  /**< @brief [05] which players have come by*/
		unsigned _u1      : 19; /**< @brief [13]*/
	};
	/**
	 * @brief data for creature banks on adventure map
	 *
	 */
	struct MapCreatureBank
	{
		unsigned _u1      : 5; /**< @brief [00]*/
		unsigned  visited : 8; /**< @brief [05] which players have come by*/
		unsigned  id      : 12;/**< @brief [13] 0..4095 Creature Bank setup index*/
		unsigned  taken   : 1; /**< @brief [25] whether the bank was cleared*/
		unsigned _u2      : 6; /**< @brief [26]*/
	};
	/**
	 * @brief data for hero on adventure map
	 *
	 */
	struct MapHero
	{
		int index; /**< @brief [00] hero's identity*/
	};
	/**
	 * @brief data for pyramid on adventure map
	 *
	 */
	struct MapPyramid
	{
		unsigned  available : 1;  /**< @brief [00] whether the Pyramid is still up for grabs*/
		unsigned  id        : 4;  /**< @brief [01] 0..15*/
		unsigned  visited   : 8;  /**< @brief [05] which players have come by*/
		unsigned  spell     : 8;  /**< @brief [13] 0..69 spell id, reserved for level 5 spells*/
		unsigned _u1        : 11; /**< @brief [21]*/
	};
	/**
	 * @brief data for monoliths on adventure map
	 *
	 */
	struct MapMonolith
	{
		int  index; /**< @brief [00] only really used for 2-way monoliths, such that entrance != exit*/
	};
	/**
	 * @brief data for mystic garden on adventure map
	 *
	 */
	struct MapMysticGarden
	{
		unsigned  id      : 5;  /**< @brief [00] 0..31 unique ID*/
		unsigned _u1      : 1;  /**< @brief [05]*/
		unsigned  resType : 4;  /**< @brief [06] 5..6 gems or gold*/
		unsigned  hasRes  : 1;  /**< @brief [10] whether the garden contains anything this week*/
		unsigned _u2      : 21; /**< @brief [11]*/
	};
	/**
	 * @brief data for windmill on adventure map
	 *
	 */
	struct MapWindmill
	{
		unsigned  resType  : 4;  /**< @brief [00] 1..5, no wood or gold*/
		unsigned _u1       : 9;  /**< @brief [04]*/
		unsigned  resValue : 4;  /**< @brief [13] 3..6 amount of resource, 0 if empty*/
		unsigned _u2       : 15; /**< @brief [17]*/
	};
	/**
	 * @brief data for mine/lighthouse on adventure map
	 *
	 */
	struct MapMine
	{
		int index; /**< @brief [00] index of custom setup*/
	};
	/**
	 * @brief data for shipyard on adventure map
	 *
	 */
	struct MapShipyard
	{
		unsigned  owner : 8; /**< @brief [00] current owner*/
		unsigned  x     : 8; /**< @brief [08]*/
		unsigned  y     : 8; /**< @brief [16]*/
		unsigned _u3    : 8; /**< @brief [24]*/
	};
	/**
	 * @brief data for magic shrine on adventure map
	 *
	 */
	struct MapMagicShrine
	{
		unsigned _u1    : 13; /**< @brief [00]*/
		unsigned  spell : 10; /**< @brief [13] 0..1023 spell ID*/
		unsigned _u2    : 9;  /**< @brief [23]*/
	};
	/**
	 * @brief data for university on adventure map
	 *
	 */
	struct MapUniversity
	{
		unsigned _u1      : 5;  /**< @brief [00]*/
		unsigned  visited : 8;  /**< @brief [05] which players have come by*/
		unsigned  id      : 12; /**< @brief [13]*/
		unsigned _u2      : 7;  /**< @brief [25]*/
	};
	/**
	 * @brief data for Flotsam on adventure map
	 *
	 */
	struct MapFlotsam
	{
		/**
		 * @brief [00] reward type
		 * 0 - empty
		 * 1 - 5 wood
		 * 2 - 5 wood & 200 gold
		 * 3 - 10 wood & 500 gold
		 */
		int type;
	};

	/**
	 * @brief data for Fountain of Fortune on adventure map
	 *
	 */
	struct MapFountainFortune
	{
		unsigned _u1       : 5;	 /**< @brief [00]*/
		unsigned visited   : 8;	 /**< @brief [05] which players have come by*/
		  signed bonusLuck : 4;	 /**< @brief [13] -1..3 luck bonus */
		unsigned _u2       : 15; /**< @brief [17]*/
	};
}

#endif /* #define _H3MAPITEMS_HPP_ */