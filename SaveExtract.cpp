//This extracts the information from a savegame
//To Run:
//	SaveExtract filename
//Copyright Arthur Moore 2012 GPLV3

//Fun header files
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "BinFile.hpp"
#include "BitArray.hpp"
#include "collection.hpp"
#include "mstring.hpp"

//Can't forget this
using namespace std;

//NOTE:  Most of the unsigned chars can become ints with proper offsets
//NOTE:  all ints, floats, and bools have a 4 byte size

struct xyzvector{	//(16 bytes total)
	float x;
	float y;
	float z;
};
struct LevelRecord{
	int nameSize;	/////////////////////////////THIS SHOULD NOT BE NEEDED, BUT IT IS/////////////////////////////
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
// struct ME1PlotTable{
	// BitArray BoolVariables;
	// collection<int> ints;
	// collection<float> floats;
	// void read(binFile& saveFile);
	// void cout();
// };
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
struct ME2Format{
	int version;		//Offset 0x00
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
	//ME2PlotTable Plot;
	//ME1PlotTable ME1PlotRecord;
	//There's other stuff, but we're ignoring it for now
	void read(binFile& saveFile);
	void cout();
};

void playerData::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &IsFemale,4);
	className.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &level,4);
	saveFile.fileStream.read((char *) &xp,4);
	firstName.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &lastname,4);
	saveFile.fileStream.read((char *) &origin,1);
	saveFile.fileStream.read((char *) &Notoriety,1);
	saveFile.fileStream.read((char *) &TalentPoints,4);
	mappedPower1.read(saveFile.fileStream);
	mappedPower2.read(saveFile.fileStream);
	mappedPower3.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &Appearance,57);
	powers.read(saveFile);
	weapons.read(saveFile);
	currentLoadout.read(saveFile);
	hotkeys.read(saveFile);
	saveFile.fileStream.read((char *) &Credits,4);
	saveFile.fileStream.read((char *) &Medigel,4);
	saveFile.fileStream.read((char *) &Eezo,4);
	saveFile.fileStream.read((char *) &Iridium,4);
	saveFile.fileStream.read((char *) &Palladium,4);
	saveFile.fileStream.read((char *) &Platinum,4);
	saveFile.fileStream.read((char *) &Probes,4);
	saveFile.fileStream.read((char *) &CurrentFuel,4);
	FaceCode.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &ClassFriendlyName,4);
}

void ME2PlotTable::read(binFile& saveFile){
	BoolVariables.read(saveFile.fileStream);
	ints.readBasic(saveFile);
	floats.readBasic(saveFile);
	saveFile.fileStream.read((char *) &QuestProgressCounter,4);
	QuestProgress.read(saveFile);
	QuestIDs.readBasic(saveFile);
	CodexEntries.read(saveFile);
	CodexIDs.readBasic(saveFile);
}
void ME2PlotTable::cout(){
	std::cout << "There are " << (BoolVariables.getSize()) << " bool values in the ME2 plot table" << endl;
	std::cout << "Displaying bools:"<<endl;
	BoolVariables.cout();
	std::cout << "There are " << ints.size() << " interger values in the ME2 plot table" << endl;
	std::cout << "Displaying ints:"<<endl;
	ints.coutBasic();
	std::cout << "There are " << floats.size() << " floating point values in the ME2 plot table" << endl;
	std::cout << "Displaying floats:"<<endl;
	floats.coutBasic();
	std::cout << " QuestProgressCounter: " << QuestProgressCounter << endl;
	std::cout << "There are " << QuestProgress.size() << " quest plots the ME2 plot table" << endl;
	std::cout << "Displaying plots:"<<endl;
	QuestProgress.cout(false);
	std::cout << "There are " << QuestIDs.size() << " quest IDs in the ME2 plot table" << endl;
	std::cout << "Displaying quest IDs:"<<endl;
	QuestIDs.coutBasic();
	std::cout << "There are " << CodexEntries.size() << " Codex Entries in the ME2 plot table" << endl;
	std::cout << "Displaying Codex Entries:"<<endl;
	CodexEntries.cout();
	std::cout << "There are " << CodexIDs.size() << " codex IDs in the ME2 plot table" << endl;
	std::cout << "Displaying codex IDs:"<<endl;
	CodexIDs.coutBasic();
}
void Power::cout(){
	std::cout << "		" << PowerName << " : " << PowerClassName << ": " << CurrentRank << "," << WheelDisplayIndex << endl;
}
void Hotkey::cout(){
	std::cout << "	" << name << " : " << PowerID << endl;
}

//void ME1PlotTable::read(binFile& saveFile){
	// BoolVariables.read(saveFile.fileStream);
	// ints.readBasic(saveFile);
	// floats.readBasic(saveFile);
//};
//void ME1PlotTable::cout(){
	// std::cout << "****************Start of ME1 Plot Table****************" << std::endl;
	// BoolVariables.cout();
	// ints.coutBasic();
	// floats.coutBasic();
	// std::cout << "****************End of ME1 Plot Table****************" << std::endl;
