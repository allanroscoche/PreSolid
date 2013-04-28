#ifndef CSREAD
#define CSREAD
#include "globals.h"
#include <iostream>


using std::istream;
using std::ostream;

class CsRead {
  friend ostream &operator<<( ostream &, const CsRead &);
  friend istream &operator>>( istream &, CsRead &);

public:
  CsRead(READ_SIZE size);
  CsRead(char size, char * read);
  CsRead(char size, char * read, int * quals);  

private:
  char * bases;
  int * quals;
  char size;

};
#endif
