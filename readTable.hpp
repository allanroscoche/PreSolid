#include "csread.hpp"
#include "globals.h"
#include <fstream>
#include <iostream>

using namespace std;

class readTable {
  friend ostream &operator<<( ostream &, const readTable &);

public:
  readTable(char * filename);
  ~readTable();
  void  loadReads();
  long numberReads();

private:
  CsRead * read;
  int ** qual;
  long size;
  fstream arquivo;
  
  long countFileSize();
};

