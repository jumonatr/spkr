CC=g++
INC_PATH=/usr/include
CFLAGS=-std=c++0x -c -Wall -I$(INC_PATH)
LDFLAGS=
LIBS=-llibvlc -llibvlccore
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=spkr

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
