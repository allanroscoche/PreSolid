#ifndef CSREAD
#define CSREAD
#include "globals.h"
#include <iostream>
#include <string>

using std::istream;
using std::ostream;

class CsRead {
  friend ostream &operator<<( ostream &, const CsRead &);
  friend istream &operator>>( istream &, CsRead &);

public:
  CsRead();
  CsRead(char size);
  CsRead(char size, char * read);
  CsRead(char size, char * read, int * quals);  

  CsRead add(int size, std::string read);
  CsRead addQual(int size, int quals[]);
  int qual(int);
  void print(ostream &);

private:
  char * bases;
  int * quals;
  char size;

};
#endif
