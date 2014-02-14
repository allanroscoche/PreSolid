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
  ~CsRead();

  void clear();
  CsRead add(int size, std::string read);
  CsRead addQual(int size, int quals[]);
  int qual(int);
  void setBad();
  bool isGood();
  int firstQual(int);
  void subs(unsigned char pos, unsigned char size, char *);
  void print(ostream &);
  int getSize();
  CsRead convert2PseudoBases();
  CsRead convert2Bases();

private:
  char * bases;
  int * quals;
  char size;
  //short first;
  bool bad;

};
#endif
