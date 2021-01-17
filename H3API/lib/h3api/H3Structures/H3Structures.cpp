//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Structures.hpp"
#include "H3Structures.inl"
#include "../H3_BinaryItems.hpp"

namespace h3
{
	_H3API_ H3NetworkData::H3NetworkData(int recipient_id, int msg_id, int data) :
		recipientId(recipient_id),
		msgId(msg_id),
		bufferSize(sizeof(H3NetworkData)),
		shortData(data)
	{
	}
	_H3API_ INT32 H3NetworkData::SendData()
	{
		return FASTCALL_4(INT32, 0x5549E0, this, 127, 0, 1);
	}

	_H3API_ BOOL H3ZStream::Save(PVOID data, UINT data_size)
	{
		return THISCALL_3(UINT, vTable->write, this, data, data_size) == data_size;
	}
	_H3API_ BOOL H3ZStream::Load(PVOID data, UINT data_size)
	{
		return THISCALL_3(UINT, vTable->read, this, data, data_size) == data_size;
	}

	_H3API_ BOOL H3ZStream::Read(H3String& string)
	{
		return FASTCALL_2(INT32, 0x4C5CD0, this, &string) >= 0;
	}

	_H3API_ BOOL H3ZStream::ReadString(H3String& string)
	{
		return FASTCALL_2(INT32, 0x4BB650, this, &string) >= 0;
	}

	_H3API_ BOOL H3ZStream::Write(const H3String& string)
	{
		if (!Write(string.Length()))
			return FALSE;
		return Save(PVOID(string.String()), string.Length());
	}

	_H3API_ BOOL H3ZStream::WriteString(const H3String& string)
	{
		return FASTCALL_2(INT32, 0x4BB820, this, &string) >= 0;
	}

	_H3API_ H3ZStream::H3ZStream(LPCSTR file_name, LPCSTR mode)
	{
		THISCALL_3(H3ZStream*, 0x4D6EB0, this, file_name, mode);
	}

	_H3API_ H3ZStream::~H3ZStream()
	{
		THISCALL_1(VOID, 0x4D6FC0, this);
	}

	_H3API_ H3Position::H3Position() :
		pos()
	{
	}

	_H3API_ H3Position::H3Position(INT16 x, INT16 y, INT8 z)
	{
		THISCALL_4(H3Position&, 0x419210, this, x, y, z);
	}

	_H3API_ H3Position::operator UINT() const
	{
		return pos;
	}
	_H3API_ UINT H3Position::Mixed()
	{
		return pos;
	}
	_H3API_ UINT H3Position::GetX()
	{
		return UnpackX(pos);
	}
	_H3API_ UINT H3Position::GetY()
	{
		return UnpackY(pos);
	}
	_H3API_ UINT8 H3Position::GetZ()
	{
		return UnpackZ(pos);
	}
	_H3API_ VOID H3Position::GetXYZ(INT& x, INT& y, INT& z)
	{
		UnpackXYZ(pos, x, y, z);
	}
	_H3API_ VOID H3Position::SetX(INT16 x)
	{
		pos &= ~0x3FF;
		pos |= (x & 0x3FF);
	}
	_H3API_ VOID H3Position::SetY(INT16 y)
	{
		pos &= ~0x03FF0000;
		pos |= ((y & 0x3FF) << 16);
	}
	_H3API_ VOID H3Position::SetZ(INT16 z)
	{
		pos &= ~0x04000000;
		pos |= ((z & 1) << 26);
	}
	_H3API_ VOID H3Position::SetXYZ(INT x, INT y, INT z)
	{
		pos = Pack(x, y, z);
	}
	_H3API_ UINT H3Position::Pack(INT x, INT y, INT z)
	{
		return ((x & 0x3FF) | ((y & 0x3FF) << 0x10) | ((z & 1) << 0x1A));
	}
	_H3API_ VOID H3Position::UnpackXYZ(UINT coord, INT& x, INT& y, INT& z)
	{
		x = UnpackX(coord);
		y = UnpackY(coord);
		z = UnpackZ(coord);
	}
	_H3API_ UINT H3Position::UnpackX(UINT coord)
	{
		return coord & 0x3FF;
	}
	_H3API_ UINT H3Position::UnpackY(UINT coord)
	{
		return (coord >> 16) & 0x3FF;
	}
	_H3API_ UINT8 H3Position::UnpackZ(UINT coord)
	{
		return (coord >> 26) & 1;
	}

	_H3API_ H3Resources::H3Resources() :
		wood(0),
		mercury(0),
		ore(0),
		sulfur(0),
		crystal(0),
		gems(0),
		gold(0)
	{
	}
	_H3API_ H3Resources::H3Resources(H3Resources const& other) :
		wood(other.wood),
		mercury(other.mercury),
		ore(other.ore),
		sulfur(other.sulfur),
		crystal(other.crystal),
		gems(other.gems),
		gold(other.gold)
	{
	}
	_H3API_ BOOL H3Resources::EnoughResources(const H3Resources& cost) const
	{
		return *this >= cost;
	}
	_H3API_ VOID H3Resources::RemoveResources(const H3Resources& cost)
	{
		operator-=(cost);
	}
	_H3API_ VOID H3Resources::GainResourcesOF(const H3Resources& gain)
	{
		operator+=(gain);
	}
	_H3API_ INT H3Resources::Count() const
	{
		INT r = 0;
		for (int i = 0; i < 7; ++i)
			if (asArray[i] != 0)
				++r;
		return r;
	}
	_H3API_ PINT H3Resources::begin()
	{
		return asArray;
	}
	_H3API_ PINT H3Resources::end()
	{
		return &asArray[7];
	}
	_H3API_ PINT H3Resources::cbegin() const
	{
		return PINT(this);
	}
	_H3API_ PINT H3Resources::cend() const
	{
		return PINT(&asArray[7]);
	}
	_H3API_ H3Resources& H3Resources::operator+=(const H3Resources& other)
	{
		for (int i = 0; i < 7; ++i)
			if (asArray[i] > 0) // positive
			{
				asArray[i] += other.asArray[i]; // add resources

				if (other.asArray[i] > 0) // check if there was overflow
				{
					if (asArray[i] <= 0)
						asArray[i] = INT_MAX;
				}
				else if (asArray[i] < 0) // no negative resources from subtraction
					asArray[i] = 0;
			}
			else // gain normally
				asArray[i] += other.asArray[i];
		return *this;
	}
	_H3API_ H3Resources& H3Resources::operator-=(const H3Resources& other)
	{
		for (int i = 0; i < 7; ++i)
		{
			if (asArray[i] >= 0)
				asArray[i] = std::max(0, asArray[i] - other.asArray[i]);
			else
				asArray[i] -= other.asArray[i];
		}
		return *this;
	}
	_H3API_ H3Resources& H3Resources::operator=(const H3Resources& other)
	{
		for (int i = 0; i < 7; ++i)
			asArray[i] = other.asArray[i];
		return *this;

	}
	_H3API_ BOOL H3Resources::operator>=(const H3Resources & other) const
	{
		return !(*this < other);
	}
	_H3API_ BOOL H3Resources::operator>(const H3Resources & other) const
	{
		return other < *this;
	}
	_H3API_ BOOL H3Resources::operator<(const H3Resources & other) const
	{
		for (int i = 0; i < 7; ++i)
			if (other.asArray[i] > asArray[i])
				return TRUE;
		return FALSE;
	}
	_H3API_ BOOL H3Resources::operator<=(const H3Resources & other) const
	{
		return !(*this > other);
	}
	_H3API_ INT & H3Resources::operator[](int index)
	{
		return asArray[index];
	}

	_H3API_ H3Army::iterator::iterator(INT32* type) :
		m_type(type)
	{
	}
	_H3API_ H3Army::iterator& H3Army::iterator::operator*()
	{
		return *this;
	}
	_H3API_ H3Army::iterator& H3Army::iterator::operator++()
	{
		++m_type;
		return *this;
	}
	_H3API_ H3Army::iterator H3Army::iterator::operator++(int)
	{
		iterator it(m_type);
		++m_type;
		return it;
	}
	_H3API_ BOOL H3Army::iterator::operator==(const iterator& other)
	{
		return m_type == other.m_type;
	}
	_H3API_ BOOL H3Army::iterator::operator!=(const iterator& other)
	{
		return m_type != other.m_type;
	}
	_H3API_ BOOL H3Army::iterator::operator!() const
	{
		return *m_type == -1;
	}
	_H3API_ INT32& H3Army::iterator::Type()
	{
		return *m_type;
	}
	_H3API_ INT32& H3Army::iterator::Count()
	{
		return m_type[7];
	}

