CL=g++
CC=g++
FLAGS=-Wall -pedantic -Wno-long-long -O3 -ggdb -std=c++11

PROGRAM=PFutil.out
PROGRAMTEST=test.out
PROGRAMSGSEARCH=SG.out

all: ctest cSGsearch cmain

run: 
	./$(PROGRAM)

test:
	./$(PROGRAMTEST)

SG:
	./$(PROGRAMSGSEARCH)

clean: 
	rm -rf ./bin/ $(PROGRAMTEST) $(PROGRAMSGSEARCH)

cmain: bin/fraction.o bin/arithmancy.o bin/dices.o bin/sacredGeometry.o bin/sacredGeometry.o bin/dices.o bin/InvalidNoArgumentsException.o bin/CommandLine.o bin/main.o
	$(CL) $^ -o $(PROGRAM)

ctest: bin/fraction.o bin/arithmancy.o bin/dices.o bin/sacredGeometry.o bin/test.o
	$(CL) $^ -o $(PROGRAMTEST)

cSGsearch: bin/fraction.o bin/sacredGeometry.o bin/SGsearch.o
	$(CL) $^ -o $(PROGRAMSGSEARCH)

count:
	wc -l src/*/*.?pp src/*.?pp

bin/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(FLAGS) -c $< -o $@

#for cpp files in folders
bin/%.o: src/*/%.cpp
	mkdir -p bin
	$(CC) $(FLAGS) -c $< -o $@

bin/InvalidArgumentException.o: src/Exceptions/InvalidArgumentException.cpp src/Exceptions/InvalidArgumentException.hpp src/Exceptions/Exception.hpp

bin/InvalidCommandUseException.o: src/Exceptions/InvalidCommandUseException.cpp src/Exceptions/InvalidCommandUseException.hpp src/Exceptions/Exception.hpp

bin/InvalidNoArgumentsException.o: src/Exceptions/InvalidNoArgumentsException.cpp src/Exceptions/InvalidNoArgumentsException.hpp src/Exceptions/Exception.hpp

bin/InvalidUseException.o: src/Exceptions/InvalidUseException.cpp src/Exceptions/InvalidUseException.hpp src/Exceptions/Exception.hpp

bin/fraction.o: src/Helpers/fraction.cpp src/Helpers/fraction.hpp

bin/arithmancy.o: src/arithmancy.cpp

bin/CommandLine.o: src/CommandLine.cpp src/CommandLine.hpp src/Exceptions/Exception.hpp src/Exceptions/InvalidNoArgumentsException.hpp src/Exceptions/Exception.hpp

bin/dices.o: src/dices.cpp src/dices.hpp

bin/main.o: src/main.cpp src/dices.hpp

bin/sacredGeometry.o: src/sacredGeometry.cpp src/sacredGeometry.hpp src/Helpers/fraction.hpp

bin/SGsearch.o: src/SGsearch.cpp src/sacredGeometry.hpp

bin/test.o: src/test.cpp src/arithmancy.hpp src/sacredGeometry.hpp src/Helpers/fraction.hpp

