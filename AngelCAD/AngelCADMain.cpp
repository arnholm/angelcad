// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017-2020 Carsten Arnholm
// All rights reserved
//
// This file may be used under the terms of either the GNU General
// Public License version 2 or 3 (at your option) as published by the
// Free Software Foundation and appearing in the files LICENSE.GPL2
// and LICENSE.GPL3 included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// EndLicense:

/***************************************************************
 * Name:      AngelCADMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Carsten Arnholm
 * Created:   2016-12-25
 * Copyright: Carsten Arnholm
 * License:
 **************************************************************/

#include "AngelCADMain.h"
#include "AngelCADDoc.h"
#include "FindReplacePanel.h"
#include "SettingsDialog.h"

#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/utils.h>

#include "ConfigSaveRestore.h"
#include "AngelCADEditor.h"
#include "AngelCADCodeTemplate.h"
#include "AngelCADDropTarget.h"

#include "ce_angelscript_ex/as_args_impl.h"
#include "ConsolePanel.h"
#include "CsgFilter.h"
#include "PolyfixPanel.h"
#include "wxProcessSync.h"

#include <stdexcept>
#include <memory>

#include "images/openscad.xpm"

#include "images/angel_16x16.xpm"
#include "images/angel_32x32.xpm"
#include "images/angel_64x64.xpm"
#include "as_csg/version.h"

#include "AngelArtProvider.h"

//(*InternalHeaders(AngelCADFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(AngelCADFrame)
const long AngelCADFrame::ID_AUINOTEBOOK1 = wxNewId();
const long AngelCADFrame::ID_PANEL1 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM2 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM1 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM3 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM4 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM6 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM7 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM8 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARLABEL1 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBARITEM5 = wxNewId();
const long AngelCADFrame::ID_TEXTCTRL1 = wxNewId();
const long AngelCADFrame::ID_AUITOOLBAR1 = wxNewId();
const long AngelCADFrame::ID_PANEL2 = wxNewId();
const long AngelCADFrame::ID_MENUITEM2 = wxNewId();
const long AngelCADFrame::ID_MENUITEM1 = wxNewId();
const long AngelCADFrame::ID_MENUITEM18 = wxNewId();
const long AngelCADFrame::ID_MENUITEM19 = wxNewId();
const long AngelCADFrame::ID_MENUITEM11 = wxNewId();
const long AngelCADFrame::ID_MENUITEM17 = wxNewId();
const long AngelCADFrame::ID_MENUITEM3 = wxNewId();
const long AngelCADFrame::ID_MENUITEM4 = wxNewId();
const long AngelCADFrame::ID_MENUITEM5 = wxNewId();
const long AngelCADFrame::ID_MENUITEM13 = wxNewId();
const long AngelCADFrame::ID_MENUITEM14 = wxNewId();
const long AngelCADFrame::idMenuQuit = wxNewId();
const long AngelCADFrame::ID_MENUITEM6 = wxNewId();
const long AngelCADFrame::ID_MENUITEM7 = wxNewId();
const long AngelCADFrame::ID_MENUITEM8 = wxNewId();
const long AngelCADFrame::ID_MENUITEM12 = wxNewId();
const long AngelCADFrame::ID_MENUITEM9 = wxNewId();
const long AngelCADFrame::ID_MENUITEM10 = wxNewId();
const long AngelCADFrame::ID_MENUITEM15 = wxNewId();
const long AngelCADFrame::ID_MENUITEM16 = wxNewId();
const long AngelCADFrame::idMenuAbout = wxNewId();
const long AngelCADFrame::ID_STATUSBAR1 = wxNewId();
//*)

const long AngelCADFrame::ID_POPUP_CLOSE_ALL_BUT_THIS = wxNewId();

BEGIN_EVENT_TABLE(AngelCADFrame,wxFrame)
    //(*EventTable(AngelCADFrame)
    //*)
    EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, AngelCADFrame::OnMRUFile)
END_EVENT_TABLE()


AngelCADFrame* AngelCADFrame::m_self=0;

