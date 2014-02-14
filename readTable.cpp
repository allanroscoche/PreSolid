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

readTable::readTable(char * nome1, char * nome2){

  this->arquivo.open(nome1, ios::in);
  this->arquivo_R3.open(nome2, ios::in);
  paired = true;
  reads_R3 = NULL;
  countFileSize();

}

readTable::~readTable(){
  this->arquivo.close();
}

void readTable::clear(){

  unsigned long i,read_index;
  read_index = 0;

  if(paired)
    good_reads = new CsRead[(size*2)-bad_reads];
  else
    good_reads = new CsRead[size-bad_reads];

  std::cout << "Cleaning..." << std::endl;
  if(paired){
    for(i=0;i<size;i++){
      if(reads_F3[i].isGood() && reads_R3[i].isGood() ){
        good_reads[read_index++] = reads_F3[i];
        good_reads[read_index++] = reads_R3[i];
      }
    }
  }
  else {
    for(i=0;i<size;i++){
      if(reads_F3[i].isGood()){
        good_reads[read_index++] = reads_F3[i];
      }
    }
  }

  delete reads_F3;
  delete reads_R3;

  if(paired)
    size = (size*2)-bad_reads-1;
  else
    size = size-bad_reads-1;

  std::cout << "Good reads:" << size << endl;

  std::cout << "Cleaning complete" << std::endl;
  std::cout << std::endl;

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

void readTable::markMinReads(int qual, int min){

  int i;
  CsRead * reads;

  reads = reads_F3;

  for(i=0;i<size;i++){
    if(reads[i].firstQual(qual) < min){
      reads[i].setBad();
    }
  }
  cout << endl;
  if(paired){
    reads = reads_R3;
    for(i=0;i<size;i++){
      if(reads[i].firstQual(qual) < min){
        reads[i].setBad();
      }
    }
    cout << endl;
  }

}

void readTable::loadQuals(char * nome1, char * nome2){
  nome_qual = nome1;
  nome_qual_R3 = nome2;
  quals(true);
  quals(false);
}
void readTable::loadQuals(char * nome){
  nome_qual = nome;
  quals(true);
}

void readTable::quals(bool pair){
  long i,j;
  string linha;

  int quals[READ_TAM];
  fstream qual_file;
  CsRead * reads;

  if(pair){
    qual_file.open(nome_qual);
    reads = reads_F3;
  }
  else {
    qual_file.open(nome_qual_R3);
    reads = reads_R3;
  }

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
      reads[i].addQual(READ_TAM,quals);
    }
  }
  else if(pair)
    cout << "arquivo " << nome_qual <<" não encontrado" << endl;
  else
    cout << "arquivo " << nome_qual_R3 <<" não encontrado" << endl;

}
int readTable::maxQual(){

  long i,j;
  int max=0;
  for(i=0;i<size;i++)
    for(j=0;j<READ_TAM-2;j++)
      if(reads_F3[i].qual(j) > max)
        max = reads_F3[i].qual(j);
  if(paired)
  for(i=0;i<size;i++)
    for(j=0;j<READ_TAM-2;j++)
      if(reads_R3[i].qual(j) > max)
        max = reads_R3[i].qual(j);

  return max;
}


long readTable::markBadReads(int min_qual){
  long i,j;

  bad_reads=0;
  for(i=0;i<size;i++){
    for(j=0;j<READ_TAM-2;j++){
      if(reads_F3[i].qual(j) < min_qual){
        bad_reads++;
        reads_F3[i].setBad();
        break;
      }
    }
  }
  if(paired){
    for(i=0;i<size;i++){
      for(j=0;j<READ_TAM-2;j++){
        if(reads_R3[i].qual(j) < min_qual){
          bad_reads++;
          reads_R3[i].setBad();
          break;
        }
      }
    }
  }
  cout << "bads: " << bad_reads << endl;
}


CsRead *  readTable::load(CsRead * reads){
  long i;
  string linha;


  reads = new CsRead[size];

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

  return reads;
}

void readTable::loadReads(){

  reads_F3 = load(reads_F3);
  if(paired)
    reads_R3 = load(reads_R3);
}

void readTable::writeGoodReads(char * name){

  long i;
  fstream outfile;
  outfile.open(name,ios::out);

  if(paired){
    for(i=0;i<size;i++){
      if(reads_F3[i].isGood() && reads_R3[i].isGood() ){
        outfile << ">" << i << "_F3" << endl;
        reads_F3[i].print(outfile);
        outfile << ">" << i << "_R3" << endl;
        reads_R3[i].print(outfile);
      }
    }
  }
  else {
    for(i=0;i<size;i++){
      if(reads_F3[i].isGood()){
	outfile << ">" << i << endl;
	reads_F3[i].print(outfile);
      }
    }
  }
  outfile.close();

}
void readTable::writeGoodReads2(char * name){

  long i;
  fstream outfile;
  outfile.open(name,ios::out);

  for(i=0;i<size;i++){
    if(reads_F3[i].isGood() && reads_R3[i].isGood()){
      outfile << ">" << i << "F3" << endl;
      reads_F3[i].print(outfile);
    }
  }
  if(paired){
    for(i=0;i<size;i++){
      if(reads_F3[i].isGood() && reads_R3[i].isGood()){
        outfile << ">" << i << "R3" << endl;
        reads_F3[i].print(outfile);
      }
    }
  }

  outfile.close();

}

void readTable::writeBadReads(char * name){

  long i;
  fstream outfile;
  outfile.open(name,ios::out);

  for(i=0;i<size;i++){
    if(!reads_F3[i].isGood()){
      outfile << ">" << i << endl;
      reads_F3[i].print(outfile);
    }
  }
  if(paired){
    for(i=0;i<size;i++){
      if(!reads_F3[i].isGood()){
        outfile << ">" << i << endl;
        reads_F3[i].print(outfile);
      }
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

unsigned long readTable::countFileSize(){

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
    novo->insert(&good_reads[i],i);
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
  if(paired){
    for(i=0;i<size;i++){
      if(reads_R3[i].isGood()){
        if((i % (size/10)) == 0 ){
          cout << ".";
          cout.flush();
        }
        reads_R3[i].convert2PseudoBases();
      }
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
