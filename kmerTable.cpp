#include "kmerTable.hpp"
#include "kmerTree.hpp"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>

#define HASH_SIZE 256

using std::cout;
using std::endl;

KmerTable::KmerTable(unsigned int k_size){


  std::cout << "k:" << k_size << std::endl;

  kmer_size = k_size;
  unsigned int i,size;

  num_tables = (kmer_size / 8) + 1;

  kmers = new kmerTree(num_tables);
  //kmers = (unsigned int * ) malloc(sizeof(unsigned int)*HASH_SIZE);
  //for(i=0;i<HASH_SIZE;i++)
  //  kmers[i] = 0;
}

KmerTable::~KmerTable() {

  free(kmers);
}

void KmerTable::print(){
  unsigned long total=0;
  unsigned long i;

  kmers->print();

  /*
  for(i=0;i<256;i++){
    std::cout << "[" << i << "]=" << (int)kmers[i] << std::endl;
    total+=kmers[i];
  }
  std::cout << total << std::endl;
  // */
}

void KmerTable::insertKmer(unsigned char * key){


  kmers->insert(key);
  //std::cout << key << std::endl;
  //kmers[key[0]]++;

}

void KmerTable::insert(CsRead * read, unsigned int id){
  unsigned int i,j;
  unsigned int pieces = read->getSize() - kmer_size;
  unsigned int * kmer_id;


  char * temp = (char * ) malloc( sizeof(char)*kmer_size);
  unsigned char * tkey = (unsigned char * ) malloc( sizeof(unsigned char)*kmer_size);

  for(i=0;i<pieces;i++){
    read->subs(i,kmer_size,temp);
    hash(temp,tkey);
    insertKmer(tkey);
  }
  free(temp);
  free(tkey);
}


bool KmerTable::hash(char *bases, unsigned char * id){

  unsigned int i,cod,temp;
  bool div4;

  for(i=0;i<num_tables;i++)
    id[i]=0;

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
    }


    id[i/8] |= cod << ((i*2)%16);

  }
  return 1;

}