AngelCADFrame::AngelCADFrame(wxWindow* parent,wxWindowID id)
: m_config(0)
, m_popup_page(-1)
{
    m_self = this;

    wxArtProvider::PushBack(new AngelArtProvider);

    //(*Initialize(AngelCADFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1100,1000));
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxPoint(83,350), wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
    AuiManager1->AddPane(AuiNotebook1, wxAuiPaneInfo().Name(_T("PaneName")).CenterPane().Caption(_("Pane caption")));
    m_console = new ConsolePanel(this, ID_PANEL1, wxDefaultPosition, wxSize(-1,150), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    AuiManager1->AddPane(m_console, wxAuiPaneInfo().Name(_T("Console")).DefaultPane().Caption(_("Console")).CaptionVisible().CloseButton(false).Bottom().TopDockable(false).LeftDockable(false).RightDockable(false).Floatable(false).BestSize(wxSize(-1,150)).Movable(false));
    AuiToolBar1 = new wxAuiToolBar(this, ID_AUITOOLBAR1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    m_args_ctrl = new wxTextCtrl(AuiToolBar1, ID_TEXTCTRL1, wxEmptyString, wxPoint(272,8), wxSize(500,-1), wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    m_args_ctrl->SetHelpText(_("Clear Script arguments"));
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM2, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("New source file"), _("New source file"), NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM1, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Open existing source file"), _("Open existing source file"), NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM3, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save current source file"), _("Save current source file"), NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM4, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_FILE_SAVE_AS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save current source file to another name"), _("Save current source file to another name"), NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM6, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_GO_FORWARD")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Build current file"), _("Build current file"), NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM7, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_KILL")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Stop current build"), _("Stop current build"), NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM8, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxSTD_CUBE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View model"), _("View model"), NULL);
    AuiToolBar1->AddSeparator();
    AuiToolBar1->AddLabel(ID_AUITOOLBARLABEL1, _("args:"));
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM5, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_CUT")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Clear script arguments"), _("Clear script arguments"), NULL);
    AuiToolBar1->AddControl(m_args_ctrl, _("Item label"));
    AuiToolBar1->Realize();
    AuiManager1->AddPane(AuiToolBar1, wxAuiPaneInfo().Name(_T("ToolBarPane")).ToolbarPane().Caption(_("Pane caption")).Layer(10).Top().Resizable().Gripper());
    m_find_replace = new FindReplacePanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    AuiManager1->AddPane(m_find_replace, wxAuiPaneInfo().Name(_T("FindReplacePane")).DefaultPane().Caption(_("Find & Replace")).CaptionVisible().Top().Hide());
    AuiManager1->Update();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem4 = new wxMenuItem(Menu1, ID_MENUITEM2, _("New ...\tCtrl+N"), _("New AngelCAD source file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Open...\tCtrl+O"), _("Open AngelCAD source file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem19 = new wxMenuItem(Menu1, ID_MENUITEM18, _("Import 2d DXF,,,"), _("Import 2d DXF"), wxITEM_NORMAL);
    Menu1->Append(MenuItem19);
    MenuItem20 = new wxMenuItem(Menu1, ID_MENUITEM19, _("Repair Mesh file(s)..."), _("Repair Mesh file(s)"), wxITEM_NORMAL);
    Menu1->Append(MenuItem20);
    Menu1->AppendSeparator();
    MenuItem12 = new wxMenuItem(Menu1, ID_MENUITEM11, _("Open Source Folder..."), _("Open file browser in source file folder"), wxITEM_NORMAL);
    Menu1->Append(MenuItem12);
    MenuItem18 = new wxMenuItem(Menu1, ID_MENUITEM17, _("Open Libraries Folder..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem18);
    Menu1->AppendSeparator();
    MenuItem5 = new wxMenuItem(Menu1, ID_MENUITEM3, _("Save\tCtrl+S"), _("Save current file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu1, ID_MENUITEM4, _("Save As...\tCtrl+Alt+S"), _("Save current file as..."), wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu1, ID_MENUITEM5, _("Save All\tCtrl+Shift+S"), _("Save All files"), wxITEM_NORMAL);
    Menu1->Append(MenuItem7);
    MenuItem15 = new wxMenu();
    MenuItem14 = new wxMenuItem(MenuItem15, ID_MENUITEM13, _("Remove Current File"), wxEmptyString, wxITEM_NORMAL);
    MenuItem15->Append(MenuItem14);
    Menu1->Append(ID_MENUITEM14, _("History"), MenuItem15, wxEmptyString);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem8 = new wxMenuItem(Menu3, ID_MENUITEM6, _("Find/Replace...\tCtrl+F"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    MenuBar1->Append(Menu3, _("Search"));
    Menu4 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu4, ID_MENUITEM7, _("Compile AngelScript\tF5"), _("Compile"), wxITEM_NORMAL);
    Menu4->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu4, ID_MENUITEM8, _("Build Current File\tF6"), _("Build"), wxITEM_NORMAL);
    Menu4->Append(MenuItem10);
    MenuBar1->Append(Menu4, _("Build"));
    Menu5 = new wxMenu();
    MenuItem13 = new wxMenuItem(Menu5, ID_MENUITEM12, _("View STL/AMF/DXF\tF7"), _("Run STL/AMF/DXF viewer"), wxITEM_NORMAL);
    Menu5->Append(MenuItem13);
    MenuItem11 = new wxMenuItem(Menu5, ID_MENUITEM9, _("View OpenSCAD CSG\tF8"), _("View OpenSCAD CSG"), wxITEM_NORMAL);
    Menu5->Append(MenuItem11);
    Menu6 = new wxMenuItem(Menu5, ID_MENUITEM10, _("Settings ..."), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(Menu6);
    MenuBar1->Append(Menu5, _("Tools"));
    Menu2 = new wxMenu();
    MenuItem16 = new wxMenuItem(Menu2, ID_MENUITEM15, _("Online documentation...\tShift+F1"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(Menu2, ID_MENUITEM16, _("Show License..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem17);
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    m_statusbar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    m_statusbar->SetFieldsCount(1,__wxStatusBarWidths_1);
    m_statusbar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(m_statusbar);

    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE,(wxObjectEventFunction)&AngelCADFrame::OnAuiNotebookPageClose);
    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED,(wxObjectEventFunction)&AngelCADFrame::OnAuiNotebookPageClosed);
    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&AngelCADFrame::OnAuiNotebookPageChanged);
    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_DOWN,(wxObjectEventFunction)&AngelCADFrame::OnAuiNotebook1TabRightDown);
    Connect(ID_AUITOOLBARITEM2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnFileNew);
    Connect(ID_AUITOOLBARITEM1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnFileOpen);
    Connect(ID_AUITOOLBARITEM3,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnFileSave);
    Connect(ID_AUITOOLBARITEM4,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnFileSaveAs);
    Connect(ID_AUITOOLBARITEM6,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnBuildCurrentFile);
    Connect(ID_AUITOOLBARITEM7,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnKillProcess);
    Connect(ID_AUITOOLBARITEM8,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnViewSTL_AMF_DXF);
    Connect(ID_AUITOOLBARITEM5,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelCADFrame::OnAuiToolBarItemCutTextClick);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnFileNew);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnFileOpen);
    Connect(ID_MENUITEM18,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnImportDXF);
    Connect(ID_MENUITEM19,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnRepairMeshFile);
    Connect(ID_MENUITEM11,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnOpenContainingFolder);
    Connect(ID_MENUITEM17,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnOpenLibrariesFolder);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnFileSave);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnFileSaveAs);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnFileSaveAll);
    Connect(ID_MENUITEM13,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnRemoveFromMRU);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnQuit);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnFindReplace);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnCompileAngelScript);
    Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnBuildCurrentFile);
    Connect(ID_MENUITEM12,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnViewSTL_AMF_DXF);
    Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnRunOpenSCAD);
    Connect(ID_MENUITEM10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnSettings);
    Connect(ID_MENUITEM15,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnOnlineDocumentation);
    Connect(ID_MENUITEM16,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnLicenseSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelCADFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AngelCADFrame::OnClose);
    //*)


    m_config = new wxConfig(wxT("AngelCAD"),wxT("angelcad"));
    m_mru.Load(*m_config);
    m_mru.UseMenu(Menu1);
    m_mru.AddFilesToMenu();

       // Drag & drop support
    SetDropTarget(new AngelCADDropTarget());

    ConfigSaveRestore helper(this,m_config);
    DOC()->RestoreConfig(helper);
    m_args_ctrl->ChangeValue(DOC()->GetArguments());
    DOC()->GetFilesOpen(m_files_open,m_files_index);

    wxIconBundle icons;
    icons.AddIcon(wxIcon(angel_16x16_xpm));
    icons.AddIcon(wxIcon(angel_32x32_xpm));
    icons.AddIcon(wxIcon(angel_64x64_xpm));
    SetIcons(icons);

    SetTitle("[AngelCAD] " + wxString::Format(wxT(AS_CSG_version)));

}

