CC=g++
INC_PATH=/usr/include/
LIB_PATH=/usr/lib/
CFLAGS=-std=c++0x -c -Wall -I$(INC_PATH)
LDFLAGS=-L$(LIB_PATH)
LIBS=-lvlc
SOURCES=main.cpp platform.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=spkr

all: $(SOURCES) $(EXECUTABLE) interfaces
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

interfaces:
	./configure
