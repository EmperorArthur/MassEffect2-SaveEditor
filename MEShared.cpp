//The shared objects between Mass Effect 2 and 3
//Copyright Arthur Moore 2012 GPLV3

#include "MEShared.hpp"


Timestamp::Timestamp(){
	SecondsSinceMidnight = 0;
	day = 0;
	month = 0;
	year = 0;
}
void Timestamp::read(fstream& saveFile,int version){
	read(saveFile);
}
void Timestamp::read(fstream& saveFile){
	saveFile.read((char *) &SecondsSinceMidnight,4);
	saveFile.read((char *) &day,4);
	saveFile.read((char *) &month,4);
	saveFile.read((char *) &year,4);
}
void Timestamp::cout(){
	std::cout << "Timestamp is:  " << SecondsSinceMidnight/3600 << ":" << (SecondsSinceMidnight/60)%60 << " " << (int) month << "/" << (int) day <<"/" << year << endl;
}
xyzvector::xyzvector(){
	x = 0;
	y = 0;
	z = 0;
}
void xyzvector::read(fstream& saveFile,int version){
	read(saveFile);
}
void xyzvector::read(fstream& saveFile){
	saveFile.read((char *) &x,4);
	saveFile.read((char *) &y,4);
	saveFile.read((char *) &z,4);
}
void xyzvector::cout(){
	std::cout << "Player's Position is:  x:" << x << "  y:" << y << " z:" << z << endl;
}
void PlayerRotation::read(fstream& saveFile,int version){
	read(saveFile);
}
PlayerRotation::PlayerRotation(){
	Pitch = 0;
	Yaw = 0;
	Roll = 0;
}
void PlayerRotation::read(fstream& saveFile){
	saveFile.read((char *) &Pitch,4);
	saveFile.read((char *) &Yaw,4);
	saveFile.read((char *) &Roll,4);
}
void PlayerRotation::cout(){
	std::cout << "Player's rotation is:  " << Yaw << endl;
}
LevelRecord::LevelRecord(){
	LevelName = "";
	ShouldBeLoaded = 0;
	ShouldBeVisible = 0;
}
void LevelRecord::read(fstream& saveFile,int version){
	read(saveFile);
}
void LevelRecord::read(fstream& saveFile){
	LevelName.read(saveFile);
	saveFile.read((char *) &ShouldBeLoaded,4);
	saveFile.read((char *) &ShouldBeVisible,4);
}
void LevelRecord::cout(){
	std::cout << "	"<< LevelName << ": " << ShouldBeLoaded << "," << ShouldBeVisible<< endl;
}
StreamingRecord::StreamingRecord(){
	name = "";
	active = 0;
}
void StreamingRecord::read(fstream& saveFile,int version){
	read(saveFile);
}
void StreamingRecord::read(fstream& saveFile){
	name.read(saveFile);
	saveFile.read((char *) &active,4);
}
void StreamingRecord::cout(){
	std::cout << "	"<< name << ": " << active<< endl;
}
guid::guid(){
	for(int j=0;j<16;j++){
		id[j] = 0;
	}
}
void guid::read(fstream& saveFile,int version){
	read(saveFile);
}
void guid::read(fstream& saveFile){
	saveFile.read((char *) &id,16);
}
void guid::cout(){
	std::cout << "	id: ";
	for(int j=0;j<16;j++){
		std::cout << hex << (unsigned short)id[j];
	}
	std::cout << dec;
}
Kismet::Kismet(){
	Value = 0;
}
void Kismet::read(fstream& saveFile,int version){
	read(saveFile);
}
void Kismet::read(fstream& saveFile){
	id.read(saveFile);
	saveFile.read((char *) &Value,4);
}
void Kismet::cout(){
	id.cout();
	std::cout << ": " << Value << endl;
}
Door::Door(){
	CurrentState = 0;
	OldState = 0;
}
void Door::read(fstream& saveFile,int version){
	read(saveFile);
}
void Door::read(fstream& saveFile){
	id.read(saveFile);
	saveFile.read((char *) &CurrentState,1);
	saveFile.read((char *) &OldState,1);
}
void Door::cout(){
	id.cout();
	std::cout << ": " << (int) CurrentState << "," << (int) OldState<< endl;
}
void Pawn::read(fstream& saveFile,int version){
	id.read(saveFile);
}
void Pawn::read(fstream& saveFile){
	id.read(saveFile);
}
void Pawn::cout(){
	id.cout();
	std::cout << endl;
}
Loadout::Loadout(){
	for(int i=0;i<6;i++){
			Weapon[i]="";
	}
}
void Loadout::read(fstream& saveFile,int version){
	read(saveFile);
}
void Loadout::read(fstream& saveFile){
	for(int i=0;i<6;i++){
			Weapon[i].read(saveFile);
	}
}
void Loadout::cout(){
	for(int i=0;i<6;i++){
		std::cout << "		" << Weapon[i] << endl;
	}
}
void ME1PlotTable::read(fstream& saveFile,int version){
	read(saveFile);
}
void ME1PlotTable::read(fstream& saveFile){
	BoolVariables.read(saveFile);
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
xyvector::xyvector(){
	x = 0;
	y = 0;
}
void xyvector::read(fstream& saveFile,int version){
	read(saveFile);
}
void xyvector::read(fstream& saveFile){
	saveFile.read((char *) &x,4);
	saveFile.read((char *) &y,4);
}
void xyvector::cout(){
	std::cout << "		"<<x<<","<<y<<endl;
}

