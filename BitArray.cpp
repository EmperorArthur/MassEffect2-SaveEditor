//Work with bools compacted so each only takes up a single bit
//Copyright Arthur Moore 2012 GPL V3

#include "BitArray.hpp"
#include <cassert>
#include <iostream>

using namespace std;
BitArray::BitArray(){
	setSize(1);
}
BitArray::BitArray(int newSize){
	setSize(newSize);
}
void BitArray::setSize(int newSize){
	assert(newSize > 0);
	if(bytes != NULL){
		delete[] bytes;
	}
	size = newSize * 4;
	bytes = new unsigned char[size];
}
int BitArray::getSize(){
	return 8*size;
}
bool BitArray::readBit(int index){
	assert(0 <= index && index < (8*size));
	int byteSelect = index/8;
	int bitSelect = index%8;
	return (bytes[byteSelect] & (1 << bitSelect));
}
void BitArray::writeBit(int index,bool newValue){
	assert(0 <= index && index < (8*size));
	int byteSelect = index/8;
	int bitSelect = index%8;
	if(newValue){
		bytes[byteSelect] |= (1 << bitSelect);
	}else{
		bytes[byteSelect] &= ~(1 << bitSelect);
	}
}
int BitArray::getRawSize(){
	return size;
}
BitArray::~BitArray(){
	if(bytes != NULL){
		delete[] bytes;
	}
}
unsigned char & BitArray::raw(int byteNumber){
	assert(0 <= byteNumber && byteNumber < size);
	assert(bytes != NULL);
	return bytes[byteNumber];
}
void BitArray::read(std::fstream& saveFile){
	int newSize;
	saveFile.read((char *) &newSize,4);
	setSize(newSize);
	//Read in a for loop
	for(int i=0;i<size;i++){
		saveFile.read((char *) &bytes[i],1);
	}
}

void BitArray::cout(){
	std::cout << "There are " << (8*size) << " bool values." << std::endl;
	for(int i=0;i<(8*size);i++){
		std::cout << "	Bool: " << i << "," << readBit(i) << std::endl;
	}
}
