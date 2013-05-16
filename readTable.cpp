#include "readTable.hpp"
#include <iostream>
#include <fstream>

using namespace std;

readTable::readTable(char * nome){
  
  this->arquivo.open(nome, ios::in);
  
  countFileSize();

}

readTable::~readTable(){
  this->arquivo.close();
}

long readTable::numberReads(){
  long size;
  size = this->size;
  return size;
}

void readTable::loadReads(){
  long i;
  string linha;


  this->read = new CsRead[size];


  arquivo.clear();
  arquivo.seekg(0, ios::beg);

  for(i=0;i<size;i++){
    getline(arquivo, linha);
    if(linha[0] == '>'){
      getline(arquivo, linha);
      read[i].add(30,linha);
    }
  }

}

ostream &operator<<( ostream & output, const readTable &read) {
  
  int i;
  for(i=0;i<read.size;i++){
    read.read[i].print(output);
  }
  return output;
}

long readTable::countFileSize(){  

  string linha;
  this->size=0;
  
  if(arquivo.is_open()){
    while(arquivo.good()){
      getline(arquivo, linha);
      if(linha[0] == '>')
	this->size++;
    }
  }
  else {
    cout << "Arquivo não pode ser aberto" << endl;
  }
}
