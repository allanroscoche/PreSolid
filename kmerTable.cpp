#include "kmerTable.hpp"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>

#define TABLE_SIZE 65536

using std::cout;
using std::endl;

KmerTable::KmerTable(unsigned int k_size){


  std::cout << "k:" << k_size << std::endl;

  kmer_size = k_size;
  unsigned int i=0,size;

  size = (kmer_size / 8) + 1;
  num_tables = size;

  kmers = (unsigned short  * *) malloc(sizeof(unsigned short *) * size);

  for(i=0;i<size;i++)
    kmers[i] = (unsigned short  *) malloc(sizeof(unsigned short) * TABLE_SIZE);

  std::cout << "hashtable size: " << num_tables << std::endl;


}

KmerTable::~KmerTable() {

  free(kmers);
}

void KmerTable::print(){
  unsigned long total=0;
  unsigned long i;

  for(i=0;i<num_tables;i++)
    total+=kmers[i][0];
  std::cout << std::endl << total << std::endl;

}

void KmerTable::insert(CsRead * read, unsigned int id){
  unsigned int i,j;
  unsigned int pieces = read->getSize() - kmer_size;
  unsigned int * kmer_id;


  char * temp = (char * ) malloc( sizeof(char)*kmer_size);
  unsigned short * hash_id = (unsigned short * ) malloc ( sizeof(unsigned short) * num_tables);

  for(i=0;i<pieces;i++){
    read->subs(i,kmer_size,temp);
    hash(temp,hash_id);
    //std::cout << std::setw(5) << "t:" << 
    //kmers[kmer_id % table_size]++;

    for(j=0;j<num_tables-1;j++)
      kmers[j][hash_id[j]] = hash_id[j+1];
    //std::cout << "kmer_id:" << hash_id[0] << std::endl;
    //free(kmer_id);
    //kmers[1][(kmer_id >> 8) %TABLE_SIZE]++;

  }
  free(temp);
}

void KmerTable::hash(char *bases, unsigned short * id){

  unsigned int i,cod,temp;
  bool div4;

  for(i=0;i<num_tables;i++)
    id[i]=0;

  for(i=0;i<kmer_size;i++){
    //std::cout << bases[i];
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
  /*
  std::cout << std::endl;
  for(i=0;i<num_tables;i++)
    std::cout << (std::bitset<16>)id[i] << ".";
  std::cout << std::endl;
  */

}
