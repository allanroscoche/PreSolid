#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
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



int main(int argc, char *argv[]){

  int min_qual=0;

#pragma GCC diagnostic ignored "-Wwrite-strings"

  if(argc < 6)
    error();

  min_qual = std::stoi(argv[1]);

  cout << "Counting reads: ";
  readTable reads(argv[2]);
  readTable reads2(argv[4]);
  cout << reads.numberReads() + reads2.numberReads() << " reads" << endl;
  cout << "Loading reads: ";
  reads.loadReads();
  reads2.loadReads();
  cout << endl << "loading complete" << endl;
  cout << "Converting reads:";
  reads.convertPseudoBases();
  reads2.convertPseudoBases();
  cout << endl << "Converting Complete" << endl;


  cout << "loadind quals: ";
  reads.loadQuals(argv[3]);
  reads2.loadQuals(argv[5]);
  cout << endl << "loading quals complete" << endl;
  reads.markBadReads(min_qual);
  reads2.markBadReads(min_qual);

  reads.merge(reads2);
  reads.writeGoodReads("data/example.out");

  /*
  cout << "Genereting Kmers: ";
  KmerTable * pKmerT;
  pKmerT = reads.generateKmerTable(min_qual);
  pKmerT->print();

  cout << endl << "Kmers Complete" << endl;
  */



  return 0;
}
