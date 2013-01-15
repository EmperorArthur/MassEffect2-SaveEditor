//The save format used by Mass Effect 2
//Copyright Arthur Moore 2012 GPLV3

#include "ME2Format.hpp"

void playerData::read(fstream& saveFile){
	saveFile.read((char *) &IsFemale,4);
	className.read(saveFile);
	saveFile.read((char *) &level,4);
	saveFile.read((char *) &xp,4);
	firstName.read(saveFile);
	saveFile.read((char *) &lastname,4);
	saveFile.read((char *) &origin,1);
	saveFile.read((char *) &Notoriety,1);
	saveFile.read((char *) &TalentPoints,4);
	mappedPower1.read(saveFile);
	mappedPower2.read(saveFile);
	mappedPower3.read(saveFile);
	myAppearance.read(saveFile);
	powers.read(saveFile);
	weapons.read(saveFile);
	currentLoadout.read(saveFile);
	hotkeys.read(saveFile);
	saveFile.read((char *) &Credits,4);
	saveFile.read((char *) &Medigel,4);
	saveFile.read((char *) &Eezo,4);
	saveFile.read((char *) &Iridium,4);
	saveFile.read((char *) &Palladium,4);
	saveFile.read((char *) &Platinum,4);
	saveFile.read((char *) &Probes,4);
	saveFile.read((char *) &CurrentFuel,4);
	FaceCode.read(saveFile);
	saveFile.read((char *) &ClassFriendlyName,4);
}

void ME2PlotTable::read(fstream& saveFile){
	BoolVariables.read(saveFile);
	ints.readBasic(saveFile);
	floats.readBasic(saveFile);
	saveFile.read((char *) &QuestProgressCounter,4);
	QuestProgress.read(saveFile);
	QuestIDs.readBasic(saveFile);
	CodexEntries.read(saveFile);
	CodexIDs.readBasic(saveFile);
}
void Appearance::read(fstream& saveFile){
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
	saveFile.read((char *) &HasMorphHead,4);
	assert(!HasMorphHead);
}
void Appearance::cout(){
	bool ThisFunctionNeedsToBeWritten = true;
	assert(!ThisFunctionNeedsToBeWritten);
}

