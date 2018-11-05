// UltimaVEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

static char* buffer;

struct Character
{
	char name[9];
	char gender;
	char status[2];
	unsigned char str;
	unsigned char intel;
	unsigned char dex;
	unsigned char magic;
	unsigned short HP;
	unsigned short HM;
	unsigned short EXP;
	unsigned char LVL;
	char UNKNOWN[2];
	char equipment[6];
	char partyFlags;

	string getName()
	{
		return string(name);
	};
	void setName(string _name)
	{
		int i;
		for (i = 0; i < 8 && i < _name.length(); i++)
		{
			name[i] = _name[i];
		}
		for (i; i < 9; i++)
		{
			name[i] = 0x00;
		}
	}
	void setMale()
	{
		gender = 0x0B;
	}
	void setFemale()
	{
		gender = 0x0C;
	}
};

// HEX TOOLS
struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(unsigned char _c) : c(_c) { }
};
inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::hex << (int)hs.c);
}
inline HexCharStruct hex(unsigned char _c)
{
	return HexCharStruct(_c);
}

void EditCharacters();
void EditItems();
//void GetCharacter();
void PrintCharacter(Character c);

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
	cout << "File Size (bytes):\t" << size << "\n";

	// STORE File in Buffer
	buffer = new char[size];
	infile.read(buffer, size);

	int i = 0;
	for (i=0; i < size; i++)
	{
		cout << hex(buffer[i]) << "\n";
		if (buffer[i] != 0x00)
		{
			break;
		}
	}
	Character* player = (Character*)(buffer+i);
	PrintCharacter(*player);

	// MODIFY the Buffer
	cout << "MODIFYING CHARACTER STATS...\n";
	player->setName("Susan");
	player->setFemale();
	player->str = 99;
	player->intel = 99;
	player->dex = 99;
	player->magic = 99;
	player->HP = 999;
	player->HM = 999;
	player->EXP = 9999;
	player->LVL = 99;

	PrintCharacter(*player);


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

	cout << "\nPress any key to continue...\n";
	int x;
	cin >> x;
    return 0;
}

void EditCharacters()
{

}

void EditItems()
{

}

void PrintCharacter(Character c)
{
	//cout << "HEX\t" << std::hex << c << "\n";
	cout << "Name:\t" << c.getName() << "\n";
	cout << "Gender:\t" << ((c.gender==0x0B)? "Male": "Female") << "\n";
	cout << "stat0:\t" << std::hex << c.status[0] << "\n";
	cout << "stat1:\t" << std::hex << c.status[1] << "\n";
	cout << "STR:\t" << std::dec << +c.str << "\n";
	cout << "INT:\t"<< std::dec << +c.intel << "\n";
	cout << "DEX:\t" << std::dec << +c.dex << "\n";
	cout << "MGC:\t" << std::dec << +c.magic << "\n";
	cout << "HP:\t" << std::dec << c.HP << "\n";
	cout << "HM:\t" << std::dec << c.HM << "\n";
	cout << "EXP:\t" << std::dec << c.EXP << "\n";
	cout << "LVL:\t" << std::dec << +c.LVL << "\n";
	cout << "???:\t" << hex(c.UNKNOWN[0]) << " " << hex(c.UNKNOWN[1]) << "\n";
	cout << "Equipment:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << "   " << i << ": " << hex(c.equipment[i]) << "\n";
	}
	cout << "pFlags:\t" << hex(c.partyFlags) << "\n";
	
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