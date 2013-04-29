presolid: main.cpp readTable.o csread.o
	g++ -o presolid main.cpp readTable.o csread.o

readTable.o : readTable.cpp readTable.hpp globals.h
	g++ readTable.cpp -c -o readTable.o

csread.o : csread.cpp csread.hpp globals.h
	g++ csread.cpp -c -o csread.o

clean:
	rm *.o