#pragma once
#include <fstream>
using namespace std;

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


// Unused
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