void AngelCADFrame::AddStartupFile(wxFileName& fname)
{
   // this is typically called from AngelCADApp
   // to provide a command line file name

   fname.Normalize();
   wxString fullpath = fname.GetFullPath();
   if(!fname.Exists()) {
      wxMessageBox(fullpath, wxT("File does not exist"), wxOK, this);
   }

   bool found = false;
   if(fullpath.Length() > 0) {
      for(size_t i=0; i<m_files_open.size(); i++){
         if(fullpath == m_files_open[i].GetFullPath()) {
            m_files_index = i;
            found = true;
         }
      }
      if(!found) {
         m_files_open.push_back(fname);
         m_files_index = m_files_open.size()-1;
      }
   }
}

void AngelCADFrame::OnMainEventLoopEnter()
{
   // called from AngelCADApp when the main event loop has started

   // we can now open editor windows that watch for file modifications
   // these watchers require the main event loop to run

   bool open_new = true;

   if(m_files_open.size() > 0) {

      for(auto file : m_files_open)  {
         if(file.Exists()) DoSourceFileOpen(file.GetFullPath());
         open_new = false;
      }
      if(m_files_index < m_files_open.size())SelectFile(m_files_open[m_files_index].GetFullPath());
   }
   else {

      // no previous files recorded as open, but this
      // might be a user of an older version of AngelCAD
      // and if so there might be files in the file history.
      // Open the most recent one that exists
      for(size_t i=0; i<m_mru.GetCount(); i++) {
         wxFileName file(m_mru.GetHistoryFile(i));
         if(file.Exists()) {
            DoSourceFileOpen(file.GetFullPath());
            open_new = false;
            break;
         }
      }
   }

   // No file was opened, probably a new user
   if(open_new) DoSourceFileNew();
}

AngelCADFrame::~AngelCADFrame()
{
   m_mru.Save(*m_config);
   delete m_config;

   // shut down AUI
   AuiManager1->UnInit();

    //(*Destroy(AngelCADFrame)
    //*)
}


void AngelCADFrame::AddFileToHistory(wxFileName filename)
{
   // it looks like sorting like below does not work
   // sorting seems to be dependent on tab order

   for(size_t i=0; i<m_mru.GetCount();i++) {
      wxFileName fname(m_mru.GetHistoryFile(i));

      // if the file is already there, remove and and
      // add it again to promote it to the top
      if(fname == filename){
         m_mru.RemoveFileFromHistory(i);
         break;
      }
   }
   m_mru.AddFileToHistory(filename.GetFullPath());
}

void AngelCADFrame::RemoveFileFromHistory(wxFileName filename)
{
   for(size_t i=0; i<m_mru.GetCount();i++) {
      wxFileName fname(m_mru.GetHistoryFile(i));

      // if the file is already there, remove and and
      // add it again to promote it to the top
      if(fname == filename){
         m_mru.RemoveFileFromHistory(i);
         break;
      }
   }
}

void AngelCADFrame::OnClose(wxCloseEvent& event)
{
   m_console->KillJobs();

   std::vector<wxFileName> files_open;
   for(size_t ipage=0; ipage<AuiNotebook1->GetPageCount(); ipage++) {
      AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetPage(ipage));
      if(page->IsModified()) {
         wxString message = "'" + page->FileName().GetFullName() + "' is modified, but not saved.";
         if(wxYES == wxMessageBox(wxT("Do you want to save it now?"), message, wxYES_NO, this)) {
            bool warn_for_unmodified = false;
            DoFileSave(page,warn_for_unmodified);
         }
      }

      files_open.push_back(page->FileName());
   }
   int index = AuiNotebook1->GetSelection();

   ConfigSaveRestore helper(this,m_config);
   DOC()->SetFilesOpen(files_open,index);
   DOC()->SetArguments(m_args_ctrl->GetValue());
   DOC()->SaveConfig(helper);

   event.Skip();
}


void AngelCADFrame::OnQuit(wxCommandEvent& event)
{
    Close();
    event.Skip();
}

void AngelCADFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxString::Format("AngelCAD %s\n",wxT(AS_CSG_version))
                 + wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


bool AngelCADFrame::SelectFile(const wxString& as_path)
{
   for(size_t ipage=0; ipage<AuiNotebook1->GetPageCount(); ipage++) {
      AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetPage(ipage));
      wxString path = page->FileName().GetFullPath();
      if(path == as_path) {
         AuiNotebook1->SetSelection(ipage);
         return true;
      }
   }
   return false;
}


bool AngelCADFrame::DoSourceFileOpen(const wxString& as_path, bool close_all_others)
{
   if(!SelectFile(as_path)) {

      wxFileName fname(as_path);
      try{
         if(close_all_others) {
            AuiNotebook1->DeleteAllPages();
         }
         AngelCADEditor* page = new AngelCADEditor(AuiNotebook1);
         wxString page_title = fname.GetFullName();
         AuiNotebook1->AddPage(page,page_title,true);
         if(page->OpenFile(fname)) {
            m_console->Clear();
            wxDateTime dtmod = page->FileName().GetModificationTime();
            m_statusbar->SetStatusText(page->FileName().GetFullPath()+ " - Modified: " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime());
            SetTitle(page->FileName().GetFullPath() +" - AngelCAD " + wxString::Format(wxT(AS_CSG_version)));

            if(fname.GetExt() == "as" || fname.GetExt() == "scad") {
               AddFileToHistory(fname);

               DOC()->SetSaveDir(fname.GetPath());
            }
            return true;
         }
      }
      catch(std::exception ex) {
         wxMessageBox(ex.what(), wxT("Exception during source file load"));
      }

      // file failed to load, remove from history
      for(size_t i=0; i<m_mru.GetCount(); i++) {
         if(m_mru.GetHistoryFile(i) == fname.GetFullPath()) {
            m_mru.RemoveFileFromHistory(i);
            break;
         }
      }

      return false;
   }
   return true;
}

