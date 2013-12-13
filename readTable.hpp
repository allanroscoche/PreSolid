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
  void loadQuals(char * filename);
  void loadQuals(char * filename, char * filename2);
  void quals(bool);
  CsRead * load(CsRead *);
  void loadReads();
  long numberReads();
  long markBadReads(int);
  void writeGoodReads(char *);
  void writeGoodReads2(char *);
  void writeBadReads(char *);
  int maxQual();
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
  fstream arquivo_R3;
  char * nome_qual;
  char * nome_qual_R3;
  long bad_reads;
  long countFileSize();
};

