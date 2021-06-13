#ifndef SETPATH_VISTOR_H
#define SETPATH_VISTOR_H
#include <string>
#include "node_visitor.h"

class File;
class Folder;
class Link;

class SetPathVisitor: public NodeVisitor
{
public:
    SetPathVisitor(int oldPathLen, std::string newPath): _oldPathLen(oldPathLen), _newPath(newPath){

    }
    void visitFolder(Folder *folder);
    void visitFile(File * file);
    void visitLink(Link * link);
private:
    int _oldPathLen;
    std::string _newPath;
};
#endif