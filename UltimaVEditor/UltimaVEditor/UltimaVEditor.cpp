// UltimaVEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HexTools.h"
#include "Character.h"
#include "Inventory.h"
using namespace std;

static char* buffer;

const unsigned short START_OFFSET = 2;
const unsigned short CHARACTER_SIZE = 32;

static Character* player;
static Character* characters[15];
static Inventory* inventory;

/* CHARACTERS (Default Order):
Player, Shamino, Iolo, Mariah, Geoffrey, Jaana, Julia, Dupre
Katrina, Sentri, Gwenno, Johne, Gorn, Maxwell, Toshi, Saduj */

void EditCharacter(Character* c);
void EditItems();

int main(int argc, char *argv[], char *envp[])
{
	// GET TARGET DIRECTORY ================================================
	string targetDir;
	if (argc < 2)
	{
		cout << "Enter UltimaV Directory Path:\n";
		cin >> targetDir;
	}
	else
	{
		targetDir = string(argv[1]);
	}
	string saveFile = targetDir + "/SAVED.GAM";
	
	cout << "Looking in Directory:" << "\n";
	cout << targetDir << "\n";
	cout << "Opening " << saveFile;

	// OPEN Save File =====================================================
	std::ifstream infile(saveFile.c_str(), std::ifstream::binary);
	infile.seekg(0, infile.end);
	long size = infile.tellg();
	infile.seekg(0);
	cout << "File Size (bytes): " << size << "\n";

	// CACHE File bytes in Buffer =========================================
	buffer = new char[size];
	infile.read(buffer, size);

	// Start of character pointers.
	char* cPtr = buffer + START_OFFSET;

	// Init Player character pointer.
	player = (Character*)(cPtr);

	// Init Character pointers.
	for (size_t i = 0; i < 15; i++)
	{
		characters[i] = (Character*)(cPtr + (CHARACTER_SIZE * (i+1)));
	}
	// Init Inventory pointer.
	inventory = (Inventory*)(cPtr + (CHARACTER_SIZE * 16));

	// MODIFY the Buffer ==================================================

	//PrintCharacter(player);
	//for (size_t i = 0; i < 15; i++)
	//{
	//	PrintCharacter(characters[i]);
	//}
	//PrintInventory(inventory);

	//EditCharacter(player);
	//inventory->food = 25;
	//inventory->equipment.mysticArmor = 4;
	//inventory->weapons.magicAxe = 9;



	// WRITE the Buffer back into the File ================================
	string outputFile = saveFile;// "TEST_OUTPUT.GAM";

	std::ofstream outfile(outputFile.c_str(), std::ofstream::binary);
	if (outfile.is_open())
	{
		cout << "Writing to save file...\n";
		outfile.write(buffer, size);
	}
	else
	{
		cout << "Failed to write to save file!\n";
	}
	
	delete[] buffer;
	outfile.close();
	infile.close();

	//cout << "\nPress any key to continue...\n";
	//int x;
	//cin >> x;
    return 0;
}

void EditCharacter(Character* c)
{
	cout << "MODIFYING CHARACTER STATS...\n";
	c->setName("Susan");
	c->setFemale();
	c->str = 99;
	c->intel = 99;
	c->dex = 99;
	c->magic = 99;
	c->HP = 999;
	c->HM = 999;
	c->EXP = 9999;
	c->LVL = 99;

	PrintCharacter(c);
}

void EditItems()
{

}


static std::vector<char> ReadAllBytes(char const* filename)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);
	ifs.close();
	return result;
}
//vector<char> bytes = ReadAllBytes(saveFile.c_str());
//long size = bytes.size();
//char* buff = reinterpret_cast<char*>(bytes.data());