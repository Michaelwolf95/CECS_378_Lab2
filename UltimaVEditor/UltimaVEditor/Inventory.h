#pragma once
/*
This structure aims to copy the exact memory layout of the Ultima V inventory.

Most of this was discovered and filled out by hand using trial-and-error 
and going off of DATA.OVL, which lists the names of items roughly in the order of memory layout.

The rest was filled out by using this helpful online resource, 
which saved many hours of work:
http://martin.brenner.de/ultima/u5save.html

I DID NOT USE THIS UNTIL THE VERY END - I just wanted to fill in the gaps.
*/

struct Equipment
{
	char leatherHelm;
	char chainCoif;
	char ironHelm;
	char spikedHelm;
	char smallShield;
	char largeShield;
	char spikedShield;
	char magicShield;
	char jeweledShield;
	char cloth;
	char leather;
	char ringMail;
	char scale;
	char chain;
	char plate;
	char mysticArmor;
};
struct Weapons
{
	char dagger;
	char sling;
	char club;
	char flamingOil;
	char mainGauche;
	char spear;
	char throwingAxe;
	char shortSword;
	char mace;
	char morningStar;
	char bow;
	char arrows;
	char crossBow;
	char quarrels;
	char longSword;
	char hammer2H;
	char axe2H;
	char sword2H;
	char halberd;
	char chaosSword;
	char magicBow;
	char silverSword;
	char magicAxe;
	char glassSword;
	char jeweledSword;
	char mysticSword;
};
struct Rings
{
	char invisibility;
	char protection;
	char regeneration;
};
struct UniqueAmulets
{
	char amuletOfTurning;
	char spikedCollar;
	char ankh;
};
struct Spells
{
	char spellIndices[48];
};
struct Scrolls
{
	char scrollIndices[8];
};
struct Potions
{
	char blue;
	char yellow;
	char red;
	char green;
	char orange;
	char purple;
	char black;
	char white;
};
struct Reagents
{
	char sulfurAsh;
	char ginseng;
	char garlic;
	char spiderSilk;
	char bloodMoss;
	char blackPearl;
	char nightShade;
	char mandrakeRoot;
};
// MAIN STRUCT
struct Inventory
{
	// Collectables
	unsigned short food;
	unsigned short gold;
	char keys;
	char gems;
	char torches;
	char grapple;		// ??
	char magicCarpet;
	char skullKeys;
	char unkown_0;
	char amulets;
	char crowns;		//
	char otherSlots[8];
	char pocketwatch;	// FF or 00
	char blackBadge;
	char sandalwoodBox;

	Equipment equipment;
	Weapons weapons;
	Rings rings;
	UniqueAmulets uniqueAmulets;
	Spells spells;
	Scrolls scrolls;
	Potions potions;
	char EMPTY_CHUNK[32];
	Reagents reagents;
	char unkown_1;
	char unkown_2;
	char unkown_3;
	char partySize; // Fun discovery
	char unkown_4;
	char karma;
	char unkown_5;
};

// Only displaying editable values.
// Showing them all would be... too much.
void PrintInventory(Inventory* inv)
{
	cout << "INVENTORY ================\n";
	cout << "Food:\t\t" << std::dec << +inv->food << "\n";
	cout << "Gold:\t\t" << std::dec << +inv->gold << "\n";
	cout << "Keys:\t\t" << +inv->keys << "\n";
	cout << "Gems:\t\t" << +inv->gems << "\n";
	cout << "Torch:\t\t" << +inv->torches << "\n";
	cout << "MgcCrpt:\t" << +inv->magicCarpet << "\n";
	cout << "SkullKeys:\t" << +inv->skullKeys << "\n";
	cout << "Amulets:\t" << +inv->amulets << "\n";
	cout << "Crowns:\t\t" << +inv->crowns << "\n";
	cout << "BlackBadge:\t" << +(((inv->blackBadge)== (char)0xFF)?1:0) << "\n";
	cout << "MagicAxe:\t" << +inv->weapons.magicAxe << "\n";
}
