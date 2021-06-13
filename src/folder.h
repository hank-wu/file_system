#ifndef FOLDER_H
#define FOLDER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "node.h"
#include "info_content_visitor.h"
#include "node_iterator.h"
#include "node_visitor.h"
#include "find_visitor.h"

class Folder:public Node{
public:
  class FolderIterator : public NodeIterator
  {
  public:
    FolderIterator(Folder * f): _folder(f)
    {
      _it = _folder->_children.begin();
    }
    void first()
    {
      _it = _folder->_children.begin();
    }
    Node* currentItem()
    {
      if (isDone())
      {
        throw std::string("no current item");
      }
      return _it->second;
    }
    void next()
    {
      if (isDone())
      {
        throw std::string("moving past the end");
      }
      _it++;
    }
    bool isDone()
    {
      return _it == _folder->_children.end();
    }
  private:
    Folder * _folder;
    std::map<std::string, Node*>::iterator _it;
  };

  Folder(const char* path):Node(path)
  {
    if(!S_ISDIR(state().st_mode))
      throw std::string("error occurs");
  }

  void add(Node *node)
  {
    node->setParent(this);
    _children.insert(std::pair<std::string, Node*>(node->name(), node));
  }

  int numberOfChildren() const
  {
    return _children.size();
  }

  void accept(NodeVisitor * fv)
  {
    fv->visitFolder(this);
  }

  NodeIterator * createIterator()
  {
    return new FolderIterator(this);
  }

  Node * enterChild(std::string name){
    std::map<std::string, Node*>::iterator it = _children.find(name);
    if(it == _children.end()){
      return nullptr;
    }else{
      return it->second;
    }
  }

private:
  std::map<std::string, Node*>_children;
};

#endif
