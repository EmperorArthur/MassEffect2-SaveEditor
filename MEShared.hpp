//The shared objects between Mass Effect 2 and 3
//Copyright Arthur Moore 2012 GPLV3

#ifndef MESHARED_H
#define MESHARED_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "BitArray.hpp"
#include "collection.hpp"
#include "mstring.hpp"

using namespace std;

//NOTE:  all ints, floats, and bools have a 4 byte size

struct Timestamp {
	int SecondsSinceMidnight;	// (In seconds)
	int day;
	int month;
	int year;
	void read(fstream& saveFile);
	void cout();
};
struct xyzvector{
	float x;
	float y;
	float z;
	void read(fstream& saveFile);
	void cout();
};

struct PlayerRotation{
	int Pitch;
	int Yaw;
	int Roll;
	void read(fstream& saveFile);
	void cout();
};
struct LevelRecord{
	int magicUnused;	/////////This causes windows to crash at the end of the program, but Level's are all messed up without it/////////
	mstring LevelName;
	bool ShouldBeLoaded;
	bool ShouldBeVisible;
	void read(fstream& saveFile);
	void cout();
};
struct StreamingRecord{
	mstring name;
	bool active;
	void read(fstream& saveFile);
	void cout();
};
struct Kismet{
	unsigned char id[16];
	bool Value;
	void read(fstream& saveFile);
	void cout();
};
struct Door{
	unsigned char id[16];
	unsigned char CurrentState; //(Display as an int)
	unsigned char OldState; //(Display as an int)
	void read(fstream& saveFile);
	void cout();
};
struct Pawn{
	unsigned char id[16];
	void read(fstream& saveFile);
	void cout();
};
struct Loadout{
	//Always in this order:
	//	AssaultRifle
	//	Shotgun
	//	SniperRifle
	//	SubmachineGun
	//	Pistol
	//	HeavyWeapon
	mstring Weapon[6];
	void read(fstream& saveFile);
	void cout();
};
struct ME1PlotTable{
	BitArray BoolVariables;
	collection<int> ints;
	collection<float> floats;
	void read(fstream& saveFile);
	void cout();
};
struct xyvector{
	int x;
	int y;
	void read(fstream& saveFile);
	void cout();
};

#endif

