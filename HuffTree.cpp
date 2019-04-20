#include "HuffTree.hpp"
#include <climits>
using namespace std;

HuffTree::HuffTree(unsigned long long * charProbs)
{
  cout<<"0"<<endl;

  for (int i = 0; i <= UCHAR_MAX; i++)
    this->charProbs[i] = charProbs[i];
  cout<<"1"<<endl;

  buildArr();

}

HuffTree::~HuffTree() {}

void HuffTree::print2DUtilHelper(HuffNode *node, int space) { 
    const int COUNT = 10;
	// Base case
    if (node == NULL)
        return;
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print2DUtilHelper(node->rightChild, space);
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%llu\n", node->charCount);
    // Process left child
    print2DUtilHelper(node->leftChild, space);
}

void HuffTree::print2DUtil(HuffNode * root, int space) {
	print2DUtilHelper(root, space);
}

bool HuffTree::findMins(size_t * iL, size_t * iR, NodeList * list)
{
  if (!iL || !iR) return false;
  if (list->size < 2) return false;
  *iL = 0;
  *iR = 1;
  size_t i;

  for (i = 2; i < list->size; i++)
  {

    if ( list->at(i)->node->charCount < list->at(*iL)->node->charCount
      && list->at(i)->node->charCount < list->at(*iR)->node->charCount)
    { 
      cout<<'8'<<endl;
      list->at(*iL)->node->charCount > list->at(*iR)->node->charCount ? *iL = i : *iR = i;}

    else if (list->at(i)->node->charCount < list->at(*iL)->node->charCount) 
    {
      cout<<'9'<<endl; 
      *iL = i;
    }
    else if (list->at(i)->node->charCount < list->at(*iR)->node->charCount) 
    {
      cout<<"10"<<endl;
      *iR = i;
    }
  }
  if (list->at(*iL)->node->charCount < list->at(*iR)->node->charCount)
  {
    i   = *iR;
    *iR = *iL;
    *iL = i;
  }
  return true;
}
void HuffTree::buildBranch(size_t leftIndex, size_t rightIndex, NodeList * list)
{
  HuffNode * leftNode = list->extract(leftIndex);
  HuffNode * rightNode = list->extract(rightIndex);
  HuffNode * n;
  if (leftNode->rightChild == NULL)
    n = leftNode;
  else
  {
    n = new HuffNode();
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
    n->rightChild = rightNode->leftChild;
    n->rightArr = rightNode->leftArr;
    //delete rightNode;
    //rightNode = NULL;
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
  cout<<"3"<<endl;

  tmp->leftChild   = NULL;
  tmp->rightChild  = NULL;
  tmp->leftArr.push_back(0);
  tmp->charCount = this->charProbs[0];
  leafs->node = tmp;
  cout<<"4"<<endl;

  for (unsigned char i = 1; i <= UCHAR_MAX && i; i++)
  {
    tmp = new HuffNode();
    tmp->leftChild  = NULL;
    tmp->rightChild = NULL;
    tmp->leftArr.push_back(i);
    tmp->charCount = this->charProbs[i];
    leafs->append(tmp);
  }
  leafs->printList();
  cout<<"5"<<endl;

  while (findMins(&l, &r, leafs))
  {
    cout<<"6"<<endl;

    buildBranch(l, r, leafs);
    leafs->printList();
    cout<<"7"<<endl;

  }
  cout<<"2"<<endl;


  root = leafs->extract(0);
  cout<<"8"<<endl;

  //delete leafs;
  //leafs = NULL;
  cout<<"9"<<endl;

  return root;
}

void HuffTree::destroyNode(HuffNode * curNode)
{
  if (curNode != NULL)
  {
    destroyNode(curNode->leftChild);
    destroyNode(curNode->rightChild);
    //delete curNode->leftArr;
    //delete curNode->rightArr;
    delete curNode;
    curNode = NULL;
  }
  return;
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
  destroyNode(root);
  return;
}
vector<int>  HuffTree::encode(unsigned char inChar)
{
  return treeArr[inChar];
}
