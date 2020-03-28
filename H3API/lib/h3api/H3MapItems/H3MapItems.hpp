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

#ifndef _H3MAPITEMS_HPP_
#define _H3MAPITEMS_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

namespace h3
{
	// * data for wandering monsters on adventure map
	struct MapMonster
	{
		unsigned  count           : 12;// +00 max 4095
		unsigned  aggression      : 5; // for diplomacy
		unsigned  noRun           : 1; // +17
		unsigned  noGrowth        : 1; // +18
		unsigned  setupIndex      : 8; // +19 up to 256 individual messages/prizes
		unsigned  growthRemainder : 4; // +27 remainder of the division by 10 for growth
		unsigned  hasSetup        : 1; // +31
	};

	// * data for wandering monsters on adventure map, as of SoD_SP 1.18
	struct SODSP_MapMonster
	{
		unsigned  count      : 12; // +00 max 4095
		unsigned  aggression : 5;  // for diplomacy
		unsigned  noRun      : 1;  // +17
		unsigned  noGrowth   : 1;  // +18
		unsigned  setupIndex : 12; // +19 up to 4096 individual messages/prizes. Extra growth is handled using the same game logic, just not stored
		unsigned  hasSetup   : 1;  // +31
	};

	// * data for artifact on the map
	struct MapArtifact
	{
		/*
		 * RoE-style artifact pickup requirements
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
		unsigned id       : 12; // reference to its structure, max 4096
		unsigned hasSetup : 1;
	};

	struct MapScroll
	{
		unsigned  type     : 8;
		unsigned _u1       : 11;
		unsigned  id       : 12; // reference to its structure, max 4096
		unsigned  hasSetup : 1;
	};

	// * data for scholar on adventure map
	struct MapScholar
	{
		unsigned  type   : 3; // 0 Primary, 1 Secondary, 2 Spell
		unsigned  pSkill : 3;
		unsigned  sSkill : 7;
		unsigned  spell  : 10;
		unsigned _u1     : 9;
	};

	// * data for event on adventure map
	// * Pandora's box is the same but only has 'id' entry
	struct MapEvent
	{
		unsigned  id        : 10; // Up to 1024
		unsigned  enabled   : 8; // which players can activate it?
		unsigned  aiEnabled : 1; // can AI activate it?
		unsigned  oneVisit  : 1; // Cancel after 1 visit?
		unsigned _u1        : 12; // ?unused? ==> could be used to expand number of uniques
	};

	// * data for treasure chest on adventure map
	struct MapTreasureChest
	{
		unsigned artifactID  : 10;
		unsigned hasArtifact : 1;
		unsigned bonus       : 4;
		unsigned _u1         : 17;
	};

	// * data for resource on adventure map
	struct MapResource
	{
		unsigned value      : 19;  // up to 524,287
		unsigned setupIndex : 12;  // for guardians and message
		unsigned hasSetup   : 1;  // TRUE/FALSE
	};

	// * data for sea chest on adventure map
	struct MapSeaChest
	{
		unsigned level      : 2;
		unsigned _u1        : 1;
		unsigned artifactID : 10;
		unsigned _u2        : 19;
	};

	// * data for warrior's tomb on adventure map
	struct MapWarriorsTomb
	{
		unsigned  hasArt     : 1;  // TRUE/FALSE
		unsigned _u1         : 4;
		unsigned  visited    : 8; // which players have come by
		unsigned  artifactID : 10;
		unsigned _u2         : 9;
	};

	// * data for tree of knowledge on adventure map
	struct MapTreeOfKnowledge
	{
		unsigned  id      : 5;  // up to 32
		unsigned  visited : 8;  // for players
		unsigned  type    : 2;  // 0,1,2 ~ cost
		unsigned _u1      : 17;
	};

	// * data for campfire on adventure map
	struct MapCampfire
	{
		unsigned  resType  : 4; // crystal, ...
		unsigned  resValue : 28; // resource = ResVal, gold = 100 * ResVal
	};

	// * data for lean to on adventure map
	struct MapLeanTo
	{
		unsigned  id       : 5;
		unsigned _u1       : 1;
		unsigned  resValue : 4;
		unsigned  resType  : 4;
		unsigned _u2       : 18;
	};

	// * data for witch's hut on adventure map
	struct MapWitchHut
	{
		unsigned _u1      : 5;
		signed    visited : 8;
		signed    sSkill  : 7; // id
		unsigned _u2      : 12;
	};

	// * data for learning stone on adventure map
	struct MapLearningStone
	{
		int id;
	};

	// * data for wagon on adventure map
	struct MapWagon
	{
		unsigned  resValue    : 5;
		signed    visited     : 8;
		unsigned  hasBonus    : 1;
		unsigned  hasArtifact : 1;
		unsigned  artifactID  : 10;
		unsigned  resType     : 4;
		unsigned _u3          : 3;
	};

	// * data for corpse on adventure map
	struct MapCorpse
	{
		unsigned  id          : 5;
		unsigned _u1          : 1;
		unsigned  artifactID  : 10;
		unsigned  hasArtifact : 1;
		unsigned _u2          : 15;
	};

	// * creature generators type 1 and 4 (2&3 don't exist)
	struct MapGenerator
	{
		int id;
	};

	// * data for magic spring on adventure map
	struct MapMagicSpring
	{
		unsigned  id   : 5;
		unsigned _u1   : 1;
		unsigned  used : 1;
		unsigned _u2   : 25;
	};

	// * data for water mill on adventure map
	struct MapWaterMill
	{
		unsigned  bonus   : 5; // gold = 500 * Bonus
		unsigned  visited : 8;
		unsigned _u1      : 19;
	};

	// * data for creature banks on adventure map
	struct MapCreatureBank
	{
		unsigned _u1      : 5;
		unsigned  visited : 8;
		unsigned  id      : 12;
		unsigned  taken   : 1;
		unsigned _u2      : 6;
	};

	// * data for hero on adventure map
	struct MapHero
	{
		int index;
	};

	// * data for pyramid on adventure map
	struct MapPyramid
	{
		unsigned  available : 1;
		unsigned  id        : 4;
		unsigned  visited   : 8;
		unsigned  spell     : 8;
		unsigned _u1        : 11;
	};

	// * data for swan pond on adventure map
	struct MapSwanPond
	{
		unsigned  id        : 5;
		unsigned  visited   : 8; //
		unsigned  bonusLuck : 4; // 1...3
		unsigned _u3        : 15;
	};

	// * data for monoliths on adventure map
	struct MapMonolith
	{
		// * only really used for 2-way monoliths, such that entrance != exit
		int  index;
	};

	// * data for mystic garden on adventure map
	struct MapMysticGarden
	{
		unsigned  id      : 5;
		unsigned _u1      : 1;
		unsigned  resType : 4;
		unsigned  hasRes  : 1;
		unsigned _u2      : 21;
	};

	// * data for windmill on adventure map
	struct MapWindmill
	{
		unsigned  resType  : 4;
		unsigned _u1       : 9;
		unsigned  resValue : 4;
		unsigned _u2       : 15;
	};

	// * data for mine/lighthouse on adventure map
	struct MapMine
	{
		int index;
	};

	// * data for shipyard on adventure map
	struct MapShipyard
	{
		unsigned  owner : 8;
		unsigned  x     : 8;
		unsigned  y     : 8;
		unsigned _u3    : 8;
	};

	// * data for magic shrine on adventure map
	struct MapMagicShrine
	{
		unsigned _u1    : 13;
		unsigned  spell : 10;
		unsigned _u2    : 9;
	};

	// * data for university on adventure map
	struct MapUniversity
	{
		unsigned _u1      : 5;
		unsigned  visited : 8;
		unsigned  id      : 12;
		unsigned _u2      : 7;
	};
}

#endif /* #define _H3MAPITEMS_HPP_ */