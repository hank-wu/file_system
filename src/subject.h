#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "node.h"
#include "observer.h"

class Subject {
public:
    Subject(Node * node):_root(node){

    }

    void attach(Observer * ob) {
      _observers.push_back(ob);
    }

    void detach(Observer * ob) {
      for(int i  = 0; i < _observers.size(); i++){
        if (_observers[i] == ob) {
          _observers.erase(_observers.begin() + i);
        }
      }
    }

    int getNumberOfObservers() const {
      return _observers.size();
    }

    void notify(){
      std::vector<Observer *>::iterator it;
      for(it=_observers.begin();it != _observers.end() ; ++it){
        (*it)->update();
      }
    }
protected:
  Node * _root;
private:
  std::vector<Observer *> _observers;
  
};

#endif
