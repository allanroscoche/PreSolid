#include "csread.hpp"
#include "globals.h"

class readTable {

public:
  readTable(char * filename);


private:
  char ** read;
  int ** qual;
  
};

