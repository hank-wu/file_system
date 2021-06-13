#ifndef TREE_VIEW_H
#define TREE_VIEW_H
#include <wx/treectrl.h>
#include "subject.h"
#include "observer.h"
#include "../gui/node_data.h"

class TreeView : public Observer {
public:
  TreeView(Subject * subject , wxTreeCtrl * tree) : _fileSystem(subject), _tree(tree) {
    _fileSystem->attach(this);
    _updateTimes = 0;
  }

  int getUpdateTimes() const{
    return _updateTimes;
  }

  void update(){
    _updateTimes++;
    nodeData * currentItem = dynamic_cast<nodeData*>(_tree->GetItemData(_itemId));
    currentItem->refresh();
    _tree->SetItemText(_itemId, currentItem->getLabel());
    _tree->SortChildren(_tree->GetItemParent(_itemId));
  }

  void setTreeItem(wxTreeItemId itemId){
    _itemId = itemId;
  }

private:
  Subject * _fileSystem;
  int _updateTimes;
  wxTreeCtrl * _tree;
  wxTreeItemId _itemId;
};

#endif
