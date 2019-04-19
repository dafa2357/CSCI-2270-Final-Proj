#include "HuffTree.hpp"

using namespace std;

NodeList::NodeList()
{
  next = NULL;
  node = NULL;
  size = 1;
}

void NodeList::append(HuffNode * n)
{
  NodeList * tmp = this;
  while (tmp->size-1)
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
    if (tmp->next == NULL) append(NULL);
    tmp = tmp->next;
  }
  return tmp;
}

NodeList * NodeList::operator[](size_t n)
{
  NodeList * tmp = this;
  for (size_t i = 0; i < n; i++)
  {
    if (tmp->next == NULL) append(NULL);
    tmp = tmp->next;
  }
  return tmp;
}

HuffNode * NodeList::extract(size_t n)
{
  NodeList * prv = NULL;
  NodeList * nxt = this;
  HuffNode * tmp;
  for (size_t i = 0; i < n; i++)
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
      nxt->node = NULL;
      nxt->next = NULL;
      delete nxt;
    }
    return tmp;
  }
  prv->next = nxt->next;
  nxt->next = NULL;
  delete nxt;
  return tmp;
}
