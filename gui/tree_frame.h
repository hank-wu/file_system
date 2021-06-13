#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/event.h>
#include <wx/msgdlg.h>
#include <iostream>
#include <map>
#include <memory>
#include "node_data.h"
#include "../src/node.h"
#include "../src/node_builder.h"
#include "buildtree_visitor.h"
#include "read_visitor.h"
#include "../src/tree_view.h"

#define TEXTLEN 600
#define TEXTWID 400

class TreeFrame : public wxFrame
{
public:
  TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height, const char * inputPath):wxFrame((wxFrame *) nullptr, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
  {
    rootPath = inputPath;
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(200,400), wxWANTS_CHARS | wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS | wxTR_HIDE_ROOT);
    _tree->Bind(wxEVT_CHAR_HOOK, &TreeFrame::OnKeyDown, this);
    saveMode = false;

    NodeBuilder nb;
    nb.build(inputPath);
    test_data = nb.getRoot();
    fs = test_data->createFileSystem();
    tv = new TreeView(fs, _tree);
    
    m_pTextCtrl = new wxTextCtrl(_tree, wxID_ANY, _T("WelCome to POSD_EDITOR"),
		wxPoint(200,0), wxSize(TEXTLEN,TEXTWID), wxTE_MULTILINE);
    m_pTextCtrl->Disable();

    rootId = _tree->AddRoot(wxT("Root"), -1,-1, new nodeData(_tree, TEXTLEN, TEXTWID));
    currentId = rootId;

    BuildtreeVisitor *bt =new BuildtreeVisitor(_tree, rootId, TEXTLEN, TEXTWID);
    test_data->accept(bt);

    saveButton = new wxButton(_tree, wxID_ANY, wxString("Save"), wxPoint(200, 400), wxSize(599, 169));
    saveButton->Disable();

    _tree->ExpandAllChildren(rootId);
    currentText = m_pTextCtrl;
    _tree->UnselectAll();
  }

void OnEdit(wxTreeEvent& event)
{
  event.Veto();
  wxString temp = event.GetLabel();
  size_t sizePos = temp.rfind(", ");
  bool pathvalid = true;
  if(temp.find("/") != wxString::npos){
    pathvalid =false;
    std::cout<<"cannot handle '/'"<<std::endl;
  }
  
  nodeData * currentItem = dynamic_cast<nodeData*>(_tree->GetItemData(event.GetItem()));
  if(temp != currentItem->getLabel() && sizePos!=wxString::npos && temp.substr(sizePos+2) == currentItem->getSize() && pathvalid){
    wxString warn("label edited: ");
    warn += temp;
    warn += wxString("-- old name was ");
    warn += currentItem->getName();
    wxMessageDialog  *confirm = new wxMessageDialog (this, warn, wxT("Confirm"), wxYES_NO | wxCANCEL);
    switch ( confirm->ShowModal() )
    {
    case wxID_YES:
      //setstate
      fs->setCurrentNode(currentItem->getNode());
      fs->setName(temp.substr(0, sizePos).ToStdString());
      tv->setTreeItem(event.GetItem());
      fs->notify();
      break;
    case wxID_NO:
      _tree->SetItemText(event.GetItem(), currentItem->getLabel());
      break;
    case wxID_CANCEL:
      _tree->SetItemText(event.GetItem(), currentItem->getLabel());
      // _tree->SetItemText(event.GetItem(), temp);
      //_tree->EditLabel( event.GetItem());
      break;
    default:
      std::cout<<"error"<<std::endl;
    }
  }else{
    _tree->SetItemText(event.GetItem(), currentItem->getLabel());
  }
  if(currentText->IsEnabled()){
    saveButton->Enable();
  }else{
    saveButton->Disable();
  }
}

void OnSelect(wxTreeEvent& event)
{
  currentText->Hide();
  currentId = event.GetItem();
  nodeData* currentItem = dynamic_cast<nodeData*>(_tree->GetItemData(event.GetItem()));
  currentText=currentItem->getText();
  if(!currentItem->readed()){
    ReadVisitor rb(currentText);
    currentItem->getNode()->accept(&rb);
    currentItem->completeRead();
  }
  if(currentText->IsEnabled()){
    saveButton->Enable();
  }else{
    saveButton->Disable();
  }
  currentText->Show();
}

void OnDbClick(wxTreeEvent& event)
{
  if(event.GetItem()!=rootId){
    wxTextCtrl * temp = _tree->EditLabel( event.GetItem());
  }
}

void OnBeginEdit(wxTreeEvent& event)
{
  saveButton->Disable();
}

void OnSave(wxCommandEvent& event)
{
  this->Save();
}

void OnKeyDown(wxKeyEvent& event)
{
  event.Skip();
  if(event.GetKeyCode() == 308){
    saveMode = true;
  }else if(event.GetKeyCode() !=308 && event.GetKeyCode() != 83){
    saveMode = false;
  }
  if(saveButton->IsEnabled() && event.GetKeyCode() == 83 && saveMode){
    event.Skip(false);
    this->Save();
  }
}

void Save(){
  nodeData* currentItem = dynamic_cast<nodeData*>(_tree->GetItemData(currentId));
  wxMessageDialog  *confirm = new wxMessageDialog (this, wxT("You want save?"), wxT("Confirm"), wxYES_NO | wxCANCEL);
  switch ( confirm->ShowModal() )
  {
    case wxID_YES:
      currentText->SaveFile(wxString(currentItem->getNode()->path()));
      //saveState
      fs->setCurrentNode(currentItem->getNode());
      fs->refreshState();
      tv->setTreeItem(currentId);
      // //notify
      fs->notify();
      break;
    case wxID_NO:
      break;
    case wxID_CANCEL:
      break;
    default:
      std::cout<<"error"<<std::endl;
  }
}

private:
  DECLARE_EVENT_TABLE()
  wxTreeCtrl *_tree;
  wxTextCtrl *m_pTextCtrl;
  wxTreeItemId rootId;
  wxTreeItemId currentId;
  wxTextCtrl *currentText;
  wxButton *saveButton;
  Node* test_data;
  const char * rootPath;
  Node::FileSystem *fs;//subject
  TreeView *tv;//observer
  bool saveMode;
};

wxBEGIN_EVENT_TABLE(TreeFrame, wxFrame)
  EVT_TREE_END_LABEL_EDIT (wxID_ANY, TreeFrame::OnEdit)
  EVT_TREE_SEL_CHANGED (wxID_ANY, TreeFrame::OnSelect)
  EVT_TREE_ITEM_ACTIVATED(wxID_ANY, TreeFrame::OnDbClick)
  EVT_TREE_BEGIN_LABEL_EDIT(wxID_ANY, TreeFrame::OnBeginEdit)
  EVT_BUTTON(wxID_ANY, TreeFrame::OnSave)
wxEND_EVENT_TABLE()

#endif
