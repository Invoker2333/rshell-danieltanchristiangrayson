$(shell mkdir -p bin)
CC = g++
CC_FLAGS = -Wall -Werror --ansi -pedantic -std=c++11

EXEC = bin/rshell
SOURCEDIR = src/
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


all: $(EXEC)


$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
