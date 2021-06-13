#ifndef BUILDTREE_VISIOR_H
#define BUILDTREE_VISIOR_H
#include "../src/node_visitor.h"
class File;
class Folder;
class Link;
class wxTreeCtrl;

class BuildtreeVisitor: public NodeVisitor
{
public:
  BuildtreeVisitor(wxTreeCtrl* tree, wxTreeItemId rootId, int length = 600, int width = 400);
  void visitFile(File *file);
  void visitFolder(Folder *folder);
  void visitLink(Link *link);
private:
  wxTreeCtrl *_tree;
  wxTreeItemId parrentId;
  int _width;
  int _length;
};

#endif