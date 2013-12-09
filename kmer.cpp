#include "kmer.hpp"

// ---------------- Kmer

ostream &operator<<( ostream & output, const Kmer &read) {

  output << "id:"<< read.read_id << " p:" << (int)read.kmer_pos << "  ";

}
