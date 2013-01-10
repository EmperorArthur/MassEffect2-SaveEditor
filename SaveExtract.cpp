//This extracts the information from a savegame
//To Run:
//	SaveExtract filename
//Copyright Arthur Moore 2012 GPLV3

#include <iostream>
#include <fstream>
#include "BinFile.hpp"
#include "ME2Format.hpp"

using namespace std;

int main(int argc, char *argv[]){
	//Make sure the filename is given
	if(argc != 2){
		cerr << "ERROR:  Command incorrect" << endl;
		cerr << "Usage:" << endl;
		cerr << "	" << argv[0] << " file1" << endl;
		return 1;
	}
	
	binFile file1;
	ME2Format me2file;
	
	file1.open(argv[1]);
	cout << "File size is:  " << file1.size() << " bytes" << endl;
	me2file.read(file1.fileStream);
	file1.fileStream.close();	
	me2file.cout();
	
	return 0;
}
