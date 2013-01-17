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
#include "RWHelper.hpp"
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
	string PowerName;
	float CurrentRank;
	string PowerClassName;
	int WheelDisplayIndex;
	void read(fstream& saveFile);
	void cout();
};
struct Weapon{
	string name;
	int AmmoUsedCount;			
	int TotalAmmo;
	string ammoName;
	bool CurrentWeapon;
	bool LastWeapon;
	void read(fstream& saveFile);
	void cout();
};
struct Hotkey{
	string name;
	int PowerID;
	void read(fstream& saveFile);
	void cout();
};
struct playerData {
	bool IsFemale;
	string className;
	int level;
	float xp;
	string firstName;
	int lastname;				//not actually used
	char origin;				//This is really an enum (Display as an int)
	char Notoriety;				//This is really an enum (Display as an int)
	int TalentPoints;
	string mappedPower1;
	string mappedPower2;
	string mappedPower3;
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
	string FaceCode;
	int ClassFriendlyName;
	void read(fstream& saveFile);
	void cout();
};
struct Henchman{
	string Tag;
	collection<Power> powers;
	int CharacterLevel;
	int TalentPoints;
	Loadout currentLoadout;
	string MappedPower;
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
	string name;
	void read(fstream& saveFile);
	void cout();
};
struct ME2Format{
	int version;		// ME2 1.0 (release) has saves of version 29 (0x1D)
	string DebugName;
	float playTime; 	//(In seconds)
	int Disc;
	string BaseLevelName;
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