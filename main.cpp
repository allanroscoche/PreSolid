#include <iostream>
#include <fstream>
#include <unordered_set>
#include "readTable.hpp"
#include "csread.hpp"
#include "kmer.hpp"

using std::cout;
using std::endl;

int main(){
#pragma GCC diagnostic ignored "-Wwrite-strings"
  cout << "Counting reads: ";
  readTable reads("data/treinamento2.csfasta");
  cout << reads.numberReads() << " reads" << endl;
  cout << "Loading reads: ";
  reads.loadReads();
  cout << endl << "loading complete" << endl << "loadind quals: ";
  //reads.loadQuals("data/example.qual");
  //cout << endl << "loading quals complete" << endl;
  //reads.markBadReads(1);
  //reads.writeGoodReads("data/example.out");

  KmerTable * pKmerT;
  pKmerT = reads.generateKmerTable(21);

  cout << endl;

  return 0;
}
