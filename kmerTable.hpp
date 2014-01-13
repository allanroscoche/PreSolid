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
  //unordered_map<unsigned int, int > kmers;
  unsigned short * * kmers;
  unsigned long num_tables;
  unsigned int kmer_size;
  void hash(char *, unsigned short * id);
};

#endif
