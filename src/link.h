#ifndef LINK_H
#define LINK_H
#include "node.h"
#include "node_visitor.h"
#include "null_iterator.h"

class Link : public Node{
public:
  Link(const char * path, Node * node = nullptr) : Node(path)
  {
    if(!S_ISLNK(state().st_mode))
      throw std::string("error occurs");
    this->addLink(node);
  }

  void accept(NodeVisitor * icv)
  {
    icv->visitLink(this);
  }

  void addLink(Node * node)
  {
    _source = node;
  }

  Node * getSource() {
    return _source;
  }

  NodeIterator* createIterator(){
    return new NullIterator(); 
  }

private:
  Node * _source;
};

#endif
