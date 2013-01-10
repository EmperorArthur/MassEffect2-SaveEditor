//Binary File easy operations
//Copyright Arthur Moore 2012 GPL V3

#include "BinFile.hpp"
#include <iostream> //for cerr
#include <cstdlib> //for exit

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
