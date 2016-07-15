CC = g++
CFLAGS = -std=c++11 -Ofast -Wno-unused-result -mcmodel=medium

default: IDA
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

PatternDB/evalPatDB: PatternDB/evalPatDB.cpp
	$(CC) PatternDB/evalPatDB.cpp $(CFLAGS) -o PatternDB/evalPatDB
	PatternDB/evalPatDB

IDA: globals.h cube.h IDA.cpp
	$(CC) IDA.cpp $(CFLAGS) -o IDA


Test/testTurn: globals.h cube.h Test/testTurn.cpp
	cd Test; $(CC) testTurn.cpp $(CFLAGS) -o testTurn;

Test/testNodeGen: globals.h cube.h Test/testNodeGen.cpp
	cd Test; $(CC) testNodeGen.cpp $(CFLAGS) -o testNodeGen;

Test/testSpeed: globals.h cube.h Test/testSpeed.cpp
	cd Test; $(CC) testSpeed.cpp $(CFLAGS) -o testSpeed;

Test/testDiskQueue: globals.h Test/testDiskQueue.cpp
	cd Test; $(CC) testDiskQueue.cpp $(CFLAGS) -o testDiskQueue;

Test/testDBSpeed: globals.h cube.h Test/testDBSpeed.cpp
	cd Test; $(CC) testDBSpeed.cpp $(CFLAGS) -o testDBSpeed;

test: Test/testTurn Test/testNodeGen Test/testSpeed
	Test/testTurn
	Test/testNodeGen
	Test/testSpeed

clean:
	-rm TurnMap/genTurnMap
	-rm PatternDB/evalPatDB PatternDB/genPatDB
	-rm queue0 queue1 queue2
	-rm IDA Test/testTurn Test/testNodeGen Test/testSpeed
	-rm Test/testDBSpeed Test/testDiskQueue	
	-rm *~ \#*\#
