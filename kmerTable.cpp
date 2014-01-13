#include "kmerTable.hpp"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>

KmerTable::KmerTable(unsigned int k_size){

  table_size = 1;
  std::cout << "k:" << k_size << std::endl;
  kmer_size = k_size;
  //unsigned int i=0;

  //for(i=0;i<kmer_size;i++)
  //  table_size *= 4;


  kmers = (unsigned char * *) malloc(sizeof(unsigned char)*256);
  std::cout << "hashtable size: " << table_size << std::endl;


}

KmerTable::~KmerTable() {

  free(kmers);
}

void KmerTable::print(){
  unsigned long total=0;
  unsigned long i;

  //for(i=0;i<table_size;i++)
  //  total+=kmers[i];
  //td::cout << (total/table_size) << std::endl;

}

void KmerTable::insertKmer(unsigned char * key){
  
  /*
  if(kmers[key[0]] > 0)
    std::cout << "!" << std::endl;
  //else
  //  kmers[key[0]] = (unsigned char *) malloc ( sizeof(unsigned char));

  kmers[key[0]] = key[1];
  */
}

void KmerTable::insert(CsRead * read, unsigned int id){
  unsigned int i;
  unsigned int pieces = read->getSize() - kmer_size;
  unsigned int kmer_id;

  char * temp = (char * ) malloc( sizeof(char)*kmer_size);
  unsigned char * tkey = (unsigned char * ) malloc( sizeof(unsigned char)*kmer_size);

  for(i=0;i<pieces;i++){
    read->subs(i,kmer_size,temp);
    hash(temp,tkey);
    insertKmer(tkey);
    //std::cout << std::setw(5) << "t:" << 
    //kmers[kmer_id % table_size]++;

    
  }
  free(temp);
  free(tkey);
}

bool KmerTable::hash(char *bases, unsigned char *key){

  unsigned int i,cod;

  for(i=0;i<(kmer_size/4);i++)
    key[i]=0;

  for(i=0;i<kmer_size;i++){
    std::cout << bases[i];
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
    
    key[i/4] |= cod << (2*(i%4));
  }
  std::cout << std::endl;
  for(i=0;i<(kmer_size/4);i++){
    std::cout << std::bitset<8>(key[i]);
  }
  std::cout << std::endl;

  return 1;
}
