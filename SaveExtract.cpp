//This extracts the information from a savegame
//To Run:
//	SaveExtract filename
//Copyright Arthur Moore 2012 GPLV3

//Fun header files
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //for exit
#include <cassert>
#include <typeinfo>
#include <vector>

//Can't forget this
using namespace std;

//This is a quick and dirty easy method of dealing with binary files
class binFile{
	public:
		string fileName;
		fstream fileStream;
		void open();
		void open(string name);
		void open(char * name);
		streampos getSize();
		streampos size();
		~binFile();
		int chompZeros();
		string readString();
	private:
		streampos length;
};
binFile::~binFile(){
	fileStream.close();
}
void binFile::open(){
	//Open the file (if it doesn't exist, complain and exit
	fileStream.open(fileName.c_str(),ios::in|ios::out|ios::binary);
	if(!fileStream.is_open()){
		cerr << "ERROR:  Unable to open file  \"" << fileName << "\"" << endl;
		exit(1);  //When we fail, we fail hard
	}
	getSize();
}
void binFile::open(string name){
	fileName = name;
	open();
}
void binFile::open(char * name){
	fileName = name;
	open();
}
streampos binFile::getSize(){
	streampos originalPointerPosition = 0;
	originalPointerPosition = fileStream.tellg();
	fileStream.seekg(0,ios::end);
	length = fileStream.tellg();
	fileStream.seekg(originalPointerPosition);
	return length;
}
streampos binFile::size(){
	return length;
}

//Read untill a non-zero is encountered, then go back one
//Returns number of zeros removed
int binFile::chompZeros(){
	char testChar;
	int zerosRemoved = 0;
	fileStream.read(&testChar,1);
	while(0 == testChar){
		zerosRemoved++;
		fileStream.read(&testChar,1);
	}
	fileStream.unget();
	return zerosRemoved;
}
//Read a null terminated string
string binFile::readString(){
	string aString = "";
	char aChar;
	fileStream.read(&aChar,1);
	while(0 != aChar){
		aString += aChar;
		fileStream.read(&aChar,1);
	}
	return aString;
}

//NOTE:  Most of the unsigned chars can become ints with proper offsets
//NOTE:  all ints, floats, and bools have a 4 byte size


class BitArray {
	public:
		BitArray();
		BitArray(int newSize);
		~BitArray();
		void setSize(int newSize);			//Warning, this wipes out all old data
		bool readBit(int index);
		void writeBit(int index,bool newValue);
		unsigned char & raw(int byteNumber);
		int getSize();
		int getRawSize();
		void read(binFile& saveFile);
		void cout();
	private:
		unsigned char * bytes;
		int size;
		int bitSelect;
};
BitArray::BitArray(){
	setSize(1);
}
BitArray::BitArray(int newSize){
	setSize(newSize);
}
void BitArray::setSize(int newSize){
	assert(newSize > 0);
	if(bytes != NULL){
		delete[] bytes;
	}
	size = newSize * 4;
	bytes = new unsigned char[size];
}
int BitArray::getSize(){
	return 8*size;
}
bool BitArray::readBit(int index){
	assert(0 <= index && index < (8*size));
	int byteSelect = index/8;
	int bitSelect = index%8;
	return (bytes[byteSelect] & (1 << bitSelect));
}
void BitArray::writeBit(int index,bool newValue){
	assert(0 <= index && index < (8*size));
	int byteSelect = index/8;
	int bitSelect = index%8;
	if(newValue){
		bytes[byteSelect] |= (1 << bitSelect);
	}else{
		bytes[byteSelect] &= ~(1 << bitSelect);
	}
}
int BitArray::getRawSize(){
	return size;
}
BitArray::~BitArray(){
	if(bytes != NULL){
		delete[] bytes;
	}
}
unsigned char & BitArray::raw(int byteNumber){
	assert(0 <= byteNumber && byteNumber < size);
	assert(bytes != NULL);
	return bytes[byteNumber];
}
void BitArray::read(binFile& saveFile){
	int newSize;
	saveFile.fileStream.read((char *) &newSize,4);
	setSize(newSize);
	//Read in a for loop
	for(int i=0;i<size;i++){
		saveFile.fileStream.read((char *) &bytes[i],1);
	}
}

void BitArray::cout(){
	std::cout << "There are " << (8*size) << " bool values." << std::endl;
	for(int i=0;i<(8*size);i++){
		std::cout << "	Bool: " << i << "," << readBit(i) << std::endl;
	}
}
	

