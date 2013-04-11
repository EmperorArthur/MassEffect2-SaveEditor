//The save format used by Mass Effect 3
//Copyright Arthur Moore 2012 GPLV3

#include "ME3Format.hpp"

//These are some macros to help me with my reading depending on version number
#define READ4(variable) saveFile.read((char *) &variable,4);
#define IFELSEREAD4(versionCheck,checkFailedState,variable) if(versionCheck){variable = checkFailedState;}else{READ4(variable);}
#define IFELSEREADBOOL(versionCheck,checkFailedState,variable) if(versionCheck){variable = checkFailedState;}else{ReadBool(saveFile,variable);}
//WATCH OUT:  This does the reading in the if block.  IFELSEREAD4 does the reading in the else block
#define IFREAD4(versionCheck,variable) if(versionCheck){READ4(variable);}

ME3Format::~ME3Format(){
	VectorDelete(levels);
	VectorDelete(streams);
	VectorDelete(kismets);
	VectorDelete(doors);
	VectorDelete(placeables);
	VectorDelete(pawns);
	//VectorDelete(henchmen);
	//VectorDelete(dlc);
}

void ME3Format::read(fstream& saveFile){
	//Read the data from the file
	saveFile.seekg(ios_base::beg + 0x00);
	saveFile.read((char *) &version,4);
	assert(29 == version||59 == version);	//Make sure we're reading the correct file type
	StringRead(saveFile,DebugName);
	saveFile.read((char *) &playTime,4);
	saveFile.read((char *) &Disc,4);
	StringRead(saveFile,BaseLevelName);
	if(version<36){
		BaseLevelNameDisplayOverrideAsRead = "None";
	}else{
		StringRead(saveFile,BaseLevelNameDisplayOverrideAsRead);
	}
	saveFile.read(&dificulty,1);
	if (version >= 43 && version <= 46){
		char unknown = 0;
		saveFile.read(&unknown,1);
	}
	saveFile.read((char *) &EndGameState,4);
	SaveDateTime.read(saveFile);
	playerPosition.read(saveFile);
	myRotation.read(saveFile);
	saveFile.read((char *) &CurrentLoadingTip,4);
	VectorRead(saveFile,levels,version);
	VectorRead(saveFile,streams,version);
	VectorRead(saveFile,kismets,version);
	VectorRead(saveFile,doors,version);
	if (version >= 46){
		VectorRead(saveFile,placeables,version);
	}
	VectorRead(saveFile,pawns,version);
	player.read(saveFile,version);
}
void ME3Format::cout(){
	std::cout << "File version is " << (int) version << endl;
	std::cout << "Debug name is:  " << DebugName << endl;
	std::cout << "Played for " << playTime << " seconds." << endl;
	std::cout << "Disc is: " << Disc << endl;
	std::cout << "BaseLevelName is:  "<<BaseLevelName<<endl;
	if(version>=36){
		std::cout << "BaseLevelNameDisplayOverrideAsRead is:  "<<BaseLevelNameDisplayOverrideAsRead<<endl;
	}
	std::cout << "dificulty is:  "<<(int)dificulty<<endl;
	std::cout << "EndGameState is:  "<<(int)EndGameState<<endl;
	SaveDateTime.cout();
	playerPosition.cout();
	myRotation.cout();
	std::cout << "CurrentLoadingTip is:  " << (int) CurrentLoadingTip << endl;
	std::cout << "Displaying Levels:"<<endl;
	VectorCout(levels);
	std::cout << "Displaying Streams:"<<endl;
	VectorCout(streams);
	std::cout << "Displaying Kismets:"<<endl;
	VectorCout(kismets);
	std::cout << "Displaying Doors:" << endl;
	VectorCout(doors);
	if (version >= 46){
		std::cout << "Displaying Placeables:" << endl;
		VectorCout(placeables);
	}
	std::cout << "Displaying Pawns:" << endl;
	VectorCout(pawns);
	player.cout(version);
	
}
Placeable::Placeable(){
	IsDestroyed = 0;
	IsDeactivated = 0;
}
void Placeable::read(fstream& saveFile,int version){
	read(saveFile);
}
void Placeable::read(fstream& saveFile){
	id.read(saveFile);
	saveFile.read((char *) &IsDestroyed,1);
	saveFile.read((char *) &IsDeactivated,1);
}
void Placeable::cout(int version){
	cout();
}
void Placeable::cout(){
	id.cout();
	std::cout << ": " << (bool)IsDestroyed << "," << (bool)IsDeactivated << endl;
}
playerData::~playerData(){
	VectorDelete(powers);
	VectorDelete(assets);
	VectorDelete(weapons);
}
void playerData::read(fstream& saveFile,int version){
	ReadBool(saveFile,IsFemale);
	StringRead(saveFile,className);
	//This if statement and the IFELSEREADBOOL are the same thing, one just involves less typing
	if(version < 37){
		IsCombatPawn = true;
	}else{
		ReadBool(saveFile,IsCombatPawn);
	}
	IFELSEREADBOOL(version < 48,false,IsInjuredPawn);
	IFELSEREADBOOL(version < 48,false,UseCasualAppearance);
	saveFile.read((char *) &level,4);
	saveFile.read((char *) &xp,4);
	StringRead(saveFile,firstName);
	saveFile.read((char *) &lastname,4);
	saveFile.read((char *) &origin,1);
	saveFile.read((char *) &Notoriety,1);
	saveFile.read((char *) &TalentPoints,4);
	StringRead(saveFile,mappedPower1);
	StringRead(saveFile,mappedPower2);
	StringRead(saveFile,mappedPower3);
	myAppearance.read(saveFile,version);
	VectorRead(saveFile,powers,version);
	if(version >=38){
		VectorRead(saveFile,assets,version);
	}
	VectorRead(saveFile,weapons,version);
	if(version >=32){
		VectorRead(saveFile,WeaponMods,version);
	}
	if(version >=18){
		currentLoadout.read(saveFile);
	}
	if(version >=41){
		StringRead(saveFile,PrimaryWeapon);
		StringRead(saveFile,SecondaryWeapon);
	}
	if(version >=33){
		VectorRead(saveFile,LoadoutWeaponGroups,version);
	}
	if(version >=19){
		VectorRead(saveFile,hotkeys,version);
	}
	IFELSEREAD4(version < 44, 0.0f, CurrentHealth);
	READ4(Credits);
	READ4(Medigel);
	READ4(Eezo);
	READ4(Iridium);
	READ4(Palladium);
	READ4(Platinum);
	READ4(Probes);
	READ4(CurrentFuel);
	IFELSEREAD4(version < 54, 0, Grenades);
}
void playerData::cout(int version){
	std::cout << "****************Start of Player Information****************" << std::endl;
	std::cout << "	Player is female: " << IsFemale << endl;
	std::cout << "	Player's class is " << className << endl;
	if(version >= 37){
		std::cout << "	Player is in combat: " << IsCombatPawn << endl;
	}
	if(version >= 48){
		std::cout << "	Player is injured: " << IsInjuredPawn << endl;
	}
	if(version >= 48){
		std::cout << "	Player is in casual wear: " << UseCasualAppearance << endl;
	}
	std::cout << "	Player's level is " << (int)level << endl;
	std::cout << "	Player's has " << xp << " XP" << endl;
	std::cout << "	Player's first name is: " << firstName << endl;
	std::cout << "	Player's last name is: " << lastname << " <- this should be 125303" << endl;
	std::cout << "	Player's origin is: " << (int)origin << endl;
	std::cout << "	Player's Notoriety is: " << (int)Notoriety << endl;
	std::cout << "	Player's has " << (int)TalentPoints << " Talent Points" << endl;
	std::cout << "	Mapped Power #1: " << mappedPower1 << endl;
	std::cout << "	Mapped Power #2: " << mappedPower2 << endl;
	std::cout << "	Mapped Power #3: " << mappedPower3 << endl;
	//myAppearance.cout(version);
	std::cout << "	Displaying powers:"<<endl;
	VectorCout(powers,version);
	if(version >=38){
		std::cout << "	Displaying Galaxy at War assets:"<<endl;
		VectorCout(assets);
	}
	std::cout << "	Displaying Weapons:"<<endl;
	VectorCout(weapons,version);
	if(version >=32){
		std::cout << "	Displaying Weapon Mods:"<<endl;
		VectorCout(WeaponMods);
	}
	if(version >=18){
		std::cout << "	Displaying Weapons Loadout:"<<endl;
		currentLoadout.cout();
	}
	if(version >=41){
		std::cout << "	Primary Weapon:    " << PrimaryWeapon << endl;
		std::cout << "	Secondary Weapon:  " << SecondaryWeapon << endl;
	}
	if(version >=33){
		std::cout << "	Displaying Loadout Weapon Groups:" << endl;
		VectorCoutBasic(LoadoutWeaponGroups);
	}
	if(version >=19){
		std::cout << "	Displaying Hotkeys:"<<endl;
		VectorCout(hotkeys,version);
	}
	if(version >=44){
		std::cout << "	Player has " << CurrentHealth << " Health" << endl;
	}
	std::cout << "	Player has " << Credits << " Credits" << endl;
	std::cout << "	Player has " << Medigel << " Medigel" << endl;
	std::cout << "	Player has " << Eezo << " Eezo" << endl;
	std::cout << "	Player has " << Iridium << " Iridium" << endl;
	std::cout << "	Player has " << Palladium << " Palladium" << endl;
	std::cout << "	Player has " << Platinum << " Platinum" << endl;
	std::cout << "	Player has " << Probes << " Probes" << endl;
	std::cout << "	Player has " << CurrentFuel << " CurrentFuel" << endl;
	if(version >=54){
		std::cout << "	Player has " << Grenades << " Grenades" << endl;
	}
	
	std::cout << "****************End of Player Information****************" << std::endl;
}
void Appearance::read(fstream& saveFile,int version){
	saveFile.read((char *) &CombatAppearance,1);
	saveFile.read((char *) &CasualID,4);
	saveFile.read((char *) &FullBodyID,4);
	saveFile.read((char *) &TorsoID,4);
	saveFile.read((char *) &ShoulderID,4);
	saveFile.read((char *) &ArmID,4);
	saveFile.read((char *) &LegID,4);
	saveFile.read((char *) &SpecID,4);
	saveFile.read((char *) &Tint1ID,4);
	saveFile.read((char *) &Tint2ID,4);
	saveFile.read((char *) &Tint3ID,4);
	saveFile.read((char *) &PatternID,4);
	saveFile.read((char *) &PatternColorID,4);
	saveFile.read((char *) &HelmetID,4);
	ReadBool(saveFile,HasMorphHead);
	assert(!HasMorphHead);
	IFELSEREAD4(version < 55,0,EmissiveId);
}
void Appearance::cout(int version){
	bool ThisFunctionNeedsToBeWritten = true;
	assert(!ThisFunctionNeedsToBeWritten);
}
Power::Power(){
	PowerName = "";
	CurrentRank = 0;
	for(int i=0;i<6;i++){
		EvolvedChoice[i] = 0;
	}
	PowerClassName = "";
	WheelDisplayIndex = -1;
}
void Power::read(fstream& saveFile,int version){
	StringRead(saveFile,PowerName);
	saveFile.read((char *) &CurrentRank,4);
	IFELSEREAD4(version < 30,0,EvolvedChoice[0]);
	IFELSEREAD4(version < 30,0,EvolvedChoice[1]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[2]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[3]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[4]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[5]);
	StringRead(saveFile,PowerClassName);
	saveFile.read((char *) &WheelDisplayIndex,4);
}
void Power::cout(int version){
	std::cout << "		" << PowerName << " : " << PowerClassName << ": " << CurrentRank << "," << WheelDisplayIndex << endl;
	if(version >= 30){
		std::cout << "			" << "Evolved Choices: ";
		for(int i=0;i<6;i++){
			std::cout << EvolvedChoice[i];
		}
		std::cout << endl;
	}
}
GAWAsset::GAWAsset(){
	ID = 0;
	Strength = 0;
}
void GAWAsset::read(fstream& saveFile,int version){
	read(saveFile);
}
void GAWAsset::read(fstream& saveFile){
	saveFile.read((char *) &ID,4);
	saveFile.read((char *) &Strength,4);
}
void GAWAsset::cout(int version){
	cout();
}
void GAWAsset::cout(){
	std::cout << "		Asset ID:  "<<ID<< " Strength:  "<<Strength<<endl;
}
Weapon::Weapon(){
	name = "";
	AmmoUsedCount = 0;
	TotalAmmo = 0;
	CurrentWeapon = 0;
	LastWeapon = 0;
	AmmoPowerName = "";
	AmmoPowerSourceTag = "";
}
void Weapon::read(fstream& saveFile,int version){
	StringRead(saveFile,name);
	saveFile.read((char *) &AmmoUsedCount,4);
	saveFile.read((char *) &TotalAmmo,4);
	ReadBool(saveFile,CurrentWeapon);
	ReadBool(saveFile,LastWeapon);
	if(version >=17){
		StringRead(saveFile,AmmoPowerName);
	}
	if(version >=59){
		StringRead(saveFile,AmmoPowerSourceTag);
	}
}
void Weapon::cout(int version){
	std::cout << "		" << name << " : " << endl;
	std::cout << "			" << (TotalAmmo - AmmoUsedCount) << "/" << TotalAmmo << endl;
	if(CurrentWeapon){
		std::cout << "			This is the currently equipped weapon."<<endl;
	}
	if(LastWeapon){
		std::cout << "			This is the last equipped weapon."<<endl;
	}
	if(version >=59){
		std::cout << "			Power:  "<< AmmoPowerName << "	From:  " << AmmoPowerSourceTag << endl;
	}else if(version >=17){
		std::cout << "			Power:  "<< AmmoPowerName << endl;
	}
}

WeaponMod::~WeaponMod(){
	//Don't need to delete the string vector since it's not a vector of pointers
}
void WeaponMod::read(fstream& saveFile, int version){
	StringRead(saveFile,name);
	VectorRead(saveFile,WeaponModClassNames,version);
}
void WeaponMod::cout(){
	std::cout << "		Mod Name:  " << name << endl;
	for(size_t i=0;i<WeaponModClassNames.size();i++){
		std::cout << "			ClassName:  " << WeaponModClassNames[i] << endl;
	}
}

Hotkey::Hotkey(){
	PawnName = "";
	PowerID = 0;
	PowerName = "";
}
void Hotkey::read(fstream& saveFile, int version){
	StringRead(saveFile,PawnName);
	if(version < 30){
		READ4(PowerID);
	}else{
		StringRead(saveFile,PowerName);
	}
}
void Hotkey::cout(int version){
	if(version < 30){
		std::cout << "		" << PawnName << " : " << PowerID << endl;
	}else{
		std::cout << "		" << PawnName << " : " << PowerName << endl;
	}
}