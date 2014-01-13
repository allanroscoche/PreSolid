#ifndef KMERTABLE
#define KMERTABLE
#include "globals.h"
#include "kmer.hpp"
#include "csread.hpp"
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using std::list;
using std::istream;
using std::ostream;
using std::unordered_map;

class KmerTable {
public:
  void insert(CsRead *, unsigned int id);
  KmerTable(unsigned int kmer_size);
  ~KmerTable();
  void print();

private:
  //unordered_map<unsigned int, int > kmers;
  list<unsigned char> * kmers;
  unsigned long table_size;
  unsigned int kmer_size;
  bool hash(char *, unsigned char *);
  void insertKmer(unsigned char *);
};

#endif
