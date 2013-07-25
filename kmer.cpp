#include "kmer.hpp"

Kmer::Kmer(){

  this->read_id = 0;
  this->kmer_pos = 0;
  this->next = NULL;

}
Kmer *  Kmer:: insert(unsigned int id, unsigned char pos){

  Kmer * temp = new Kmer();

  temp->read_id = id;
  temp->kmer_pos = pos;

  if( this->next == NULL){
    this->next = temp;
    return this;
  }
  else {
    temp->next = this;
    return temp;
  }

}
