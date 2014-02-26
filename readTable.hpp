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
  readTable(char * filename1, char * filename2);
  ~readTable();
  void loadQuals(char * filename, int );
  void loadQuals(char * filename, char * filename2, int);
  void quals();
  CsRead * load(CsRead *);
  void loadReads();
  long numberReads();
  void writeGoodReads(char *);
  void markBadReads(int min);
  void clear();
  void convertBases();
  void merge(readTable & );
  void convertPseudoBases();
  KmerTable * generateKmerTable(unsigned int kmer_size);
  CsRead *  getRead(unsigned int read);

private:
  bool paired;
  CsRead * reads;

  unsigned long size;
  fstream arquivo;
  fstream arquivo_R3;
  char * nome_qual;
  char * nome_qual_R3;
  long bad_reads;
  unsigned long countFileSize();
};

