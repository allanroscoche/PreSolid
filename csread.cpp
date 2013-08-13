#include "csread.hpp"
#include "globals.h"
#include <iostream>
#include <string>
#include <stdlib.h>

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
void CsRead::subs(unsigned char pos, unsigned char sub_size, char * subs ){
  //char * subs = (char *) malloc (sizeof(char) * size);

  int i,j=0;
  int end = pos + sub_size;
  if( end > size){
    subs[0] = 0;
    return;
  }
  for(i=pos;i<end;i++)
    subs[j++] = bases[i];
  subs[j] = 0;

}

CsRead CsRead::convert2PseudoBases(){

  unsigned int i;
  for(i=2;i<size;i++) {
    switch(bases[i]){
    case '0':
      bases[i-2] = 'A';
      break;
    case '1':
      bases[i-2] = 'C';
      break;
    case '2':
      bases[i-2] = 'G';
      break;
    case '3':
      bases[i-2] = 'T';
      break;
    }
  }
  bases[i-1] = bases[i-2] = 0;
  size -= 2;
  return *this;
}
CsRead CsRead::convert2Bases(){


  switch(bases[1]){
  case '1':
    bases[0] = 'G';
    break;
  case '2':
    bases[0] = 'C';
    break;
  case '3':
    bases[0] = 'A';
    break;
  }

  char base = bases[0];
  char * temp = bases;
  int i;
  for(i=2;i<size;i++){
    switch(bases[i]){
    case '0':
      *temp=base;
      break;
    case '1':
      switch(base){
      case 'A':
        *temp = 'C';
        break;
      case 'C':
        *temp = 'A';
        break;
      case 'G':
        *temp = 'T';
        break;
      case 'T':
        *temp = 'G';
        break;
      }
      break;
    case '2':
      switch(base){
      case 'A':
        *temp = 'G';
        break;
      case 'C':
        *temp = 'T';
        break;
      case 'G':
        *temp = 'A';
        break;
      case 'T':
        *temp = 'C';
        break;
      }
      break;
    case '3':
      switch(base){
      case 'A':
        *temp = 'T';
        break;
      case 'C':
        *temp = 'G';
        break;
      case 'G':
        *temp = 'C';
        break;
      case 'T':
        *temp = 'A';
        break;
      }
      break;
    }
    *temp++;
    base = bases[i-2];
  }
  bases[i-1]=bases[i-2] = 0;
  size -=2;

  return *this;
}

int CsRead::getSize(){
  return size;
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
