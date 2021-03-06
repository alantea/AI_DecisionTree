CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp decision_tree.cpp tree.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=decision_tree.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
