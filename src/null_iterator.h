#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H
#include "node_iterator.h"

class Node;

class NullIterator:public NodeIterator
{
public:
    NullIterator(){

    }
    void first(){
        throw std::string("no child member");
    }
    Node* currentItem(){
        throw std::string("no child member");
    }

    void next() {
        throw std::string("no child member");
    }

    bool isDone(){
        return true;
    }
};
#endif