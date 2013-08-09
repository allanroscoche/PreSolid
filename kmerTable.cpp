#include "kmerTable.hpp"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

KmerTable::KmerTable(unsigned int k_size){

  table_size = 1;
  std::cout << "k:" << k_size << std::endl;
  kmer_size = k_size;
  unsigned int i=0;

  for(i=0;i<(kmer_size/4);i++)
    table_size *= 4;

  kmers.reserve(table_size);

  //kmers = (Kmer *) malloc(sizeof(Kmer) * table_size);
  std::cout << "hashtable size: " << table_size << std::endl;


}

KmerTable::~KmerTable() {

}

void KmerTable::print(){
  for( auto it = kmers.cbegin(); it != kmers.cend(); it++)
    std::cout << "\t" << it->second << ",   ";
  std::cout << std::endl;
}

void KmerTable::insert(CsRead * read, unsigned int id){
  unsigned int i;
  unsigned int pieces = read->getSize() - kmer_size;
  unsigned int kmer_id;


  Kmer * n_kmer;
  for(i=0;i<pieces;i++){
    kmer_id = hash(read->subs(i,kmer_size));
    n_kmer = new Kmer(id,i);
    if(kmers.count(kmer_id) > 0)
      kmers.emplace(kmer_id,*n_kmer);
    else
      std::cout << *n_kmer << std::endl;
  }
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
