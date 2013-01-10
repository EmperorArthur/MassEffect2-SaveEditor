//Subclass of string that supports read operation
//Copyright Arthur Moore 2012 GPL V3

#ifndef MSTRING_H
#define MSTRING_H

#include <string>
#include <fstream>

using namespace std;
class mstring : public string
{
	public:
	void read(fstream& saveFile);
	mstring& operator=(const mstring& instring);
	mstring& operator=(const string& instring);
};

#endif

