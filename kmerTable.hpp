#ifndef KMERTABLE
#define KMERTABLE
#include "globals.h"
#include "kmer.hpp"
#include "csread.hpp"
#include <iostream>
#include <string>
#include <unordered_set>

using std::istream;
using std::ostream;

class KmerTable {
public:
  void insert(CsRead *);
  KmerTable(unsigned int kmer_size);
  ~KmerTable();

private:
  KmerStack *  kmer;
  unsigned long table_size;
  unsigned int kmer_size;
  unsigned int hash(char *);
};

#endif
