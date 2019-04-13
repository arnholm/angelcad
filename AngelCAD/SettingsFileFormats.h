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
   
#ifndef SETTINGSFILEFORMATS_H
#define SETTINGSFILEFORMATS_H

//(*Headers(SettingsFileFormats)
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
//*)

#include "wxNoteBookPageBase.h"

class SettingsFileFormats: public wxPanel, public wxNoteBookPageBase {
public:

   SettingsFileFormats(wxWindow* parent,wxWindowID id=wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "SettingsFileFormats");
   virtual ~SettingsFileFormats();

   // init page fills the data from data store -> GUI controls
   virtual void InitPage();

   // ApplyPage applies the from GUI controls ->  data store
   virtual void ApplyPage();

   //(*Declarations(SettingsFileFormats)
   wxCheckBox* m_amf;
   wxCheckBox* m_csg;
   wxCheckBox* m_dxf;
   wxCheckBox* m_obj;
   wxCheckBox* m_off;
   wxCheckBox* m_stl;
   wxCheckBox* m_svg;
   //*)

protected:

   //(*Identifiers(SettingsFileFormats)
   static const long ID_CHECKBOX1;
   static const long ID_CHECKBOX2;
   static const long ID_CHECKBOX3;
   static const long ID_CHECKBOX4;
   static const long ID_CHECKBOX6;
   static const long ID_CHECKBOX7;
   static const long ID_CHECKBOX5;
   //*)

private:

   //(*Handlers(SettingsFileFormats)
   void OnCheckClick(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()
};

#endif