template <class T>
struct collection{
	int size();
	void readBasic(binFile& saveFile);
	void read(binFile& saveFile);
	T & operator[](int index);
	void cout(bool verbose = true);
	void coutBasic(bool verbose = false);
	private:
	T * items;
	int numberofItems;
};
template <class T>
int collection<T>::size(){
	return numberofItems;
}
template <class T>
T & collection<T>::operator[](int index){
	assert(0 <= index && index < numberofItems);
	return items[index];
}
//This is like the regular read, but for built in types
template <class T>
void collection<T>::readBasic(binFile& saveFile){
	saveFile.fileStream.read((char *) &numberofItems,4);
	cerr << "Reading  " << numberofItems << " of type: " << typeid(T).name() << std::endl;
	items = new T[numberofItems];
	for(int i=0;i<numberofItems;i++){
		saveFile.fileStream.read((char *) &items[i],4);
	}
}
//This reads in multiple items, calling the read function for each individual item
template <class T>
void collection<T>::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &numberofItems,4);
	items = new T[numberofItems];
	for(int i=0;i<numberofItems;i++){
		items[i].read(saveFile);
	}
}
//This is like the regular cout, but for built in types
template <class T>
void collection<T>::coutBasic(bool verbose){
	if(verbose){
		std::cout << "There are " << this->size() << " " << typeid(T).name() << " values." << std::endl;
	}
	for(int i=0;i<(this->size());i++){
		std::cout << "		" << typeid(T).name() << ": " << i << "," << items[i] << std::endl;
	}
}
//Output something from all the member funcitons
template <class T>
void collection<T>::cout(bool verbose){
	if(verbose){
		std::cout << "There are " << this->size() << " " << typeid(T).name() << " values." << std::endl;
	}
	for(int i=0;i<this->size();i++){
		if(verbose){
			std::cout << "	" << typeid(T).name() << " , " << i << ":"<<endl;
		}
		items[i].cout();
	}
}

class mstring : public string
{
	public:
	void read(fstream& saveFile);
	mstring& operator=(const mstring& instring);
	mstring& operator=(const string& instring);
};
mstring& mstring::operator=(const mstring& instring){
	assign(instring);
	return *this;
}
mstring& mstring::operator=(const string& instring){
	assign(instring);
	return *this;
}
void mstring::read(fstream& saveFile){
	int readSize;
	char readChar;
	saveFile.read((char *) &readSize,4);
	clear();
	if(0 == readSize){
		return;
	}
	//This currently assumes that the readSize is correct
	//I could look for the null terminator, but why bother.
	for(int i=0;i< (readSize-1);i++){
		saveFile.read(&readChar,1);
		append(1,readChar);
	}
	//Read and discard the null at the end of the string
	saveFile.read(&readChar,1);
}

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
struct ME1PlotTable{
	BitArray BoolVariables;
	collection<int> ints;
	collection<float> floats;
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
	collection<Door> doors;
	//Gibbed's code talks about pawn records, but I don't see anything
	playerData player;
	collection<Henchman> henchmen;
	ME2PlotTable Plot;
	ME1PlotTable ME1PlotRecord;
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
	cerr << "Reading ME2PlotTable: Bools" << endl;
	BoolVariables.read(saveFile);
	cerr << "Reading ME2PlotTable: ints" << endl;
	ints.readBasic(saveFile);
	cerr << "Reading ME2PlotTable: floats" << endl;
	floats.readBasic(saveFile);
	cerr << "Reading ME2PlotTable: QuestProgressCounter" << endl;
	saveFile.fileStream.read((char *) &QuestProgressCounter,4);
	cerr << "Reading ME2PlotTable: QuestProgress" << endl;
	QuestProgress.read(saveFile);
	cerr << "Reading ME2PlotTable: QuestIDs" << endl;
	QuestIDs.readBasic(saveFile);
	cerr << "Reading ME2PlotTable: CodexEntries" << endl;
	CodexEntries.read(saveFile);
	cerr << "Reading ME2PlotTable: CodexIDs" << endl;
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
	// BoolVariables.read(saveFile);
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
	std::cout << "Skipping ===>" << saveFile.fileStream.seekg(4,ios_base::cur)<<"<=== on Line: " << __LINE__ << " KismetRecords" << endl;
	doors.read(saveFile);
	std::cout << "Skipping ===>" << saveFile.fileStream.seekg(4,ios_base::cur)<<"<=== on Line: " << __LINE__ << " PawnRecords" << endl;
	player.read(saveFile);
	henchmen.read(saveFile);
	cerr << "Reading plot" << endl;
	Plot.read(saveFile);
	//ME1PlotRecord.read(saveFile);
	cerr << "Done Reading ME2Format"<<endl;
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
	Plot.cout();
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
	cerr << "All data has now been read" << endl;
	
	file1.fileStream.close();
	me2file.cout();
	
	
	return 0;
}
