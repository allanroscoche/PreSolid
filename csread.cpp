#include "csread.hpp"
#include "globals.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

CsRead::CsRead(void){
  bad = false;
  size=0;
}

CsRead::CsRead(char size) {
  bad = false;
  this->size = size;
  bases = new char[size];
}
CsRead::CsRead( char size, char * read) {
  bad = false;
  bases = new char[size];
  this->size = size;
  for(int i=0;i<size;i++)
    bases[i]=read[i];
}

CsRead::CsRead(char size, char * read, int * qual){

  bad = false;
  bases = new char[size];
  quals = new int[size];

  for(int i=0;i<size;i++){
    bases[i] = read[i];
    quals[i] = qual[i];
  }
}

int CsRead::qual(int i){
  return quals[i];
}

void CsRead::setBad(){
  bad = true;
}
bool CsRead::isGood(){
  return !bad;
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


CsRead CsRead::addQual(int n_size, int n_quals[]){
  
  quals = new int[n_size];
  if(size != n_size)
    cout << "Erro\n";

  int i;
  for(i=0;i<size;i++){
    quals[i] = n_quals[i];
  }
  return *this;
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
