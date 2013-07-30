#include "csread.hpp"
#include "kmerTable.hpp"
#include "globals.h"
#include <fstream>
#include <iostream>

using namespace std;

class readTable {
  friend ostream &operator<<( ostream &, const readTable &);

public:
  readTable(char * filename);
  ~readTable();
  void loadQuals(char * filename);
  void loadReads();
  long numberReads();
  long markBadReads(int);
  void writeGoodReads(char *);
  void convertPseudoBases();
  void convertBases();
  KmerTable * generateKmerTable(unsigned int kmer_size);
  CsRead *  getRead(unsigned int read);

private:
  CsRead * read;
  long size;
  fstream arquivo;
  long bad_reads;
  long countFileSize();
};