void ME2PlotTable::cout(){
	std::cout << "There are " << (BoolVariables.size()) << " bool values in the ME2 plot table" << endl;
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
	QuestProgress.cout();
	std::cout << "There are " << QuestIDs.size() << " quest IDs in the ME2 plot table" << endl;
	std::cout << "Displaying quest IDs:"<<endl;
	QuestIDs.coutBasic();
	std::cout << "There are " << CodexEntries.size() << " Codex Entries in the ME2 plot table" << endl;
	std::cout << "Displaying Codex Entries:"<<endl;
	CodexEntries.cout(true);
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
void Henchman::cout(){
	std::cout << "	" << Tag << ":" << endl;
	std::cout << "	Displaying powers:"<<endl;
	powers.cout();
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
void Power::read(fstream& saveFile){

	PowerName.read(saveFile);
	saveFile.read((char *) &CurrentRank,4);

	PowerClassName.read(saveFile);
	saveFile.read((char *) &WheelDisplayIndex,4);
}
void CodexEntry::read(fstream& saveFile){
	pages.read(saveFile);
}
void CodexEntry::cout(){
	pages.cout();
}
void CodexPage::read(fstream& saveFile){
	saveFile.read((char *) &Page,4);
	saveFile.read((char *) &isNew,4);
}
void CodexPage::cout(){
		std::cout <<"		Page: "<< Page << endl;
		std::cout <<"		isNew: "<< isNew << endl;
}

void PlotQuest::read(fstream& saveFile){
	saveFile.read((char *) &QuestCounter,4);
	saveFile.read((char *) &QuestUpdated,4);
	History.readBasic(saveFile);
}
void PlotQuest::cout(){
	std::cout << "	" << QuestCounter << "," << QuestUpdated << endl;
	History.coutBasic();
}

void Henchman::read(fstream& saveFile){
	Tag.read(saveFile);
	powers.read(saveFile);
	saveFile.read((char *) &CharacterLevel,4);
	saveFile.read((char *) &TalentPoints,4);
	currentLoadout.read(saveFile);
	MappedPower.read(saveFile);
}

void Weapon::read(fstream& saveFile){
	name.read(saveFile);
	saveFile.read((char *) &AmmoUsedCount,4);
	saveFile.read((char *) &TotalAmmo,4);
	saveFile.read((char *) &CurrentWeapon,1);
	std::cout << "Skipping ===>" << saveFile.seekg(3,ios_base::cur)<<"<=== on Line: " << __LINE__ << endl;
	saveFile.read((char *) &LastWeapon,1);
	std::cout << "Skipping ===>" << saveFile.seekg(3,ios_base::cur)<<"<=== on Line: " << __LINE__ << endl;
	ammoName.read(saveFile);
}

void Hotkey::read(fstream& saveFile){
	name.read(saveFile);
	saveFile.read((char *) &PowerID,4);
}

void ME2Format::read(fstream& saveFile){
	//Read the data from the file
	saveFile.seekg(ios_base::beg + 0x00);
	saveFile.read((char *) &version,4);
	assert(29 == version);	//Make sure we're reading the correct file type
	DebugName.read(saveFile);
	saveFile.read((char *) &playTime,4);
	saveFile.read((char *) &Disc,4);
	BaseLevelName.read(saveFile);
	saveFile.read(&dificulty,1);
	saveFile.read((char *) &EndGameState,4);
	SaveDateTime.read(saveFile);
	playerPosition.read(saveFile);
	myRotation.read(saveFile);
	saveFile.read((char *) &CurrentLoadingTip,4);
	levels.read(saveFile);
	streams.read(saveFile);
	kismets.read(saveFile);
	doors.read(saveFile);
	pawns.read(saveFile);
	player.read(saveFile);
	henchmen.read(saveFile);
	Plot.read(saveFile);
	ME1PlotRecord.read(saveFile);
	galaxy.read(saveFile);
	dlc.read(saveFile);
	saveFile.read((char *) &crc,4);
	//Make sure we're at eof (another read will fail the stream, se we could check that way)
	streampos currentLocation = saveFile.tellg();
	saveFile.seekg(0,ios::end);
	assert(saveFile.tellg() == currentLocation);
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
	powers.cout();
	std::cout << "Displaying Weapons:"<<endl;
	weapons.cout();
	std::cout << "Displaying Weapons Loadout:"<<endl;
	currentLoadout.cout();
	std::cout << "Displaying Hotkeys:"<<endl;
	hotkeys.cout();
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
	SaveDateTime.cout();
	playerPosition.cout();
	myRotation.cout();
	std::cout << "CurrentLoadingTip is:  " << (int) CurrentLoadingTip << endl;
	std::cout << "There are "<<levels.size()<< " levels"<< endl;
	std::cout << "Displaying Levels:"<<endl;
	levels.cout();
	std::cout << "Displaying Streams:"<<endl;
	streams.cout();
	std::cout << "Displaying Kismets:"<<endl;
	kismets.cout();
	std::cout << "Displaying Doors:" << endl;
	doors.cout();
	std::cout << "Displaying Pawns:" << endl;
	pawns.cout();
	player.cout();
	std::cout << "There are " << henchmen.size() << " Henchmen" <<endl;
	std::cout << "Displaying Henchmen:"<<endl;
	henchmen.cout();
	Plot.cout();
	ME1PlotRecord.cout();
	galaxy.cout();
	std::cout << "This save depends on:" << std::endl;
	dlc.cout();
	std::cout << "CRC:  0x" << hex << crc << dec << endl;
}

void Planet::read(fstream& saveFile){
	saveFile.read((char *) &PlanetID,4);
	saveFile.read((char *) &Visited,4);
	Probes.read(saveFile);
}
void Planet::cout(){
	std::cout << "Planet ID: "<<PlanetID<<endl;
	std::cout << "	Visited: "<<Visited<<endl;
	Probes.cout();
}
void GalaxyMap::read(fstream& saveFile){
	Planets.read(saveFile);
}
void GalaxyMap::cout(){
	std::cout << "****************Start of Galaxy Map****************" << std::endl;
	std::cout << "There are "<< Planets.size() << " Planets"<<endl;
	std::cout << "Listing Planets"<<endl;
	Planets.cout();
	std::cout << "*****************End of Galaxy Map*****************" << std::endl;
}
void DependentDLC::read(fstream& saveFile){
	saveFile.read((char *) &ModuleID,4);
	name.read(saveFile);
}
void DependentDLC::cout(){
	std::cout << "	" << name << " : " << ModuleID << endl;
}


