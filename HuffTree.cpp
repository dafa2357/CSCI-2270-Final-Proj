#include "HuffTree.hpp"

using namespace std;

HuffTree::HuffTree(unsigned long long * charProbs)
{
  for (int i = 0; i < 256; i++)
    this->charProbs[i] = charProbs[i];
  buildTree();
}

HuffTree::~HuffTree()
{

}

bool HuffTree::findMins(size_t * iL, size_t * iR, NodeList * list)
{
  if (!iL || !iR) return false;
  if (list->size < 2) return false;
  *iL = 0;
  *iR = 1;
  for (size_t i = 2; i < list->size; i++)
  {
    if ( list[i].node->charCount < list[*iL].node->charCount 
      && list[i].node->charCount < list[*iR].node->charCount)
    { *iL > *iR ? *iL = i : *iR = i; }
    else if (list[i].node->charCount < list[*iL].node->charCount) *iL = i;
    else if (list[i].node->charCount < list[*iR].node->charCount) *iR = i;
  }
  return true;
}
void HuffTree::buildBranch(size_t leftIndex, size_t rightIndex, NodeList * list)
{
  HuffNode * leftNode = list->extract(leftIndex);
  HuffNode * rightNode = list->extract(rightIndex);
  HuffNode * n = new HuffNode();
  if (leftNode->rightChild == NULL)
  {
    delete n;
    n = leftNode;
  }
  else
  {
    n->leftChild = leftNode;
    n->charCount = leftNode->charCount;
    for (size_t i = 0; i < leftNode->leftArr.size(); i++)
      n->leftArr.push_back(leftNode->leftArr[i]);
    for (size_t i = 0; i < leftNode->rightArr.size(); i++)
      n->leftArr.push_back(leftNode->rightArr[i]);
  }
  n->charCount += rightNode->charCount;
  if (rightNode->rightChild == NULL)
  {
    n->rightChild = NULL;
    n->rightArr = rightNode->leftArr;
    delete rightNode;
  }
  else
  {
    n->rightChild = rightNode;
    for (size_t i = 0; i < rightNode->leftArr.size(); i++)
      n->rightArr.push_back(rightNode->leftArr[i]);
    for (size_t i = 0; i < rightNode->rightArr.size(); i++)
      n->rightArr.push_back(rightNode->rightArr[i]);
  }
  list->append(n);
}

void HuffTree::buildTree()
{
  size_t l,r;
  NodeList * leafs = new NodeList();
  HuffNode * tmp   = new HuffNode();
  tmp->leftChild   = NULL;
  tmp->rightChild  = NULL;
  tmp->leftArr.push_back(0);
  //tmp->leftArr = new vector<unsigned char>[1];
  //tmp->leftArr[0] = 0;
  //tmp->rightArr = NULL;
  tmp->charCount = this->charProbs[0];
  leafs->node = tmp;
  for (unsigned char i = 1; i < 256 && i; i++)
  {
    tmp = new HuffNode();
    tmp->leftChild  = NULL;
    tmp->rightChild = NULL;
    tmp->leftArr.push_back(i);
    //tmp->leftArr = new vector<unsigned char>[1];
    //tmp->leftArr[0] = i;
    //tmp->rightArr = NULL;
    tmp->charCount = this->charProbs[i];
    leafs->append(tmp);
  }
  while (findMins(&l, &r, leafs))
  {
    buildBranch(l, r, leafs);
  }
  root = leafs->extract(0);
  delete leafs;
  return;
}

