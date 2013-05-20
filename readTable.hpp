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
  void loadQuals(char * filename);
  void loadReads();
  long numberReads();
  void markBadReads();

private:
  CsRead * read;
  int ** qual;
  bool * badread;
  long size;
  fstream arquivo;
  
  long countFileSize();
};

