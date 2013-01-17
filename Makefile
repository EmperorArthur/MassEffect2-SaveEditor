CC=g++
#-std=gnu++0x should be changed to -std=c++11, but I'm using an older compiler
CFLAGS=-c -g -Wall -std=gnu++0x
LDFLAGS=
SOURCES=SaveExtract.cpp BinFile.cpp BitArray.cpp MEShared.cpp ME3Format.cpp RWHelper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=SaveExtract

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)
