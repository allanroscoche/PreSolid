#include <iostream>
#include <fstream>
#include <unordered_set>
#include "readTable.hpp"
#include "csread.hpp"
#include "kmer.hpp"

using std::cout;
using std::endl;
using std::string;
using std::unordered_set ;

int main(){
#pragma GCC diagnostic ignored "-Wwrite-strings"
  cout << "Counting reads: ";
  readTable reads("data/treinamento.csfasta");
  cout << reads.numberReads() << " reads" << endl;
  cout << "Loading reads: ";
  reads.loadReads();
  cout << endl << "loading complete" << endl;
  cout << "Converting reads:";
  reads.convertPseudoBases();
  cout << endl << "Converting Complete" << endl;

  /*
  cout << "loadind quals: ";
  reads.loadQuals("data/example.qual");
  cout << endl << "loading quals complete" << endl;
  reads.markBadReads(1);
  reads.writeGoodReads("data/example.out");
  */

  cout << "Genereting Kmers: ";
  KmerTable * pKmerT;
  pKmerT = reads.generateKmerTable(21);
  //pKmerT->print();

  cout << "Kmers Complete" << endl;




  return 0;
}