	_H3API_ VOID H3Army::AddStack(INT32 type, INT32 amount, INT32 slot)
	{
		THISCALL_4(VOID, 0x44A9B0, this, type, amount, slot);
	}
	_H3API_ VOID H3Army::SplitFromStackToStack(INT32 fromStack, INT32 toStack, INT32 fraction)
	{
		INT32 num = count[fromStack] / fraction;
		count[fromStack] -= num;
		AddStack(type[fromStack], num, toStack);
	}
	_H3API_ INT32 H3Army::FirstFreeSlot()
	{
		INT32 r = 0;
		for (INT32 i = 0; i < 7; i++)
		{
			if (type[i] != -1)
				r++;
			else
				return r;
		}
		return -1;
	}
	_H3API_ INT32 H3Army::FindExistingByIndex(INT32 index)
	{
		if (index >= 0 && index < 7)
		{
			int j = 0;
			for (int i = 0; i < 7; i++)
			{
				if (type[i] != -1)
					j++;
				if (j == index)
					return i;
			}
		}
		return -1;
	}
	_H3API_ INT32 H3Army::GetStackCount()
	{
		return THISCALL_1(INT32, 0x44A990, this);
	}
	_H3API_ INT32 H3Army::GetCreaturesCount()
	{
		return THISCALL_1(INT32, 0x44AA70, this);
	}
	_H3API_ BOOL8 H3Army::HasCreatureType(INT32 cre)
	{
		return THISCALL_2(BOOL8, 0x44A850, this, cre);
	}
	_H3API_ BOOL H3Army::HasCreatures()
	{
		return THISCALL_1(BOOL, 0x449370, this);
	}
	_H3API_ VOID H3Army::Clear()
	{
		THISCALL_1(VOID, 0x44A750, this);
	}
	_H3API_ VOID H3Army::Clear(INT stack)
	{
		THISCALL_2(VOID, 0x44A830, this, stack);
	}
	_H3API_ VOID H3Army::ClearAndGive(INT type, INT count)
	{
		THISCALL_3(VOID, 0x44A770, this, type, count);
	}
	_H3API_ BOOL8 H3Army::IsUndeadArmy()
	{
		return THISCALL_1(BOOL8, 0x44A7F0, this);
	}
	_H3API_ INT32 H3Army::NumberAlignments(INT8(&towns)[9])
	{
		return THISCALL_2(INT32, 0x44A880, this, &towns);
	}
	_H3API_ INT32 H3Army::GetArmyValue()
	{
		return THISCALL_1(INT32, 0x44A950, this);
	}
	_H3API_ H3Army::iterator H3Army::begin()
	{
		return iterator(type);
	}
	_H3API_ H3Army::iterator H3Army::end()
	{
		return iterator(type + 7);
	}
	_H3API_ H3Army& H3Army::operator=(const H3Army& other)
	{
		for (int i = 0; i < 7; ++i)
		{
			count[i] = other.count[i];
			type[i] = other.type[i];
		}
		return *this;
	}

	_H3API_ H3Army::iterator H3Army::operator[](UINT index)
	{
		return iterator(type + index);
	}

