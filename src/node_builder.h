#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string.h>

class NodeBuilder {
public:
  NodeBuilder() {
    _root = nullptr;
  }

  void build(const char * path) {
    if (lstat(path, &st) == 0) {
      if (S_ISREG(st.st_mode)){
        _root = new File(path);
      } 
      else if (S_ISLNK(st.st_mode)){
        _root = new Link(path);
      }
      else if (S_ISDIR(st.st_mode)) {
        _root = new Folder(path);
        DIR * dir = opendir(path);
        if (dir == nullptr)
          throw std::string("open folder error");

        struct dirent * entry = nullptr;
        while((entry = readdir(dir)) != nullptr) {
          if (std::string(entry->d_name) != "."
              && std::string(entry->d_name) != "..") {
            NodeBuilder nb;
            std::string temp = (std::string(path) + "/" + entry->d_name);
            char * pathName = new char[temp.size()+1];
            strcpy(pathName, temp.c_str());
            nb.build(pathName);
            _root->add(nb.getRoot());
          }
        }
      }
    }
  }

  Node * getRoot() {
    return _root;
  }

private:
  Node * _root;
  struct stat st;
};

#endif
