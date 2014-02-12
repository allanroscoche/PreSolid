#ifndef KMERTREE
#define KMERTREE


struct kmerNode
{

  kmerNode * next[256];
  unsigned char code, level;

};

class kmerTree {
public:
  kmerTree(unsigned int);
  ~kmerTree();
  void insert(unsigned char * key);
  void print();

  private:
  kmerNode * insert(unsigned char * key, kmerNode * no );
  kmerNode * root;

  unsigned int kmer_size;
  unsigned int num_tables;

  unsigned char * tprint;

  kmerNode * novo_no(unsigned char key, unsigned char level);
  kmerNode * rec_print(kmerNode *);

};

#endif
