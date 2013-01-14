//The save format used by Mass Effect 3
//Copyright Arthur Moore 2012 GPLV3

#ifndef ME3FORMAT_H
#define ME3FORMAT_H

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

//NOTE: all commented out items (with the exception of headmorph) are done so becausethere's something in Gibbed's code that looks like a version check.

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
	//int EmissiveId; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct Power{
	mstring PowerName;
	float CurrentRank;
	//This is the choice made when evolving a power
	//Either the top or bottom choice should be selected
	//Not sure about these
	// bool Evolution4TopChoice;
	// bool Evolution4BottomChoice;
	// bool Evolution5TopChoice;
	// bool Evolution5BottomChoice;
	// bool Evolution6TopChoice;
	// bool Evolution6BottomChoice;
	mstring PowerClassName;
	int WheelDisplayIndex;
	void read(fstream& saveFile);
	void cout();
};
//GAW stands for "Galaxy at War," which requires online mode.
struct GAWAsset{
	int ID;
	int Strength;
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
	//mstring AmmoPowerName; //Not sure about this
	//mstring AmmoPowerSourceTag; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct WeaponMod{
	mstring name;
	collection<mstring> WeaponModClassNames;
	void read(fstream& saveFile);
	void cout();
};
struct Hotkey{
	mstring PawnName;
	int PowerID; //Not sure about this
	//mstring PowerName; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct playerData {
	bool IsFemale;
	mstring className;
	//bool IsCombatPawn; //Not sure about this
	//bool IsInjuredPawn; //Not sure about this
	//bool UseCasualAppearance; //Not sure about this
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
	//collection<GAWAsset> assets; //Not sure about this
	collection<Weapon> weapons;
	//collection<WeaponMod> WeaponMods; //Not sure about this
	//Loadout currentLoadout; //Not sure about this
	//mstring PrimaryWeapon; //Not sure about this
	//mstring SecondaryWeapon; //Not sure about this
	//collection<int> LoadoutWeaponGroups; //Not sure about this
	//collection<Hotkey> hotkeys; //Not sure about this
	//float CurrentHealth; //Not sure about this
	int Credits;
	int Medigel;
	int Eezo;
	int Iridium;
	int Palladium;
	int Platinum;
	int Probes;
	float CurrentFuel;
	//int Grenades; //Not sure about this
	//mstring FaceCode; //Not sure about this
	//int ClassFriendlyName; //Not sure about this
	//unsigned char id[16]; //Not sure about this
	void read(fstream& saveFile);
	void cout();
};
struct Planet{
	int PlanetID;
	bool Visited;
	collection<xyvector> Probes;
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
}
struct GalaxyMap{
	collection<Planet> Planets;
	collection<System> Systems;
	void read(fstream& saveFile);
	void cout();
};
struct DependentDLC{
	int ModuleID;
	mstring name;
	mstring CanonicalName;
	void read(fstream& saveFile);
	void cout();
};
struct ME3Format{
	unsigned int version;		// This handles saves of version 29 and 59 (Coppied from Gibbed's work)
	mstring DebugName;
	float playTime; 	//(In seconds)
	int Disc;
	mstring BaseLevelName;
	//mstring _BaseLevelNameDisplayOverrideAsRead; //Not sure what this is.
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
	//collection<Placeable> placeables; //Not sure what this is.
	collection<Pawn> pawns;
	playerData player;
	collection<Henchman> henchmen;
	ME3PlotTable Plot;
	ME1PlotTable ME1PlotRecord;
	//collection<PlayerVariable> _PlayerVariables; //Not sure what this is
	GalaxyMap galaxy;
	collection<DependentDLC> dlc;
	//More stuff here///////////////////////////////////////
	unsigned int crc;
};

#endif