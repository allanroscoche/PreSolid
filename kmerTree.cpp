#include "kmerTree.hpp"
#include <iostream>

using namespace std;

kmerTree::kmerTree(unsigned int ksize){

  unsigned int i;
  kmer_size = ksize;

  //num_tables = (kmer_size / 8) + 1;
  num_tables = kmer_size;
  tprint = (unsigned char *) malloc (sizeof(unsigned char)*num_tables);

  cout << "Test, num_tables: " << num_tables << endl;
  root = (kmerNode *) malloc( sizeof(kmerNode ));
  for(i=0;i<256;i++)
    root->next[i] = NULL;

}

kmerTree::~kmerTree(){

}


kmerNode * kmerTree::novo_no(unsigned char key, unsigned char level){

  unsigned int i;
  kmerNode * no = (kmerNode *) malloc (sizeof(kmerNode));
  for(i=0;i<256;i++)
    no->next[i] = NULL;
  no->code = key;
  return no;

}


void kmerTree::insert(unsigned char * key){

  unsigned int i;
  kmerNode * no = root;

  for(i=0;i<num_tables-1;i++){
    if(no->next[key[i]] == NULL)
       no->next[key[i]] = novo_no(key[i],i);
    no = no->next[key[i]];
  }

  if(no->next[key[i]] == NULL){
    //no->next[key[i]] = (kmerNode *) malloc(sizeof(kmerNode));
    //no->next[key[i]]->code = 0;
  }
  else
    no->next[key[i]]->code++;

}



unsigned long total;

kmerNode * kmerTree::rec_print(kmerNode * no){

  int i;
  kmerNode * temp;

  for(i=0;i<256;i++){
    if(no->next[i] != 0){
      rec_print(no->next[i]);
      total++;
      }
  }

  return no;
}

void kmerTree::print(){

  cout << "printing..." << endl;
  total=0;
  int i;
  for(i=0;i<256;i++)
    if(root->next[i] != 0){
      rec_print(root->next[i]);
    }
  cout << "total kmers:" << total;
  cout << endl;
}
