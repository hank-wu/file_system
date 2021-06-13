#include "output_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"


void OutputVisitor::visitFile(File* file){
    std::cout<<file->name()<<std::endl;
    std::cout<<file->size()<<std::endl;
}

void OutputVisitor::visitFolder(Folder* folder){
    std::cout<<folder->name()<<std::endl;
    std::cout<<folder->size()<<std::endl;
    NodeIterator * it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        it->currentItem()->accept(this);
    }
}

void OutputVisitor::visitLink(Link* link){
    std::cout<<link->name()<<std::endl;
    std::cout<<link->size()<<std::endl;
}