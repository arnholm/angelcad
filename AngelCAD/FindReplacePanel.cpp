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
   
#include "FindReplacePanel.h"
#include "AngelCADMain.h"

//(*InternalHeaders(FindReplacePanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FindReplacePanel)
const long FindReplacePanel::ID_TEXTCTRL1 = wxNewId();
const long FindReplacePanel::ID_BUTTON1 = wxNewId();
const long FindReplacePanel::ID_FIND_FWD_BUTTON = wxNewId();
const long FindReplacePanel::ID_TEXTCTRL2 = wxNewId();
const long FindReplacePanel::ID_BUTTON3 = wxNewId();
const long FindReplacePanel::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FindReplacePanel,wxPanel)
	//(*EventTable(FindReplacePanel)
	//*)
END_EVENT_TABLE()

FindReplacePanel::FindReplacePanel(wxWindow* parent,wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	//(*Initialize(FindReplacePanel)
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Find - F3"));
	m_findTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticBoxSizer1->Add(m_findTextCtrl, 2, wxRIGHT|wxALIGN_TOP, 5);
	FindRevButton = new wxButton(this, ID_BUTTON1, _("<"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FindRevButton->SetToolTip(_("Find Previous"));
	FindRevButton->SetHelpText(_("Find Previous"));
	StaticBoxSizer1->Add(FindRevButton, 0, wxRIGHT|wxALIGN_TOP, 5);
	FindFwdButton = new wxButton(this, ID_FIND_FWD_BUTTON, _(">"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_FIND_FWD_BUTTON"));
	FindFwdButton->SetToolTip(_("Find Next (F3)"));
	FindFwdButton->SetHelpText(_("Find Next (F3)"));
	StaticBoxSizer1->Add(FindFwdButton, 0, wxALIGN_TOP, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Replace with"));
	m_replaceTxtCtrl = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	StaticBoxSizer2->Add(m_replaceTxtCtrl, 2, wxRIGHT|wxALIGN_TOP, 5);
	ReplaceButton = new wxButton(this, ID_BUTTON3, _("Replace"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	ReplaceButton->SetToolTip(_("Replace one"));
	ReplaceButton->SetHelpText(_("Replace one"));
	StaticBoxSizer2->Add(ReplaceButton, 0, wxRIGHT|wxALIGN_TOP, 5);
	ReplaceAllButton = new wxButton(this, ID_BUTTON5, _("All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	ReplaceAllButton->SetToolTip(_("Replace All"));
	ReplaceAllButton->SetHelpText(_("Replace All"));
	StaticBoxSizer2->Add(ReplaceAllButton, 0, wxALIGN_TOP, 5);
	BoxSizer1->Add(StaticBoxSizer2, 1, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindReplacePanel::OnFindRevButtonClick);
	Connect(ID_FIND_FWD_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindReplacePanel::OnFindFwdButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindReplacePanel::OnReplaceButtonClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindReplacePanel::OnReplaceAllButtonClick);
	//*)

	// install 'F3' as accelerator for the find forward button
	wxAcceleratorEntry entries[1];
	entries[0].Set(wxACCEL_NORMAL , WXK_F3 , ID_FIND_FWD_BUTTON);
	SetAcceleratorTable(wxAcceleratorTable(1, entries));
}

FindReplacePanel::~FindReplacePanel()
{
	//(*Destroy(FindReplacePanel)
	//*)
}

bool FindReplacePanel::Show(bool show)
{
   if(show) {
      m_findTextCtrl->SetFocus();

      // if any text is selected in the editor, set it as the default search item
      wxString selected_text = AngelCADFrame::singleton()->GetSelectedText();
      if(selected_text.length() > 0) {
         m_findTextCtrl->SetValue(selected_text);
      }
	}
   return wxPanel::Show(show);
}

void FindReplacePanel::OnFindFwdButtonClick(wxCommandEvent& event)
{
   wxString txt = m_findTextCtrl->GetValue();
   AngelCADFrame::singleton()->Find(txt,true);
}

void FindReplacePanel::OnFindRevButtonClick(wxCommandEvent& event)
{
   wxString txt = m_findTextCtrl->GetValue();
   AngelCADFrame::singleton()->Find(txt,false);
}

void FindReplacePanel::OnReplaceButtonClick(wxCommandEvent& event)
{
   wxString newtxt = m_replaceTxtCtrl->GetValue();
   AngelCADFrame::singleton()->Replace(newtxt);
}

void FindReplacePanel::OnReplaceAllButtonClick(wxCommandEvent& event)
{
   wxString txt = m_findTextCtrl->GetValue();
   wxString newtxt = m_replaceTxtCtrl->GetValue();
   AngelCADFrame::singleton()->ReplaceAll(txt,newtxt);
}
