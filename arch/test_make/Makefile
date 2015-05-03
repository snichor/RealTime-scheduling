CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=core.cpp frame.cpp user.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=relay

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -rf *o coremodule
