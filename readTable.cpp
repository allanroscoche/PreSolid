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

long readTable::markBadReads(int min_qual){
  long i,j;


  bad_reads=0;
  for(i=0;i<size;i++){
    for(j=0;j<READ_TAM;j++){
      if(read[i].qual(j) < min_qual){
	bad_reads++;
	read[i].setBad();
	break;
      }
     }
  }

  cout << "bads: " << bad_reads << endl;
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

void readTable::writeGoodReads(char * name){

  long i;
  fstream outfile;
  outfile.open(name,ios::out);

  for(i=0;i<size;i++){
    if(read[i].isGood()){
      outfile << ">" << i << endl;
      read[i].print(outfile);
    }
  }
  outfile.close();

}

ostream &operator<<( ostream & output, const readTable &read) {

  int i;
  for(i=0;i<read.size;i++){
    output << ">" << i << endl;
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
KmerTable * readTable::generateKmerTable(unsigned int kmer_size){

  KmerTable * novo = new KmerTable(kmer_size);
  unsigned int i;

  for(i=0;i<size;i++)
    novo->insert(&read[i],i);

  return novo;

}

CsRead * readTable::getRead(unsigned int read_id){
  CsRead * copy = new CsRead(read[read_id]);
  return copy;
}

void readTable::convertPseudoBases() {
  unsigned long i;

  for(i=0;i<size;i++){
    if(read[i].isGood()){
      read[i].convert2PseudoBases();
    }
  }
}

void readTable::convertBases(){
  unsigned long i;

  for(i=0;i<size;i++){
    if(read[i].isGood()){
      read[i].convert2Bases();
    }
  }
}
