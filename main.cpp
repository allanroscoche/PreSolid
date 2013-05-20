#include <iostream>
#include "readTable.hpp"
#include "csread.hpp"

using std::cout;
using std::endl;

int main(){
  
  cout << "Opening file..." << endl;
  readTable reads("data/example.csfasta");
  cout << reads.numberReads() << " reads" << endl;
  reads.loadReads();
  cout << "loading complete" << endl << "loadind quals..." << endl;
  reads.loadQuals("data/example.qual");

  //CsRead read(5,(char *)"ACGTT");
  //int quals[5] = { 10, 20, 30, 40, 50};
  //read.addQual(5,quals);

  //cout << reads << endl;
  
  return 0;
}
