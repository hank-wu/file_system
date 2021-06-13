#include <vector>
#include <iostream>
#include "find_link_visitor.h"
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_visitor.h"

FindLinkVisitor::FindLinkVisitor(){
    //
}

void FindLinkVisitor::visitFile(File *file){
    
}

void FindLinkVisitor::visitFolder(Folder *folder){
    NodeIterator * it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        it->currentItem()->accept(this);
    }
}

void FindLinkVisitor::visitLink(Link *link){
    links.push_back(link);
}

std::vector<Node*>FindLinkVisitor::getLinks(){
    return links;
}