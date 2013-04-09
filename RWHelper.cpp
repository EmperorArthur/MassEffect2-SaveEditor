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

void VectorRead(fstream& saveFile,vector<string>& items,int version){
	int numberofItems = 0;
	saveFile.read((char *) &numberofItems,4);
	items.clear();
	if(numberofItems){
		items.reserve(numberofItems);
		for(int i=0;i<numberofItems;i++){
			if(!saveFile.good()){
				cerr << "Error in void VectorRead(fstream& saveFile,vector<T> aVector,int version)" << endl; 
				cerr << "FileStream is not good" << endl;
				exit(1);
			}
			string aString;
 			StringRead(saveFile,aString);
			items.push_back(aString);
		}
	}
}
