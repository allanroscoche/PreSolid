#include "csread.hpp"
#include "globals.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

CsRead::CsRead(void){
  size=0;
}

CsRead::CsRead(char size) {
  this->size = size;
  bases = new char[size];
}
CsRead::CsRead( char size, char * read) {
  bases = new char[size];
  this->size = size;
  for(int i=0;i<size;i++)
    bases[i]=read[i];
}

CsRead::CsRead(char size, char * read, int * qual){

  bases = new char[size];
  quals = new int[size];

  for(int i=0;i<size;i++){
    bases[i] = read[i];
    quals[i] = qual[i];
  }
}

void CsRead::print(ostream & output ){
  int i;
  
  for(i=0;i<size;i++)
    output << bases[i];
  output << endl;
}


CsRead CsRead::add(int size, std::string read){
  
  bases = new char[size];
  this->size = size;
  int i;
  for(i=0;i<size;i++)
    bases[i] = read[i];

  return *this;
}
CsRead CsRead::addQual(int size, int quals[]){


}


ostream &operator<<( ostream & output, const CsRead &read) {

  int i;
  for(i=0;i< read.size;i++)
    output << read.bases[i];

  return output;
}
istream &operator>>( istream & input, CsRead &read){
  input >> read.bases;

  return input;
}
