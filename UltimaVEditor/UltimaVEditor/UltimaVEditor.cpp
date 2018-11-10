// UltimaVEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <sstream>
#include <iterator>
#include "HexTools.h"
#include "Character.h"
#include "Inventory.h"
using namespace std;

const unsigned short START_OFFSET = 2;
const unsigned short CHARACTER_SIZE = 32;

static char* buffer;
static Character* player;
static Character* characters[16];
static Inventory* inventory;

// Utility
static bool IsChoice(string command, const char* choice);

// Menus
void EditorMainMenu();
void CharacterSelectMenu(bool* done);
void EditInventoryMenu(bool* done);
void EditCharacterMenu(Character* c, bool* done);

int main(int argc, char *argv[], char *envp[])
{
	// GET TARGET DIRECTORY ================================================
	string targetDir;
	if (argc < 2)
	{
		cout << "Enter UltimaV Directory Path:\n";
		cin >> targetDir;
		if (targetDir == "d" || targetDir == "default")
		{
			targetDir = R"(D:\DOS\Ultima_5)"; // Raw string literal
		}
	}
	else
	{
		targetDir = string(argv[1]);
	}

	string saveFile = targetDir + "/SAVED.GAM";
	
	cout << "Looking in Directory:\t" << targetDir << "\n";
	cout << "Opening Save File:\t" << saveFile << "\n";

	// OPEN Save File =====================================================
	std::ifstream infile(saveFile.c_str(), std::ifstream::binary);
	infile.seekg(0, infile.end);
	long size = infile.tellg();
	infile.seekg(0);
	cout << "File Size (bytes):\t" << size << "\n";

	// CACHE File bytes in Buffer =========================================
	buffer = new char[size];
	infile.read(buffer, size);

	// Start of character pointers.
	char* cPtr = buffer + START_OFFSET;

	// Init Player character pointer.
	player = (Character*)(cPtr);
	characters[0] = player;
	// Init Character pointers.
	for (size_t i = 1; i < 16; i++)
	{
		characters[i] = (Character*)(cPtr + (CHARACTER_SIZE * (i)));
	}
	// Init Inventory pointer.
	inventory = (Inventory*)(cPtr + (CHARACTER_SIZE * 16));

	// MODIFY the Buffer ==================================================
	EditorMainMenu();

	// WRITE the Buffer back into the File ================================
	string outputFile = saveFile;// "TEST_OUTPUT.GAM";
	std::ofstream outfile(outputFile.c_str(), std::ofstream::binary);
	if (outfile.is_open())
	{
		cout << "Writing to Save File...\n";
		outfile.write(buffer, size);
	}
	else
	{
		cout << "Failed to write to Save File!\n";
	}
	
	delete[] buffer;
	outfile.close();
	infile.close();
    return 0;
}

void EditorMainMenu()
{
	cout << "\n== MAIN MENU =============================================================\n";
	bool done = false;
	string command = "";
	while (!done)
	{
		cout << "Please Select what you want to Edit.\n";
		cout << "[C]haracters, [I]nventory, [DONE]\n";
		cin >> command;
		if(IsChoice(command, "Characters"))
		{
			CharacterSelectMenu(&done);
		}
		else if (IsChoice(command, "Inventory"))
		{
			EditInventoryMenu(&done);
		}
		else if (IsChoice(command, "DONE"))
		{
			done = true;
		}
		else
		{
			cout << "Command not Recognized.\n";
		}
	}
	cout << "DONE!\n\n";
}

/* CHARACTERS (Default Order):
Player, Shamino, Iolo, Mariah, Geoffrey, Jaana, Julia, Dupre
Katrina, Sentri, Gwenno, Johne, Gorn, Maxwell, Toshi, Saduj */
void CharacterSelectMenu(bool* done)
{
	cout << "\n== CHARACTER SELECT ======================================================\n";
	string command = "";
	bool back = false;
	while (!*done && !back)
	{
		cout << "Choose a Character to edit:\n";
		for (size_t i = 0; i < 16; i++)
		{
			cout << "[" << i << "]: " << characters[i]->getName();
			if ((i+1) % 4 == 0)
			{
				cout << "\n";
			}
			else
			{
				cout << ",\t";
			}
		}
		cout << "\n[#] Character, [B]ack, [DONE]\n";
		cin >> command;
		int num = -1;
		sscanf(command.c_str(), "%d", &num);
		if (num >= 0 && num < 16)
		{
			EditCharacterMenu(characters[num], done);
		}
		else if (IsChoice(command, "Back"))
		{
			back = true;
		}
		else if (IsChoice(command, "DONE"))
		{
			*done = true;
		}
		else
		{
			cout << "Command not Recognized.\n";
		}
	}
	cout << "Done Editing Characters.\n";
}