void AngelCADFrame::OnMRUFile(wxCommandEvent& event)
{
   wxString as_file(m_mru.GetHistoryFile(event.GetId() - wxID_FILE1));
   if (!as_file.empty()) {
      DoSourceFileOpen(as_file);
   }
}


void AngelCADFrame::OnRemoveFromMRU(wxCommandEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage()))  {
      wxFileName fname = page->FileName();
      for(size_t i=0; i<m_mru.GetCount(); i++) {
         if(m_mru.GetHistoryFile(i) == fname.GetFullPath()) {
            m_mru.RemoveFileFromHistory(i);
            break;
         }
      }
   }
}

void AngelCADFrame::OnAuiNotebookPageChanged(wxAuiNotebookEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage()))  {
      wxFileName fname =  page->FileName();
      if(fname.Exists()) {
         wxDateTime dtmod = page->FileName().GetModificationTime();
         m_statusbar->SetStatusText(page->FileName().GetFullPath()+ " - Modified: " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime());
         AddFileToHistory(fname);
      }
      else  {
         m_statusbar->SetStatusText(page->FileName().GetFullPath() + " - File has not been saved");
      }
      SetTitle(page->FileName().GetFullPath() +" - AngelCAD " + wxString::Format(wxT(AS_CSG_version)));
   }
   else {
      m_statusbar->SetStatusText("");
      SetTitle("AngelCAD " + wxString::Format(wxT(AS_CSG_version)));
   }
}

void AngelCADFrame::OnAuiNotebookPageClose(wxAuiNotebookEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage()))  {
      if(page->IsModified()) {

          wxString message = "The file has been modified, do you want to save the changes?";
          int answer = wxMessageBox(message, wxT("Please Confirm"), wxYES_NO | wxCANCEL, this);
          if (answer == wxYES) {
             DoFileSave(page);
          }

          // veto the close event if the user decided to cancel the page close
          if (answer == wxCANCEL) {
             event.Veto();
          }
      }
   }
}

void AngelCADFrame::OnAuiNotebookPageClosed(wxAuiNotebookEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage()))    {
      wxFileName fname =  page->FileName();
      if(fname.Exists()) {
         wxDateTime dtmod = fname.GetModificationTime();
         m_statusbar->SetStatusText(fname.GetFullPath()+ " - Modified: " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime());
         SetTitle(page->FileName().GetFullPath() +" - AngelCAD " + wxString::Format(wxT(AS_CSG_version)));
      }
      else {
         m_statusbar->SetStatusText("");
         SetTitle("[AngelCAD] " + wxString::Format(wxT(AS_CSG_version)));
      }
   }
   else {
      m_statusbar->SetStatusText("");
      SetTitle("[AngelCAD] " + wxString::Format(wxT(AS_CSG_version)));
   }
}

bool AngelCADFrame::DoSourceFileNew()
{
   AngelCADEditor* page = new AngelCADEditor(AuiNotebook1);
   wxString page_title = wxString::Format("New %d",static_cast<int>(AuiNotebook1->GetPageCount()+1));
   AuiNotebook1->AddPage(page,page_title,true);
   page->AddText(AngelCADCodeTemplate::GetCSGText());
//   page->DiscardEdits();    // by not doing this, the page is marked as modified
 //  page->SetModified(true); // not implemented, causes crash
   return true;
}

void AngelCADFrame::OnFileNew(wxCommandEvent& event)
{
   DoSourceFileNew();
}


void AngelCADFrame::OnFileOpen(wxCommandEvent& event)
{
   wxString default_dir = DOC()->GetSaveDir();
   wxFileDialog dlg(this,wxT("Open source file"),default_dir,wxT(""),wxT("AngelCAD/OpenSCAD source files (*.as;*.scad)|*.as;*.scad|AngelCAD source file (*.as)|*.as|OpenSCAD source file (*.scad)|*.scad|All files (*.*)|*.*"),wxFD_OPEN|wxFD_FILE_MUST_EXIST);
   if(dlg.ShowModal() == wxID_OK) {
      wxArrayString paths;

      dlg.GetPaths(paths);
      DoSourceFileOpen(paths[0]);
   }
}

void AngelCADFrame::OnImportDXF(wxCommandEvent& event)
{
   wxString default_dir = DOC()->GetSaveDir();
   wxFileDialog dlg(this,wxT("DXF file"),default_dir,wxT(""),wxT("DXF file (*.dxf)|*.dxf;*.DXF|All files (*.*)|*.*"),wxFD_OPEN|wxFD_FILE_MUST_EXIST);
   if(dlg.ShowModal() == wxID_OK) {
      wxArrayString paths;
      dlg.GetPaths(paths);

      DoImportDXF(paths[0]);
   }
}

void AngelCADFrame::OnFileSave(wxCommandEvent& event)
{
   DoFileSave(0,false);
}

void AngelCADFrame::OnFileSaveAs(wxCommandEvent& event)
{
   DoFileSaveAs();
}

bool AngelCADFrame::DoFileSave(AngelCADEditor* page, bool warn_for_unmodified )
{
   if(page == 0) page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage());
   if(page) {

      wxString path = page->FileName().GetFullPath();
      if(page->IsModified() || (path.Length() == 0)) {
         if(path.Length() > 0) {
            if( page->SaveFile(path)) {
               wxFileName fname(path);
               SetTitle(fname.GetFullPath() +" - AngelCAD " + wxString::Format(wxT(AS_CSG_version)));
               wxDateTime dtmod = fname.GetModificationTime();
               m_statusbar->SetStatusText(fname.GetFullPath()+ " - Modified: " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime());
               AddFileToHistory(fname);
               return true;
            }
         }
         else {
            return DoFileSaveAs(page);
         }
      }
      else {
         if(warn_for_unmodified) {
            wxString message = "The source code has not been been modified, use File->Save As.. if you want to save to a new file\n" + path;
            wxMessageBox(message, wxT("Please Confirm"), wxOK, this);
         }
         else {
            // m_console->AppendText("The file was not modified: " + path);
         }
      }
   }
   return false;
}

