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
  KmerTable(unsigned int kmer_size);
  ~KmerTable();
  void print();

private:

  kmerTree *  kmers;
  unsigned long num_tables;
  unsigned int kmer_size;
  bool hash(char *, unsigned char *);
  void insertKmer(unsigned char *);

};

#endif
