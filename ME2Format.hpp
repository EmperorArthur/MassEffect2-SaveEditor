//The save format used by Mass Effect 2
//Copyright Arthur Moore 2012 GPLV3

#ifndef ME2FORMAT_H
#define ME2FORMAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "BitArray.hpp"
#include "collection.hpp"
#include "mstring.hpp"
#include "MEShared.hpp"

using namespace std;

//NOTE:  all ints, floats, and bools have a 4 byte size

//This is 57 bytes without a head morph
struct Appearance{
	unsigned char CombatAppearance; //(display as an int) really an enum(0 means parts, 1 means full)
	int CasualID;
	int FullBodyID;
	int TorsoID;
	int ShoulderID;
	int ArmID;
	int LegID;
	int SpecID;
	int Tint1ID;
	int Tint2ID;
	int Tint3ID;
	int PatternID;
	int PatternColorID;
	int HelmetID;
	bool HasMorphHead;	//assert(!HasMorphHead);	//I don't properly handle this right now
	//MorphHead myHead;
	void read(fstream& saveFile);
	void cout();
};
struct Power{
	mstring PowerName;
	float CurrentRank;
	mstring PowerClassName;
	int WheelDisplayIndex;
	void read(fstream& saveFile);
	void cout();
};
struct Weapon{
	mstring name;
	int AmmoUsedCount;			
	int TotalAmmo;
	mstring ammoName;
	bool CurrentWeapon;
	bool LastWeapon;
	void read(fstream& saveFile);
	void cout();
};
struct Hotkey{
	mstring name;
	int PowerID;
	void read(fstream& saveFile);
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
	Appearance myAppearance;
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
	mstring FaceCode;
	int ClassFriendlyName;
	void read(fstream& saveFile);
	void cout();
};
struct Henchman{
	mstring Tag;
	collection<Power> powers;
	int CharacterLevel;
	int TalentPoints;
	Loadout currentLoadout;
	mstring MappedPower;
	void read(fstream& saveFile);
	void cout();
};
struct PlotQuest{
	unsigned int QuestCounter;
	bool QuestUpdated;
	collection<int> History;
	void read(fstream& saveFile);
	void cout();
};
struct CodexPage{
	int Page;
	bool isNew;
	void read(fstream& saveFile);
	void cout();
};
struct CodexEntry{
	collection<CodexPage> pages;
	void read(fstream& saveFile);
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
	void read(fstream& saveFile);
	void cout();
};
struct Planet{
	int PlanetID;
	bool Visited;
	collection<xyvector> Probes;
	void read(fstream& saveFile);
	void cout();
};
struct GalaxyMap{
	collection<Planet> Planets;
	void read(fstream& saveFile);
	void cout();
};
struct DependentDLC{
	int ModuleID;
	mstring name;
	void read(fstream& saveFile);
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
	Timestamp SaveDateTime;
	xyzvector playerPosition;
	PlayerRotation myRotation;
	int CurrentLoadingTip;
	collection<LevelRecord> levels;
	collection<StreamingRecord> streams;
	collection<Kismet> kismets;
	collection<Door> doors;
	collection<Pawn> pawns;
	playerData player;
	collection<Henchman> henchmen;
	ME2PlotTable Plot;
	ME1PlotTable ME1PlotRecord;
	GalaxyMap galaxy;
	collection<DependentDLC> dlc;
	unsigned int crc;							// CRC32 of save data (from start) to before CRC32 value
	void read(fstream& saveFile);
	void cout();
};


#endif