	_H3API_ INT32 H3Hero::MaxLandMovement()
	{
		return THISCALL_2(INT32, 0x4E4C00, this, 0);
	}
	_H3API_ INT32 H3Hero::MaxWaterMovement()
	{
		return THISCALL_2(INT32, 0x4E4C00, this, 1);
	}
	_H3API_ INT32 H3Hero::CalcMaxMovement()
	{
		return THISCALL_1(INT32, 0x4E5000, this);
	}
	_H3API_ VOID H3Hero::GiveArtifact(H3Artifact& art, INT32 slot)
	{
		THISCALL_3(VOID, 0x4E2C70, this, &art, slot);
	}
	_H3API_ VOID H3Hero::GiveArtifact(H3Artifact & art)
	{
		THISCALL_4(void, 0x4E32E0, this, &art, 0, 0);
	}
	_H3API_ VOID H3Hero::GiveBackpackArtifact(H3Artifact & art, INT32 index)
	{
		THISCALL_3(void, 0x4E3200, this, &art, index);
	}
	_H3API_ VOID H3Hero::LearnSecondarySkill(INT32 id, INT32 increase)
	{
		return THISCALL_3(VOID, 0x4E2540, this, id, increase);
	}
	_H3API_ INT32 H3Hero::GetSpellExpertise(INT32 spell_id, INT32 special_terrain)
	{
		return THISCALL_3(INT32, 0x4E52F0, this, spell_id, special_terrain);
	}
	_H3API_ BOOL8 H3Hero::HasCreatureType(INT32 type)
	{
		return army.HasCreatureType(type);
	}
	_H3API_ INT32 H3Hero::GetSpellSpecialtyEffect(INT32 spellID, INT32 creatureLevel, INT32 baseDamage)
	{
		return THISCALL_4(INT32, 0x4E6260, this, spellID, creatureLevel, baseDamage);
	}
	_H3API_ INT32 H3Hero::GetSorceryEffect(INT32 spellID, INT32 baseDamage, H3CombatMonster* mon)
	{
		return THISCALL_4(INT32, 0x4E59D0, this, spellID, baseDamage, mon);
	}
	_H3API_ INT32 H3Hero::GetRealSpellDamage(INT32 baseDamage, H3CombatMonster* mon, INT32 spellID, H3Hero* enemy)
	{
		INT32 dmg = GetSorceryEffect(spellID, baseDamage, mon);
		dmg = FASTCALL_3(INT32, 0x44B180, dmg, spellID, mon->type); // golem-style resistance
		return mon->GetProtectiveSpellEffect(dmg, spellID);
	}
	_H3API_ INT32 H3Hero::GetSpecialTerrain()
	{
		return THISCALL_1(INT32, 0x4E5130, this);
	}
	_H3API_ INT32 H3Hero::GetSpecialSpellTerrain()
	{
		return THISCALL_1(INT32, 0x4E5210, this);
	}
	_H3API_ BOOL H3Hero::HasSpell(INT32 spell)
	{
		return learnedSpells[spell] | availableSpells[spell];
	}
	_H3API_ VOID H3Hero::BuildCombinationArtifact(INT32 combo_id)
	{
		THISCALL_3(VOID, 0x4DC1A0, this, combo_id, -1);
	}
	_H3API_ BOOL H3Hero::UnlearnSkill(INT32 id)
	{
		if (secSkill[id])
		{
			secSkill[id] = 0;
			int pos = secSkillPosition[id];
			secSkillPosition[id] = 0;
			for (int i = 0; i < 28; i++)
			{
				if (secSkillPosition[i] > pos)
					secSkillPosition[i] -= 1;
			}
			secSkillCount -= 1;
			return TRUE;
		}
		return FALSE;
	}
	_H3API_ VOID H3Hero::RecalculateMovement()
	{
		H3AdventureManager* adv = H3Internal::_adventureManager();
		adv->movementCalculated = 0;
		adv->movementCalculated1 = 0;
		if (dest_x != -1)
		{
			adv->MovementCalculations(H3Position::Pack(dest_x, dest_y, dest_z));
			adv->MakeHeroPath();
		}
	}
	_H3API_ BOOL8 H3Hero::CanFlyOnTile()
	{
		return THISCALL_1(BOOL8, 0x4E5F50, this);
	}
	_H3API_ INT32 H3Hero::GetMovementCost(INT32 orientation, UINT32 mixedPos)
	{
		return FASTCALL_4(INT32, 0x4B1620, this, orientation, mixedPos, movement);
	}
	_H3API_ INT32 H3Hero::SSkillsLeftToLearn()
	{
		int known_skills = 0;
		for (int i = 0; i < 28; i++)
			known_skills += secSkill[i];

		int maxSkills = 3 * ByteAt(0x4E256A); // usually 3 * 8

		if (known_skills >= maxSkills)
			return 0;

		// hero has not learned all of his available skills
		int skills_can_be_learned = 0;

		int sslevel;
		H3Main* main = H3Internal::_main();

		for (int i = 0; i < 28; i++)
		{
			sslevel = secSkill[i];
			if (!main->bannedSkills[i] || sslevel > 0)
				skills_can_be_learned += 3 - sslevel;
		}
		// only necropolis heroes can learn necromancy, unless hero already has it
		if (hero_class != NH3Heroes::NECROMANCER && hero_class != NH3Heroes::DEATH_KNIGHT && secSkill[NH3Skills::NECROMANCY] == 0 && !main->bannedSkills[NH3Skills::NECROMANCY])
			skills_can_be_learned -= 3;
		// necropolis heroes cannot learn leadership, unless hero already has it
		if ((hero_class == NH3Heroes::NECROMANCER || hero_class == NH3Heroes::DEATH_KNIGHT) && secSkill[NH3Skills::LEADERSHIP] == 0 && !main->bannedSkills[NH3Skills::LEADERSHIP])
			skills_can_be_learned -= 3;
		// dungeon heroes cannot learn water magic, unless hero already has it
		if ((hero_class == NH3Heroes::OVERLORD || hero_class == NH3Heroes::WARLOCK) && secSkill[NH3Skills::WATER_MAGIC] == 0 && !main->bannedSkills[NH3Skills::WATER_MAGIC])
			skills_can_be_learned -= 3;
		// rampart heroes cannot learn fire magic, unless hero already has it
		if ((hero_class == NH3Heroes::RANGER || hero_class == NH3Heroes::DRUID) && secSkill[NH3Skills::FIRE_MAGIC] == 0 && !main->bannedSkills[NH3Skills::FIRE_MAGIC])
			skills_can_be_learned -= 3;

		skills_can_be_learned = std::min(maxSkills - known_skills, skills_can_be_learned);
		skills_can_be_learned = std::max(skills_can_be_learned, 1);
		return skills_can_be_learned - 1; // -1 because it's already included in formula for level to go to
	}
	_H3API_ BOOL H3Hero::WearsArtifact(INT id)
	{
		return THISCALL_2(BOOL, 0x4D9460, this, id);
	}
	_H3API_ INT32 H3Hero::GetHeroPrimary(INT primary)
	{
		return THISCALL_2(INT32, 0x5BE240, this, primary);
	}
	_H3API_ INT32 H3Hero::HasSimilarCreature(INT id)
	{
		return FASTCALL_2(INT32, 0x4A7230, this, id);
	}
	_H3API_ LPCSTR H3Hero::GetHeroClassName()
	{
		return THISCALL_1(LPCSTR, 0x4D91E0, this);
	}
	_H3API_ VOID H3Hero::ShowDialog() const
	{
		return FASTCALL_4(VOID, 0x4E1A70, id, 1, 1, 1);
	}
	_H3API_ INT H3Hero::GetPower() const
	{
		return THISCALL_1(INT32, 0x427650, this);
	}
	_H3API_ BOOL8 H3Hero::CanReplaceArtifact(int id, int slot) const
	{
		return THISCALL_3(BOOL8, 0x4E2AB0, this, id, slot);
	}
	_H3API_ BOOL8 H3Hero::CanPlaceArtifact(int id, int slot) const
	{
		return THISCALL_3(BOOL8, 0x4E27C0, this, id, slot);
	}
	_H3API_ VOID H3Hero::RemoveArtifact(int slot)
	{
		THISCALL_2(VOID, 0x4E2E40, this, slot);
	}
	_H3API_ VOID H3Hero::RemoveBackpackArtifact(int slot)
	{
		THISCALL_2(VOID, 0x4E2FC0, this, slot);
	}
	_H3API_ VOID H3Hero::ShowCreatureDialog(int slot, BOOL rightClick)
	{
		THISCALL_9(VOID, 0x4C6910, H3Internal::_main(), &army, slot, this, 0, 119, 20, 0, rightClick);
	}
	_H3API_ VOID H3Hero::ShowSpellInfo(int spell, BOOL RMB)
	{
		int expertise = GetSpellExpertise(spell, GetSpecialSpellTerrain());
		FASTCALL_12(VOID, 0x4F6C00, H3Internal::_spell()[spell].description[expertise],
					RMB ? 4 : 1, -1, -1, 9, spell, -1, 0, - 1, 0, - 1, 0);
	}
	_H3API_ VOID H3Hero::ShowSSkillInfo(int skill, BOOL RMB)
	{
		int lvl = secSkill[skill];
		if (lvl == 0)
			lvl = 1;
		int frame = 3 * skill + 1 + lvl;
		FASTCALL_12(VOID, 0x4F6C00, H3Internal::_secondarySkillsInfo(skill).description[lvl],
			RMB ? 4 : 1, -1, -1, 20, frame, -1, 0, -1, 0, -1, 0);
	}
	_H3API_ VOID H3Hero::ShowPSkillInfo(int skill, BOOL RMB)
	{
		int value = GetHeroPrimary(skill) | 0x100000; // removes the '+' in front of number
		FASTCALL_12(VOID, 0x4F6C00, StrAt(0x6A75A8 + 4 * skill),
			RMB ? 4 : 1, -1, -1, 34, value, -1, 0, -1, 0, -1, 0);
	}
	_H3API_ BOOL H3Hero::HasAllCombinationParts(INT slot)
	{
		// game code uses bitfields to determine this
		// this code is flexible in the sense that it doesn't
		// rely on unknown-at-compile-time bitfield length
		// the downside is that it is less efficient

		int artId = bodyArtifacts[slot].id;
		if (id == -1)
			return FALSE;

		int comboId = H3Internal::_artifactSetup()[artId].comboID;
		if (comboId != -1) // it's already a combination artifact
			return FALSE;
		comboId = H3Internal::_artifactSetup()[artId].partOfCombo;
		if (comboId == -1) // not part of a combination
			return FALSE;

		int numArts = H3Internal::_artifactCount();

		for (int i = 0; i < numArts; ++i)
		{
			if (H3Internal::_artifactSetup()[i].partOfCombo == comboId)
			{
				if (!WearsArtifact(i))
					return FALSE;
			}
		}

		return TRUE;
	}
	_H3API_ VOID H3Hero::DisassembleCombinationArtifact(INT slot)
	{
		int artId = bodyArtifacts[slot].id;
		if (artId == -1)
			return;
		int comboId = H3Internal::_artifactSetup()[artId].comboID;
		if (comboId == -1) // not a combo artifact
			return;
		RemoveArtifact(slot);
		int numArts = H3Internal::_artifactCount();
		for (int i = 0; i < numArts; ++i)
		{
			if (H3Internal::_artifactSetup()[i].partOfCombo == comboId)
			{
				H3Artifact art;
				art.id = i;
				art.subtype = -1;
				GiveArtifact(art);
			}
		}
	}
	_H3API_ INT32 H3Hero::CalculateSpellCost(INT spell, H3Army * opponentArmy, INT specialTerrain)
	{
		return THISCALL_4(INT32, 0x4E54B0, this, spell, opponentArmy, specialTerrain);
	}
	_H3API_ INT32 H3Hero::CalculateAdventureMapSpellCost(INT spell)
	{
		return CalculateSpellCost(spell, nullptr, GetSpecialSpellTerrain());
	}
	_H3API_ VOID H3Hero::RemoveSpellPointsAndRefresh(UINT16 spellPoints)
	{
		THISCALL_2(VOID, 0x4D9540, this, spellPoints);
	}
	_H3API_ VOID H3Hero::UpdateAvailableSpells()
	{
		THISCALL_1(VOID, 0x4D9840, this);
	}
	_H3API_ VOID H3Hero::Hide()
	{
		THISCALL_1(VOID, 0x4D7950, this);
	}
	_H3API_ VOID H3Hero::Show()
	{
		THISCALL_3(VOID, 0x4D7840, this, NH3Objects::eObjectTypes::HERO, id);
	}
	_H3API_ UINT32 H3Date::CurrentDay() const
	{
		return 28 * (month - 1) + 7 * (week - 1) + day - 1;
	}

	_H3API_ INT32& H3TownCreatureTypes::iterator::Base()
	{
		return *m_base;
	}
	_H3API_ H3TownCreatureTypes::iterator::iterator(INT32* base) :
		m_base(base)
	{
	}
	_H3API_ INT32& H3TownCreatureTypes::iterator::Upgraded()
	{
		return m_base[7];
	}
	_H3API_ H3TownCreatureTypes::iterator& H3TownCreatureTypes::iterator::operator*()
	{
		return *this;
	}
	_H3API_ H3TownCreatureTypes::iterator& H3TownCreatureTypes::iterator::operator++()
	{
		++m_base;
		return *this;
	}
	_H3API_ H3TownCreatureTypes::iterator H3TownCreatureTypes::iterator::operator++(int)
	{
		iterator it(m_base);
		++m_base;
		return it;
	}
	_H3API_ BOOL H3TownCreatureTypes::iterator::operator==(const iterator& other) const
	{
		return m_base == other.m_base;
	}
	_H3API_ BOOL H3TownCreatureTypes::iterator::operator!=(const iterator& other) const
	{
		return m_base != other.m_base;
	}

