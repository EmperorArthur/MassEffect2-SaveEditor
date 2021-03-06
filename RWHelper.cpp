//Helper functions for binary read write of strings and vectors
//Copyright Arthur Moore 2012 GPL V3

#include "RWHelper.hpp"

void StringRead(fstream& saveFile,string& aString){
	int readSize;
	char readChar;
	saveFile.read((char *) &readSize,4);
	aString.clear();
	if(0 == readSize){
		return;
	}
	//This currently assumes that the readSize is correct
	//I could look for the null terminator, but why bother.
	for(int i=0;i< (readSize-1);i++){
		saveFile.read(&readChar,1);
		aString.append(1,readChar);
	}
	//Read and discard the null at the end of the string
	saveFile.read(&readChar,1);
}

void ReadBool(fstream& saveFile,bool& aBool){
	unsigned char rawBool;
	saveFile.read((char *) &rawBool,1);
	aBool = (bool) rawBool;
	saveFile.seekg(3,ios_base::cur);
}
