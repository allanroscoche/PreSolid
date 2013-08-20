#include "kmerTable.hpp"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

KmerTable::KmerTable(unsigned int k_size){

  table_size = 1;
  std::cout << "k:" << k_size << std::endl;
  kmer_size = k_size;
  unsigned int i=0;

  for(i=0;i<kmer_size;i++)
    table_size *= 4;


  kmers = (unsigned int  *) malloc(sizeof(unsigned int) * table_size);
  std::cout << "hashtable size: " << table_size << std::endl;


}

KmerTable::~KmerTable() {
  free(kmers);
}

void KmerTable::print(){
  unsigned long total=0;
  unsigned long i;

  for(i=0;i<table_size;i++)
    total+=kmers[i];
  std::cout << (total/table_size) << std::endl;
}

void KmerTable::insert(CsRead * read, unsigned int id){
  unsigned int i;
  unsigned int pieces = read->getSize() - kmer_size;
  unsigned int kmer_id;
  //stack<Kmer> * kmer_st;

  char * temp = (char * ) malloc( sizeof(char)*kmer_size);
  for(i=0;i<pieces;i++){
    read->subs(i,kmer_size,temp);
    kmer_id = hash(temp);
    if(kmer_id <= table_size)
      kmers[kmer_id]++;
    else
      std::cout << "error\n";
  }
  free(temp);
}

unsigned int KmerTable::hash(char *bases){

  unsigned int add,i,cod,temp;
  bool div4;
  add  = 0;
  for(i=0;i<kmer_size;i++){
    switch(bases[i]){
    case 'A':
      cod = 0;
      break;
    case 'C':
      cod = 1;
      break;
    case 'G':
      cod = 2;
      break;
    case 'T':
      cod= 3;
      break;
    default:
      return 0;
    }
    div4 = (i%4)==0;

    if(div4)
      temp = cod;
    else
      temp |= cod << ((2*i)%(sizeof(char)));

    if(div4)
      add |= temp << (2*i);
  }
  //std::cout << add << "\t    ";

  return add;
}
