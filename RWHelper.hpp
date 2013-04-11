//Helper functions for binary read write of strings and vectors
//Copyright Arthur Moore 2012 GPL V3

#ifndef RWHELPER_H
#define RWHELPER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>	//for cerr
#include <cstdlib> //for exit
#include <typeinfo> //for typeid

using namespace std;

//This handles reading a string from a binary file
//This is a format where the length of the string is stored as an int before the string itself.
void StringRead(fstream& saveFile,string& aString);
//Read a bool from a binary file
//This is for binary files that store bools as a 4 byte little endian value, where 1 is true and 0 is false.
void ReadBool(fstream& saveFile,bool& aBool);
//Read an int from a binary file
//This is for binary files that store ints as a 4 byte little endian value
void ReadInt(fstream& saveFile,int& anInt);
//Read a float from a binary file
//This is for binary files that store floats as a 4 byte little endian value
void ReadFloat(fstream& saveFile,float& aFloat);
//Read an unsigned int from a binary file
//This is for binary files that store unsigned ints as a 4 byte little endian value
void ReadUInt(fstream& saveFile,unsigned int& anInt);

//I'm lazy, so these will let me read anything with one function
void ReadBasic(fstream& saveFile,int& anItem);
void ReadBasic(fstream& saveFile,float& anItem);
void ReadBasic(fstream& saveFile,bool& anItem);
void ReadBasic(fstream& saveFile,unsigned int& anItem);

//This allows me to cut down on copy and pasted codes
//Read a string into a vector
void ReadItem(fstream& saveFile,vector<string>& items,int version);
//Read an int into a vector
void ReadItem(fstream& saveFile,vector<int>& items,int version);
//Read a float into a vector
void ReadItem(fstream& saveFile,vector<float>& items,int version);
//Read an item into a vector
template <typename T>
void ReadItem(fstream& saveFile,vector<T*>& items,int version){
		T * anItem = new T;
		anItem->read(saveFile,version);
		items.push_back(anItem);
}

//Read a saved vector from the file
template <typename T>
void VectorRead(fstream& saveFile,vector<T>& items,int version){
	int numberofItems = 0;
	ReadInt(saveFile,numberofItems);
	items.clear();
	if(numberofItems){
		items.reserve(numberofItems);
		for(int i=0;i<numberofItems;i++){
			if(!saveFile.good()){
				cerr << "Error in void VectorRead(fstream& saveFile,vector<T> aVector,int version)" << endl; 
				cerr << "FileStream is not good" << endl;
				exit(1);
			}
			ReadItem(saveFile,items,version);
		}
	}
}

template <typename  T>
void VectorCout(vector<T>& items,int version){
	for(size_t i=0;i<items.size();i++){
		items[i]->cout(version);
	}
}
//This is the same as above, but without the version information
template <typename  T>
void VectorCout(vector<T>& items){
	for(size_t i=0;i<items.size();i++){
		items[i]->cout();
	}
}

template <typename  T>
void VectorCoutBasic(const vector<T>& items){
	for(size_t i=0;i<items.size();i++){
		std::cout << "		" << typeid(T).name() << ": " << i << "," << items[i] << std::endl;
	}
}

//Delete all the objects in a vector of pointers
template <typename  T>
void VectorDelete(vector<T*>& items){
	T * temp;
	while(0!=items.size()){
		temp = items.back();
		items.pop_back();
		delete temp;
	}
}

#endif
