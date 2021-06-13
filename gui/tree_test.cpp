#include <wx/wx.h>
#include <sys/stat.h>
#include <iostream>
#include "tree_test.h"
#include "tree_frame.h"

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit()
{
  struct stat st;
  if(this->argc == 1){
    std::cout<<"no input path"<<std::endl;
    return false;
  }

	wxString input = this->argv[1];
  char * inputPath = new char[input.Len()+1];
  strcpy(inputPath, input.c_str());

  if(lstat(inputPath, &st)){
    std::cout<<"invalid path"<<std::endl;
    return false;
  }

  wxFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100,100,800,600, inputPath);
  frame->Show(true);
  this->SetTopWindow(frame);
  return true;
}
