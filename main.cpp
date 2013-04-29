#include <iostream>
#include "csread.hpp"

using std::cout;
using std::endl;

int main(){
  
  CsRead read(5,(char *)"ACGTT");

  cout << read << endl;

  //cout << "Reading file..." << endl;
  //cout << "Read complete.." << endl;
  
  return 0;
}
