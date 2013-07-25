#ifndef KMER
#define KMER
#include "globals.h"
#include <iostream>
#include <string>

using std::istream;
using std::ostream;

class Kmer {
public:
  Kmer(unsigned int id, unsigned char pos){
    this->read_id = id;
    this->kmer_pos = pos;
  }
  // data
  unsigned int read_id;
  unsigned char kmer_pos;
  Kmer * next;
};

class KmerStack {

public:
  KmerStack();
  Kmer * push(unsigned int id, unsigned char pos);
  Kmer * pop();

private:
  Kmer * head;
};

#endif
