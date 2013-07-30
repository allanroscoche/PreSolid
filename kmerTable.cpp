#include "kmerTable.hpp"
#include <stdio.h>
#include <stdlib.h>

KmerTable::KmerTable(unsigned int k_size){

  table_size = 1;
  std::cout << "k:" << k_size << std::endl;
  kmer_size = k_size;
  unsigned int i=0;

  for(i=0;i<(kmer_size/4);i++)
    table_size *= 4;


  kmer = (KmerStack *) malloc(sizeof(Kmer) * table_size);
  std::cout << "hashtable size: " << table_size << std::endl;


}

KmerTable::~KmerTable() {
  int i;

  free(kmer);

}

void KmerTable::insert(CsRead * read){
  unsigned int i;
  unsigned int pieces = read->getSize() - kmer_size;

  for(i=0;i<pieces;i++)
    //hash(read->subs(i,kmer_size));
#pragma GCC diagnostic ignored "-Wwrite-strings"
    hash("CAAAC");

}

unsigned int KmerTable::hash(char *bases){

  unsigned int add,i,cod,temp;
  bool div4;
  add  = 0;
  for(i=0;i<5;i++){
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
