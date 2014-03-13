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
  ~CsRead();

  void clear();
  CsRead add(int size, std::string read);
  void setBad();
  void setGood();
  bool isGood();
  void subs(unsigned char pos, unsigned char size, char *);
  void print(ostream &);
  int getSize();
  CsRead convert2PseudoBases();
  CsRead convert2Bases();

private:
  char * bases;
  //int * quals;
  char size;
  //short first;
  bool bad;

};
#endif
