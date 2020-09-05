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
   
#ifndef SETTINGSEXTERNALFILES_H
#define SETTINGSEXTERNALFILES_H

//(*Headers(SettingsExternalFiles)
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include <wx/filename.h>
#include "ConfigEnums.h"
#include "wxNoteBookPageBase.h"

class SettingsExternalFiles: public wxPanel, public wxNoteBookPageBase {
public:

   SettingsExternalFiles(wxWindow* parent,wxWindowID id=wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "SettingsExternalFiles");
   virtual ~SettingsExternalFiles();

   wxFileName GetFilePath(ConfigEnums::ExtFile file);

   // init page fills the data from data store -> GUI controls
   virtual void InitPage();

   // ApplyPage applies the from GUI controls ->  data store
   virtual void ApplyPage();

   //(*Declarations(SettingsExternalFiles)
   wxCheckBox* m_nosubdir;
   wxFilePickerCtrl* m_file_as_csg;
   wxFilePickerCtrl* m_file_openscad;
   wxFilePickerCtrl* m_file_xcsg;
   wxFilePickerCtrl* m_reader_dxf;
   wxFilePickerCtrl* m_viewer_dxf;
   wxFilePickerCtrl* m_viewer_stl_amf;
   wxStaticBoxSizer* StaticBoxSizer2;
   wxTextCtrl* m_text_docurl;
   wxTextCtrl* m_text_outsub;
   //*)

protected:

   //(*Identifiers(SettingsExternalFiles)
   static const long ID_FILEPICKERCTRL1;
   static const long ID_TEXTCTRL1;
   static const long ID_CHECKBOX1;
   static const long ID_TEXTCTRL2;
   static const long ID_FILEPICKERCTRL2;
   static const long ID_FILEPICKERCTRL5;
   static const long ID_FILEPICKERCTRL3;
   static const long ID_FILEPICKERCTRL6;
   static const long ID_FILEPICKERCTRL4;
   //*)

private:

   //(*Handlers(SettingsExternalFiles)
   void OnText(wxCommandEvent& event);
   void OnFileChanged(wxFileDirPickerEvent& event);
   void OnNoSubdirClick(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()
};

#endif
