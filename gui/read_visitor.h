#ifndef READ_VISIOR_H
#define READ_VISIOR_H
#include "../src/node_visitor.h"
class File;
class Folder;
class Link;
class wxTextCtrl;

class ReadVisitor: public NodeVisitor
{
public:
  ReadVisitor(wxTextCtrl * text);
  void visitFile(File *file);
  void visitFolder(Folder *folder);
  void visitLink(Link *link);
private:
  wxTextCtrl * _text;
};

#endif