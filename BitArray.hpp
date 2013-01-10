//Work with bools compacted so each only takes up a single bit
//Copyright Arthur Moore 2012 GPL V3

#ifndef BITARRAY_H
#define BITARRAY_H
#include <fstream>
class BitArray {
	public:
		BitArray();
		BitArray(int newSize);
		~BitArray();
		void setSize(int newSize);			//Warning, this wipes out all old data
		bool readBit(int index);
		void writeBit(int index,bool newValue);
		unsigned char & raw(int byteNumber);
		int getSize();
		int getRawSize();
		void read(std::fstream& saveFile);
		void cout();
	private:
		unsigned char * bytes;
		int size;
		int bitSelect;
};

#endif

