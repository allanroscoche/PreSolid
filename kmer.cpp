#include "kmer.hpp"

KmerStack::KmerStack(){
  this->head = NULL;
}
Kmer *  KmerStack:: push(unsigned int id, unsigned char pos){

  Kmer * temp = new Kmer(id, pos);
 
  if( this->head == NULL){
    this->head = temp;
    return this->head;
  }
  else {
    //temp->next = temp;
    this->head = temp;
  }

}

Kmer * KmerStack::pop(){
  Kmer * temp = this->head;
  //this->head = this->head->next;
  return temp;
}

void KmerStack::erase(){



}

// ---------------- Kmer

ostream &operator<<( ostream & output, const Kmer &read) {

  output << "id:"<< read.read_id << " p:" << (int)read.kmer_pos << "  ";

}
