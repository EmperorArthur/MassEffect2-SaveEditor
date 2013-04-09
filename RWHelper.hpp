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
//This is a format where the length of the string is stored as a 4 byte little endian int before the string itself.
void StringRead(fstream& saveFile,string& aString);
//Read a bool from a binary file
//This is for binary files that store bools as a 4 byte little endian value, where 1 is true and 0 is false.
void ReadBool(fstream& saveFile,bool& aBool);

//This allows me to cut down on copy and pasted codes
//Read a string into a vector
void ReadItem(fstream& saveFile,vector<string>& items,int version);
//Read an item into a vector
template <typename T>
void ReadItem(fstream& saveFile,vector<T*>& items,int version){
		T * anItem = new T;
		anItem->read(saveFile,version);
		items.push_back(anItem);
}

template <typename T>
void VectorRead(fstream& saveFile,vector<T>& items,int version){
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
			ReadItem(saveFile,items,version);
		}
	}
}

//This is a copy of VectorRead with the "anItem.read(...)" replaced by reading in 4 bytes, and version removed
template <typename  T>
void VectorRead4(fstream& saveFile,vector<T>& items){
	unsigned int numberofItems = 0;
	saveFile.read((char *) &numberofItems,4);
	items.clear();
	if(numberofItems){
		items.reserve(numberofItems);
		for(unsigned int i=0;i<numberofItems;i++){
			if(!saveFile.good()){
				cerr << "Error in void VectorRead(fstream& saveFile,vector<T> aVector,int version)" << endl; 
				cerr << "FileStream is not good" << endl;
				exit(1);
			}
			T anItem;
			saveFile.read((char *) &anItem,4);
			items.push_back(anItem);
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
