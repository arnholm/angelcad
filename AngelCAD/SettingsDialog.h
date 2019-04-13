// BeginLicense:
// Part of: angelcad - script based 3D solid modeller 
// Copyright (C) 2017 Carsten Arnholm
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
   
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

//(*Headers(SettingsDialog)
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/sizer.h>
//*)

#include "SettingsFileFormats.h"
#include "SettingsExternalFiles.h"

class SettingsDialog: public wxDialog {
public:

   enum Page { FileFormats, ExternalFiles };

   SettingsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
   virtual ~SettingsDialog();

   void SetInitialPage(Page page);

   // init page fills the data from data store -> GUI controls
   void InitPages();

   // ApplyPage applies the from GUI controls ->  data store
   void ApplyPages();

   //(*Declarations(SettingsDialog)
   SettingsExternalFiles* Panel2;
   SettingsFileFormats* Panel1;
   wxAuiNotebook* AuiNotebook1;
   //*)

protected:

   //(*Identifiers(SettingsDialog)
   static const long ID_PANEL1;
   static const long ID_PANEL2;
   static const long ID_AUINOTEBOOK1;
   static const long ID_BUTTON2;
   //*)

private:

   //(*Handlers(SettingsDialog)
   void OnCloseButtonClick(wxCommandEvent& event);
   void OnApplyButtonClick(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()
};

#endif
