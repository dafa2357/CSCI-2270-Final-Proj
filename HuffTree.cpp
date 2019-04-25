#include "HuffTree.hpp"
#include <climits>
using namespace std;

HuffTree::HuffTree(unsigned long long * charProbs)
{
  for (size_t i = 0; i <= UCHAR_MAX; i++)
    this->charProbs[i] = charProbs[i];
  root = buildTree();
  buildArr();
  curDecodeNode = root;
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
        {printf(" ");}
        cout<<node->charCount<<endl;
    // Process left child
    print2DUtilHelper(node->leftChild, space);
}

void HuffTree::print2DUtil(HuffNode * root, int space) {
	print2DUtilHelper(root, space);
}

bool HuffTree::findMins(size_t * iL, size_t * iR,  NodeList * list)
{
  if (!iL || !iR) return false;
  if (list->size < 2) return false;
  *iL = 0;
  *iR = 1;
  size_t i=2;
  NodeList * lN = list;
  NodeList * rN = list->next;
  NodeList * temp = list->next->next;
  if(temp == NULL)
  {
    if (*iL < *iR)
    {
      i = *iR;
      *iR = *iL;
      *iL = i;
    }
    return true;
  }
  while( temp->next != NULL){
    if((lN->node->charCount > temp->node->charCount) && (rN->node->charCount > temp->node->charCount)){
      if(lN->node->charCount > rN->node->charCount){
        *iL = i;
        lN = temp;
      }
      else{
        *iR = i;
        rN = temp;
      }
    }
    else if( temp->node->charCount < lN->node->charCount){
      *iL = i;
      lN = temp;
    }
    else if(temp->node->charCount < rN->node->charCount){
      *iR = i;
      rN = temp;
    }
    temp = temp->next;
    i++;
  }
  if (*iL < *iR)
  {
    i = *iR;
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
  if (leftNode->rightChild == NULL&&leftNode->rightArr.size() ==0)
  {
    //cout<<"left->right=null"<<endl;
    n = leftNode;
    n->rightChild = rightNode;
    for (size_t i = 0; i < rightNode->leftArr.size(); i++)
      n->rightArr.push_back(rightNode->leftArr[i]);
    for (size_t i = 0; i < rightNode->rightArr.size(); i++)
      n->rightArr.push_back(rightNode->rightArr[i]);
    n->charCount += rightNode->charCount;
  }
  else
  {
    //cout<<"create new node"<<endl;
    n = new HuffNode();
    n->leftChild = leftNode;
    n->rightChild = rightNode;
    n->charCount = leftNode->charCount + rightNode->charCount;
    for (size_t i = 0; i < leftNode->leftArr.size(); i++)
      n->leftArr.push_back(leftNode->leftArr[i]);
    for (size_t i = 0; i < leftNode->rightArr.size(); i++)
      n->leftArr.push_back(leftNode->rightArr[i]);

    if (rightNode->rightChild == NULL&&rightNode->rightArr.size() ==0)
    {
      //cout<<"r->rc=null"<<endl;
      n->rightChild = rightNode->leftChild;
      n->rightArr = rightNode->leftArr;
      //delete rightNode;
      //rightNode = NULL;
    }
    else
    {
      //cout<<"r->rc != null"<<endl;
      for (size_t i = 0; i < rightNode->leftArr.size(); i++)
        n->rightArr.push_back(rightNode->leftArr[i]);
      for (size_t i = 0; i < rightNode->rightArr.size(); i++)
        n->rightArr.push_back(rightNode->rightArr[i]);
    }
  }
  list->append(n);
}

HuffNode * HuffTree::buildTree()
{
  size_t l,r;
  NodeList * leafs = new NodeList();
  HuffNode * tmp ;
  HuffNode * rootn;
  for (size_t i = 0; i <= UCHAR_MAX ; i++)
  {
    tmp = new HuffNode();
    tmp->leftChild  = NULL;
    tmp->rightChild = NULL;
    tmp->leftArr.push_back(i);
    tmp->charCount = this->charProbs[i];
    leafs->append(tmp);
  }
  //leafs->printList(); ////////////UNCOMMENT TO SEE BUILDING OF TREE

  while (findMins(&l, &r, leafs))
  {
    buildBranch(l, r, leafs);
    //leafs->printList();///////////UNCOMMENT TO SEE BUILDING OF TREE
  }
  rootn = leafs->extract(0);

  //delete leafs;
  //leafs = NULL;
  return rootn;
}

void HuffTree::destroyNode(HuffNode * curNode)
{
  if (curNode != NULL)
  {
    destroyNode(curNode->leftChild);
    destroyNode(curNode->rightChild);
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
      if (tmpNode->rightArr.size() == 1) break;
      tmpNode = tmpNode->rightChild;
    }
    else
    {
      if (tmpNode->leftArr.size() == 1) break;
      tmpNode = tmpNode->leftChild;
    }
  }
  return charCode;
}

void HuffTree::buildArr()
{
  for (size_t i = 0; i <= UCHAR_MAX; i++)//*shrugs*
{
    treeArr[i] = search(root, (unsigned char) i);
    //////uncomment to see the codes for individual bytes
    /*
    std::cout<<"["<<(int)i<<"]: ";
    p = treeArr[i].size();
    for(int j =0;  j<p; j++){ cout<<treeArr[i][j];}
    cout<<endl;
    */
}
  return;
}

const vector<int>  HuffTree::encode(unsigned char inChar)
{
  return treeArr[inChar];
}

bool HuffTree::decode(unsigned char * outChar, unsigned char inBits = 0)// if blank set to 0
{
  int bit =0;
  if (!leftOverBits())//parse inBits into the bitBuffer
  {
    for (int i = 7; i >= 0; i--)
    {
      bit = (int)(inBits >> i) & 1;
      this->bitBuffer.push_back(bit);
    }
  }
  do
  {
    if (bitBuffer.empty()) return false;
    bit = this->bitBuffer[0];
    this->bitBuffer.erase(bitBuffer.begin());
  } while (!decodeHelper(&outChar, bit));
  return true;
}
bool HuffTree::decodeHelper(unsigned char ** outChar, int inBit)// not compleate
{

  //cout<<"decodeHelper "<<inBit<<endl;
  //curDecodeNode->printNode();
  if (inBit)
  {
    if (curDecodeNode->rightArr.size() == 1)
    {
      **outChar = curDecodeNode->rightArr[0];
      curDecodeNode = root;
      return true;
    }
    curDecodeNode = curDecodeNode->rightChild;
  }
  else
  {
    if (curDecodeNode->leftArr.size() == 1 )
    {
      **outChar = curDecodeNode->leftArr[0];
      curDecodeNode = root;
      return true;
    }
    curDecodeNode = curDecodeNode->leftChild;
  }
  return false;
}
bool HuffTree::leftOverBits()
{
  return !bitBuffer.empty();
}
