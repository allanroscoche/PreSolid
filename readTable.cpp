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

void readTable::loadQuals(char * nome){
  long i,j;
  string linha;

  int quals[30];
  fstream qual_file;
  qual_file.open(nome);

  cout << nome << endl;

  if(qual_file.is_open()){
  
    for(i=0;i<size;i++){
      getline(qual_file, linha);
      if(linha[0] == '>'){
	for(j=0;j<30;j++){
	  qual_file >> quals[i];
	}
	read[i].addQual(30,quals);
      }
    }
  }
  else
    cout << "arquivo não encontrado" << endl;

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
