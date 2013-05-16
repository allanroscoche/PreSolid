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
  cout << "loading complete" << endl;

  //CsRead read(5,(char *)"ACGTT");

  cout << reads << endl;
  
  return 0;
}
