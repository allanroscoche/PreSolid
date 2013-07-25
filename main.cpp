#include <iostream>
#include <fstream>
#include <unordered_set>
#include "readTable.hpp"
#include "csread.hpp"

using std::cout;
using std::endl;

int main(){

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


  std::unordered_set<std::string> myset = {"Allan", "Tais", "Melão"};

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

  return 0;
}
