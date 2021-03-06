//An easy way to work with a collection of objects
//Copyright Arthur Moore 2012 GPL V3

#ifndef COLLECTION_H
#define COLLECTION_H

#include <fstream>
#include <typeinfo>
#include <cassert>
#include <iostream>
#include <cstdlib> //for exit
using namespace std;

template <class T>
struct collection{
	collection();
	~collection();
	int size();
	void readBasic(fstream& saveFile);
	void read(fstream& saveFile);
	void read(fstream& saveFile,int version);
	T & operator[](int index);
	void cout(bool verbose = false);
	void cout(int version);
	void coutBasic(bool verbose = false);
	private:
		T * items;
		int numberofItems;
};
template <class T>
collection<T>::collection(){
	numberofItems = 0;
}
template <class T>
collection<T>::~collection(){
	if(0 !=numberofItems){
		delete[] items;
	}
}
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
void collection<T>::readBasic(fstream& saveFile){
	saveFile.read((char *) &numberofItems,4);
	//Do nothing if we're asked to read something with no values
	if(numberofItems){
		try{
			items = new T[numberofItems];
		}
		catch (bad_alloc& ba){
			cerr << "bad_alloc caught: " << ba.what() << endl;
			exit(1);
		}	
		catch (exception& e){
			cerr << "exception caught: " << e.what() << endl;
			exit(1);
		}
		for(int i=0;i<numberofItems;i++){
			if(!saveFile.good()){
				throw "FileStream is not good";
			}
			try{
				saveFile.read((char *) &items[i],4);
			}
			catch (exception& e){
				cerr << "exception: " << e.what() << endl;
			exit(1);
			}
		}
	}
}
//This reads in multiple items, calling the read function for each individual item
template <class T>
void collection<T>::read(fstream& saveFile){
	saveFile.read((char *) &numberofItems,4);
	//Do nothing if we're asked to read something with no values
	if(numberofItems){
		try{
			items = new T[numberofItems];
		}
		catch (bad_alloc& ba){
			cerr << "bad_alloc caught: " << ba.what() << endl;
			exit(1);
		}
		catch (exception& e){
			cerr << "exception caught: " << e.what() << endl;
			exit(1);
		}
		for(int i=0;i<numberofItems;i++){
			if(!saveFile.good()){
				throw "FileStream is not good";
			}
			try{
				items[i].read(saveFile);
			}
			catch (exception& e){
				cerr << "exception caught: " << e.what() << endl;
			}
		}
	}
}
//This reads in multiple items, calling the read function for each individual item
//(With version specific details
template <class T>
void collection<T>::read(fstream& saveFile,int version){
	saveFile.read((char *) &numberofItems,4);
	//Do nothing if we're asked to read something with no values
	if(numberofItems){
		try{
			items = new T[numberofItems];
		}
		catch (bad_alloc& ba){
			cerr << "bad_alloc caught: " << ba.what() << endl;
			exit(1);
		}
		catch (exception& e){
			cerr << "exception caught: " << e.what() << endl;
			exit(1);
		}
		for(int i=0;i<numberofItems;i++){
			if(!saveFile.good()){
				throw "FileStream is not good";
			}
			try{
				items[i].read(saveFile,version);
			}
			catch (exception& e){
				cerr << "exception caught: " << e.what() << endl;
			}
		}
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
//Output something from all the members (with version specific details)
template <class T>
void collection<T>::cout(int version){
	for(int i=0;i<this->size();i++){
		items[i].cout(version);
	}
}
#endif

