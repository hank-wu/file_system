#ifndef FIND_LINK_VISITOR_H
#define FIND_LINK_VISITOR_H

#include <vector>
#include "node_visitor.h"
#include "node.h"

class Folder;
class File;
class Link;

class FindLinkVisitor: public NodeVisitor{
public:
    FindLinkVisitor();
    void visitFolder(Folder * folder);
    void visitFile(File * file);
    void visitLink(Link * link);
    std::vector<Node*> getLinks();

private:
    std::vector<Node*>links;
};

#endif