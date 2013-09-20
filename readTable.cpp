#include "readTable.hpp"
#include <iostream>
#include <fstream>

#define READ_TAM 30
using namespace std;

readTable::readTable(char * nome){

  this->arquivo.open(nome, ios::in);
  paired = false;
  reads_R3 = NULL;
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

void readTable::merge(readTable & table){

  unsigned long i;
  paired = true;

  size+=table.size;
  //for(i=0;i<table.size;i++)
  //  ;

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
      reads_R3[i].addQual(READ_TAM,quals);
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
      if(reads_F3[i].qual(j) < min_qual){
	bad_reads++;
	reads_F3[i].setBad();
	break;
      }
     }
  }

  cout << "bads: " << bad_reads << endl;
}


void readTable::load(CsRead *){
  long i;
  string linha;


  reads_F3 = new CsRead[size];

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
    reads_F3[i].add(READ_TAM,linha);
  }
}

void readTable::loadReads(){

  load(reads_F3);

}

void readTable::writeGoodReads(char * name){

  long i;
  fstream outfile;
  outfile.open(name,ios::out);

  for(i=0;i<size;i++){
    if(reads_F3[i].isGood()){
      outfile << ">" << i << endl;
      reads_F3[i].print(outfile);
    }
  }
  outfile.close();

}

ostream &operator<<( ostream & output, const readTable &read) {

  int i;
  for(i=0;i<read.size;i++){
    output << ">" << i << endl;
    read.reads_F3[i].print(output);
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

  for(i=0;i<size;i++){
    if((i % (size/10)) == 0 ){
      cout << ".";
      cout.flush();
      }
    novo->insert(&reads_F3[i],i);
  }

  return novo;

}

CsRead * readTable::getRead(unsigned int read_id){
  CsRead * copy = new CsRead(reads_F3[read_id]);
  return copy;
}

void readTable::convertPseudoBases() {
  unsigned long i;

  for(i=0;i<size;i++){
    if(reads_F3[i].isGood()){
      if((i % (size/10)) == 0 ){
	cout << ".";
	cout.flush();
      }
      reads_F3[i].convert2PseudoBases();
    }
  }
}

void readTable::convertBases(){
  unsigned long i;

  for(i=0;i<size;i++){
    if(reads_F3[i].isGood()){
      if((i % (size/10)) == 0 ){
	cout << ".";
	cout.flush();
      }
      reads_F3[i].convert2Bases();
    }
  }
}
