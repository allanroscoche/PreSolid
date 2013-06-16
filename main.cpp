#include <iostream>
#include <fstream>
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

  //cout << reads << endl;
  //CsRead read(5,(char *)"ACGTT");
  //int quals[5] = { 10, 20, 30, 40, 50};
  //read.addQual(5,quals);

  //cout << reads << endl;
  
  return 0;
}
