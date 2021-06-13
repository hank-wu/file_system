#ifndef FIND_NODE_BY_PATHNAME_H
#define FIND_NODE_BY_PATHNAME_H
#include <vector>
#include <string>
#include "node_visitor.h"

class File;
class Folder;
class Link;
class Node;

class FindNodeByPathnameVisitor : public NodeVisitor{
    public:
        FindNodeByPathnameVisitor(std::vector<std::string>* pathnames):_pathnames(pathnames){
            result = nullptr;
            level = _pathnames->begin();
        }

        void visitFolder(Folder * folder);
        void visitFile(File * file);
        void visitLink(Link * link);
        Node * getNode() const;
    private:
        std::vector<std::string>* _pathnames;
        std::vector<std::string>::iterator level;
        Node * result;
};


#endif