bool AngelCADFrame::DoFileSaveAs(AngelCADEditor* page)
{
   if(page == 0) page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage());

   if(page) {
      int index = AuiNotebook1->GetPageIndex(page);

      wxFileName fname     = page->FileName();
      wxString defaultname = fname.GetFullName();
      defaultname.Replace(" ","_");

      // default is to save to the same dir as previous save
      wxString local_path = DOC()->GetSaveDir();

      wxFileDialog dlg(this,wxT("AngelCAD source"),local_path,defaultname,wxT("AngelCAD source file (*.as)|*.as"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
      if(dlg.ShowModal() == wxID_OK) {
         wxFileName path(dlg.GetPath());
         if(path.GetFullPath().Length() > 0) {

            // make sure there is a file extension
            if(path.GetExt().Length()==0)path.SetExt("as");

            if(page->SaveFileAs(path)) {
               AuiNotebook1->SetPageText(index,path.GetFullName());

               SetTitle(path.GetFullPath() +" - AngelCAD " + wxString::Format(wxT(AS_CSG_version)));
               wxDateTime dtmod = path.GetModificationTime();
               m_statusbar->SetStatusText(path.GetFullPath()+ " - Modified: " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime());
               AddFileToHistory(path);

               DOC()->SetSaveDir(path.GetPath());
               return true;
            }
         }
      }
   }
   return false;
}

void AngelCADFrame::OnFileSaveAll(wxCommandEvent& event)
{
   DoFileSaveAll();
}

bool AngelCADFrame::DoFileSaveAll()
{
   for(size_t ipage=0; ipage<AuiNotebook1->GetPageCount(); ipage++) {
      AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetPage(ipage));
      bool warn_for_unmodified = false;
      DoFileSave(page,warn_for_unmodified);
   }
   return true;
}


bool AngelCADFrame::ExecutableCheck(const wxFileName& exec, wxString& message)
{
   bool exists = exec.Exists();
   bool executable = false;
   message = exec.GetFullPath();
   if(exists) {
      message += "   ==> exists";
      executable = exec.IsFileExecutable();
      if(executable)  {
         message += ", executable (OK)";
         return true;
      }
      else {
         message += ", but NOT executable";
      }
   }
   else {
      message += "   ==> FILE NOT FOUND";
   }
   return false;
}

void AngelCADFrame::OnCompileAngelScript(wxCommandEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      wxFileName path(page->FileName());
      wxString ext = path.GetExt().MakeLower();
      if(ext != "as") {
         wxString message = "Please use Build (F6) for other source types than AngelCAD";
         int answer = wxMessageBox(message, wxT("File is not AngelCAD source file"), wxOK, this);
         return;
      }

      bool can_execute = true;
      if(page->IsModified())  can_execute = DoFileSave(page);

      if(can_execute) {

         wxFileName as_csg = DOC()->GetConfigFilePath(ConfigEnums::AS_CSG);
         wxString message;
         if(ExecutableCheck(as_csg,message)) {

            wxFileName as_path(page->FileName());
/*
            wxFileName xcsg_path(DOC()->GetXcsgFileName(as_path));
            if(xcsg_path.Exists()) {
               wxDateTime as_time   = as_path.GetModificationTime();
               wxDateTime xcsg_time = xcsg_path.GetModificationTime();
               if(as_time.IsEarlierThan(xcsg_time)) {
                   wxString message = "The .xcsg target file is already up-to-date, do you still want to build?";
                   int answer = wxMessageBox(message, wxT("Please Confirm"), wxYES_NO, this);
                   if (answer != wxYES) return;
               }
            }
*/
            // create the list of jubs to run (1)
            std::list<ConsolePanel::JobPair> jobs;

            // Angelscript compilation
            wxString cmd = "\"" + as_csg.GetFullPath() + "\"  \"" + as_path.GetFullPath() + "\" -outsub=\"" + DOC()->GetOutSubDir().GetFullPath() + "\"";

            wxString include_path = DOC()->GetLibraryDir().GetPath();
            if(include_path.length() > 0) {
               cmd +=  " -include=\"" + include_path + "\" ";
            }

            jobs.push_back(std::make_pair(cmd,page));

            // submit the jobs in the list
            m_console->Execute(jobs);
         }
         else {
            wxMessageBox(message, wxT("as_csg could not execute"), wxOK, this);

            SettingsDialog dlg(this);
            dlg.SetInitialPage(SettingsDialog::ExternalFiles);
            dlg.ShowModal();
         }
      }
      else {
         m_console->AppendText("Compilation cancelled by user.");
      }
   }
}

void AngelCADFrame::OnBuildCurrentFile(wxCommandEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      DoFileSaveAll();
      wxFileName path(page->FileName());
      wxString ext = path.GetExt().MakeLower();
      if(ext == "as") DoBuildAngelCAD();
      else if(ext == "scad") DoBuildOpenSCAD();
   }
}

