/**
 * @file
 * @author Arthur Moore
 * @brief Helper functions for binary read write of strings and vectors
 * @section LICENSE
 * Copyright Arthur Moore 2012 GPLV3
 */

#ifndef RWHELPER_H
#define RWHELPER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>	//for cerr
#include <cstdlib> //for exit
#include <typeinfo> //for typeid

using namespace std;

/**
 * @brief This handles reading a string from a binary file.
 * 
 * Strings are stored in a format where the length of the string is stored as an unsigned int before the string itself.
 * 
 * @param saveFile An fstream handle to the file to read from.
 * @param aString The string that's being read.
 */
void StringRead(fstream& saveFile,string& aString);

/**
 * @brief Read a bool from a binary file.
 * 
 * This is for binary files that store bools as a 4 byte little endian value, where 1 is true and 0 is false.
 * 
 * @param saveFile An fstream handle to the file to read from.
 * @param aBool The bool that's being read.
 */
void ReadBool(fstream& saveFile,bool& aBool);

/**
 * @brief Read an int from a binary file.
 * 
 * This is for binary files that store ints as a 4 byte little endian value.
 * 
 * @param saveFile An fstream handle to the file to read from.
 * @param anInt The interger that's being read.
 */
void ReadInt(fstream& saveFile,int& anInt);

/**
 * Read a float from a binary file.
 * 
 * This is for binary files that store floats as a 4 byte little endian value.
 * 
 * @param saveFile An fstream handle to the file to read from.
 * @param aFloat The float that's being read.
 */
void ReadFloat(fstream& saveFile,float& aFloat);

/**
 * Read an unsigned int from a binary file.
 * 
 * This is for binary files that store unsigned ints as a 4 byte little endian value.
 * 
 * @param saveFile An fstream handle to the file to read from.
 * @param aUInt The unsigned interger that's being read.
 */
void ReadUInt(fstream& saveFile,unsigned int& aUInt);

/**
 * Overloaded function to handle reading in the basic data types
 * 
 * It handles int, float, bool, and unsigned int.
 * It does NOT handle reading in strings.
 * \TODO:  Make this function handle reading strings
 * 
 * 
 * @param saveFile An fstream handle to the file to read from.
 * @param anItem The thing to be read from the file
 */
void ReadBasic(fstream& saveFile,int& anItem);
/**
 * \overload
 */
void ReadBasic(fstream& saveFile,float& anItem);
/**
 * \overload
 */
void ReadBasic(fstream& saveFile,bool& anItem);
/**
 * \overload
 */
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
	unsigned int numberofItems = 0;
	ReadBasic(saveFile,numberofItems);
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
