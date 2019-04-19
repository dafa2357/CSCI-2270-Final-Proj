#include "HuffTree.hpp"
#include <climits>
using namespace std;

HuffTree::HuffTree(unsigned long long * charProbs)
{
  for (int i = 0; i <= UCHAR_MAX; i++)
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

HuffNode * HuffTree::buildTree()
{
  size_t l,r;
  NodeList * leafs = new NodeList();
  HuffNode * tmp   = new HuffNode();
  HuffNode * root;
  tmp->leftChild   = NULL;
  tmp->rightChild  = NULL;
  tmp->leftArr.push_back(0);
  tmp->charCount = this->charProbs[0];
  leafs->node = tmp;
  for (unsigned char i = 1; i <= UCHAR_MAX && i; i++)
  {
    tmp = new HuffNode();
    tmp->leftChild  = NULL;
    tmp->rightChild = NULL;
    tmp->leftArr.push_back(i);
    tmp->charCount = this->charProbs[i];
    leafs->append(tmp);
  }
  while (findMins(&l, &r, leafs))
  {
    buildBranch(l, r, leafs);
  }
  root = leafs->extract(0);
  delete leafs;
  return root;
}
vector<int> HuffTree::search(HuffNode * root, unsigned char c)
{
  vector<int> charCode;
  HuffNode * tmpNode = root;
  bool atLeaf = false;
  size_t i;
  int code = 1;
  while (!atLeaf)
  {
    code = 1;
    for (i = 0; i < tmpNode->leftArr.size(); i++)
    {
      if (c == tmpNode->leftArr[i]) code = 0;
    }
    charCode.push_back(code);
    if (code)
    {
      if (tmpNode->rightChild == NULL) break;
      tmpNode = tmpNode->rightChild;
    }
    else
    {
      if (tmpNode->leftChild == NULL) break;
      tmpNode = tmpNode->leftChild;
    }
  }
  return charCode;
}
void HuffTree::buildArr()
{
  HuffNode * root = buildTree();
  for (unsigned char i = 0; i <= UCHAR_MAX; i++)
    treeArr[i] = search(root, i);
  return;
}
vector<int>  HuffTree::encode(unsigned char inChar)
{
  return treeArr[inChar];
}
