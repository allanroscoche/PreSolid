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

  //kmers = (unsigned short  * *) malloc(sizeof(unsigned short *) * size);

  //for(i=0;i<size;i++)
  //kmers[i] = (list<unsigned short>) malloc(sizeof(list<unsigned short>) * TABLE_SIZE);

  kmers = (unsigned char * ) malloc(sizeof(unsigned char)*256);
  //std::cout << "hashtable size: " << table_size << std::endl;


}

KmerTable::~KmerTable() {

  free(kmers);
}

void KmerTable::print(){
  unsigned long total=0;
  unsigned long i;

  for(i=0;i<256;i++)
    std::cout << "[" << i << "]=" << (int)kmers[i] << std::endl;
  //  total+=kmers[i];
  //td::cout << (total/table_size) << std::endl;


}

void KmerTable::insertKmer(unsigned char * key){


  kmers[key[0]]++;

  //if(kmers[key[0]] > 0)
  //  std::cout << "!" << std::endl;
  //else
  //  kmers[key[0]] = (unsigned char *) malloc ( sizeof(unsigned char));

  //kmers[key[0]] = key[1];

}

void KmerTable::insert(CsRead * read, unsigned int id){
  unsigned int i,j;
  unsigned int pieces = read->getSize() - kmer_size;
  unsigned int * kmer_id;


  char * temp = (char * ) malloc( sizeof(char)*kmer_size);
  //unsigned short * hash_id = (unsigned short * ) malloc ( sizeof(unsigned short) * num_tables);

  /*
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

    ======= */
  //unsigned int kmer_id;

  //char * temp = (char * ) malloc( sizeof(char)*kmer_size);
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


bool KmerTable::hash(char *bases, unsigned char * id){

  unsigned int i,cod,temp;
  bool div4;

  //for(i=0;i<num_tables;i++)
  //  id[i]=0;

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
  /*
    key[i/4] |= cod << (2*(i%4));
  }
  std::cout << std::endl;
  for(i=0;i<(kmer_size/4);i++){
    std::cout << std::bitset<8>(key[i]);
  }
  std::cout << std::endl;
  */
  return 1;

}
