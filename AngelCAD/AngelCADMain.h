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
 * Name:      AngelCADMain.h
 * Purpose:   Defines Application Frame
 * Author:    Carsten Arnholm
 * Created:   2016-12-25
 * Copyright: Carsten Arnholm
 * License:
 **************************************************************/

#ifndef ANGELCADMAIN_H
#define ANGELCADMAIN_H

#include <wx/docview.h>
#include <wx/config.h>
#include <wx/filename.h>

//(*Headers(AngelCADFrame)
#include <wx/aui/aui.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

class ConsolePanel;
class AngelCADEditor;
class FindReplacePanel;

class AngelCADFrame: public wxFrame {
public:

   static AngelCADFrame* singleton() { return m_self; }

   AngelCADFrame(wxWindow* parent,wxWindowID id = -1);
   virtual ~AngelCADFrame();

   wxString GetSelectedText();
   bool Find(const wxString& txt, bool fwd);
   bool Replace(const wxString& newtxt);
   int  ReplaceAll(const wxString& txt, const wxString& newtxt);

   bool DoSourceFileOpen(const wxString& as_path, bool close_all_others = false);

private:

   void init();
   bool DoSourceFileNew();

   bool DoImportDXF(const wxString& as_path);

   bool is_file_open(const wxString& as_path);

   bool DoFileSave(AngelCADEditor* page = 0, bool warn_for_unmodified = true);
   bool DoFileSaveAs(AngelCADEditor* page = 0);
   bool DoFileSaveAll();

   void AddFileToHistory(wxFileName filename);

   bool TargetUpToDate(AngelCADEditor* page, const wxFileName& source,const wxFileName& target, wxLongLong& target_millis);

   bool ExecutableCheck(const wxFileName& exec, wxString& message);

   //(*Handlers(AngelCADFrame)
   void OnQuit(wxCommandEvent& event);
   void OnAbout(wxCommandEvent& event);
   void OnClose(wxCloseEvent& event);
   void OnFileOpen(wxCommandEvent& event);
   void OnFileNew(wxCommandEvent& event);
   void OnFileSave(wxCommandEvent& event);
   void OnFileSaveAs(wxCommandEvent& event);
   void OnFileSaveAll(wxCommandEvent& event);
   void OnAuiNotebookPageChanged(wxAuiNotebookEvent& event);
   void OnAuiNotebookPageClosed(wxAuiNotebookEvent& event);
   void OnCompileAngelScript(wxCommandEvent& event);
   void OnAuiNotebookPageClose(wxAuiNotebookEvent& event);
   void OnBuildCurrentFile(wxCommandEvent& event);
   void OnRunOpenSCAD(wxCommandEvent& event);
   void OnFindReplace(wxCommandEvent& event);
   void OnSettings(wxCommandEvent& event);
   void OnRemoveFromMRU(wxCommandEvent& event);
   void OnKillProcess(wxCommandEvent& event);
   void OnViewSTL_AMF_DXF(wxCommandEvent& event);
   void OnOnlineDocumentation(wxCommandEvent& event);
   void OnOpenContainingFolder(wxCommandEvent& event);
   void OnLicenseSelected(wxCommandEvent& event);
   void OnOpenLibrariesFolder(wxCommandEvent& event);
   void OnAuiToolBarItemCutTextClick(wxCommandEvent& event);
   void OnImportDXF(wxCommandEvent& event);
   //*)

   //(*Identifiers(AngelCADFrame)
   static const long ID_AUINOTEBOOK1;
   static const long ID_PANEL1;
   static const long ID_AUITOOLBARITEM2;
   static const long ID_AUITOOLBARITEM1;
   static const long ID_AUITOOLBARITEM3;
   static const long ID_AUITOOLBARITEM4;
   static const long ID_AUITOOLBARITEM6;
   static const long ID_AUITOOLBARITEM7;
   static const long ID_AUITOOLBARITEM8;
   static const long ID_AUITOOLBARLABEL1;
   static const long ID_AUITOOLBARITEM5;
   static const long ID_TEXTCTRL1;
   static const long ID_AUITOOLBAR1;
   static const long ID_PANEL2;
   static const long ID_MENUITEM2;
   static const long ID_MENUITEM1;
   static const long ID_MENUITEM18;
   static const long ID_MENUITEM11;
   static const long ID_MENUITEM17;
   static const long ID_MENUITEM3;
   static const long ID_MENUITEM4;
   static const long ID_MENUITEM5;
   static const long ID_MENUITEM13;
   static const long ID_MENUITEM14;
   static const long idMenuQuit;
   static const long ID_MENUITEM6;
   static const long ID_MENUITEM7;
   static const long ID_MENUITEM8;
   static const long ID_MENUITEM12;
   static const long ID_MENUITEM9;
   static const long ID_MENUITEM10;
   static const long ID_MENUITEM15;
   static const long ID_MENUITEM16;
   static const long idMenuAbout;
   static const long ID_STATUSBAR1;
   //*)

   void OnMRUFile(wxCommandEvent& event);

   //(*Declarations(AngelCADFrame)
   ConsolePanel* m_console;
   FindReplacePanel* m_find_replace;
   wxAuiManager* AuiManager1;
   wxAuiNotebook* AuiNotebook1;
   wxAuiToolBar* AuiToolBar1;
   wxMenu* Menu3;
   wxMenu* Menu4;
   wxMenu* Menu5;
   wxMenu* MenuItem15;
   wxMenuItem* Menu6;
   wxMenuItem* MenuItem10;
   wxMenuItem* MenuItem11;
   wxMenuItem* MenuItem12;
   wxMenuItem* MenuItem13;
   wxMenuItem* MenuItem14;
   wxMenuItem* MenuItem16;
   wxMenuItem* MenuItem17;
   wxMenuItem* MenuItem18;
   wxMenuItem* MenuItem19;
   wxMenuItem* MenuItem3;
   wxMenuItem* MenuItem4;
   wxMenuItem* MenuItem5;
   wxMenuItem* MenuItem6;
   wxMenuItem* MenuItem7;
   wxMenuItem* MenuItem8;
   wxMenuItem* MenuItem9;
   wxStatusBar* m_statusbar;
   wxTextCtrl* m_args_ctrl;
   //*)

DECLARE_EVENT_TABLE()

private:
   static AngelCADFrame* m_self;
   wxConfig*             m_config;
   wxFileHistory         m_mru;
};

#endif // ANGELCADMAIN_H
