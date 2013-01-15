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
	Timestamp();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct xyzvector{
	float x;
	float y;
	float z;
	xyzvector();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};

struct PlayerRotation{
	int Pitch;
	int Yaw;
	int Roll;
	PlayerRotation();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct LevelRecord{
	int magicUnused;	/////////This causes windows to crash at the end of the program, but Level's are all messed up without it/////////
	mstring LevelName;
	bool ShouldBeLoaded;
	bool ShouldBeVisible;
	LevelRecord();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct StreamingRecord{
	mstring name;
	bool active;
	StreamingRecord();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct guid{
	unsigned char id[16];
	guid();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct Kismet{
	guid id;
	bool Value;
	Kismet();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct Door{
	guid id;
	unsigned char CurrentState; //(Display as an int)
	unsigned char OldState; //(Display as an int)
	Door();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
//This only exists because of legacy code
//I can probably easily get rid of it.
struct Pawn{
	guid id;
	//guid's default constructor is automatically called
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
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
	Loadout();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct ME1PlotTable{
	BitArray BoolVariables;
	collection<int> ints;
	collection<float> floats;
	//Have to leave it up to the default constructors that are automatically called
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};
struct xyvector{
	int x;
	int y;
	xyvector();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
};

#endif

