CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=SaveExtract.cpp BinFile.cpp BitArray.cpp mstring.cpp ME2Format.cpp
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