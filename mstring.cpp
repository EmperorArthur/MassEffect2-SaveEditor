//Subclass of string that supports read operation
//Copyright Arthur Moore 2012 GPL V3

#include "mstring.hpp"

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