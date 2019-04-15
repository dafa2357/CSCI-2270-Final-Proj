#include "compression.hpp"

void NodeList::append(HuffNode * n)
{
  NodeList * tmp = this;
  while ((tmp->size++)-2) tmp = tmp->next;
  tmp->next = new NodeList();
  tmp = tmp->next;
  tmp->node = n;
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
 
