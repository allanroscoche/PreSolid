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
  readTable reads("data/example.csfasta");
  cout << reads.numberReads() << " reads" << endl;
  cout << "Loading reads: ";
  reads.loadReads();
  cout << endl << "loading complete" << endl << "loadind quals: ";
  reads.loadQuals("data/example.qual");
  cout << endl << "loading quals complete" << endl;
  reads.markBadReads(1);

  reads.writeGoodReads("data/example.out");

  CsRead * teste = reads.getRead(2);
  cout << "t: " << *teste << endl;
  cout << "s: " << teste->subs(20,10) << endl;

  KmerTable * pKmerT;
  pKmerT = reads.generateKmerTable(21);

  cout << endl;
  /*
  std::unordered_set<Kmer> myset;

  cout << "myset contains:";
  for( auto it = myset.cbegin(); it != myset.cend(); it++)
    std::cout << " " << *it;
  std::cout << std::endl;

  std::cout << "myset's buckets contains:\n";
  for( unsigned i = 0; i < myset.bucket_count(); ++i) {
    cout << "bucket #" << i << " contains:";
    for( auto local_it = myset.cbegin(i); local_it != myset.cend(i); ++local_it )
      cout << " " << *local_it;
    cout << endl;
  }

  //cout << reads << endl;
  //CsRead read(5,(char *)"ACGTT");
  //int quals[5] = { 10, 20, 30, 40, 50};
  //read.addQual(5,quals);

  //cout << reads << endl;
  */
  return 0;
}