void AngelCADFrame::DoBuildAngelCAD()
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      wxFileName as_path(page->FileName());
      wxString ext = as_path.GetExt().MakeLower();
      if(ext != "as")return;

      bool can_execute = true;

      // save all pages in case of multifile project where an include file has been edited, but not saved
      DoFileSaveAll();

      if(can_execute) {
         // check existence of executables
         wxFileName as_csg = DOC()->GetConfigFilePath(ConfigEnums::AS_CSG);
         wxFileName xcsg = DOC()->GetConfigFilePath(ConfigEnums::XCSG);
         wxString as_csg_message,xcsg_message;

         if( ExecutableCheck(as_csg,as_csg_message) &&  ExecutableCheck(xcsg,xcsg_message) ) {

            wxFileName xcsg_path(DOC()->GetXcsgFileName(as_path));

/*
            if(xcsg_path.Exists()) {
               wxDateTime as_time   = as_path.GetModificationTime();
               wxDateTime xcsg_time = xcsg_path.GetModificationTime();
               if(as_time.IsEarlierThan(xcsg_time)) {
                   wxString message = "The .xcsg target file is already up-to-date, do you still want to build?";
                   int answer = wxMessageBox(message, wxT("Please Confirm"), wxYES_NO, this);
                   if (answer != wxYES) return;
               }
            }
*/

            // create the list of jubs to run (2)
            std::list<ConsolePanel::JobPair> jobs;


            // Angelscript compilation
            wxString cmd1 = "\"" + as_csg.GetFullPath() + "\"  \"" + as_path.GetFullPath() + "\" -outsub=\"" + DOC()->GetOutSubDir().GetFullPath() + "\"";

            wxString include_path = DOC()->GetLibraryDir().GetPath();
            if(include_path.length() > 0) {
               cmd1 +=  " -include=\"" + include_path + "\" ";
            }

            wxString args = m_args_ctrl->GetLineText(0);
            if(args.length() > 0) {
               cmd1 +=  " -args=\"" + args + "\" ";
            }

            jobs.push_back(std::make_pair(cmd1,page));

            // XCSG compilation
            wxString options = DOC()->GetXcsgFormatOptionString();
            wxString export_options = DOC()->GetExportOptionString();
            wxString cmd2 = "\"" + xcsg.GetFullPath() + "\"" + options + " \"" + xcsg_path.GetFullPath() + "\" "+export_options;
            jobs.push_back(std::make_pair(cmd2,page));

            // submit the jobs in the list
            m_console->Execute(jobs);
         }
         else {
            wxString message = as_csg_message +'\n' + xcsg_message;
            wxMessageBox(message, wxT("as_csg and/or xcsg could not execute"), wxOK, this);

            SettingsDialog dlg(this);
            dlg.SetInitialPage(SettingsDialog::ExternalFiles);
            dlg.ShowModal();
         }
      }
      else {
         m_console->AppendText("Compilation cancelled by user.");
      }
   }

}

void AngelCADFrame::DoBuildOpenSCAD()
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      m_console->Clear();

      wxFileName source_path(page->FileName());
      wxString ext = source_path.GetExt().MakeLower();
      if(ext != "scad")return;

      bool can_execute = true;

      // save all pages in case of multifile project where an include file has been edited, but not saved
      DoFileSaveAll();

      if(can_execute) {
         // check existence of executables
         wxFileName scad   = DOC()->GetConfigFilePath(ConfigEnums::OPENSCAD);
         wxFileName csgfix = DOC()->GetConfigFilePath(ConfigEnums::CSGFIX);
         wxFileName xcsg   = DOC()->GetConfigFilePath(ConfigEnums::XCSG);
         wxString scad_message,csgfix_message, xcsg_message;

         if( ExecutableCheck(scad,scad_message)
         &&  ExecutableCheck(csgfix,csgfix_message)
         &&  ExecutableCheck(xcsg,xcsg_message) ) {

            // set the output format for OpenSCAD to be *.csg
            wxFileName csg_path(DOC()->GetXcsgFileName(source_path));
            csg_path.SetExt("csg");

            // we have to create the output directory because openscad won't do it
            if(!wxFileName::Exists(csg_path.GetPath()))wxMkdir(csg_path.GetPath());

            // create the list of jubs to run (3)
            std::list<ConsolePanel::JobPair> jobs;

            // remove existing .csg in case it already exists
            if(csg_path.Exists()) {
               wxRemoveFile(csg_path.GetFullPath());
            }

            // OpenSCAD compilation to *.csg
            wxString cmd1 = "\"" + scad.GetFullPath() + "\"  \"" + source_path.GetFullPath() + "\" --o=\"" + csg_path.GetFullPath() + "\"";
            jobs.push_back(std::make_pair(cmd1,page));

            // csgfix compilation to *.csg
            wxString cmd2 = "\"" + csgfix.GetFullPath() + "\"  -scad=\"" + source_path.GetFullPath() + "\" -csg=\"" + csg_path.GetFullPath() + "\"";
            jobs.push_back(std::make_pair(cmd2,page));

            // XCSG compilation, using *.csg as input
            wxString options = DOC()->GetXcsgFormatOptionString();
            wxString export_options = DOC()->GetExportOptionString();

            // check for secant_tolerance parameter
            wxString args = m_args_ctrl->GetLineText(0);
            if(args.length() > 0) {
               as_args_impl parser;
               parser.parse(args.ToStdString());
               if(parser.has_argument("secant_tolerance")) {
                  double secant_tolerance = parser.get_double("secant_tolerance");
                  options += wxString::Format(" --sec_tol=%f",secant_tolerance);
               }
               else if(parser.has_argument("sec_tol")) {
                  double secant_tolerance = parser.get_double("sec_tol");
                  options += wxString::Format(" --sec_tol=%f",secant_tolerance);
               }
            }
            wxString cmd3 = "\"" + xcsg.GetFullPath() + "\"" + options + " \"" + csg_path.GetFullPath() + "\" "+export_options;
            jobs.push_back(std::make_pair(cmd3,page));

            // submit the jobs in the list
            m_console->Execute(jobs,false);
         }
         else {
            wxString message = scad_message +'\n' + xcsg_message;
            wxMessageBox(message, wxT("OpenSCAD and/or xcsg could not execute"), wxOK, this);

            SettingsDialog dlg(this);
            dlg.SetInitialPage(SettingsDialog::ExternalFiles);
            dlg.ShowModal();
         }
      }
      else {
         m_console->AppendText("Compilation cancelled by user.");
      }
   }
}


void AngelCADFrame::OnKillProcess(wxCommandEvent& event)
{
   m_console->KillJobs();
}


