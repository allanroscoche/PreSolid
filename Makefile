presolid: main.cpp readTable.o csread.o kmer.o kmerTable.o kmerTree.o
	g++ -std=c++0x -o presolid main.cpp readTable.o csread.o kmer.o kmerTable.o kmerTree.o

readTable.o : readTable.cpp readTable.hpp globals.h
	g++ -std=c++0x readTable.cpp -c -o readTable.o

csread.o : csread.cpp csread.hpp globals.h
	g++ csread.cpp -c -o csread.o

kmer.o : kmer.cpp kmer.hpp globals.h
	g++ kmer.cpp -c -o kmer.o

kmerTable.o: kmerTable.cpp kmerTable.hpp globals.h
	g++ kmerTable.cpp -c -std=c++0x -o kmerTable.o

kmerTree.o: kmerTree.cpp kmerTree.hpp globals.h
	g++ kmerTree.cpp -c -std=c++0x -o kmerTree.o

clean:
	rm *.o
