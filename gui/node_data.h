#ifndef NODE_DATA_H
#define NODE_DATA_H

#include<wx/wx.h>
#include<wx/treebase.h>
#include<wx/string.h>
#include"../src/node.h"

class nodeData: public wxTreeItemData
{
public:
    nodeData(wxWindow* tree, int length=600, int width=400, wxString size=wxString("123"), wxString name= wxString("test"), Node* node =NULL){
        _node = node;
        _text = new wxTextCtrl(tree, wxID_ANY, _T("initualize"),
		wxPoint(200,0), wxSize(length,width), wxTE_MULTILINE);
        _text->Hide();
        _size = size;
        _name = name;
        _label = _name + ", " + _size;
        _readed = false;
    }

    wxString getLabel(){
        return _label;
    }

    wxString getSize (){
        return _size;
    }

    wxString getName (){
        return _name;
    }

    wxTextCtrl *getText(){
        return _text;
    }

    Node * getNode(){
        return _node;
    }

    bool readed(){
        return _readed;
    }

    bool completeRead(){
        _readed = true;
    }

    void refresh(){
        wxString _name = wxString(_node->name());
        std::string tempSize = std::to_string(_node->size());
        _size = wxString(tempSize);
        _label = _name + ", " + wxString(tempSize);
    }
private:
    wxTextCtrl *_text;
    wxString _label;
    wxString _size;
    wxString _name;
    Node * _node;
    bool _readed;
};

#endif