//}
void Henchman::cout(){
	std::cout << "	" << Tag << ":" << endl;
	std::cout << "	Displaying powers:"<<endl;
	powers.cout(false);
	std::cout << "	Level: " << CharacterLevel << endl;
	std::cout << "	TalentPoints: " << TalentPoints << endl;
	std::cout << "	Displaying Weapons Loadout:"<<endl;
	currentLoadout.cout();
	std::cout << "	MappedPower:  " << MappedPower << endl;
}
void Weapon::cout(){
	std::cout << "	" << name << " : " << endl;
	std::cout << "		" << (TotalAmmo - AmmoUsedCount) << "/" << TotalAmmo << endl;
	if(CurrentWeapon){
		std::cout << "		This is the currently equipped weapon."<<endl;
	}
	if(LastWeapon){
		std::cout << "		This is the last equipped weapon."<<endl;
	}
}
void Door::cout(){
	std::cout << "	id: ";
	for(int j=0;j<16;j++){
		std::cout << hex << (unsigned short)id[j];
	}
	std::cout <<	dec << ": " << (int) CurrentState << "," << (int) OldState<< endl;
}

void Power::read(binFile& saveFile){

	PowerName.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &CurrentRank,4);

	PowerClassName.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &WheelDisplayIndex,4);
}

void Loadout::read(binFile& saveFile){
	for(int i=0;i<6;i++){
			Weapon[i].read(saveFile.fileStream);
	}
}
void Loadout::cout(){
	for(int i=0;i<6;i++){
		std::cout << "		" << Weapon[i] << endl;
	}
}
void CodexEntry::read(binFile& saveFile){
	pages.read(saveFile);
}
void CodexEntry::cout(){
	pages.cout(false);
}
void CodexPage::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &Page,4);
	saveFile.fileStream.read((char *) &isNew,4);
}
void CodexPage::cout(){
		std::cout <<"		Page: "<< Page << endl;
		std::cout <<"		isNew: "<< isNew << endl;
}

void PlotQuest::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &QuestCounter,4);
	saveFile.fileStream.read((char *) &QuestUpdated,4);
	History.readBasic(saveFile);
}
void PlotQuest::cout(){
	std::cout << "	" << QuestCounter << "," << QuestUpdated << endl;
	History.coutBasic();
}

void Henchman::read(binFile& saveFile){
	Tag.read(saveFile.fileStream);
	powers.read(saveFile);
	saveFile.fileStream.read((char *) &CharacterLevel,4);
	saveFile.fileStream.read((char *) &TalentPoints,4);
	currentLoadout.read(saveFile);
	MappedPower.read(saveFile.fileStream);
}

void Weapon::read(binFile& saveFile){
	name.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &AmmoUsedCount,4);
	saveFile.fileStream.read((char *) &TotalAmmo,4);
	saveFile.fileStream.read((char *) &CurrentWeapon,1);
	std::cout << "Skipping ===>" << saveFile.fileStream.seekg(3,ios_base::cur)<<"<=== on Line: " << __LINE__ << endl;
	saveFile.fileStream.read((char *) &LastWeapon,1);
	std::cout << "Skipping ===>" << saveFile.fileStream.seekg(3,ios_base::cur)<<"<=== on Line: " << __LINE__ << endl;
	ammoName.read(saveFile.fileStream);
}

void Hotkey::read(binFile& saveFile){
	name.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &PowerID,4);
}

void Door::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &id,16);
	saveFile.fileStream.read((char *) &CurrentState,1);
	saveFile.fileStream.read((char *) &OldState,1);
}

void StreamingRecord::read(binFile& saveFile){
	name.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &active,4);
}
void StreamingRecord::cout(){
	std::cout << "	"<< name << ": " << active<< endl;
}

void LevelRecord::read(binFile& saveFile){
	LevelName.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &Unknown1,4);
	saveFile.fileStream.read((char *) &Unknown2,4);
}
void LevelRecord::cout(){
	std::cout << "	"<< LevelName << ": " << Unknown1 << "," << Unknown2<< endl;
}

void ME2Format::read(binFile& saveFile){
	//Read the data from the file
	saveFile.fileStream.seekg(ios_base::beg + 0x00);
	saveFile.fileStream.read((char *) &version,4);
	DebugName.read(saveFile.fileStream);
	saveFile.fileStream.read((char *) &playTime,4);
	Disc.read(saveFile.fileStream);
	BaseLevelName.read(saveFile.fileStream);
	saveFile.fileStream.read(&dificulty,1);
	saveFile.fileStream.read((char *) &EndGameState,4);
	saveFile.fileStream.read((char *) &timestamp.SecondsSinceMidnight,4);
	saveFile.fileStream.read((char *) &timestamp.day,4);
	saveFile.fileStream.read((char *) &timestamp.month,4);
	saveFile.fileStream.read((char *) &timestamp.year,4);
	saveFile.fileStream.read((char *) &playerPosition,16);
	saveFile.fileStream.read((char *) &playerRotation,4);
	std::cout << "Skipping ===>" << saveFile.fileStream.seekg(4,ios_base::cur)<<"<=== on Line: " << __LINE__ << " between playerRotation and CurrentLoadingTip" << endl;
	saveFile.fileStream.read((char *) &CurrentLoadingTip,4);
	levels.read(saveFile);
	streams.read(saveFile);
	saveFile.fileStream.read((char *) &numberofKismets,4);
	assert(0==numberofKismets);
	doors.read(saveFile);
	saveFile.fileStream.read((char *) &numberofPawns,4);
	assert(0==numberofPawns);
	player.read(saveFile);
	henchmen.read(saveFile);
	//Plot.read(saveFile);
	//ME1PlotRecord.read(saveFile);
}

