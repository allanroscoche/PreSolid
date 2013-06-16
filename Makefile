presolid: main.cpp readTable.o csread.o kmer.o kmerTable.o
	g++ -o presolid main.cpp readTable.o csread.o

readTable.o : readTable.cpp readTable.hpp globals.h
	g++ readTable.cpp -c -o readTable.o

csread.o : csread.cpp csread.hpp globals.h
	g++ csread.cpp -c -o csread.o

kmer.o : kmer.cpp kmer.hpp globals.h
	g++ kmer.cpp -c -o kmer.o
kmerTable.o: kmerTable.cpp kmerTable.hpp globals.h
	g++ kmerTable.cpp -c -o kmerTable.o

clean:
	rm *.o