void AngelCADFrame::OnRunOpenSCAD(wxCommandEvent& event)
{

   wxFileName openscad = DOC()->GetConfigFilePath(ConfigEnums::OPENSCAD);
   wxString message;
   if(!ExecutableCheck(openscad,message)){
      wxMessageBox(message, wxT("OpenSCAD could not execute"), wxOK, this);

      SettingsDialog dlg(this);
      dlg.SetInitialPage(SettingsDialog::ExternalFiles);
      dlg.ShowModal();
   }


   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      wxFileName source   = page->FileName();
      wxFileName csg_file = DOC()->GetXcsgFileName(source).GetFullPath();
      csg_file.SetExt("csg");
      wxLongLong target_millis = 0;
      if(csg_file.Exists() && TargetUpToDate(page, source,csg_file,target_millis) ) {

         // Process the file. Encapsulated path in quotes to accomodate spaces
         wxString cmd = "\"" + openscad.GetFullPath() + "\"  \"" + csg_file.GetFullPath() + "\"";
         m_console->AppendText(cmd);
         wxExecute(cmd);
      }
      else {
         wxString message = "Please rebuild the source file to create it (F6)";
         if(page->IsModified()) message += "\nThe source has been edited but was not saved/rebuilt.";
         else                   message += "\nEither the target file does not exist or is out of date.";
                                message += "\nCSG must be selected for output when using OpenSCAD for viewing.";
         wxMessageBox(message, wxT("The OpenSCAD .csg file does not exist or is not up-to-date"), wxOK, this);
      }
   }
}

bool AngelCADFrame::TargetUpToDate(AngelCADEditor* page, const wxFileName& source,const wxFileName& target, wxLongLong& target_millis)
{
   if(page->IsModified()) return false;

   if(!source.Exists()) return false;
   double source_jdn = source.GetModificationTime().GetJDN();
   target_millis  = 0;

   wxString ext = target.GetExt();

   // does the file exist?
   if(target.Exists()) {
      wxDateTime target_time = target.GetModificationTime();
      double target_jdn = target_time.GetJDN();
      if(target_jdn >= source_jdn) {

          // number of milliseconds since Jan 1, 1970 UTC.
          target_millis = target_time.GetValue();
          // m_console->AppendText(wxString::Format("target %lld  %s ",target_millis,target.GetFullPath()));
          return true;
      }
   }
   return false;
}


void AngelCADFrame::OnViewSTL_AMF_DXF(wxCommandEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      wxFileName source   = page->FileName();
      wxFileName stl_file = DOC()->GetXcsgFileName(source); stl_file.SetExt("stl");
      wxFileName amf_file = DOC()->GetXcsgFileName(source); amf_file.SetExt("amf");
      wxFileName dxf_file = DOC()->GetXcsgFileName(source); dxf_file.SetExt("dxf");
      wxFileName svg_file = DOC()->GetXcsgFileName(source); svg_file.SetExt("svg");

      // make prioritised list of target files, keyed on milliseconds since 1970
      std::map<wxLongLong,wxFileName> targets;
      int ipri=0;

      // The files may get identical modification times, so check in a prioritised order.
      // We prefer STL over AMF, so if we check STL last and they have the same time, STL wins.
      wxLongLong target_millis = 0;
      if(TargetUpToDate(page, source,amf_file,target_millis)) targets[target_millis] = amf_file;
      if(TargetUpToDate(page, source,dxf_file,target_millis)) targets[target_millis] = dxf_file;
      if(TargetUpToDate(page, source,svg_file,target_millis)) targets[target_millis] = svg_file;
      if(TargetUpToDate(page, source,stl_file,target_millis)) targets[target_millis] = stl_file;

      if( targets.size() > 0 ) {

         // ok, a target file was accepted
         wxFileName target_file = targets.rbegin()->second;
         wxFileName viewer;
         wxString   cmd;

         // Select viewer for the most recent target file type
         // Encapsulated path in quotes to accomodate spaces
         bool default_svg_viewer = false;
         if(target_file.GetExt() == "dxf") {
            viewer = DOC()->GetConfigFilePath(ConfigEnums::DXFVIEW);
            cmd = "\"" + viewer.GetFullPath() + "\"  \"" + target_file.GetFullPath() + "\"";
         }
         else if(target_file.GetExt() == "svg") {
            default_svg_viewer = true;
         }
         else {
            viewer = DOC()->GetConfigFilePath(ConfigEnums::STLAMFVIEW);
            cmd = "\"" + viewer.GetFullPath() + "\"  \"" + target_file.GetFullPath() + "\"";
         }

         if(default_svg_viewer) {
            wxString path = "file:" + target_file.GetFullPath();
            wxLaunchDefaultApplication(path);
         }
         else {

            // ordinary viewer
            wxString message;
            if(!ExecutableCheck(viewer,message)){
               wxMessageBox(message, wxString::Format("Model viewer could not run: %s\n",viewer.GetFullPath()), wxOK, this);
               SettingsDialog dlg(this);
               dlg.SetInitialPage(SettingsDialog::ExternalFiles);
               dlg.ShowModal();
               return;
            }

            // launch the viewer with the target file as parameter
            cmd = "\"" + viewer.GetFullPath() + "\"  \"" + target_file.GetFullPath() + "\"";
            m_console->AppendText(cmd);
            wxExecute(cmd);
         }
      }
      else {
         wxString message  = "Please rebuild the source (F6) file to update.";
         if(page->IsModified()) message += "\nThe source has been edited but was not saved/rebuilt.";
         else                   message += "\nEither the target file does not exist or is out of date.";
                                message += "\nSTL/AMF or DXF (2D) must be selected for output.";
         wxMessageBox(message, wxT("No up-to-date 2D or 3D file available"), wxOK, this);
      }

   }
}

void AngelCADFrame::OnFindReplace(wxCommandEvent& event)
{
   wxString PaneName = "FindReplacePane";
   AuiManager1->GetPane(PaneName).Show(!AuiManager1->GetPane(PaneName).IsShown());
   AuiManager1->Update();
}

wxString AngelCADFrame::GetSelectedText()
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {
      return page->GetSelectedText();
   }
   return "";
}

bool AngelCADFrame::Find(const wxString& txt, bool fwd)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {
      if(!page->Find(txt,fwd)) {
         m_console->AppendText(wxT("Find/Replace reached end of document\n"));
         return true;
      }
   }
   return false;
}

bool AngelCADFrame::Replace(const wxString& newtxt)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {
      if(page->Replace(newtxt)) {
         return true;
      }
   }
   m_console->AppendText(wxT("Find/Replace replaced nothing\n"));
   return false;
}

