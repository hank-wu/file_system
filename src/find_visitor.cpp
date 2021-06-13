#include <iostream>
#include <string>
#include <vector>
#include "find_visitor.h"
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"

FindVisitor::FindVisitor(std::string name): _name(name){
    _findResult = "";
}

void FindVisitor::visitFile(File * file){
    _findResult = "";
    _findPath.clear();
    if(file->name() == _name){
        _findPath.push_back(file->name());
    }
}


void FindVisitor::visitFolder(Folder * folder){
    _findResult = "";
    _findPath.clear();
    NodeIterator * it = folder->createIterator();
    std::vector<std::string> result;
    std::vector<std::string> temp;
    for(it->first(); !it->isDone(); it->next()){
        temp = find(it->currentItem());
        result.insert(result.end(), temp.begin(), temp.end());
    }
    for(std::vector<std::string>::iterator _it = result.begin(); _it != result.end(); _it++){
        *_it = "./" + *_it;
    }
    _findPath = result;
}

void FindVisitor::visitLink(Link * Link){

}

std::vector<std::string>FindVisitor::find(Node* node){
    std::vector<std::string> result;
    std::vector<std::string> temp;
    if(node->name() == _name){
        result.push_back(node->name());
    }
    NodeIterator * it = node->createIterator();
    if(it->isDone()){
        return result;
    }
    for(it->first(); !it->isDone(); it->next()){
        temp = find(it->currentItem());
        for(std::vector<std::string>::iterator _it = temp.begin(); _it != temp.end(); _it++){
            *_it = "/" + *_it;
            *_it = node->name() + *_it;
        }
        result.insert(result.end(), temp.begin(), temp.end());
    }
    return result;
}


