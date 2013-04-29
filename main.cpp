#include <iostream>
<<<<<<< HEAD
#include "readTable.hpp"
=======
#include "csread.hpp"
>>>>>>> 34a75abbb878bc9a3eb686e16f9b823da3af331d

using std::cout;
using std::endl;

int main(){
  
<<<<<<< HEAD
  readTable reads("data/example.csfasta");
  cout << "Reading file..." << endl;
  
  cout << "Read complete.." << endl;
=======
  CsRead read(5,(char *)"ACGTT");

  cout << read << endl;

  //cout << "Reading file..." << endl;
  //cout << "Read complete.." << endl;
>>>>>>> 34a75abbb878bc9a3eb686e16f9b823da3af331d
  
  return 0;
}
