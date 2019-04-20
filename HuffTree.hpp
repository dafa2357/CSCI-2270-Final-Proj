#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP
#include <iostream>
#include <vector>
#include <bitset>
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

struct NodeList {
  NodeList * next;
  HuffNode * node;
  size_t     size;

  NodeList();
  void append(HuffNode * n);
  NodeList * at(size_t n);
  NodeList * operator[](size_t n);
  HuffNode * extract(size_t n);
};

class HuffTree
{
  unsigned long long charProbs[UCHAR_MAX + 1];
  vector<int> treeArr[UCHAR_MAX + 1];

  bool findMins(size_t *, size_t *, NodeList *);
  void buildBranch(size_t, size_t, NodeList *);
  HuffNode * buildTree();
  void destroyNode(HuffNode *);
  vector<int> search(HuffNode *, unsigned char);
  void buildArr();
  void print2DUtilHelper(HuffNode *currNode, int space);

public:
  HuffTree(unsigned long long * charProbs);
  HuffTree(char * fileName);
  ~HuffTree();
  void print2DUtil(int space);

  vector<int> encode(unsigned char);
  //decode();
};

#endif
