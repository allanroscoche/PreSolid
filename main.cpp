#include <iostream>
#include "readTable.hpp"
#include "csread.hpp"

using std::cout;
using std::endl;

int main(){
  
  cout << "Reading file..." << endl;
  readTable reads("data/example.csfasta");
  cout << "Read complete.." << endl;

  CsRead read(5,(char *)"ACGTT");

  cout << read << endl;
  
  return 0;
}