	_H3API_ H3TownCreatureTypes::iterator H3TownCreatureTypes::begin()
	{
		return iterator(base);
	}
	_H3API_ H3TownCreatureTypes::iterator H3TownCreatureTypes::end()
	{
		return iterator(base + 7);
	}
	_H3API_ BOOL H3Town::IsBuildingBuilt(INT32 id) const
	{
		return THISCALL_3(BOOL, 0x4305A0, this, id, id >= 32 ? 1 : 0);
	}
	_H3API_ LPCSTR H3Town::GetTownTypeName() const
	{
		return THISCALL_1(LPCSTR, 0x5C1850, this);
	}
	_H3API_ H3Hero* H3Town::GetGarrisonHero() const
	{
		return H3Internal::_main()->GetHero(garrisonHero);
	}
	_H3API_ H3Hero* H3Town::GetVisitingHero() const
	{
		return H3Internal::_main()->GetHero(visitingHero);
	}
	_H3API_ BOOL8 H3Town::IsMageGuildBuilt(INT level) const
	{
		return magicGuild[level];
	}
	_H3API_ H3String H3Town::GetNameAndType() const
	{
		H3String str(this->name);
		str.Append(", ").Append(GetTownTypeName());
		return str;
	}
	_H3API_ INT32 H3Town::GoldIncome(BOOL count_silo) const
	{
		return THISCALL_2(INT32, 0x5BFA00, this, count_silo ? 1 : 0);
	}
	_H3API_ H3Resources& H3Town::GetResourceSiloIncome() const
	{
		return THISCALL_1(H3Resources&, 0x5C1680, this);
	}
	_H3API_ H3TownCreatureTypes& H3Town::GetCreatureTypes() const
	{
		return H3Internal::_townCreatureTypes()[type];
	}
	_H3API_ BOOL H3Town::CanBeBuilt(eBuildings id) const
	{
		return buildableMask[0].GetState(int(id));
	}
	_H3API_ H3Resources H3Town::TotalIncome() const
	{
		H3Resources total;
		total.gold = GoldIncome(TRUE);
		total += GetResourceSiloIncome();
		return total;
	}
	_H3API_ H3Hero* H3Player::GetActiveHero()
	{
		return H3Internal::_main()->GetHero(currentHero);
	}
	_H3API_ H3ObjectDraw::H3ObjectDraw(UINT16 sprite, UINT8 tile_id, UINT8 layer) :
		sprite(sprite),
		tileID(tile_id),
		layer(layer)
	{
	}
	_H3API_ PINT H3University::begin()
	{
		return sSkill;
	}
	_H3API_ PINT H3University::end()
	{
		return &sSkill[4];
	}
	_H3API_ H3University* H3MapItem::GetUniversity()
	{
		return STDCALL_1(H3University*, 0x405DA0, this);
	}
	_H3API_ H3MapItem* H3MapItem::GetEntrance()
	{
		return THISCALL_1(H3MapItem*, 0x4FD0F0, this);
	}
	_H3API_ BOOL H3MapItem::IsEntrance() const
	{
		return access & 0x10;
	}
	_H3API_ BOOL H3MapItem::IsBlocked() const
	{
		return access & 0x01;
	}
	_H3API_ BOOL H3MapItem::CanDig() const
	{
		return access & 0x40;
	}
	_H3API_ INT H3MapItem::GetRealType() const
	{
		if (objectType != NH3Objects::HERO)
			return objectType;
		PH3Hero hero = H3Internal::_main()->GetHero(setup);
		if (!hero || !hero->objectBelow)
			return objectType;
		return hero->objectTypeUnder;
	}
	_H3API_ UINT H3MapItem::GetRealSetup() const
	{
		if (objectType != NH3Objects::HERO)
			return setup;
		PH3Hero hero = H3Internal::_main()->GetHero(setup);
		if (!hero || !hero->objectBelow)
			return setup;
		return hero->objectBelowSetup;
	}
	_H3API_ MapMonster* H3MapItem::CastMonster()
	{
		return (MapMonster*)this;
	}
	_H3API_ MapScholar* H3MapItem::CastScholar()
	{
		return (MapScholar*)this;
	}
	_H3API_ MapScroll * H3MapItem::CastScroll()
	{
		return (MapScroll*)this;
	}
	_H3API_ MapEvent* H3MapItem::CastEvent()
	{
		return (MapEvent*)this;
	}
	_H3API_ MapTreasureChest* H3MapItem::CastTreasureChest()
	{
		return (MapTreasureChest*)this;
	}
	_H3API_ MapWarriorsTomb* H3MapItem::CastWarriorsTomb()
	{
		return (MapWarriorsTomb*)this;
	}
	_H3API_ MapTreeOfKnowledge* H3MapItem::CastTreeKnowledge()
	{
		return (MapTreeOfKnowledge*)this;
	}
	_H3API_ MapCampfire* H3MapItem::CastCampfire()
	{
		return (MapCampfire*)this;
	}
	_H3API_ MapLeanTo* H3MapItem::CastLeanTo()
	{
		return (MapLeanTo*)this;
	}
	_H3API_ MapWitchHut* H3MapItem::CastWitchHut()
	{
		return (MapWitchHut*)this;
	}
	_H3API_ MapLearningStone* H3MapItem::CastLearningStone()
	{
		return (MapLearningStone*)this;
	}
	_H3API_ MapWagon* H3MapItem::CastWagon()
	{
		return (MapWagon*)this;
	}
	_H3API_ MapCorpse* H3MapItem::CastCorpse()
	{
		return (MapCorpse*)this;
	}
	_H3API_ MapMagicSpring* H3MapItem::CastMagicSpring()
	{
		return (MapMagicSpring*)this;
	}
	_H3API_ MapWaterMill* H3MapItem::CastWatermill()
	{
		return (MapWaterMill*)this;
	}
	_H3API_ MapCreatureBank* H3MapItem::CastCreatureBank()
	{
		return (MapCreatureBank*)this;
	}
	_H3API_ MapPyramid* H3MapItem::CastPyramid()
	{
		return (MapPyramid*)this;
	}
	_H3API_ MapMonolith* H3MapItem::CastMonolith()
	{
		return (MapMonolith*)this;
	}
	_H3API_ MapMysticGarden* H3MapItem::CastMysticGarden()
	{
		return (MapMysticGarden*)this;
	}
	_H3API_ MapWindmill* H3MapItem::CastWindmill()
	{
		return (MapWindmill*)this;
	}
	_H3API_ MapMine* H3MapItem::CastMine()
	{
		return (MapMine*)this;
	}
	_H3API_ MapShipyard* H3MapItem::CastShipyard()
	{
		return (MapShipyard*)this;
	}
	_H3API_ MapMagicShrine* H3MapItem::CastMagicShrine()
	{
		return (MapMagicShrine*)this;
	}
	_H3API_ MapUniversity* H3MapItem::CastUniversity()
	{
		return (MapUniversity*)this;
	}
	_H3API_ MapResource* H3MapItem::CastResource()
	{
		return (MapResource*)this;
	}
	_H3API_ MapSeaChest* H3MapItem::CastSeaChest()
	{
		return (MapSeaChest*)this;
	}
	_H3API_ MapArtifact* H3MapItem::CastArtifact()
	{
		return (MapArtifact*)this;
	}
	_H3API_ MapGenerator* H3MapItem::CastGenerator()
	{
		return (MapGenerator*)this;
	}
	_H3API_ BOOL H3CreatureBank::HasUpgradedStack()
	{
		return guardians.type[0] != guardians.type[2];
	}
	_H3API_ VOID H3CreatureBank::SetupBank(int type, int level)
	{
		H3CreatureBankState* cbs = &H3Internal::_creatureBankSetup()[type].states[level];
		guardians = cbs->guardians;
		resources = cbs->resources;
		creatureRewardType = cbs->creatureRewardType;
		creatureRewardCount = cbs->creatureRewardCount;

		const int stacks = guardians.GetStackCount();
		int stack_to_split;
		int first_free_slot;
		int fractions;
		switch (stacks)
		{
		case 1:
			fractions = 5;
			stack_to_split = 0;
			while (fractions > 1)
			{
				first_free_slot = guardians.FirstFreeSlot();
				if (first_free_slot != -1)
					guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);
				fractions--;
			}
			break;
		case 2:
			stack_to_split = 1;
			fractions = 2;
			first_free_slot = guardians.FirstFreeSlot();
			if (first_free_slot != -1)
				guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);

