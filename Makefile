genTurnMap: TurnMap/genTurnMap.cpp TurnMap/cube.h TurnMap/globals.h
	g++ TurnMap/genTurnMap.cpp -Ofast -o TurnMap/genTurnMap
	TurnMap/genTurnMap

testTurn: cube.h globals.h testTurn.cpp
	g++ testTurn.cpp -Ofast -o testTurn

testSpeed: cube.h globals.h testSpeed.cpp
	g++ testSpeed.cpp -Ofast -o testSpeed

run: genTurnMap testTurn testSpeed
	./testTurn 
	./testSpeed

clean:
	rm testTurn testSpeed
	rm *~ \#*\#
