#ifndef KMERTABLE
#define KMERTABLE
#include "globals.h"
#include "kmer.hpp"
#include "csread.hpp"
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using std::istream;
using std::ostream;
using std::unordered_map;
using std::stack;

class KmerTable {
public:
  void insert(CsRead *, unsigned int id);
  KmerTable(unsigned int kmer_size);
  ~KmerTable();
  void print();

private:
  unordered_map<unsigned int, stack<Kmer> > kmers;
  unsigned long table_size;
  unsigned int kmer_size;
  unsigned int hash(char *);
};

#endif