			fractions = 3;
			stack_to_split = 0;
			while (fractions > 1)
			{
				first_free_slot = guardians.FirstFreeSlot();
				if (first_free_slot != -1)
					guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);
				fractions--;
			}
			break;
		case 3:
			fractions = 2; // split in 2
			stack_to_split = 1; // stack 1 is first split
			first_free_slot = guardians.FirstFreeSlot();
			if (first_free_slot != -1)
				guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);

			stack_to_split = 0; // then stack 0 is split
			first_free_slot = guardians.FirstFreeSlot();
			if (first_free_slot != -1)
				guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);
			break;
		default:
			break;
		}
	}
	_H3API_ VOID H3CreatureBank::UpgradeStack(BOOL upg)
	{
		if (upg) // in code there are additional checks for game type (RoE) and creature (4 Elementals)
		{
			if (THISCALL_1(char, 0x47AA50, guardians.type[0])) // creature has upgrade?
				guardians.type[2] = THISCALL_1(INT32, 0x47AAD0, guardians.type[0]);
		}
		else
			guardians.type[2] = guardians.type[0];
	}
	_H3API_ INT32 H3Spell::GetBaseEffect(INT32 level, INT32 spellPower)
	{
		return base_value[level] + spellPower * sp_effect;
	}

	_H3API_ LPCSTR H3CreatureInformation::GetCreatureName(INT32 count)
	{
		return count > 1 ? namePlural : nameSingular;
	}

	_H3API_ H3Resources H3CreatureInformation::UpgradeCost(H3CreatureInformation* upg, INT32 count)
	{
		H3Resources res;
		res = upg->cost;
		res.RemoveResources(cost);
		for (PINT it = res.begin(); it != res.end(); ++it)
			*it *= count;
		return res;
	}

	_H3API_	LPCSTR H3CombatMonster::GetCreatureName()
	{
		return info.GetCreatureName(numberAlive);
	}
	_H3API_ INT32 H3CombatMonster::GetSecondSquare()
	{
		return THISCALL_1(INT32, 0x4463C0, this);
	}
	_H3API_ INT32 H3CombatMonster::GetStackSpeed()
	{
		return THISCALL_1(INT32, 0x4489F0, this);
	}
	_H3API_ INT32 H3CombatMonster::HexRelativePosition(INT32 considered_hex, INT32 relative_orientation)
	{
		return THISCALL_3(INT32, 0x524280, this, considered_hex, relative_orientation);
	}

	_H3API_ BOOL H3CombatMonster::IsDone()
	{
		return info.flags.done;
	}

	_H3API_ BOOL H3CombatMonster::IsClone()
	{
		return info.flags.clone;
	}

	_H3API_ BOOL H3CombatMonster::IsSiege()
	{
		return info.flags.siegeWeapon;
	}

	_H3API_ BOOL H3CombatMonster::IsSummon()
	{
		return info.flags.summon;
	}

	_H3API_ BOOL H3CombatMonster::HadMorale()
	{
		return info.flags.morale;
	}

	_H3API_ BOOL H3CombatMonster::IsWaiting()
	{
		return info.flags.waiting;
	}

	_H3API_ BOOL H3CombatMonster::HasMoved()
	{
		return info.flags.done;
	}

	_H3API_ INT32 H3CombatMonster::Index()
	{
		return sideIndex + 21 * side;
	}

	_H3API_ VOID H3CombatMonster::ShowStatsDialog(BOOL RightClick)
	{
		THISCALL_3(VOID, 0x468440, H3Internal::_combatManager(), this, RightClick);
	}

	_H3API_ INT32 H3CombatMonster::GetSide()
	{
		return THISCALL_1(INT, 0x43FE60, this);
	}

	_H3API_ H3Hero* H3CombatMonster::GetOwner()
	{
		return THISCALL_1(H3Hero*, 0x4423B0, this);
	}

	_H3API_ INT32 H3CombatMonster::GetProtectiveSpellEffect(INT32 damage, INT32 spellID)
	{
		return STDCALL_3(INT32, 0x5A7EC0, damage, spellID, this);
	}

	_H3API_ INT32 H3CombatMonster::MagicMirrorEffect()
	{
		return THISCALL_1(INT32, 0x448510, this);
	}

	_H3API_ INT32 H3CombatMonster::ApplyPhysicalDamage(INT32 amount)
	{
		return THISCALL_2(INT32, 0x443DB0, this, amount);
	}

	_H3API_ VOID H3CombatMonster::ApplySpell(INT32 spellId, INT32 spellPower, INT32 schoolLevel, H3Hero* hero)
	{
		return THISCALL_5(VOID, 0x444610, this, spellId, spellPower, schoolLevel, hero);
	}

	_H3API_ BOOL8 H3CombatMonster::CanReceiveSpell(INT32 spellId)
	{
		return FASTCALL_2(BOOL8, 0x4477A0, spellId, this);
	}

	_H3API_ BOOL H3CombatMonster::CanCastSpellAtEmptyHex(INT32 hexId)
	{
		return THISCALL_2(BOOL, 0x4470F0, this, hexId);
	}

	_H3API_ BOOL8 H3CombatMonster::MoveToHex(INT32 hexId)
	{
		return THISCALL_3(BOOL8, 0x445A30, this, hexId, 0);
	}

	_H3API_ BOOL8 H3CombatMonster::UseEnchanters()
	{
		return THISCALL_1(BOOL8, 0x447D00, this);
	}

	_H3API_ INT32 H3CombatMonster::GetX() const
	{
		return THISCALL_1(INT32, 0x446380, this);
	}

	_H3API_ INT32 H3CombatMonster::GetY() const
	{
		return THISCALL_1(INT32, 0x446350, this);
	}

	_H3API_ PINT8 H3PrimarySkills::begin()
	{
		return PINT8(this);
	}

	_H3API_ PINT8 H3PrimarySkills::end()
	{
		return &PINT8(this)[4] ;
	}

	_H3API_ INT32 H3Quest::QuestVector::Count()
	{
		return last - first;
	}

	_H3API_ INT32& H3Quest::QuestVector::operator[](INT32 index)
	{
		return first[index];
	}

	_H3API_ INT32* H3Quest::QuestVector::begin()
	{
		return first;
	}

	_H3API_ INT32* H3Quest::QuestVector::end()
	{
		return last;
	}

	_H3API_ H3Quest::eQuestType H3Quest::GetQuestType() const
	{
		return eQuestType((reinterpret_cast<DWORD>(vTable) - 0x641798) / 0x3C + 1);
	}

	_H3API_ H3Resources & H3Quest::GetResources()
	{
		return *reinterpret_cast<H3Resources*>(&data);
	}

	_H3API_ H3Quest::eQuestType H3QuestGuard::QuestType() const
	{
		return quest ? quest->GetQuestType() : H3Quest::eQuestType::QT_NONE;
	}

	_H3API_ WORD H3SeerHut::CreatureCount() const
	{
		return rewardValue2;
	}
	_H3API_ INT8 H3SeerHut::Luck() const
	{
		return INT8(rewardValue);
	}
	_H3API_ INT8 H3SeerHut::Morale() const
	{
		return INT8(rewardValue);
	}
	_H3API_ INT32 H3SeerHut::Primary() const
	{
		return rewardValue;
	}
	_H3API_ INT8 H3SeerHut::PrimaryCount() const
	{
		return INT8(rewardValue2);
	}

	_H3API_ H3MapItem* H3MainSetup::GetMapItem(int x, int y, int z)
	{
		return THISCALL_4(H3MapItem*, 0x4086D0, this, x, y, z);
	}

	_H3API_ VOID H3MainSetup::DrawItem(H3MapItem* mitem, H3ObjectDraw* draw)
	{
		THISCALL_3(VOID, 0x505880, this, mitem, draw);
	}

	_H3API_ VOID H3MainSetup::AddObjectAttribute(H3ObjectAttributes* oa)
	{
		H3Vector<H3ObjectAttributes>* list = &objectLists[oa->type];
		THISCALL_4(VOID, 0x4D15F0, list, list->end(), 1, oa);
	}

	_H3API_ H3Point H3MainSetup::GetCoordinates(H3MapItem* item)
	{
		H3Point coordinates;
		UINT delta = item - mapitems;
		coordinates.x = delta % mapSize;
		delta /= mapSize;
		coordinates.y = delta % mapSize;
		coordinates.z = delta / mapSize;
		return coordinates;
	}

	_H3API_ H3Map_MapItem H3MainSetup::GetMap()
	{
		return H3Map_MapItem(mapitems, static_cast<UINT>(mapSize), hasUnderground);
	}

	_H3API_ H3FastMap_MapItem H3MainSetup::GetFastMap()
	{
		return H3FastMap_MapItem(mapitems, static_cast<UINT>(mapSize), hasUnderground);
	}

	_H3API_ VOID H3AiFastBattle::DeleteCreatures()
	{
		THISCALL_2(VOID, 0x424880, this, 1);
	}

	_H3API_ UINT8 H3TileMovement::GetX()
	{
		return mixedPosition.GetX();
	}

	_H3API_ UINT8 H3TileMovement::GetY()
	{
		return mixedPosition.GetY();
	}

	_H3API_ UINT8 H3TileMovement::GetZ()
	{
		return mixedPosition.GetZ();
	}

	_H3API_ BOOL H3TileMovement::ZoneControlled()
	{
		return (0x0100 & FASTCALL_3(UINT16, 0x4F8040, GetX(), GetY(), GetZ()));
	}

	_H3API_ H3MapItem* H3TileMovement::GetMapItem()
	{
		return H3Internal::_adventureManager()->GetMapItem(*(int*)this);
	}

	_H3API_ H3TileMovement* H3MovementManager::GetMovementInfo(UINT32 mixed_position)
	{
		return THISCALL_3(H3TileMovement*, 0x42ECC0, this, mixed_position, 0);
	}

	_H3API_ H3Map_TileMovement H3MovementManager::GetMap()
	{
		return H3Map_TileMovement(movementInfo, H3Internal::_main()->mainSetup.mapSize, H3Internal::_main()->mainSetup.hasUnderground);
	}

	_H3API_ H3FastMap_TileMovement H3MovementManager::GetFastMap()
	{
		return H3FastMap_TileMovement(movementInfo, H3Internal::_main()->mainSetup.mapSize, H3Internal::_main()->mainSetup.hasUnderground);
	}

	_H3API_	H3MapItem* H3Main::GetMapItem(UINT32 mixedPosition)
	{
		return THISCALL_2(H3MapItem*, 0x42ED80, this, mixedPosition);
	}
	_H3API_ H3Player* H3Main::GetPlayer()
	{
		return THISCALL_1(H3Player*, 0x4CE670, this);
	}
	_H3API_ INT32 H3Main::GetPlayerID()
	{
		return THISCALL_1(INT32, 0x4CE6E0, this);
	}
	_H3API_ H3Hero* H3Main::GetHero(INT32 id)
	{
		return THISCALL_2(H3Hero*, 0x4317D0, this, id);
	}
	_H3API_ VOID H3Main::ResetRandomArtifacts()
	{
		F_memset(randomArtifacts, 0, sizeof(randomArtifacts));
	}
	_H3API_ INT32 H3Main::GetRandomArtifactOfLevel(INT32 level)
	{
		return THISCALL_2(INT32, 0x4C9190, this, level);
	}
	_H3API_ VOID H3Main::SaveGame(LPCSTR save_name)
	{
		THISCALL_6(VOID, 0x4BEB60, this, save_name, 1, 1, 1, 0);
	}
	_H3API_ VOID H3Main::PlaceObjectOnMap(int x, int y, int z, int type, int subtype, int setup)
	{
		{ THISCALL_7(VOID, 0x4C9550, this, x, y, z, type, subtype, setup); }
	}
	_H3API_ VOID H3Main::RefreshMapItemAppearrance(H3MapItem* mi)
	{
		{ THISCALL_2(VOID, 0x4C9650, this, mi); }
	}

	_H3API_ H3Point H3Main::GetCoordinates(H3MapItem* item)
	{
		return mainSetup.GetCoordinates(item);
	}
	_H3API_ BOOL8 H3Main::IsHuman(INT32 player_id)
	{
		return THISCALL_2(BOOL8, 0x4CE600, this, player_id);
	}

	_H3API_ VOID H3Main::UpdateMapItemAppearance(H3MapItem* item)
	{
		THISCALL_2(VOID, 0x4C9650, this, item);
	}

	_H3API_ H3Map_MapItem H3Main::GetMap()
	{
		return mainSetup.GetMap();
	}

	_H3API_ H3FastMap_MapItem H3Main::GetFastMap()
	{
		return mainSetup.GetFastMap();
	}

	_H3API_ VOID H3Manager::SetPreviousManager(H3Manager* prev)
	{
		parent = prev;
	}

	_H3API_ VOID H3Manager::SetNextManager(H3Manager* next)
	{
		child = next;
	}

	_H3API_ VOID H3ExecutiveMgr::RemoveManager(H3Manager* mgr)
	{
		THISCALL_2(VOID, 0x4B0950, this, mgr);
	}

	_H3API_ INT H3ExecutiveMgr::AddManager(H3Manager* mgr, int order)
	{
		return THISCALL_3(INT, 0x4B0880, this, mgr, order);
	}

	_H3API_ VOID H3MouseManager::TurnOn()
	{
		THISCALL_2(VOID, 0x50D7B0, this, 1);
	}

	_H3API_ VOID H3MouseManager::TurnOff()
	{
		THISCALL_2(VOID, 0x50D7B0, this, 0);
	}

	_H3API_ INT32 H3MouseManager::GetType() const
	{
		return cursorType;
	}

	_H3API_ INT32 H3MouseManager::GetFrame() const
	{
		return cursorFrame;
	}

	_H3API_ VOID H3MouseManager::SetCursor(INT32 frame, INT32 type)
	{
		THISCALL_3(VOID, 0x50CEA0, this, frame, type);
	}

	_H3API_ VOID H3MouseManager::DefaultCursor()
	{
		SetCursor(0, 0);
	}

	_H3API_ VOID H3MouseManager::SetArtifactCursor(INT32 art_id)
	{
		SetCursor(art_id, int(H3MouseManager::MouseCursorType::CURSOR_ARTIFACT));
	}

	_H3API_ VOID H3WindowManager::H3Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy)
	{
		THISCALL_5(VOID, 0x603190, this, x, y, dx, dy);
	}

	_H3API_ UINT32 H3WindowManager::ClickedItemID() const
	{
		return resultItemID;
	}

	_H3API_ VOID H3WindowManager::SetClickedItemId(UINT32 id)
	{
		resultItemID = id;
	}

	_H3API_ BOOL H3WindowManager::ClickedOK() const
	{
		return resultItemID == int(H3WindowManager::eClickId::H3ID_OK);
	}

	_H3API_ BOOL H3WindowManager::ClickedCancel() const
	{
		return resultItemID == int(H3WindowManager::eClickId::H3ID_CANCEL);
	}

	_H3API_ H3LoadedPcx16* H3WindowManager::GetDrawBuffer()
	{
		return screenPcx16;
	}

	_H3API_ VOID H3SoundManager::ClickSound()
	{
		H3WavFile* button_wav = (*(H3WavFile**)0x694DF4);
		INT32 backup = clickSoundVar;
		button_wav->spinCount = 64;
		button_wav->debugInfo = PRTL_CRITICAL_SECTION_DEBUG(1);
		button_wav->lockSemaphore = HANDLE(HANDLE_FLAG_PROTECT_FROM_CLOSE | HANDLE_FLAG_INHERIT);
		THISCALL_2(VOID, 0x59A510, this, button_wav);
		clickSoundVar = backup;
	}

