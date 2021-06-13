#ifndef VISTOR
#define VISTOR

class File;
class Folder;
class Link;

class NodeVisitor
{
  public:
      virtual void visitFolder(Folder *folder) = 0;
      virtual void visitFile(File * file) = 0;
      virtual void visitLink(Link * link) = 0;
};
#endif