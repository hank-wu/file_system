#ifndef NODE_H
#define NODE_H
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "setpath_visitor.h"
#include "node_iterator.h"
#include "subject.h"

class NodeVisitor;
class FindVisitor;
class InfoContentVisitor;


class Node
{
public:
class FileSystem : public Subject {
  public:
    FileSystem(Node * root) : Subject(root){}

    //setState functions
    void setCurrentNode(Node * node){
      _root = node;
    }

    void setName(std::string newName){
      _root->fileName = newName;
      std::string nodeName;
      nodeName += _root->_path;
      std::size_t pos = nodeName.rfind("/");
      nodeName.erase(pos+1);
      nodeName+=newName;
      int result;
      const char * oldname =_root->_path;
      const char * newname = nodeName.c_str();
      result= rename( oldname , newname );

      SetPathVisitor *spv = new SetPathVisitor(strlen(_root->_path), nodeName);
      _root->accept(spv);
    }
  
    void refreshState(){
      _root->refresh();
    }

    //getState functions
    Node * getCurrentNode(){
      return _root;
    }

  };

  Node(const char * path):_path(path)
  {
    // _path = new char[strlen(path)+1];
    // strcpy(_path, path);
    if(lstat(_path, &_st) != 0)
      throw std::string("error");

    std::string nodeName = path;
    std::size_t pos = nodeName.rfind("/");
    fileName = nodeName.substr(pos+1); 
    lstat(_path, &_st);
    parent = nullptr;
  }

  std::string name() const
  {
    return fileName;
  }

  int size() const
  {
    return _st.st_size;
  }

  virtual void accept(NodeVisitor * fv) = 0;

  virtual void add(Node *node)
  {
    throw std::string("unable to add");
  }

  virtual int numberOfChildren() const
  {
    throw std::string("number of children: not applicable");
  }

  virtual NodeIterator* createIterator() = 0;

  const char * path(){
    return _path;  
  }

  Node * getParent(){
    return parent;
  }

  void * setParent(Node* p){
    parent = p;
  }

  FileSystem* createFileSystem(){
    return new FileSystem(this);
  }

  void setPath(int oldPathLen, std::string newName){
    std::string nodeName = _path;
    nodeName.erase(0, oldPathLen);
    nodeName = newName + nodeName;
    char * newPath = new char[nodeName.size()+1];
    strcpy(newPath, nodeName.c_str());
    _path = newPath;
  }

  void refresh(){
    lstat(_path, &_st);
  }

protected:
  struct stat state(){
    return _st;
  }
private:
  const char * _path;
  struct stat _st;
  std::string fileName;
  Node * parent;
};

#endif
