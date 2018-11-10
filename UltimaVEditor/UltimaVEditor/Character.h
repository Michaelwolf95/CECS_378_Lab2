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
	cout << "CHARACTER ====================================================\n";
	cout << "Name:\t" << c->getName() << "\n";
	cout << "Gender:\t" << ((c->gender == 0x0B) ? "Male" : "Female") << "\n";
	cout << "Status: " << (c->status[0]) << " " << (c->status[1]) << "\n";
	cout << "STR: " << std::dec << +c->str << "\t";
	cout << "INT: " << std::dec << +c->intel << "\t";
	cout << "DEX: " << std::dec << +c->dex << "\t";
	cout << "MGC: " << std::dec << +c->magic << "\n";
	cout << "HP: " << std::dec << c->HP << "\t";
	cout << "HM: " << std::dec << c->HM << "\t";
	cout << "EXP: " << std::dec << c->EXP << "\n";
	cout << "LVL: " << std::dec << +c->LVL << "\n";
	cout << "???:\t" << hex(c->UNKNOWN[0]) << " " << hex(c->UNKNOWN[1]) << "\n";

	cout << "Equipment:\n|";
	for (int i = 0; i < 6; i++)
	{
		cout << "| [" << i << "]\t|";
	}
	cout << "|\n|";
	for (int i = 0; i < 6; i++)
	{
		cout << "| " << hex(c->equipment[i]) << "\t|";
	}
	cout << "|\n";

	cout << "pFlags:\t" << hex(c->partyFlags) << "\n";
	cout << "==============================================================\n";

}