int AngelCADFrame::ReplaceAll(const wxString& txt, const wxString& newtxt)
{
   int nrep = 0;
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {
      nrep = page->ReplaceAll(txt,newtxt);
   }
   m_console->AppendText(wxString::Format("Find/Replace replaced %d items\n",nrep));
   return nrep;
}


void AngelCADFrame::OnSettings(wxCommandEvent& event)
{
   SettingsDialog dlg(this);
   dlg.ShowModal();
}

void AngelCADFrame::OnOnlineDocumentation(wxCommandEvent& event)
{
   wxLaunchDefaultBrowser(DOC()->GetDocUrl());
}

void AngelCADFrame::OnLicenseSelected(wxCommandEvent& event)
{
   wxLaunchDefaultBrowser(DOC()->GetLicenseUrl());
}

void AngelCADFrame::OnOpenContainingFolder(wxCommandEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {
      wxFileName source   = page->FileName();

      // using a "file:" prefix and a local path will launch the user's file browser
      wxString path = "file:" + source.GetPath();
      wxLaunchDefaultApplication(path);
   }
   else {
      wxString message = "The containing folder is defined only when a source file is open.";
      wxMessageBox(message, wxT("No current source file"), wxOK, this);
   }
}

void AngelCADFrame::OnOpenLibrariesFolder(wxCommandEvent& event)
{
   wxLaunchDefaultApplication("file:" + DOC()->GetLibraryDir().GetPath());
}

void AngelCADFrame::OnAuiToolBarItemCutTextClick(wxCommandEvent& event)
{
   m_args_ctrl->SetValue("");
}


bool AngelCADFrame::DoImportDXF(const wxString& dxf_file)
{
   // check existence of executables
   wxFileName dxfreader = DOC()->GetConfigFilePath(ConfigEnums::DXFREADER);
   wxString dxfreader_message;

   if( ExecutableCheck(dxfreader,dxfreader_message) ) {

      wxFileName dxf_path(dxf_file);

      // dxfreader job
      wxString cmd1 = "\"" + dxfreader.GetFullPath() + "\" -as \"" + dxf_path.GetFullPath() + "\"";

      // create the list of jubs to run (2)
      std::list<ConsolePanel::JobPair> jobs;
      jobs.push_back(std::make_pair(cmd1,nullptr));

      // submit the jobs in the list
      m_console->Execute(jobs);

      wxFileName as_path(dxf_path);
      as_path.SetExt("as");
      as_path.Normalize();

      // Give it a couple of seconds to complete
      for(size_t i=0;i<10; i++) {
         if(as_path.Exists()) {
            DoSourceFileOpen(as_path.GetFullPath());
            break;
         }
         wxMilliSleep(500);
      }

   }
   return true;
}

void AngelCADFrame::OnAuiNotebook1TabRightDown(wxAuiNotebookEvent& event)
{
   // Save the page index pointed to (not necessarily the same as current selection)
   m_popup_page = event.GetSelection();

   // Create popup menu and connect it to an event handler
   wxMenu popup;
   popup.Append(ID_POPUP_CLOSE_ALL_BUT_THIS,"Save && close all but this");
   popup.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AngelCADFrame::OnPopupClick), NULL, this);

   // show the popup menu
   PopupMenu(&popup);
}

void AngelCADFrame::OnPopupClick(wxCommandEvent &evt)
{
 	if(evt.GetId() == ID_POPUP_CLOSE_ALL_BUT_THIS) {

      if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetPage(m_popup_page))) {

         // Remove current page without deleting it
         AuiNotebook1->RemovePage(m_popup_page);

         // save & close remaining files
         DoFileSaveAll();
         AuiNotebook1->DeleteAllPages();

         // add back the page we just removed
         wxString page_title = page->FileName().GetFullName();
         AuiNotebook1->AddPage(page,page_title,true);
      }
   }
}

void AngelCADFrame::OnRepairMeshFile(wxCommandEvent& event)
{
   if(AngelCADEditor* page = dynamic_cast<AngelCADEditor*>(AuiNotebook1->GetCurrentPage())) {

      wxString working_dir = wxFileName::GetCwd();

      wxFileName pfix = DOC()->GetConfigFilePath(ConfigEnums::POLYFIX);
      pfix.Normalize();
      wxString message;
      if(!ExecutableCheck(pfix,message)){
         wxMessageBox(message, wxT("polyfix could not execute"), wxOK, this);

         SettingsDialog dlg(this);
         dlg.SetInitialPage(SettingsDialog::ExternalFiles);
         dlg.ShowModal();
         pfix = DOC()->GetConfigFilePath(ConfigEnums::POLYFIX);
      }

      // select the mesh files. Multiple selection allowed
      wxString default_dir = DOC()->GetSaveDir();
      wxFileDialog dlg(this,wxT("Select surface mesh file"),default_dir,"",wxT("STL/AMF/OBJ/OFF files (*.stl;*.amf;*.obj;*.off)|*.stl;*.amf;*.obj;*.off|STL file (*.stl)|*.stl|AMF Files (*.amf)|*.amf|OBJ Files (*.obj)|*.obj|OFF Files (*.off)|*.off|All files (*.*)|*.*"),wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
      dlg.SetExtraControlCreator(&PolyfixPanel::CreatePanel);
      if(dlg.ShowModal() == wxID_OK) {

         // get access to the extra data and extract polyfix command line options
         PolyfixPanel* extra = static_cast<PolyfixPanel*>(dlg.GetExtraControl());
         wxString options = extra->GetOptions();

         // create list of polyfix runs to execute
         std::list<ConsolePanel::JobPair> jobs;

         wxArrayString paths;
         dlg.GetPaths(paths);
         size_t nfiles = paths.GetCount();
         for(size_t i=0; i<nfiles; i++) {

            wxFileName mesh_file(paths[i]);

            // polyfix job
            wxString cmd = "\"" + pfix.GetFullPath() +"\" " + options + " \"" +mesh_file.GetFullPath() + "\"";
            jobs.push_back(std::make_pair(cmd,page));
         }

         // submit the jobs in the list
         m_console->Execute(jobs);
      }
   }
}
