//An easy way to work with a collection of objects
//Copyright Arthur Moore 2012 GPL V3

#ifndef COLLECTION_H
#define COLLECTION_H

#include <cassert>
#include <iostream>
#include <cstdlib> //for exit

template <class T>
struct collection{
	int size();
	void readBasic(binFile& saveFile);
	void read(binFile& saveFile);
	T & operator[](int index);
	void cout(bool verbose = true);
	void coutBasic(bool verbose = false);
	private:
		T * items;
		int numberofItems;
};
template <class T>
int collection<T>::size(){
	return numberofItems;
}
template <class T>
T & collection<T>::operator[](int index){
	assert(0 <= index && index < numberofItems);
	return items[index];
}
//This is like the regular read, but for built in types
template <class T>
void collection<T>::readBasic(binFile& saveFile){
	saveFile.fileStream.read((char *) &numberofItems,4);
	try{
		items = new T[numberofItems];
	}
	catch (bad_alloc& ba){
		cerr << "bad_alloc caught: " << ba.what() << endl;
		exit(1);
	}
	for(int i=0;i<numberofItems;i++){
		assert(saveFile.fileStream.good());
		saveFile.fileStream.read((char *) &items[i],4);
	}
}
//This reads in multiple items, calling the read function for each individual item
template <class T>
void collection<T>::read(binFile& saveFile){
	saveFile.fileStream.read((char *) &numberofItems,4);
	try{
		items = new T[numberofItems];
	}
	catch (bad_alloc& ba){
		cerr << "bad_alloc caught: " << ba.what() << endl;
		exit(1);
	}
	for(int i=0;i<numberofItems;i++){
		assert(saveFile.fileStream.good());
		items[i].read(saveFile);
	}
}
//This is like the regular cout, but for built in types
template <class T>
void collection<T>::coutBasic(bool verbose){
	if(verbose){
		std::cout << "There are " << this->size() << " " << typeid(T).name() << " values." << std::endl;
	}
	for(int i=0;i<(this->size());i++){
		std::cout << "		" << typeid(T).name() << ": " << i << "," << items[i] << std::endl;
	}
}
//Output something from all the member funcitons
template <class T>
void collection<T>::cout(bool verbose){
	if(verbose){
		std::cout << "There are " << this->size() << " " << typeid(T).name() << " values." << std::endl;
	}
	for(int i=0;i<this->size();i++){
		if(verbose){
			std::cout << "	" << typeid(T).name() << " , " << i << ":"<<endl;
		}
		items[i].cout();
	}
}
#endif

