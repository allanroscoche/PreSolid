#include <iostream>
#include "readTable.hpp"
#include "csread.hpp"

using std::cout;
using std::endl;

int main(){
  
  readTable reads("data/example.csfasta");

  CsRead read(5,(char *)"ACGTT");

  cout << read << endl;

  //cout << "Reading file..." << endl;
  //cout << "Read complete.." << endl;
  
  return 0;
}