void EditCharacterMenu(Character* c, bool* done)
{
	cout << "\n== MODIFYING CHARACTER ===================================================\n";
	PrintCharacter(c);
	string command = "";
	string value = "";
	bool back = false;
	while (!*done && !back)
	{
		bool validCommand = true;

		cout << "\nEnter an edit command: \t\t\t[BACK], [DONE]\n";
		cout << "[Stat] [Value] - (Ex: STR 99, Gender Female, of Name Bob)\n";
		
		cin >> command;
		// Single word commands
		if (command == "BACK")
		{
			back = true;
			break;
		}
		else if (command == "DONE")
		{
			*done = true;
			break;
		}
		
		cin >> value;
		// Two word commands
		if (command == "Name")
		{
			value.resize(8);
			c->setName(value);
		}
		else if (command == "Gender")
		{
			if (IsChoice(value, "Male"))
			{
				c->setMale();
			}
			else if (IsChoice(value, "Female"))
			{
				c->setFemale();
			}
			else validCommand = false;
		}
		else
		{
			int num = -1;
			sscanf(value.c_str(), "%d", &num);
			if (num < 0)
			{
				cout << "Cannot set values to negative.\n";
				validCommand = false;
			}
			else
			{
				if (command == "STR")
				{
					c->str = (unsigned char)num;
				}
				else if (command == "INT")
				{
					c->intel = (unsigned char)num;
				}
				else if (command == "DEX")
				{
					c->dex = (unsigned char)num;
				}
				else if (command == "MGC")
				{
					c->magic = (unsigned char)num;
				}
				else if (command == "HP")
				{
					c->HP = (unsigned short)num;
				}
				else if (command == "HM")
				{
					c->HM = (unsigned short)num;
				}
				else if (command == "EXP")
				{
					c->EXP = (unsigned short)num;
				}
				else if (command == "LVL")
				{
					c->LVL = (unsigned char)num;
				}
				else
				{
					cout << "No stat can be set to that number.\n";
					validCommand = false;
				}
			}
		}
		// Update display if successful.
		if (validCommand)
		{
			PrintCharacter(c);
		}
		else
		{
			cout << "Invalid Command.\n";
		}
	}

	cout << "Done Editing Character.\n";
}


void EditInventoryMenu(bool* done)
{
	cout << "\n== MODIFYING INVENTORY ====================================================\n";
	PrintInventory(inventory);
	string command = "";
	string value = "";
	bool back = false;
	while (!*done && !back)
	{
		bool validCommand = true;

		cout << "\nEnter an edit command: \t\t\t[BACK], [DONE]\n";
		cout << "[Item Name] [Value] - (Ex: Food 9999, MagicAxe 99)\n";

		cin >> command;
		// Single word commands
		if (command == "BACK")
		{
			back = true;
			break;
		}
		else if (command == "DONE")
		{
			*done = true;
			break;
		}

		cin >> value;
		// Two word commands
		int num = -1;
		sscanf(value.c_str(), "%d", &num);
		if (num < 0)
		{
			cout << "Cannot set values to negative.\n";
			validCommand = false;
		}
		else
		{
			if (command == "Food")
			{
				inventory->food = (unsigned short)num;
			}
			else if (command == "Gold")
			{
				inventory->gold = (unsigned short)num;
			}
			else if (command == "Keys")
			{
				inventory->keys = (unsigned char)num;
			}
			else if (command == "Gems")
			{
				inventory->gems = (unsigned char)num;
			}
			else if (command == "Torch" || command == "Torches")
			{
				inventory->torches = (unsigned char)num;
			}
			else if (command == "MgcCrpt" || command == "MagicCarpet")
			{
				inventory->magicCarpet = (unsigned char)num;
			}
			else if (command == "SkullKeys")
			{
				inventory->skullKeys = (unsigned char)num;
			}
			else if (command == "Amulets")
			{
				inventory->amulets = (unsigned char)num;
			}
			else if (command == "Crowns")
			{
				inventory->crowns = (unsigned char)num;
			}
			else if (command == "BlackBadge")
			{
				inventory->blackBadge = (unsigned char)((num > 0) ? (char)0xFF : (char)0x00);
			}
			else if (command == "MagicAxe")
			{
				inventory->weapons.magicAxe = (unsigned char)num;
			}
			else
			{
				cout << "No stat can be set to that number.\n";
				validCommand = false;
			}
		}
		// Update display if successful.
		if (validCommand)
		{
			PrintInventory(inventory);
		}
		else
		{
			cout << "Invalid Command.\n";
		}
	}
	cout << "Done Editing Inventory.\n";
}

static bool IsChoice(string command, const char* choice)
{
	if (command == choice) return true;
	return toupper(command[0]) == toupper(choice[0]);
}
