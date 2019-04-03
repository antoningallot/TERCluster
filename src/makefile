test: Solver_kmeans.o Solver.o Instance.o Point.o Solver_parent.o 
	g++ -W -I../include -std=gnu++11 Point.o Instance.o Solver.o Solver_kmeans.o Solver_parent.o -o test test.cpp

Solver_kmeans.o : Solver.o Solver_kmeans.cpp
	g++ -W -c -I../include Solver_kmeans.cpp

Solver.o: Solver_parent.o Solver.cpp
	g++ -W -c -I../include Solver.cpp

Solver_parent.o: Instance.o Solver_parent.cpp
	g++ -W -c -I../include Solver_parent.cpp

Instance.o: Point.o Instance.cpp
	g++ -W -c -I../include Instance.cpp

Point.o: Point.cpp
		g++ -W -c -I../include Point.cpp

