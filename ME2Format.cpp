//The save format used by Mass Effect 2
//Copyright Arthur Moore 2012 GPLV3

#include "ME2Format.hpp"

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

void ME1PlotTable::read(binFile& saveFile){
	BoolVariables.read(saveFile.fileStream);
	ints.readBasic(saveFile);
	floats.readBasic(saveFile);
};
void ME1PlotTable::cout(){
	std::cout << "****************Start of ME1 Plot Table****************" << std::endl;
	std::cout << "There are " << (BoolVariables.size()) << " bool values in the ME1 plot table" << endl;
	std::cout << "Displaying bools:"<<endl;
	BoolVariables.cout();
	std::cout << "There are " << ints.size() << " interger values in the ME1 plot table" << endl;
	std::cout << "Displaying ints:"<<endl;
	ints.coutBasic();
	std::cout << "There are " << floats.size() << " floating point values in the ME1 plot table" << endl;
	std::cout << "Displaying floats:"<<endl;
	floats.coutBasic();
	std::cout << "****************End of ME1 Plot Table****************" << std::endl;
}
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
	Plot.read(saveFile);
	ME1PlotRecord.read(saveFile);
	galaxy.read(saveFile);
	dlc.read(saveFile);
	saveFile.fileStream.read((char *) &crc,4);
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
	Plot.cout();
	ME1PlotRecord.cout();
	galaxy.cout();
	std::cout << "This save depends on:" << std::endl;
	dlc.cout(false);
	std::cout << "CRC:  0x" << hex << crc << dec << endl;
}
void xyvector::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &x,4);
	saveFile.fileStream.read((char *) &y,4);
}
void xyvector::cout(){
	std::cout << "		"<<x<<","<<y<<endl;
}
void Planet::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &PlanetID,4);
	saveFile.fileStream.read((char *) &Visited,4);
	Probes.read(saveFile);
}
void Planet::cout(){
	std::cout << "Planet ID: "<<PlanetID<<endl;
	std::cout << "	Visited: "<<Visited<<endl;
	Probes.cout(false);
}
void GalaxyMap::read(binFile& saveFile){
	Planets.read(saveFile);
}
void GalaxyMap::cout(){
	std::cout << "****************Start of Galaxy Map****************" << std::endl;
	std::cout << "There are "<< Planets.size() << " Planets"<<endl;
	std::cout << "Listing Planets"<<endl;
	Planets.cout(false);
	std::cout << "*****************End of Galaxy Map*****************" << std::endl;
}
void DependentDLC::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &ModuleID,4);
	name.read(saveFile.fileStream);
}
void DependentDLC::cout(){
	std::cout << "	" << name << " : " << ModuleID << endl;
}


