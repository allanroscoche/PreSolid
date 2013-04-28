#include "csread.hpp"
#include "globals.h"
#include <iostream>

using std::cout;
using std::endl;

CsRead::CsRead(READ_SIZE size) {
  bases = new READ_SIZE[size];
}
CsRead::CsRead( char size, char * read) {
  bases = new READ_SIZE[size];

  for(int i=0;i<size;i++)
    bases[i]=read[i];
}

CsRead::CsRead(char size, char * read, int * qual){
  bases = new READ_SIZE[size];
  quals = new int[size];

  for(int i=0;i<size;i++){
    bases[i] = read[i];
    quals[i] = qual[i];
  }

}
ostream &operator<<( ostream & output, const CsRead &read) {
 
  output << read.bases;

  return output;
}
istream &operator>>( istream & input, CsRead &read){
  input >> read.bases;

  return input;
}
