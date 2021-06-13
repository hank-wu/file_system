#include "setpath_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"

void SetPathVisitor::visitFile(File* file){
    file->setPath(_oldPathLen, _newPath);
    file->refresh();
}

void SetPathVisitor::visitFolder(Folder* folder){
    folder->setPath(_oldPathLen, _newPath);
    folder->refresh();
    NodeIterator * it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        it->currentItem()->accept(this);
    }
}

void SetPathVisitor::visitLink(Link* link){
    link->setPath(_oldPathLen, _newPath);
    link->refresh();
}