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

#ifndef FINDREPLACEPANEL_H
#define FINDREPLACEPANEL_H

//(*Headers(FindReplacePanel)
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
//*)

class FindReplacePanel: public wxPanel {
public:

   FindReplacePanel(wxWindow* parent,wxWindowID id=wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "FindReplacePanel");
   virtual ~FindReplacePanel();

   virtual bool Show(bool show = true);

   //(*Declarations(FindReplacePanel)
   wxButton* FindFwdButton;
   wxButton* FindRevButton;
   wxButton* ReplaceAllButton;
   wxButton* ReplaceButton;
   wxTextCtrl* m_findTextCtrl;
   wxTextCtrl* m_replaceTxtCtrl;
   //*)

protected:

   //(*Identifiers(FindReplacePanel)
   static const long ID_TEXTCTRL1;
   static const long ID_BUTTON1;
   static const long ID_FIND_FWD_BUTTON;
   static const long ID_TEXTCTRL2;
   static const long ID_BUTTON3;
   static const long ID_BUTTON5;
   //*)

private:

   //(*Handlers(FindReplacePanel)
   void OnFindRevButtonClick(wxCommandEvent& event);
   void OnFindFwdButtonClick(wxCommandEvent& event);
   void OnReplaceButtonClick(wxCommandEvent& event);
   void OnReplaceAllButtonClick(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()
};

#endif
