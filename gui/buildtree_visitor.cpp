#include <wx/wx.h>
#include <wx/treectrl.h>
#include <string>
#include <iostream>
#include "buildtree_visitor.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/node_iterator.h"
#include "node_data.h"

BuildtreeVisitor::BuildtreeVisitor(wxTreeCtrl* tree,  wxTreeItemId rootId, int length, int width): _tree(tree), parrentId(rootId), _length(length), _width(width){

}

void BuildtreeVisitor::visitFile(File* file){
    std::string temp;
    std::string tempSize = std::to_string(file->size());
    temp = file->name() + ", " + tempSize;
    _tree->AppendItem(parrentId, wxString(temp), -1, -1, new nodeData(_tree, _length, _width, wxString(tempSize), wxString(file->name()), file));
}

void BuildtreeVisitor::visitFolder(Folder* folder){
    std::string temp;
    std::string tempSize = std::to_string(folder->size());
    temp = folder->name() + ", " + tempSize;
    parrentId = _tree->AppendItem(parrentId, wxString(temp), -1, -1, new nodeData(_tree, _length, _width, wxString(tempSize), wxString(folder->name()),folder));
    NodeIterator * it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        it->currentItem()->accept(this);
    }
    parrentId = _tree->GetItemParent(parrentId);
}

void BuildtreeVisitor::visitLink(Link* link){
    std::string temp;
    std::string tempSize = std::to_string(link->size());
    temp = link->name() + ", " + tempSize;
    _tree->AppendItem(parrentId, wxString(temp), -1, -1, new nodeData(_tree, _length, _width, wxString(tempSize), wxString(link->name()),link));
}