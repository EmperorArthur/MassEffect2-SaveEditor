//Work with bools compacted so each only takes up a single bit
//Copyright Arthur Moore 2012 GPL V3

#include "BitArray.hpp"
#include <cassert>
#include <iostream>
#include <cstdlib> //for exit

using namespace std;

int BitArray::size(){
	return 8*numberofbytes;
}
bool BitArray::readBit(int index){
	assert(0 <= index && index < (8*numberofbytes));
	int byteSelect = index/8;
	int bitSelect = index%8;
	return (bytes[byteSelect] & (1 << bitSelect));
}
void BitArray::writeBit(int index,bool newValue){
	assert(0 <= index && index < (8*numberofbytes));
	int byteSelect = index/8;
	int bitSelect = index%8;
	if(newValue){
		bytes[byteSelect] |= (1 << bitSelect);
	}else{
		bytes[byteSelect] &= ~(1 << bitSelect);
	}
}
int BitArray::getRawSize(){
	return numberofbytes;
}
BitArray::BitArray(){
	numberofbytes = 0;
}
BitArray::~BitArray(){
	if(0 != numberofbytes){
		delete[] bytes;
	}
}
unsigned char & BitArray::raw(int byteNumber){
	assert(0 <= byteNumber && byteNumber < numberofbytes);
	assert(bytes != NULL);
	return bytes[byteNumber];
}
void BitArray::read(std::fstream& saveFile){
	saveFile.read((char *) &numberofbytes,4);
	numberofbytes *=4;
	try{
		if(0 != numberofbytes){
			bytes = new unsigned char[numberofbytes];
		}
	}
	catch (bad_alloc& ba){
		cerr << "bad_alloc caught: " << ba.what() << endl;
		exit(1);
	}	
	catch (exception& e){
		cerr << "exception caught: " << e.what() << endl;
		exit(1);
	}
	//Read in a for loop
	for(int i=0;i<numberofbytes;i++){
		saveFile.read((char *) &bytes[i],1);
	}
}

void BitArray::cout(){
	std::cout << "There are " << (8*numberofbytes) << " bool values." << std::endl;
	for(int i=0;i<(8*numberofbytes);i++){
		std::cout << "	Bool: " << i << "," << readBit(i) << std::endl;
	}
}
