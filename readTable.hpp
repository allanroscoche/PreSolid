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
  void load(CsRead *);
  void loadReads();
  long numberReads();
  long markBadReads(int);
  void writeGoodReads(char *);
  void writeBadReads(char *);
  void convertBases();
  void merge(readTable & );
  void convertPseudoBases();
  KmerTable * generateKmerTable(unsigned int kmer_size);
  CsRead *  getRead(unsigned int read);

private:
  bool paired;
  CsRead * reads_F3;
  CsRead * reads_R3;
  long size;
  fstream arquivo;
  long bad_reads;
  long countFileSize();
};

