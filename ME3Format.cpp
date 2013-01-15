//The save format used by Mass Effect 3
//Copyright Arthur Moore 2012 GPLV3

#include "ME3Format.hpp"

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
	
}
void ME3Format::cout(){
	std::cout << "File version is " << (int) version << endl;
	std::cout << "Debug name is:  " << DebugName << endl;
	std::cout << "Played for " << playTime << " seconds." << endl;
	std::cout << "Disc is: " << Disc << endl;
	std::cout << "BaseLevelName is:  "<<BaseLevelName<<endl;
	std::cout << "BaseLevelNameDisplayOverrideAsRead is:  "<<BaseLevelNameDisplayOverrideAsRead<<endl;
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
	std::cout << "Displaying Placeables (ME3 only):" << endl;
	placeables.cout();
	std::cout << "Displaying Pawns:" << endl;
	pawns.cout();
	
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