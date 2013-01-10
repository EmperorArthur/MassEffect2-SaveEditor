//Binary File easy operations
//Copyright Arthur Moore 2012 GPL V3

#ifndef BINFILE_H
#define BINFILE_H

#include <fstream>
#include <string>

using namespace std;

//This is a quick and dirty easy method of dealing with binary files
class binFile{
	public:
		string fileName;
		fstream fileStream;
		void open();
		void open(string name);
		void open(char * name);
		streampos getSize();
		streampos size();
		~binFile();
		int chompZeros();
		string readString();
	private:
		streampos length;
};
#endif

