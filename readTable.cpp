#include "readTable.hpp"
#include <iostream>
#include <fstream>

#define READ_TAM 30
using namespace std;

readTable::readTable(char * nome){

  this->arquivo.open(nome, ios::in);
  paired = false;
  countFileSize();

}

readTable::readTable(char * nome1, char * nome2){

  this->arquivo.open(nome1, ios::in);
  this->arquivo_R3.open(nome2, ios::in);
  paired = true;
  countFileSize();

}

readTable::~readTable(){

}


unsigned long readTable::countFileSize(){

  string linha;
  unsigned int l_size=0;

  if(arquivo.is_open()){
    while(arquivo.good()){
      getline(arquivo, linha);
      if(linha[0] == '>')
        l_size++;
    }
  }
  else {
    cout << "Arquivo não pode ser aberto" << endl;
  }
  size = l_size;

  if(paired){
    l_size=0;
    if(arquivo_R3.is_open()){
      while(arquivo_R3.good()){
        getline(arquivo_R3, linha);
        if(linha[0] == '>')
          l_size++;
      }
    }
    else {
      cout << "Arquivo2 não pode ser aberto" << endl;
      return 0;
    }
    if(l_size == size)
      size = size*2;
    else {
      cout << "Arquivos de tamanhos diferentes: " << l_size << ", " << size << endl;
      return 0;
    }
  }
  return size;
}

void readTable::loadReads(){
  long i;
  string linha;

  reads = new CsRead[size];
  if(!paired){
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
      reads[i].add(READ_TAM,linha);
    }
    arquivo.close();
  }
  else {
    arquivo.clear();
    arquivo_R3.clear();
    arquivo.seekg(0, ios::beg);
    arquivo_R3.seekg(0, ios::beg);
    for(i=0;i<size;i++){
      if((i % (size/10)) == 0 ){
        cout << ".";
        cout.flush();
      }
      if(i%2){
        do{
          getline(arquivo, linha);
        }while(linha[0] != '>');
        getline(arquivo, linha);
      }
      else {
        do{
          getline(arquivo_R3, linha);
        }while(linha[0] != '>');
        getline(arquivo_R3, linha);
      }
      reads[i].add(READ_TAM,linha);
    }
    arquivo.close();
    arquivo_R3.close();
  }
}

void readTable::convertPseudoBases() {
  unsigned long i;

  for(i=0;i<size;i++){
    if(reads[i].isGood()){
      if((i % (size/10)) == 0 ){
        cout << ".";
        cout.flush();
      }
      reads[i].convert2PseudoBases();
    }
  }
}

void readTable::convertBases(){
  unsigned long i;

  for(i=0;i<size;i++){
    if(reads[i].isGood()){
      if((i % (size/10)) == 0 ){
        cout << ".";
        cout.flush();
      }
      reads[i].convert2Bases();
    }
  }
}


void readTable::clear(){

  unsigned long i,read_index;
  read_index = 0;

}

long readTable::numberReads(){
  long size;
  size = this->size;
  return size;
}

void readTable::merge(readTable & table){

  unsigned long i;
  paired = true;

}

void readTable::loadQuals(char * nome1, char * nome2, int min_qual){
  nome_qual = nome1;
  nome_qual_R3 = nome2;
}
void readTable::loadQuals(char * nome, int min_qual){
  nome_qual = nome;
}

void readTable::markBadReads(int min){

  long i,j;
  string linha;

  fstream qual_file,qual_file_R3;

  bool bad;
  int quals[READ_TAM];

  if(!paired){

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


      for(j=0;j<READ_TAM;j++){
        qual_file >> quals[j];
      }
      for(j=0;j<READ_TAM;j++){
        if(quals[j] <= 0 )
           reads[i].setBad();
      }


      getline(arquivo, linha);

    }
  }
  else {

    arquivo.open(nome_qual, ios::in);
    arquivo_R3.open(nome_qual_R3, ios::in);

    arquivo.clear();
    arquivo_R3.clear();
    arquivo.seekg(0, ios::beg);
    arquivo_R3.seekg(0, ios::beg);

    for(i=0;i<size;i++){
      if((i % (size/10)) == 0 ){
        cout << ".";
        cout.flush();
      }
      if(i%2){
        do{
          getline(arquivo, linha);
        }while(linha[0] != '>');
        getline(arquivo, linha);
      }
      else {
        do{
          getline(arquivo_R3, linha);
        }while(linha[0] != '>');
        getline(arquivo_R3, linha);
      }

      reads[i].add(READ_TAM,linha);
    }
  }
}



void readTable::quals(){
  long i,j;
  string linha;

  bool bad;
  int quals[READ_TAM];
  fstream qual_file;
  CsRead * reads;

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
      for(j=0;j<READ_TAM;j++){
        if(quals[j] <= 0)
          bad = true;
      }
      if(bad)
        reads[i].setBad();

    }
  }

  cout << "arquivo " << nome_qual <<" não encontrado" << endl;
}

void readTable::writeGoodReads(char * name){

  long i;
  fstream outfile;
  outfile.open(name,ios::out);

  if(paired){
    for(i=0;i<size;i++){
        outfile << ">" << i << "_F3" << endl;
        reads[i].print(outfile);
    }
  }
  else {
    for(i=0;i<size;i++){
      if(reads[i].isGood()){
        outfile << ">" << i << endl;
        reads[i].print(outfile);
      }
    }
  }
  outfile.close();

}

ostream &operator<<( ostream & output, const readTable &read) {

  int i;
  for(i=0;i<read.size;i++){
    output << ">" << i << endl;
    read.reads[i].print(output);
  }
  return output;
}


KmerTable * readTable::generateKmerTable(unsigned int kmer_size){

  KmerTable * novo = new KmerTable(kmer_size);
  unsigned int i;


  for(i=0;i<size;i++){
    if((i % (size/10)) == 0 ){
      std::cout << ".";
      std::cout.flush();
    }
    //novo->insert(&good_reads[i],i);
  }

  return novo;

}

CsRead * readTable::getRead(unsigned int read_id){
  CsRead * copy = new CsRead(reads[read_id]);
  return copy;
}
