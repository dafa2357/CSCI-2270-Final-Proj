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
  void printNode()
  {
    cout << "charCount: " << charCount << endl;
    cout << "leftArr (size " << leftArr.size() << ") :";
    for (size_t i = 0; i < leftArr.size(); i++)
      cout << (int)leftArr[i] << ' ';
    cout << endl;
    cout << "rightArr (size " << rightArr.size() << ") :";
    for (size_t i = 0; i < rightArr.size(); i++)
      cout << (int)rightArr[i] << ' ';
    cout << endl;
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
  void printList()
  {
    NodeList * tmp = this;
    while (tmp != NULL)
    {
      cout << "List Size: " << tmp->size << endl;
      tmp->node->printNode();
      tmp = tmp->next;
    }
  }
};


class HuffTree
{
  unsigned long long charProbs[UCHAR_MAX + 1];
  vector<int> treeArr[UCHAR_MAX + 1];
  HuffNode * root;
  HuffNode * curDecodeNode;

  bool findMins(size_t *, size_t *, NodeList *);
  void buildBranch(size_t, size_t, NodeList *);
  HuffNode * buildTree();
  void destroyNode(HuffNode *);
  vector<int> search(HuffNode *, unsigned char);
  void buildArr();
  void print2DUtilHelper(HuffNode *, int);

public:
  HuffTree(unsigned long long * charProbs);
  ~HuffTree();
  void print2DUtil(HuffNode *, int);

  const vector<int> encode(unsigned char);
  bool decode(unsigned char * outChar, int inBit);
};

#endif
 
