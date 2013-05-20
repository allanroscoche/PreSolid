#include "readTable.hpp"
#include <iostream>
#include <fstream>

#define READ_TAM 30
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

  int quals[READ_TAM];
  fstream qual_file;
  qual_file.open(nome);

  if(qual_file.is_open()){
    for(i=0;i<size;i++){
      
      if((i % (size/10)) == 0 ){
	cout << ".";
	cout.flush();
	}
           
      getline(qual_file,linha);
      while(linha[0] != '>')
	getline(qual_file,linha);

      for(j=0;j<READ_TAM;j++){
	qual_file >> quals[j];
      }
      read[i].addQual(READ_TAM,quals);
    }
  }
  else
    cout << "arquivo não encontrado" << endl;

}

long readTable::markBadReads(){
  long i,j, bads;

  
  bads=0;
  for(i=0;i<size;i++){
    for(j=0;j<READ_TAM;j++){
      if(read[i].qual(j) < 10){
	bads++;
	break;
      }
	//else
	//badread[i] = false;
     }
  }
  
  cout << "bads: " << bads << endl;
}

void readTable::loadReads(){
  long i;
  string linha;


  this->read = new CsRead[size];

  arquivo.clear();
  arquivo.seekg(0, ios::beg);

  for(i=0;i<size;i++){
    if((i % (size/10)) == 0 ){
      cout << ".";
      cout.flush();
      }
    do{
      getline(arquivo, linha);
    }while(linha[0] != '>');
    
    getline(arquivo, linha);
    read[i].add(READ_TAM,linha);
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
