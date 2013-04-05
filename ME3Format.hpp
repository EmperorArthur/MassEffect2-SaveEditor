//The save format used by Mass Effect 3
//Copyright Arthur Moore 2012 GPLV3

#ifndef ME3FORMAT_H
#define ME3FORMAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include "BitArray.hpp"
#include "RWHelper.hpp"
#include "MEShared.hpp"

using namespace std;

//NOTE:  all ints and floats are 4 byte little endian values
//NOTE: all commented out items (with the exception of headmorph) are done so because there's something in Gibbed's code that looks like a version check.
//NOTE:  all comments that look like (Version < 36,"None") or (Version < 46) are things that do not exist below that version number.
//		The second item is what the default constructor needs to be, if the item is not read (because it doesn't exist in the version number being read)

//These are the actuall new stuff in ME3
struct Placeable{
	guid id;
	char IsDestroyed;		//This is really a bool
	char IsDeactivated;		//This is really a bool
	Placeable();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
	void cout(int version);
};
//GAW stands for "Galaxy at War," which requires online mode.
struct GAWAsset{
	int ID;
	int Strength;
	GAWAsset();
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	void cout();
	void cout(int version);
};

//All of these are just ME2 structs with some extra stuff added on
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
	int EmissiveId; //Version < 55,0
	void read(fstream& saveFile,int version);
	void cout(int version);
};
struct Power{
	string PowerName;
	float CurrentRank;
	//This is the choice made when evolving a power (I'm not sure exactly how it maps to the in game power choice)
	int EvolvedChoice[6]; //0-1 is (Version < 30,0) and  2-5 is (Version < 31,0)
	string PowerClassName;
	int WheelDisplayIndex;
	Power();
	void read(fstream& saveFile,int version);
	void cout(int version);
};
struct Weapon{
	string name;
	int AmmoUsedCount;			
	int TotalAmmo;
	bool CurrentWeapon;
	bool LastWeapon;
	string AmmoPowerName; //Version < 17
	string AmmoPowerSourceTag; //Version < 59
	Weapon();
	void read(fstream& saveFile,int version);
	void cout(int version);
};
struct WeaponMod{
	~WeaponMod();
	string name;
	vector<string*> WeaponModClassNames;
	void read(fstream& saveFile);
	void cout();
};
struct Hotkey{
	string PawnName;
	int PowerID; //Not sure about this
	//mstring PowerName; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct playerData {
	~playerData();
	bool IsFemale;
	string className;
	bool IsCombatPawn; //Version < 37,true
	bool IsInjuredPawn; //Version < 48,false
	bool UseCasualAppearance; //Version < 48,false
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
	vector<Power*> powers;
	vector<GAWAsset*> assets; //Version < 38
	vector<Weapon*> weapons;
	//vector<WeaponMod*> WeaponMods; //Version < 32
	//Loadout currentLoadout; //s => s.Version < 18, () => new Loadout());
	//string PrimaryWeapon; //s => s.Version < 41, () => null);
	//string SecondaryWeapon; //s => s.Version < 41, () => null);
	//vector<int> LoadoutWeaponGroups; //Version < 33
	//vector<Hotkey*> hotkeys; //Version < 19
	//float CurrentHealth; //s => s.Version < 44, () => 0.0f);
	int Credits;
	int Medigel;
	int Eezo;
	int Iridium;
	int Palladium;
	int Platinum;
	int Probes;
	float CurrentFuel;
	int Grenades; //Version < 54,0
	//string FaceCode; //assert(stream.Version >= 25) (this is pretty much what gibbed's code does)
	//int ClassFriendlyName; //Version < 26,0
	//guid id; //s.Version < 42, () => Guid.Empty);
	void read(fstream& saveFile,int version);
	void cout(int version);
};
struct Henchman{
	~Henchman();
	string Tag;
	vector<Power*> powers;
	int CharacterLevel;
	int TalentPoints;
	//Loadout currentLoadout; //Not sure about this
	//mstring MappedPower; //Not sure about this
	//vector<WeaponMod*> WeaponMods; //Not sure about this
	//int Grenades; //Not sure about this
	//vector<Weapon*> weapons; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct ME3PlotTable{
	//Stuff goes here
};
struct Planet{
	~Planet();
	int PlanetID;
	bool Visited;
	vector<xyvector*> Probes;
	//bool ShowAsScanned; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct System{
	int ID;
	float ReaperAlertLevel;
	//bool ReapersDetected; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct GalaxyMap{
	~GalaxyMap();
	vector<Planet*> Planets;
	vector<System*> Systems;
	void read(fstream& saveFile);
	void cout();
};
struct DependentDLC{
	int ModuleID;
	string name;
	string CanonicalName;
	void read(fstream& saveFile);
	void cout();
};
struct ME3Format{
	~ME3Format();
	unsigned int version;		// This handles saves of version 29 and 59 (Coppied from Gibbed's work)
								// 29 is ME2 and 59 is ME3
	string DebugName;
	float playTime; 	//(In seconds)
	int Disc;
	string BaseLevelName;
	string BaseLevelNameDisplayOverrideAsRead; //Version < 36,"None"
	char dificulty;		//This is really an enum (Display as an int)
	int EndGameState;	//This is really an enum
	Timestamp SaveDateTime;
	xyzvector playerPosition;
	PlayerRotation myRotation;
	int CurrentLoadingTip;
	vector<LevelRecord*> levels;
	vector<StreamingRecord*> streams;
	vector<Kismet*> kismets;
	vector<Door*> doors;
	vector<Placeable*> placeables; //Version < 46
	vector<Pawn*> pawns;
	playerData player;
	/*
	vector<Henchman*> henchmen;
	ME3PlotTable Plot;
	ME1PlotTable ME1PlotRecord;
	//vector<PlayerVariable*> _PlayerVariables; //Version < 34
	GalaxyMap galaxy;
	vector<DependentDLC*> dlc;
	//More stuff here///////////////////////////////////////
	unsigned int crc;
	*/
	void read(fstream& saveFile);
	void cout();
};

#endif