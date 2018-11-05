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

void EditCharacter(Character* c);
void EditItems();
//void GetCharacter();
//void PrintCharacter(Character* c);
//void PrintInventory(Inventory* inv);

int main(int argc, char *argv[], char *envp[])
{
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

	// OPEN Save File
	std::ifstream infile(saveFile.c_str(), std::ifstream::binary);
	infile.seekg(0, infile.end);
	long size = infile.tellg();
	infile.seekg(0);
	cout << "File Size (bytes): " << size << "\n";

	// STORE File in Buffer
	buffer = new char[size];
	infile.read(buffer, size);

	char* cPtr = buffer + START_OFFSET;
	Character* player = (Character*)(cPtr);
	PrintCharacter(player);

	/*
	Player, Shamino, Iolo, Mariah
	Geoffrey, Jaana, Julia, Dupre
	Katrina, Sentri, Gwenno, Johne
	Gorn, Maxwell, Toshi, Saduj
	*/
	//cout << "\nSHAMINO\t==================" << "\n";
	//Character* Shamino = (Character*)(cPtr + (CHARACTER_SIZE * 1));
	//PrintCharacter(Shamino);
	//cout << "\nIOLO\t==================" << "\n";
	//Character* Iolo = (Character*)(cPtr + (CHARACTER_SIZE* 2));
	//PrintCharacter(Iolo);
	//cout << "\nMARIAH\t==================" << "\n";
	//Character* Mariah = (Character*)(cPtr + (CHARACTER_SIZE * 3));
	//PrintCharacter(Mariah);

	//ToDo: Inventory
	Inventory* inv = (Inventory*)(cPtr + (CHARACTER_SIZE * 16));
	PrintInventory(inv);

	// MODIFY the Buffer

	//EditCharacter(player);
	inv->food = 25;
	inv->equipment.mysticArmor = 4;
	inv->weapons.magicAxe = 3;


	// WRITE the Buffer back into the File
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