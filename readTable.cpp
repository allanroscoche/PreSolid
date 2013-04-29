#include "readTable.hpp"
#include <iostream>
#include <fstream>

using namespace std;

readTable::readTable(char * nome){

  arquivo.open(nome);
  
}

