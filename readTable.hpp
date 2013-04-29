#include "csread.hpp"
#include "globals.h"
#include <fstream>
#include <iostream>

using namespace std;

class readTable {

public:
  readTable(char * filename);


private:
  char ** read;
  int ** qual;
  ifstream arquivo;
  
};

