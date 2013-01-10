//The save format used by Mass Effect 2
//Copyright Arthur Moore 2012 GPLV3

#ifndef ME2FORMAT_H
#define ME2FORMAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "BinFile.hpp"
#include "BitArray.hpp"
#include "collection.hpp"
#include "mstring.hpp"

using namespace std;

//NOTE:  all ints, floats, and bools have a 4 byte size

struct xyzvector{	//(16 bytes total) (This is the only struct without it's own read function)
	float x;
	float y;
	float z;
};
struct LevelRecord{
	mstring LevelName;
	bool Unknown1; // could be ShouldBeVisible or ShouldBeLoaded
	bool Unknown2; // could be ShouldBeVisible or ShouldBeLoaded
	void read(binFile& saveFile);
	void cout();
};
struct StreamingRecord{
	mstring name;
	bool active;
	void read(binFile& saveFile);
	void cout();
};
struct Door{
	unsigned char id[16];
	unsigned char CurrentState; //(Display as an int)
	unsigned char OldState; //(Display as an int)
	void read(binFile& saveFile);
	void cout();
};
struct Power{
	mstring PowerName;
	float CurrentRank;
	mstring PowerClassName;
	int WheelDisplayIndex;
	void read(binFile& saveFile);
	void cout();
};
struct Weapon{
	mstring name;
	int AmmoUsedCount;			
	int TotalAmmo;
	mstring ammoName;
	bool CurrentWeapon;
	bool LastWeapon;
	void read(binFile& saveFile);
	void cout();
};
struct Hotkey{
	mstring name;
	int PowerID;
	void read(binFile& saveFile);
	void cout();
};
struct Loadout{
	int WeaponSize[6];
	mstring Weapon[6];
	void read(binFile& saveFile);
	void cout();
};
struct playerData {
	bool IsFemale;
	mstring className;
	int level;
	float xp;
	mstring firstName;
	int lastname;				//not actually used
	char origin;				//This is really an enum (Display as an int)
	char Notoriety;				//This is really an enum (Display as an int)
	int TalentPoints;
	mstring mappedPower1;
	mstring mappedPower2;
	mstring mappedPower3;
	unsigned char Appearance[57];	 //This is a whole seperate struct that I'm currently ignoring
	collection<Power> powers;
	collection<Weapon> weapons;
	Loadout currentLoadout;
	collection<Hotkey> hotkeys;
	int Credits;
	int Medigel;
	int Eezo;
	int Iridium;
	int Palladium;
	int Platinum;
	int Probes;
	float CurrentFuel;
	int FaceCodeSize;
	mstring FaceCode;
	int ClassFriendlyName;
	void read(binFile& saveFile);
	void cout();
};
struct Henchman{
	mstring Tag;
	collection<Power> powers;
	int CharacterLevel;
	int TalentPoints;
	Loadout currentLoadout;
	mstring MappedPower;
	void read(binFile& saveFile);
	void cout();
};
struct PlotQuest{
	unsigned int QuestCounter;
	bool QuestUpdated;
	collection<int> History;
	void read(binFile& saveFile);
	void cout();
};
struct CodexPage{
	int Page;
	bool isNew;
	void read(binFile& saveFile);
	void cout();
};
struct CodexEntry{
	collection<CodexPage> pages;
	void read(binFile& saveFile);
	void cout();
};
struct ME2PlotTable{
	BitArray BoolVariables;
	collection<int> ints;
	collection<float> floats;
	int QuestProgressCounter;
	collection<PlotQuest> QuestProgress;
	collection<int> QuestIDs;
	collection<CodexEntry> CodexEntries;
	collection<int> CodexIDs;
	void read(binFile& saveFile);
	void cout();
};
struct ME1PlotTable{
	BitArray BoolVariables;
	collection<int> ints;
	collection<float> floats;
	void read(binFile& saveFile);
	void cout();
};
struct xyvector{
	int x;
	int y;
	void read(binFile& saveFile);
	void cout();
};
struct Planet{
	int PlanetID;
	bool Visited;
	collection<xyvector> Probes;
	void read(binFile& saveFile);
	void cout();
};
struct GalaxyMap{
	collection<Planet> Planets;
	void read(binFile& saveFile);
	void cout();
};
struct DependentDLC{
	int ModuleID;
	mstring name;
	void read(binFile& saveFile);
	void cout();
};
struct ME2Format{
	int version;		// ME2 1.0 (release) has saves of version 29 (0x1D)
	mstring DebugName;
	float playTime; 	//(In seconds)
	mstring Disc;
	mstring BaseLevelName;
	char dificulty;		//This is really an enum (Display as an int)
	int EndGameState;	//This is really an enum
	struct {
		int SecondsSinceMidnight;	// (In seconds)
		int day;
		int month;
		int year;
	} timestamp;
	xyzvector playerPosition;		//(16 byte size)
	int playerRotation;
	int CurrentLoadingTip;
	collection<LevelRecord> levels;
	collection<StreamingRecord> streams;
	//Gibbed's code talks about kismets, but I don't see anything
	int numberofKismets;	//assert(0==numberofKismets);
	collection<Door> doors;
	//Gibbed's code talks about pawn records, but I don't see anything
	int numberofPawns;	//assert(0==numberofPawns);
	playerData player;
	collection<Henchman> henchmen;
	ME2PlotTable Plot;
	ME1PlotTable ME1PlotRecord;
	GalaxyMap galaxy;
	collection<DependentDLC> dlc;
	unsigned int crc;							// CRC32 of save data (from start) to before CRC32 value
	void read(binFile& saveFile);
	void cout();
};


#endif