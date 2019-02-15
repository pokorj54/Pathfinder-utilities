CL=g++
CC=g++
FLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11

PROGRAMTEST=test.out
PROGRAMSGSEARCH=SG.out

all: ctest cSGsearch

test:
	./$(PROGRAMTEST)

SG:
	./$(PROGRAMSGSEARCH)

clean: 
	rm -rf ./bin/ $(PROGRAMTEST) $(PROGRAMSGSEARCH)

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

bin/fraction.o: src/Helpers/fraction.cpp src/Helpers/fraction.hpp

bin/arithmancy.o: src/arithmancy.cpp

bin/dices.o: src/dices.cpp src/dices.hpp

bin/sacredGeometry.o: src/sacredGeometry.cpp src/sacredGeometry.hpp src/Helpers/fraction.hpp

bin/SGsearch.o: src/SGsearch.cpp src/sacredGeometry.hpp

bin/test.o: src/test.cpp src/arithmancy.hpp src/sacredGeometry.hpp src/Helpers/fraction.hpp