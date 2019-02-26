test: Instance.o Point.o Solver.o
	g++ -W -I../include Instance.o Point.o Solver.o -o test test.cpp

Solver.o: Instance.o Solver.cpp
	g++ -W -c -I../include Solver.cpp

Instance.o: Point.o Instance.cpp
	g++ -W -c -I../include Instance.cpp

Point.o: Point.cpp
		  g++ -W -c -I../include Point.cpp
