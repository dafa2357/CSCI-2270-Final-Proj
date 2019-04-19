#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

#include <vector>
#include <climits>
#include <stddef.h>

using namespace std;

struct HuffNode
{
  HuffNode *            leftChild ; // coded 0
  HuffNode *            rightChild; // coded 1
  vector<unsigned char> leftArr;
  vector<unsigned char> rightArr;
  unsigned long long    charCount;

  HuffNode * copy(HuffNode * n)
  {
    this->leftChild = n->leftChild;
    this->rightChild = n->rightChild;
    this->leftArr = n->leftArr;
    this->rightArr = n->rightArr;
    this->charCount = n->charCount;
    return this;
  }
};

struct NodeList
{
  NodeList * next;
  HuffNode * node;
  size_t     size;

  NodeList();
  void append(HuffNode * n);
  NodeList * operator[](size_t n); 
  HuffNode * extract(size_t n);
};

class HuffTree
{
  HuffNode * root; 
  unsigned long long charProbs[UCHAR_MAX +1];

  bool findMins(size_t *, size_t *, NodeList *);
  void buildBranch(size_t, size_t, NodeList *);
  void buildTree();

public:
  HuffTree(unsigned long long * charProbs);
  HuffTree(char * fileName);
  ~HuffTree();

  //encode(char *);
  //decode(char *);
};

#endif
