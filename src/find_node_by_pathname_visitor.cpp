#include "find_node_by_pathname_visitor.h"
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <iostream>

void FindNodeByPathnameVisitor::visitFolder(Folder * folder){
    if((level+1) == _pathnames->end() && (*level) == folder->name()){
        result = folder;
        return;
    }else if((level+1) == _pathnames->end() && (*level) != folder->name()){
        result = nullptr;
        return;
    }

    level++;
    Node * child = folder->enterChild(*level);
    if(folder->enterChild(*level)!=nullptr){
        child->accept(this);
    }
}

void FindNodeByPathnameVisitor::visitFile(File * file){
    if ((level+1) != _pathnames->end() || (*level) != file->name()){
        result == nullptr;
    }else if((level+1) == _pathnames->end() && (*level) == file->name()){
        result = file;
    }
}

void FindNodeByPathnameVisitor::visitLink(Link * link){
    if ((level+1) != _pathnames->end() || (*level) != link->name()){
        result == nullptr;
    }else if((level+1) == _pathnames->end() && (*level) == link->name()){
        result = link;
    }
}

Node * FindNodeByPathnameVisitor::getNode() const{
    return result;
}