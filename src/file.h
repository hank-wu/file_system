#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>
#include "node.h"
#include "info_content_visitor.h"
#include "node_visitor.h"
#include "find_visitor.h"
#include "node_iterator.h"
#include "null_iterator.h"


class File: public Node{
public:
  File(const char * path): Node(path)
  {
    if(!S_ISREG(state().st_mode))
      throw std::string("error occurs");
  }

  void accept(NodeVisitor *fv)
  {
    fv->visitFile(this);
  }


  NodeIterator* createIterator(){
    return new NullIterator(); 
  }
};

#endif
