CC = g++
CFLAGS = -std=c++11 -Ofast -Wno-unused-result -mcmodel=medium

default: map.in databaseC.in databaseS.in IDA
	./IDA

map.in: TurnMap/genTurnMap
	TurnMap/./genTurnMap

TurnMap/genTurnMap: TurnMap/globals_.h TurnMap/cube_.h TurnMap/genTurnMap.cpp
	$(CC) TurnMap/genTurnMap.cpp $(CFLAGS) -o TurnMap/genTurnMap

databaseC.in: PatternDB/genPatDB
	PatternDB/genPatDB C

databaseS.in: PatternDB/genPatDB
	PatternDB/genPatDB S

PatternDB/genPatDB: globals.h cube.h PatternDB/genPatDB.cpp
	$(CC) PatternDB/genPatDB.cpp $(CFLAGS) -o PatternDB/genPatDB

evalPatDB: map.in databaseC.in databaseS.in PatternDB/evalPatDB.cpp
	$(CC) PatternDB/evalPatDB.cpp $(CFLAGS) -o PatternDB/evalPatDB
	PatternDB/evalPatDB

IDA: globals.h cube.h IDA.cpp
	$(CC) IDA.cpp $(CFLAGS) -o IDA


testTurn: globals.h cube.h testTurn.cpp
	$(CC) testTurn.cpp $(CFLAGS) -o testTurn

testNodeGen: globals.h cube.h testNodeGen.cpp
	$(CC) testNodeGen.cpp $(CFLAGS) -o testNodeGen

testSpeed: globals.h cube.h testSpeed.cpp
	$(CC) testSpeed.cpp $(CFLAGS) -o testSpeed

testDiskQueue: globals.h testDiskQueue.cpp
	$(CC) testDiskQueue.cpp $(CFLAGS) -o testDiskQueue

test: map.in database.in testTurn testNodeGen testSpeed
	./testTurn
	./testNodeGen
	./testSpeed

clean:
	-rm TurnMap/genTurnMap
	-rm PatternDB/evalPatDB PatternDB/genPatDB
	-rm queue0 queue1 queue2
	-rm IDA testTurn testNodeGen testSpeed testDiskQueue
	-rm *~ \#*\#
