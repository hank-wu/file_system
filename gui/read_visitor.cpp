#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/string.h>
#include <fstream>
#include "read_visitor.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"

ReadVisitor::ReadVisitor(wxTextCtrl * text): _text(text){

}

void ReadVisitor::visitFile(File* file){
    int c;
    std::ifstream a(file->path());
    while((c = a.get()) != EOF && c <= 127){
    }
    if(c == EOF) {
        _text->LoadFile(wxString(file->path()));
    }else {
        _text->Clear();
        _text->SetValue(wxString("The file is not displayed in the editor because it uses an unsupported text encoding."));
        _text->Disable();
    }
}

void ReadVisitor::visitFolder(Folder* folder){
    _text->Clear();
    _text->Disable();
}

void ReadVisitor::visitLink(Link* link){
    _text->Clear();
    _text->SetValue(wxString("The file is not displayed in the editor because it uses an unsupported text encoding."));
    _text->Disable();
}