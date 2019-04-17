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
   
#include "SettingsDialog.h"

//(*InternalHeaders(SettingsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(SettingsDialog)
const long SettingsDialog::ID_PANEL1 = wxNewId();
const long SettingsDialog::ID_PANEL2 = wxNewId();
const long SettingsDialog::ID_AUINOTEBOOK1 = wxNewId();
const long SettingsDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SettingsDialog,wxDialog)
	//(*EventTable(SettingsDialog)
	//*)
END_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SettingsDialog)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxButton* CloseButton;

	Create(parent, id, _("AngelCAD Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxSize(800,500), wxAUI_NB_DEFAULT_STYLE);
	Panel1 = new SettingsFileFormats(AuiNotebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel2 = new SettingsExternalFiles(AuiNotebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	AuiNotebook1->AddPage(Panel1, _("Output File Formats"));
	AuiNotebook1->AddPage(Panel2, _("External Files"));
	BoxSizer1->Add(AuiNotebook1, 1, wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	CloseButton = new wxButton(this, ID_BUTTON2, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(CloseButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_RIGHT, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SettingsDialog::OnCloseButtonClick);
	//*)

	InitPages();
}

SettingsDialog::~SettingsDialog()
{
	//(*Destroy(SettingsDialog)
	//*)
}

void SettingsDialog::SetInitialPage(Page page)
{
   switch(page) {
      case FileFormats:   { AuiNotebook1->ChangeSelection(0); break; }
      case ExternalFiles: { AuiNotebook1->ChangeSelection(1); break; }
      default: {}
   }
}

void SettingsDialog::OnCloseButtonClick(wxCommandEvent& event)
{
   Close();
}


void SettingsDialog::InitPages()
{
   size_t npages = AuiNotebook1->GetPageCount();
   for(size_t ipage=0; ipage<npages; ipage++) {
      if(wxNoteBookPageBase* page = dynamic_cast<wxNoteBookPageBase*>(AuiNotebook1->GetPage(ipage))) {
         page->InitPage();
      }
   }
}

void SettingsDialog::ApplyPages()
{
   size_t npages = AuiNotebook1->GetPageCount();
   for(size_t ipage=0; ipage<npages; ipage++) {
      if(wxNoteBookPageBase* page = dynamic_cast<wxNoteBookPageBase*>(AuiNotebook1->GetPage(ipage))) {
         page->ApplyPage();
      }
   }
}

void SettingsDialog::OnApplyButtonClick(wxCommandEvent& event)
{
   ApplyPages();
}
