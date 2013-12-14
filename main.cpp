#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <string.h>
#include "readTable.hpp"
#include "csread.hpp"
#include "kmer.hpp"

using std::cout;
using std::endl;
using std::string;
using std::unordered_set ;

void error(){
  cout << "Usage: presolid min_qual file1 qual1 file2 qual2\n";
}

#pragma GCC diagnostic ignored "-Wwrite-strings"


int main(int argc, char *argv[]){

  int min_qual=0;


  if(argc < 6){
    error();
    return 1;
  }

  min_qual = std::stoi(argv[1]);

  cout << "Counting reads: ";
  readTable reads(argv[3],argv[5]);
  cout << reads.numberReads() << " reads" << endl;
  cout << "Loading reads: ";
  reads.loadReads();

  cout << endl << "loading complete" << endl;
  cout << "Converting reads:";
  reads.convertPseudoBases();

  cout << endl << "Converting Complete" << endl;


  cout << "loadind quals: ";
  reads.loadQuals(argv[4], argv[6]);
  cout << endl << "loading quals complete" << endl;
  /*
  int max = reads.maxQual();
  for(max; max>min_qual;max--){
    cout << "min: " << max << " ";
    reads.markBadReads(max);
  }

  */

  reads.markBadReads(min_qual);
  reads.markMinReads(min_qual, 21);
  char good[50],bad[50];
  strcpy(good,argv[2]);
  strcpy(bad,argv[2]);

  reads.writeGoodReads(strcat(good,"/good.out"));
  reads.writeBadReads(strcat(bad,"/bad.out"));


  /*
  cout << "Genereting Kmers: ";
  KmerTable * pKmerT;
  pKmerT = reads.generateKmerTable(min_qual);
  pKmerT->print();

  cout << endl << "Kmers Complete" << endl;
  */



  return 0;
}
