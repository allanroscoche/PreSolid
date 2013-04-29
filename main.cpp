#include <iostream>
#include "readTable.hpp"

using std::cout;
using std::endl;


int main(){
  
  readTable reads("data/example.csfasta");
  cout << "Reading file..." << endl;
  
  cout << "Read complete.." << endl;
  
  return 0;
}
