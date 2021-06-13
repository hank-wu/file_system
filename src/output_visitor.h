#ifndef OUTPUT_VISITOR_H
#define OUTPUT_VISITOR_H
#include "node_visitor.h"
class File;
class Folder;
class Link;

class OutputVisitor: public NodeVisitor
{
public:
  OutputVisitor(){

  }
  void visitFile(File *file);
  void visitFolder(Folder *folder);
  void visitLink(Link *link);
};

#endif
