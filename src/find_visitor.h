#ifndef FIND_VISITOR
#define FIND_VISITOR
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "node_visitor.h"

class Node;
class File;
class Folder;
class Link;

class FindVisitor :public NodeVisitor
{
public:
    FindVisitor(std::string name);
    void visitFile(File * file);
    void visitFolder(Folder * folder);
    void visitLink(Link * link);
    std::string findResult(){
        std::set<std::string>temp;
        for(std::vector<std::string>::iterator it = _findPath.begin(); it != _findPath.end(); it++){
            temp.insert(*it);
        }
        for(std::set<std::string>::iterator it = temp.begin(); it != temp.end(); it++){
            _findResult += *it;
            _findResult = _findResult + "\n";
        }
        if(_findResult!=""){
            _findResult = _findResult.substr(0,_findResult.length()-1);
        }
        return _findResult;
    }

private:
    std::string _name;
    std::string _findResult;
    std::vector<std::string> _findPath;
    std::vector<std::string> find(Node* node);
};

#endif