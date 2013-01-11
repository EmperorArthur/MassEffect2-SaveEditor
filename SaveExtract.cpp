//This extracts the information from a savegame
//To Run:
//	SaveExtract filename
//Copyright Arthur Moore 2012 GPLV3

#include <iostream>
#include <fstream>
#include "BinFile.hpp"
#include "ME2Format.hpp"

using namespace std;

void printHelp(char* programName){
	cout << "Usage:" << endl;
	cout << "	" << programName << "[options] filename" << endl;
	cout << endl;
	cout << "Options are:"<<endl;
	cout << "	-p		Display only the ME2 Plot table"<<endl;
}

int main(int argc, char *argv[]){
	bool argumentP = false;
	
	//For each argument
	for(int i = 1;i<(argc-1);i++){
		//If we're passing in an option
		if('-' == argv[i][0]){
			if('p' == argv[i][1]){
				argumentP = true;
			}else{
				cerr << "Unrecognized argument" << endl;
				printHelp(argv[0]);
			}
		}
	}
	
	//Make sure the filename is given
	if(argc < 2){
		cerr << "ERROR:  Command incorrect" << endl;
		cerr << "Usage:" << endl;
		cerr << "	" << argv[0] << "[options] filename" << endl;
		return 1;
	}
	//Note, if a filename is not given, but at least one argument is:
	//	Then the last argument is also treated as the file name in addition to its regular fuctions
	
	binFile file1;
	ME2Format me2file;
	cerr << "Extracting file: " << argv[argc-1] << endl;
	file1.open(argv[argc-1]);
	cout << "File size is:  " << file1.size() << " bytes" << endl;
	me2file.read(file1.fileStream);
	if(argumentP){
		me2file.Plot.cout();
	}else{
		me2file.cout();
	}
	
	return 0;
}
