#pragma once

///
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

void PrintCharacter(Character* c)
{
	cout << "CHARACTER ================\n";
	//cout << "HEX\t" << std::hex << c << "\n";
	cout << "Name:\t" << c->getName() << "\n";
	cout << "Gender:\t" << ((c->gender == 0x0B) ? "Male" : "Female") << "\n";
	cout << "stat0:\t" << std::hex << c->status[0] << "\n";
	cout << "stat1:\t" << std::hex << c->status[1] << "\n";
	cout << "STR:\t" << std::dec << +c->str << "\n";
	cout << "INT:\t" << std::dec << +c->intel << "\n";
	cout << "DEX:\t" << std::dec << +c->dex << "\n";
	cout << "MGC:\t" << std::dec << +c->magic << "\n";
	cout << "HP:\t" << std::dec << c->HP << "\n";
	cout << "HM:\t" << std::dec << c->HM << "\n";
	cout << "EXP:\t" << std::dec << c->EXP << "\n";
	cout << "LVL:\t" << std::dec << +c->LVL << "\n";
	cout << "???:\t" << hex(c->UNKNOWN[0]) << " " << hex(c->UNKNOWN[1]) << "\n";
	cout << "Equipment:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << "  " << i << ":\t" << hex(c->equipment[i]) << "\n";
	}
	cout << "pFlags:\t" << hex(c->partyFlags) << "\n\n";

}