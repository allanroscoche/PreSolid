#ifndef KMER
#define KMER
#include "globals.h"
#include <iostream>
#include <string>

using std::istream;
using std::ostream;

class Kmer {

public:
  Kmer();
  Kmer * insert(unsigned int id, unsigned char pos);

private:
  // data
  unsigned int read_id;
  unsigned char kmer_pos;

  // structure
  Kmer * next;
};

#endif
