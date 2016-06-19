CC = g++
CFLAGS = -Ofast -Wno-unused-result

default: map.in database.in IDA
	./IDA

map.in: TurnMap/globals_.h TurnMap/cube_.h TurnMap/genTurnMap.cpp
	$(CC) TurnMap/genTurnMap.cpp $(CFLAGS) -o TurnMap/genTurnMap
	TurnMap/./genTurnMap

database.in: globals.h cube.h PatternDB/genPatDB.cpp
	$(CC) PatternDB/genPatDB.cpp $(CFLAGS) -o PatternDB/genPatDB
	PatternDB/./genPatDB

evalPatDB: map.in database.in globals.h cube.h PatternDB/evalPatDB.cpp
	$(CC) PatternDB/evalPatDB.cpp $(CFLAGS) -o PatternDB/evalPatDB
	PatternDB/./evalPatDB

IDA: globals.h cube.h IDA.cpp
	$(CC) IDA.cpp $(CFLAGS) -o IDA

testTurn: globals.h cube.h testTurn.cpp
	$(CC) testTurn.cpp $(CFLAGS) -o testTurn

testNodeGen: globals.h cube.h testNodeGen.cpp
	$(CC) testNodeGen.cpp $(CFLAGS) -o testNodeGen

testSpeed: globals.h cube.h testSpeed.cpp
	$(CC) testSpeed.cpp $(CFLAGS) -o testSpeed

test: map.in database.in testTurn testNodeGen testSpeed
	./testTurn
	./testNodeGen
	./testSpeed

clean:
	-rm TurnMap/genTurnMap map.in
	-rm PatternDB/evalPatDB PatternDB/genPatDB database.in
	-rm IDA testTurn testNodeGen testSpeed
	-rm *~ \#*\#
