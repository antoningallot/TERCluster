test: Instance.o Point.o Solver.o
	g++ -W -I../include Instance.o Point.o Solver.o -o test test.cpp

Solver.o: Instance.o Solver.cpp
	g++ -W -c -I../include Solver.cpp

Instance.o: Point.o Instance.cpp
	g++ -W -c -I../include Instance.cpp

<<<<<<< HEAD
parser.o: parser.cpp
		g++ -W -c -I../include parser.cpp

=======
>>>>>>> 2fdcfde58da9c79c934aa2bb0c8dd488920a6841
Point.o: Point.cpp
		g++ -W -c -I../include Point.cpp
