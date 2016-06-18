CC = g++
CFLAGS = -Ofast -Wno-unused-result

default: map.in database.in IDA
	./IDA

map.in: TurnMap/globals_.h TurnMap/cube_.h TurnMap/genTurnMap.cpp
	$(CC) TurnMap/genTurnMap.cpp $(CFLAGS) -o TurnMap/genTurnMap
	TurnMap/./genTurnMap

database.in: globals.h cube.h PatternDB/genPatternDB.cpp
	$(CC) PatternDB/genPatternDB.cpp $(CFLAGS) -o PatternDB/genPatternDB
	PatternDB/./genPatternDB

IDA: globals.h cube.h IDA.cpp
	$(CC) IDA.cpp $(CFLAGS) -o IDA

testTurn: globals.h cube.h testTurn.cpp
	$(CC) testTurn.cpp $(CFLAGS) -o testTurn

testCorrectness: globals.h cube.h testCorrectness.cpp
	$(CC) testCorrectness.cpp $(CFLAGS) -o testCorrectness

testSpeed: globals.h cube.h testSpeed.cpp
	$(CC) testSpeed.cpp $(CFLAGS) -o testSpeed

test: map.in database.in testTurn testCorrectness testSpeed
	./testTurn
	./testCorrectness
	./testSpeed

clean all:
	-rm TurnMap/genTurnMap map.in
	-rm PatternDB/genPatternDB database.in
	-rm IDA testTurn testCorrectness testSpeed
	-rm *~ \#*\#
