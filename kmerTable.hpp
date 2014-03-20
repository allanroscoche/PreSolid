#ifndef KMERTABLE
#define KMERTABLE
#include "globals.h"
#include "kmer.hpp"
#include "kmerTree.hpp"
#include "csread.hpp"
#include <iostream>
#include <string>

using std::istream;
using std::ostream;

class KmerTable {
public:
  void insert(CsRead *, unsigned int id);
  void insert(CsRead *, unsigned int id, int [], int);
  KmerTable(unsigned int kmer_size);
  ~KmerTable();
  void print();

private:

  kmerTree *  kmers;
  unsigned long num_tables;
  unsigned int kmer_size;
  bool hash(char *, unsigned char *);
  void insertKmer(unsigned char *);
  int min(int [], unsigned int, unsigned int);

};

#endif
