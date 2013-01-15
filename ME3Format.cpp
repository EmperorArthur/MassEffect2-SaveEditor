//The save format used by Mass Effect 3
//Copyright Arthur Moore 2012 GPLV3

#include "ME3Format.hpp"

//These are some macros to help me with my reading depending on version number
#define READ4(variable) saveFile.read((char *) &variable,4);
#define IFELSEREAD4(versionCheck,checkFailedState,variable) if(versionCheck){variable = checkFailedState;}else{READ4(variable);}

void ME3Format::read(fstream& saveFile){
	//Read the data from the file
	saveFile.seekg(ios_base::beg + 0x00);
	saveFile.read((char *) &version,4);
	assert(29 == version||59 == version);	//Make sure we're reading the correct file type
	DebugName.read(saveFile);
	saveFile.read((char *) &playTime,4);
	saveFile.read((char *) &Disc,4);
	BaseLevelName.read(saveFile);
	if(version<36){
		BaseLevelNameDisplayOverrideAsRead = "None";
	}else{
		BaseLevelNameDisplayOverrideAsRead.read(saveFile);
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
	levels.read(saveFile);
	streams.read(saveFile);
	kismets.read(saveFile);
	doors.read(saveFile);
	if (version >= 46){
		placeables.read(saveFile);
	}
	pawns.read(saveFile);
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
	levels.cout();
	std::cout << "Displaying Streams:"<<endl;
	streams.cout();
	std::cout << "Displaying Kismets:"<<endl;
	kismets.cout();
	std::cout << "Displaying Doors:" << endl;
	doors.cout();
	if (version >= 46){
		std::cout << "Displaying Placeables:" << endl;
		placeables.cout();
	}
	std::cout << "Displaying Pawns:" << endl;
	pawns.cout();
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
void Placeable::cout(){
	id.cout();
	std::cout << ": " << IsDestroyed << "," << IsDeactivated << endl;
}
void playerData::read(fstream& saveFile,int version){
	saveFile.read((char *) &IsFemale,4);
	className.read(saveFile);
	//This if statement and the IFELSEREAD4 are the same thing, one just involves less typing
	if(version < 37){
		IsCombatPawn = true;
	}else{
		saveFile.read((char *) &IsCombatPawn,4);
	}
	IFELSEREAD4(version < 48,false,IsInjuredPawn);
	IFELSEREAD4(version < 48,false,UseCasualAppearance);
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
	myAppearance.read(saveFile,version);
	powers.read(saveFile,version);
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
	powers.cout(version);
	
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
	saveFile.read((char *) &HasMorphHead,4);
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
	PowerName.read(saveFile);
	saveFile.read((char *) &CurrentRank,4);
	IFELSEREAD4(version < 30,0,EvolvedChoice[0]);
	IFELSEREAD4(version < 30,0,EvolvedChoice[1]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[2]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[3]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[4]);
	IFELSEREAD4(version < 31,0,EvolvedChoice[5]);
	PowerClassName.read(saveFile);
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