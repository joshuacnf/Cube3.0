genTurnMap: TurnMap/genTurnMap.cpp TurnMap/cube.h TurnMap/globals.h
	g++ TurnMap/genTurnMap.cpp -Ofast -o TurnMap/genTurnMap
	TurnMap/genTurnMap

testTurn: cube.h globals.h testTurn.cpp
	g++ testTurn.cpp -Ofast -o testTurn

testSpeed: cube.h globals.h testSpeed.cpp
	g++ testSpeed.cpp -Ofast -o testSpeed

testCorrectness: cube.h globals.h testCorrectness.cpp
	g++ testCorrectness.cpp -Ofast -o testCorrectness

test: genTurnMap testTurn testSpeed testCorrectness
	./testTurn 
	./testSpeed
	./testCorrectness

clean:
	rm TurnMap/genTurnMap map.in
	rm testTurn testSpeed testCorrectness
	rm *~ \#*\#