void playerData::cout(){
	std::cout << "Player is female: " << IsFemale << endl;
	std::cout << "Player's class is " << className << endl;
	std::cout << "Player's level is " << (int)level << endl;
	std::cout << "Player's has " << xp << " XP" << endl;
	std::cout << "Player's first name is: " << firstName << endl;
	std::cout << "Player's last name is: " << lastname << " <- this should be 125303" << endl;
	std::cout << "Player's origin is: " << (int)origin << endl;
	std::cout << "Player's Notoriety is: " << (int)Notoriety << endl;
	std::cout << "Player's has " << (int)TalentPoints << " Talent Points" << endl;
	std::cout << "Mapped Power #1: " << mappedPower1 << endl;
	std::cout << "Mapped Power #2: " << mappedPower2 << endl;
	std::cout << "Mapped Power #3: " << mappedPower3 << endl;
	std::cout << "Displaying powers:"<<endl;
	powers.cout(false);
	std::cout << "Displaying Weapons:"<<endl;
	weapons.cout(false);
	std::cout << "Displaying Weapons Loadout:"<<endl;
	currentLoadout.cout();
	std::cout << "Displaying Hotkeys:"<<endl;
	hotkeys.cout(false);
	std::cout << "Player has " << Credits << " Credits" << endl;
	std::cout << "Player has " << Medigel << " Medigel" << endl;
	std::cout << "Player has " << Eezo << " Eezo" << endl;
	std::cout << "Player has " << Iridium << " Iridium" << endl;
	std::cout << "Player has " << Palladium << " Palladium" << endl;
	std::cout << "Player has " << Platinum << " Platinum" << endl;
	std::cout << "Player has " << Probes << " Probes" << endl;
	std::cout << "Player has " << CurrentFuel << " CurrentFuel" << endl;
	std::cout << "Player's FaceCode is: " << FaceCode << endl;
	std::cout << "Player's ClassFriendlyName is:  " << ClassFriendlyName << endl;
}

void ME2Format::cout(){
	std::cout << "File version is " << (int) version << endl;
	std::cout << "Debug name is:  " << DebugName << endl;
	std::cout << "Played for " << playTime << " seconds." << endl;
	std::cout << "Disc is: " << Disc << endl;
	std::cout << "BaseLevelName is:  "<<BaseLevelName<<endl;
	std::cout << "dificulty is:  "<<(int)dificulty<<endl;
	std::cout << "EndGameState is:  "<<(int)EndGameState<<endl;
	std::cout << "Timestamp is:  " << timestamp.SecondsSinceMidnight/3600 << ":" << (timestamp.SecondsSinceMidnight/60)%60 << " "
		 << (int) timestamp.month << "/" << (int) timestamp.day << "/" << timestamp.year << endl;
	std::cout << "Player's Position is:  x:" << playerPosition.x << "  y:" << playerPosition.y << " z:" << playerPosition.z << endl;
	std::cout << "Player's rotation is:  " << playerRotation << endl;
	std::cout << "CurrentLoadingTip is:  " << (int) CurrentLoadingTip << endl;
	std::cout << "There are "<<levels.size()<< " levels"<< endl;
	std::cout << "Displaying Levels:"<<endl;
	levels.cout(false);
	std::cout << "Displaying Streams:"<<endl;
	streams.cout(false);
	std::cout << "Displaying Doors:" << endl;
	doors.cout(false);
	player.cout();
	std::cout << "There are " << henchmen.size() << " Henchmen" <<endl;
	std::cout << "Displaying Henchmen:"<<endl;
	henchmen.cout(false);
	//Plot.cout();
}

//And now the main function
int main(int argc, char *argv[]){
	//Make sure the filename is given
	if(argc != 2){
		cerr << "ERROR:  Command incorrect" << endl;
		cerr << "Usage:" << endl;
		cerr << "	" << argv[0] << " file1" << endl;
		return 1;
	}
	
	binFile file1;
	ME2Format me2file;
	
	file1.open(argv[1]);

	cout << "File size is:  " << file1.size() << " bytes" << endl;
	me2file.read(file1);
	
	file1.fileStream.close();
	me2file.cout();
	
	
	return 0;
}
