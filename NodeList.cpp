#include "HuffTree.hpp"

using namespace std;

NodeList::NodeList()
{
  next = NULL;
  node = NULL;
  size = 1;
}

size_t NodeList::sizze()
{
  NodeList * tmp = this;
  size_t t = 1;
  while (tmp->next != NULL)
  {
    t++;
    tmp = tmp->next;
  }
  return t;
}
void NodeList::append(HuffNode * n)
{
  NodeList * tmp = this;
  if (this->node == NULL) 
  {
    this->node = n;
    return;
  }
  while (tmp->next != NULL)
  {
    tmp->size++;
    tmp = tmp->next;
  }
  tmp->size++;


  tmp->next = new NodeList();
  tmp->next->node = n;
}

NodeList * NodeList::at(size_t n)
{
  NodeList * tmp = this;
  for (size_t i = 0; i < n; i++)
  {
    if (tmp->next == NULL) return NULL;
    tmp = tmp->next;
  }
  return tmp;
}

NodeList * NodeList::operator[](size_t n)
{
  NodeList * tmp = this;
  for (size_t i = 0; i < n; i++)
  {
    if (tmp->next == NULL) return NULL;
    tmp = tmp->next;
  }
  return tmp;
}

HuffNode * NodeList::extract(size_t n)
{
  NodeList * prv = NULL;
  NodeList * nxt = this;
  HuffNode * tmp;
  if (nxt->sizze()<= n) return NULL;
  for (size_t i = 0; i < n ; i++)
  {
    nxt->size--;
    prv = nxt;
    nxt = nxt->next;
  }
  tmp = nxt->node;
  if (prv == NULL)
  {
    nxt = nxt->next;
    if (nxt != NULL)
    {
      this->node = nxt->node;
      this->next = nxt->next;
      this->size--;
      nxt->node = NULL;
      nxt->next = NULL;
      //!!! needs destructor !!!
//      delete nxt;
    }
    return tmp;
  }
  prv->next = nxt->next;
  nxt->next = NULL;
//  delete nxt;
  return tmp;
}