#pragma push_macro("PlaySound")
#ifdef PlaySound
#undef PlaySound
#endif
	_H3API_ VOID H3SoundManager::PlaySound(H3WavFile * wav)
	{
		THISCALL_2(VOID, 0x59A510, this, wav);
	}
	_H3API_ VOID H3SoundManager::PlaySound(LPCSTR wav_name)
	{
		H3WavLoader wav(wav_name);
		if (wav)
			PlaySound(*wav);
	}
	_H3API_ VOID H3SoundManager::PlaySoundAndWait(LPCSTR wav_name, INT milliseconds)
	{
		H3WavLoader wav(wav_name);
		if (!wav)
			return;
		PlaySound(*wav);
		THISCALL_3(VOID, 0x59A7C0, milliseconds, *wav, wav->hSample);
	}

	_H3API_ VOID H3SoundManager::PlaySoundAsync(LPCSTR wav_name, INT32 duration /*= -1*/)
	{
		FASTCALL_3(VOID, 0x59A890, wav_name, duration, 3);
	}

#pragma pop_macro("PlaySound")

	_H3API_ H3MapItem* H3AdventureManager::GetMapItem()
	{
		return THISCALL_2(H3MapItem*, 0x412B30, this, mousePosition.Mixed());
	}

	_H3API_ H3MapItem* H3AdventureManager::GetMapItem(int mixedPos)
	{
		return THISCALL_2(H3MapItem*, 0x412B30, this, mixedPos);
	}

	_H3API_ H3MapItem* H3AdventureManager::GetMapItem(int x, int y, int z)
	{
		return THISCALL_4(H3MapItem*, 0x4086D0, map, x, y, z);
	}

	_H3API_ UINT8 H3AdventureManager::GetX()
	{
		return mousePosition.GetX();
	}

	_H3API_ UINT8 H3AdventureManager::GetY()
	{
		return mousePosition.GetY();
	}

	_H3API_ UINT8 H3AdventureManager::GetZ()
	{
		return mousePosition.GetZ();
	}

	_H3API_ VOID H3AdventureManager::FullUpdate()
	{
		THISCALL_3(VOID, 0x417380, this, 1, 0);
	}

	_H3API_ VOID H3AdventureManager::MobilizeHero()
	{
		THISCALL_4(VOID, 0x417540, this, 0, 0, 0);
	}

	_H3API_ VOID H3AdventureManager::DemobilizeHero()
	{
		THISCALL_3(VOID, 0x4175E0, this, 0, 0);
	}

	_H3API_ VOID H3AdventureManager::MovementCalculationsMouse()
	{
		THISCALL_2(VOID, 0x419400, this, mousePosition.Mixed());
	}

	_H3API_ VOID H3AdventureManager::MovementCalculations(UINT32 mixedPosition)
	{
		THISCALL_2(VOID, 0x419400, this, mixedPosition);
	}

	_H3API_ VOID H3AdventureManager::MakeHeroPath()
	{
		THISCALL_4(VOID, 0x418D30, this, 1, 1, 1);
	}

	_H3API_ VOID H3AdventureManager::ShowCoordinates(UINT32 x, UINT32 y, UINT8 z)
	{
		if (x < H3Internal::_mapSize() && y < H3Internal::_mapSize())
		{
			UINT edge_x = H3Internal::_gameEdgeHorizontal();
			UINT edge_y = H3Internal::_gameEdgeVertical();
			UINT dx = x - (screenPosition.GetX() - edge_x);
			UINT dy = y - (screenPosition.GetY() - edge_y);
			DemobilizeHero();
			screenPosition.SetXYZ(edge_x + x, edge_y + y, z);
			FullUpdate(); // force immediate redraw
			mousePosition.SetXYZ(mousePosition.GetX() + dx, mousePosition.GetY() + dy, z); // update cursor position
		}
	}

	_H3API_ INT H3AdventureManager::SimulateMouseOver(INT x, INT y)
	{
		return THISCALL_3(int, 0x40E2C0, this, x, y);
	}

	_H3API_ INT H3AdventureManager::SimulateMouseOver(POINT& p)
	{
		return SimulateMouseOver(p.x, p.y);
	}

	_H3API_ CHAR H3AdventureManager::UpdateHintMessage()
	{
		return THISCALL_5(CHAR, 0x40B0B0, this, GetMapItem(), GetX(), GetY(), GetZ());
	}

	_H3API_ H3Point H3AdventureManager::GetCoordinates(H3MapItem* item)
	{
		return map->GetCoordinates(item);
	}

	_H3API_ VOID H3AdventureManager::StopSound(H3WavFile* wav)
	{
		THISCALL_2(VOID, 0x59A180, this, wav->hSample);
	}

	_H3API_ H3Map_MapItem H3AdventureManager::GetMap()
	{
		return map->GetMap();
	}

	_H3API_ H3FastMap_MapItem H3AdventureManager::GetFastMap()
	{
		return map->GetFastMap();
	}

	_H3API_ H3Map_UINT16 H3AdventureManager::GetPathMap()
	{
		return H3Map_UINT16(arrowPathFrames, DwordAt(0x6783C7), H3Internal::_main()->mainSetup.hasUnderground);
	}

	_H3API_ H3FastMap_UINT16 H3AdventureManager::GetPathFastMap()
	{
		return H3FastMap_UINT16(arrowPathFrames, DwordAt(0x6783C7), H3Internal::_main()->mainSetup.hasUnderground);
	}

	_H3API_ VOID H3TownManager::Draw()
	{
		THISCALL_1(VOID, 0x5D5930, this);
	}

	_H3API_ VOID H3TownManager::RefreshScreen()
	{
		THISCALL_1(VOID, 0x5D5810, this);
	}

	_H3API_ VOID H3TownManager::ViewTavern()
	{
		THISCALL_1(char, 0x5D82C0, this);
	}

	_H3API_ H3InputManager::InputMessages& H3InputManager::GetCurrentMessage()
	{
		return messages[currentMessage];
	}

	_H3API_ H3CombatMonster* H3CombatSquare::GetMonster()
	{
		return THISCALL_1(H3CombatMonster*, 0x4E7230, this);
	}

	_H3API_ VOID H3CombatManager::SimulateMouseAtHex(int hex_id)
	{
		return THISCALL_2(VOID, 0x477550, this, hex_id);
	}

	_H3API_ BOOL8 H3CombatManager::CanCastSpellAtCoord(int spell_id, int spell_expertise, int coordinates)
	{
		return THISCALL_7(BOOL8, 0x5A3CD0, this, spell_id, spell_expertise, coordinates, currentActiveSide, 1, 0);
	}

	_H3API_ VOID H3CombatManager::WinBattle()
	{
		return THISCALL_2(VOID, 0x468F80, this, 1 - currentActiveSide);
	}

	_H3API_ VOID H3CombatManager::LoadSpell(INT32 spell_id)
	{
		return THISCALL_3(VOID, 0x59EF60, this, spell_id, 0);
	}

	_H3API_ VOID H3CombatManager::CastSpell(int spell_id, int hex_ix, int cast_type_012, int hex2_ix, int skill_level, int spell_power)
	{
		THISCALL_7(VOID, 0x5A0140, this, spell_id, hex_ix, cast_type_012, hex2_ix, skill_level, spell_power);
	}

	_H3API_ H3CombatMonster* H3CombatManager::GetResurrectionTarget(INT32 coordinate, INT32 caster_kind)
	{
		return THISCALL_4(H3CombatMonster*, 0x5A3FD0, this, currentActiveSide, coordinate, caster_kind);
	}

	_H3API_ H3CombatMonster* H3CombatManager::GetAnimateDeadTarget(INT32 coordinate)
	{
		return THISCALL_3(H3CombatMonster*, 0x5A4260, this, currentActiveSide, coordinate);
	}

	_H3API_ int H3CombatManager::NextCreatureToMove()
	{
		return THISCALL_2(int, 0x464C60, this, 1);
	}

	_H3API_ BOOL8 H3CombatManager::IsHiddenBattle()
	{
		return THISCALL_1(BOOL8, 0x46A080, this);
	}

	_H3API_ BOOL8 H3CombatManager::IsBattleOver()
	{
		return THISCALL_1(BOOL8, 0x465410, this);
	}

	_H3API_ VOID H3CombatManager::Refresh()
	{
		Refresh(1, 0, 1);
	}

	_H3API_ VOID H3CombatManager::Refresh(BOOL redrawScreen, INT timeDelay, BOOL redrawBackground)
	{
		THISCALL_7(VOID, 0x493FC0, this, redrawScreen, 0, 0, timeDelay, redrawBackground, 0);
	}

	_H3API_ VOID H3CombatManager::RefreshCreatures()
	{
		THISCALL_1(VOID, 0x495770, this);
	}

	_H3API_ VOID H3CombatManager::ShadeSquare(int index)
	{
		if (index < 0 || index > 187)
			return;
		H3CombatSquare* sq = &squares[index];
		CCellShdPcx->DrawToPcx16(0, 0, 0x2D, 0x34, drawBuffer, sq->left, sq->top, TRUE); // copied from 0x4935B9 and below
	}

	_H3API_ BOOL8 H3CombatManager::IsHumanTurn()
	{
		return isHuman[currentActiveSide];
	}

	_H3API_ VOID H3CombatManager::AddStatusMessage(LPCSTR message, BOOL permanent)
	{
		THISCALL_4(VOID, 0x4729D0, dlg, message, permanent, 0);
	}

	_H3API_ VOID H3CombatManager::PlayMagicAnimation(INT32 id, H3CombatMonster* target, INT32 timeStep, BOOL8 show_hit)
	{
		return THISCALL_5(VOID, 0x4963C0, this, id, target, timeStep, show_hit);
	}

	_H3API_ VOID H3CombatManager::ReportDamageDone(H3Spell* spell, LPCSTR attacker, INT32 dmg, H3CombatMonster* target, INT32 killedCount)
	{
		return THISCALL_6(VOID, 0x469670, this, spell, attacker, dmg, target, killedCount);
	}

	_H3API_ BOOL8 H3CombatManager::ShouldCastSpellAfterHit(INT32 spellId, INT32 side, H3CombatMonster* target)
	{
		return THISCALL_6(BOOL8, 0x5A8950, this, spellId, side, target, 1, 1);
	}

	_H3API_ VOID H3CombatManager::ResurrectTarget(H3CombatMonster* target, INT32 hitPoints, INT32 isTemporary)
	{
		return THISCALL_4(VOID, 0x5A7870, this, target, hitPoints, isTemporary);
	}

	_H3API_ H3CombatMonster* H3CombatManager::SummonCreature(INT32 side, INT32 creatureId, INT32 amount, INT32 position, INT32 redrawAnimation, BOOL redraw)
	{
		return THISCALL_7(H3CombatMonster*, 0x479A30, this, side, creatureId, amount, position, redrawAnimation, redraw);
	}

	_H3API_ H3CombatMonster* H3CombatManager::GetSummonDemonTarget(INT32 side, INT32 coordinate)
	{
		return THISCALL_3(H3CombatMonster*, 0x5A4150, this, side, coordinate);
	}

	_H3API_ VOID H3CombatManager::RaiseDemon(H3CombatMonster* caster, H3CombatMonster* target)
	{
		return THISCALL_3(VOID, 0x5A76A0, this, caster, target);
	}

	_H3API_ BOOL8 H3CombatManager::CanApplyCreatureSpell(INT32 spell_id, INT32 creature_side, H3CombatMonster* target)
	{
		return THISCALL_6(BOOL8, 0x5A8950, this, spell_id, creature_side, target, 1, 1); // the last 2 parameters are always 1 and 1
	}

	_H3API_ VOID H3CombatManager::DrawRay(BOOL redraw, INT startX, INT startY, INT dstX, INT dstY, INT allowBranches, INT randomnessRange, INT startThickness, INT endThickness, WORD color565, INT amplitude, INT arching, INT rayStraightness, INT smoothness, BOOL pathRandomness, INT timeDelay)
	{
		THISCALL_18(VOID, 0x5A5F30, this, redraw, startX, startY, dstX, dstY, allowBranches, randomnessRange, startThickness, endThickness, color565, amplitude, arching, rayStraightness, smoothness, pathRandomness, timeDelay, 0);
	}

	_H3API_ VOID H3CombatManager::DrawRay(BOOL redraw, H3CombatMonster * start, H3CombatMonster * end, INT allowBranches, INT randomnessRange, INT startThickness, INT endThickness, WORD color565, INT amplitude, INT arching, INT rayStraightness, INT smoothness, BOOL pathRandomness, INT timeDelay)
	{
		DrawRay(redraw, start->GetX(), start->GetY(), end->GetX(), end->GetY(), allowBranches, randomnessRange, startThickness, endThickness, color565, amplitude, arching, rayStraightness, smoothness, pathRandomness, timeDelay);
	}

	namespace H3Internal
	{
		_H3API_ H3MouseManager* _mouseManager()
		{
			return *reinterpret_cast<H3MouseManager**>(0x6992B0);
		}

		_H3API_ H3WindowManager* _windowManager()
		{
			return *reinterpret_cast<H3WindowManager**>(0x6992D0);
		}

		_H3API_ H3ExecutiveMgr* _executiveMgr()
		{
			return *reinterpret_cast<H3ExecutiveMgr**>(0x699550);
		}

		_H3API_ H3Main* _main()
		{
			return *reinterpret_cast<H3Main**>(0x699538);
		}

		_H3API_ H3CombatManager* _combatManager()
		{
			return *reinterpret_cast<H3CombatManager**>(0x699420);
		}

		_H3API_ H3TownManager* _townManager()
		{
			return *reinterpret_cast<H3TownManager**>(0x69954C);
		}

		_H3API_ H3SoundManager* _soundManager()
		{
			return *reinterpret_cast<H3SoundManager**>(0x699414);
		}

		_H3API_ H3InputManager* _inputManager()
		{
			return *reinterpret_cast<H3InputManager**>(0x699530);
		}

		_H3API_ H3AdventureManager* _adventureManager()
		{
			return *reinterpret_cast<H3AdventureManager**>(0x6992B8);
		}

		_H3API_ H3MovementManager* _movementManager()
		{
			return *reinterpret_cast<H3MovementManager**>(0x6992D4);
		}

		_H3API_ H3GlobalObjectSettings* _globalObjectSettings()
		{
			return *reinterpret_cast<H3GlobalObjectSettings**>(0x660428);
		}

		_H3API_ H3Spell* _spell()
		{
			return *reinterpret_cast<H3Spell**>(0x687FA8);
		}

		_H3API_ H3CreatureBankSetup* _creatureBankSetup()
		{
			return *reinterpret_cast<H3CreatureBankSetup**>(0x47A3C1 + 1);
		}

		_H3API_ H3ValidCatapultTargets* _validCatapultTargets()
		{
			return *reinterpret_cast<H3ValidCatapultTargets**>(0x4929DD + 3);
		}

		_H3API_ H3ArtifactSetup* _artifactSetup()
		{
			return *reinterpret_cast<H3ArtifactSetup**>(0x660B68);
		}

		_H3API_ INT _artifactCount()
		{
			return IntAt(0x44D1A8 + 2);
		}

		_H3API_ H3CreatureInformation* _creatureInformation()
		{
			return *reinterpret_cast<H3CreatureInformation**>(0x6747B0);
		}

		_H3API_ H3ObstacleInfo* _obstacleInfo()
		{
			return *reinterpret_cast<H3ObstacleInfo**>(0x465C21);
		}

		_H3API_ H3Hero* _dialogHero()
		{
			return *reinterpret_cast<H3Hero**>(0x698B70);
		}

		_H3API_ H3TurnTimer* _turnTimer()
		{
			return *reinterpret_cast<H3TurnTimer**>(0x4AD194 + 1);
		}

		_H3API_ H3HeroSpecialty* _heroSpecialty()
		{
			return *reinterpret_cast<H3HeroSpecialty**>(0x4B8AF1 + 1);
		}

		_H3API_ H3TownCreatureTypes* _townCreatureTypes()
		{
			return *reinterpret_cast<H3TownCreatureTypes**>(0x47AB00 + 3);
		}
		_H3API_ H3SecondarySkillInfo& _secondarySkillsInfo(int skill)
		{
			return (*reinterpret_cast<H3SecondarySkillInfo**>(0x67DCF0))[skill];
		}
		_H3API_ H3ComboArtifactSetup * _combinationArtifacts()
		{
			return **(H3ComboArtifactSetup***)(0x4DDFF2 + 2);
		}
	}
	_H3API_ H3IndexVector::H3IndexVector(INT min_num, INT max_num)
	{
		THISCALL_3(H3IndexVector*, 0x50C8D0, this, min_num, max_num);
	}
	_H3API_ H3IndexVector::~H3IndexVector()
	{
		F_delete(PVOID(m_begin));
	}
	_H3API_ INT H3IndexVector::ChooseRandom()
	{
		return THISCALL_1(INT, 0x50C930, this);
	}
	_H3API_ INT H3IndexVector::InvalidIndex()
	{
		return m_minimum - 1;
	}
}


