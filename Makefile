CC = g++
CFLAGS = -Ofast -Wno-unused-result

default: map.in database.in

map.in: TurnMap/genTurnMap.cpp TurnMap/cube_.h TurnMap/globals_.h
	$(CC) TurnMap/genTurnMap.cpp $(CFLAGS) -o TurnMap/genTurnMap
	TurnMap/genTurnMap

database.in: PatternDB/genPatternDB.cpp
	$(CC) PatternDB/genPatternDB.cpp $(CFLAGS) -o PatternDB/genPatternDB
	PatternDB/genPatternDB

testTurn: cube.h globals.h testTurn.cpp
	$(CC) testTurn.cpp $(CFLAGS) -o testTurn

testCorrectness: cube.h globals.h testCorrectness.cpp
	$(CC) testCorrectness.cpp $(CFLAGS) -o testCorrectness

testSpeed: cube.h globals.h testSpeed.cpp
	$(CC) testSpeed.cpp $(CFLAGS) -o testSpeed

test: map.in database.in testTurn testCorrectness testSpeed
	./testTurn
	./testCorrectness
	./testSpeed

clean all:	
	-rm TurnMap/genTurnmap map.in
	-rm PatternDB/genPatternDB database.in
	-rm testTurn testCorrectness testSpeed
	-rm *~ \#*\#
