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

#include "SettingsExternalFiles.h"
#include "AngelCADDoc.h"

//(*InternalHeaders(SettingsExternalFiles)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(SettingsExternalFiles)
const long SettingsExternalFiles::ID_FILEPICKERCTRL1 = wxNewId();
const long SettingsExternalFiles::ID_TEXTCTRL1 = wxNewId();
const long SettingsExternalFiles::ID_CHECKBOX1 = wxNewId();
const long SettingsExternalFiles::ID_TEXTCTRL2 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL2 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL5 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL3 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL6 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL4 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL7 = wxNewId();
const long SettingsExternalFiles::ID_FILEPICKERCTRL8 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SettingsExternalFiles,wxPanel)
	//(*EventTable(SettingsExternalFiles)
	//*)
END_EVENT_TABLE()

SettingsExternalFiles::SettingsExternalFiles(wxWindow* parent,wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	//(*Initialize(SettingsExternalFiles)
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer9;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticText* StaticText10;
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	wxStaticText* StaticText3;
	wxStaticText* StaticText4;
	wxStaticText* StaticText5;
	wxStaticText* StaticText6;
	wxStaticText* StaticText7;
	wxStaticText* StaticText8;
	wxStaticText* StaticText9;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer1->Add(100,5,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("AngelCAD script compiler"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("as_csg compiler (for *.as)"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer2->Add(StaticText1, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_file_as_csg = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, wxEmptyString, _("Select AngelCAD compiler executable"), _T("as_csg*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	BoxSizer2->Add(m_file_as_csg, 3, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	StaticBoxSizer1->Add(BoxSizer2, 0, wxEXPAND, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText5 = new wxStaticText(this, wxID_ANY, _("Relative output subdirectory"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer6->Add(StaticText5, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_text_outsub = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer6->Add(m_text_outsub, 2, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_nosubdir = new wxCheckBox(this, ID_CHECKBOX1, _("No subdir"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_nosubdir->SetValue(false);
	BoxSizer6->Add(m_nosubdir, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	StaticBoxSizer1->Add(BoxSizer6, 0, wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, wxID_ANY, _("Online Documentation"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer4->Add(StaticText3, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_text_docurl = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer4->Add(m_text_docurl, 3, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	StaticBoxSizer1->Add(BoxSizer4, 0, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(100,5,0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Constructive Solid Geometry engine"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("xcsg compiler (for *.xcsg)"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer3->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_file_xcsg = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL2, wxEmptyString, _("Select xcsg compiler executable"), _T("xcsg*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL2"));
	BoxSizer3->Add(m_file_xcsg, 3, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	StaticBoxSizer2->Add(BoxSizer3, 0, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(100,5,0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Miscellaneous"));
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText6 = new wxStaticText(this, wxID_ANY, _("STL/AMF/OFF/OBJ viewer"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer7->Add(StaticText6, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_viewer_stl_amf = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL5, wxEmptyString, _("Select STL/AMF viewer executable"), _T("angelview*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL5"));
	BoxSizer7->Add(m_viewer_stl_amf, 3, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 4);
	StaticBoxSizer3->Add(BoxSizer7, 0, wxEXPAND, 5);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	StaticText8 = new wxStaticText(this, wxID_ANY, _("DXF reader"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer9->Add(StaticText8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_reader_dxf = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL3, wxEmptyString, _("Select DXF viewer executable"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL3"));
	BoxSizer9->Add(m_reader_dxf, 3, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 4);
	StaticBoxSizer3->Add(BoxSizer9, 1, wxEXPAND, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	StaticText7 = new wxStaticText(this, wxID_ANY, _("DXF viewer"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer8->Add(StaticText7, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_viewer_dxf = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL6, wxEmptyString, _("Select DXF viewer executable"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL6"));
	BoxSizer8->Add(m_viewer_dxf, 3, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 4);
	StaticBoxSizer3->Add(BoxSizer8, 0, wxEXPAND, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, wxID_ANY, _("OpenSCAD"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer5->Add(StaticText4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_file_openscad = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL4, wxEmptyString, _("Select OpenSCAD executable"), _T("openscad*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL4"));
	BoxSizer5->Add(m_file_openscad, 3, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 4);
	StaticBoxSizer3->Add(BoxSizer5, 0, wxEXPAND, 5);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	StaticText9 = new wxStaticText(this, wxID_ANY, _("polyfix"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer10->Add(StaticText9, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_file_polyfix = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL7, wxEmptyString, _("Select OpenSCAD executable"), _T("polyfix*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL7"));
	BoxSizer10->Add(m_file_polyfix, 3, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 4);
	StaticBoxSizer3->Add(BoxSizer10, 1, wxEXPAND, 5);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	StaticText10 = new wxStaticText(this, wxID_ANY, _("csgfix"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer11->Add(StaticText10, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
	m_file_csgfix = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL8, wxEmptyString, _("Select OpenSCAD executable"), _T("csgfix*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL8"));
	BoxSizer11->Add(m_file_csgfix, 3, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 4);
	StaticBoxSizer3->Add(BoxSizer11, 1, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SettingsExternalFiles::OnText);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsExternalFiles::OnNoSubdirClick);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SettingsExternalFiles::OnText);
	Connect(ID_FILEPICKERCTRL2,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_FILEPICKERCTRL5,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_FILEPICKERCTRL3,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_FILEPICKERCTRL6,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_FILEPICKERCTRL4,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_FILEPICKERCTRL7,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	Connect(ID_FILEPICKERCTRL8,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SettingsExternalFiles::OnFileChanged);
	//*)
}

SettingsExternalFiles::~SettingsExternalFiles()
{
	//(*Destroy(SettingsExternalFiles)
	//*)
}

wxFileName SettingsExternalFiles::GetFilePath(ConfigEnums::ExtFile file)
{
   switch(file) {
      case ConfigEnums::AS_CSG:      { return m_file_as_csg->GetFileName(); break; }
      case ConfigEnums::AS_OUTSUB:   { return wxFileName(m_text_outsub->GetValue()); break; }
      case ConfigEnums::XCSG:        { return m_file_xcsg->GetFileName(); break; }
      case ConfigEnums::OPENSCAD:    { return m_file_openscad->GetFileName(); break; }
      case ConfigEnums::STLAMFVIEW:  { return m_viewer_stl_amf->GetFileName(); break; }
      case ConfigEnums::DXFVIEW:     { return m_viewer_dxf->GetFileName(); break; }
      case ConfigEnums::DXFREADER:   { return m_reader_dxf->GetFileName(); break; }
      case ConfigEnums::POLYFIX:     { return m_file_polyfix->GetFileName(); break; }
      case ConfigEnums::CSGFIX:      { return m_file_csgfix->GetFileName(); break; }
      default: { throw std::logic_error("SettingsExternalFiles: unhandled parameter"); }
   };

   return wxFileName();
}


void SettingsExternalFiles::InitPage()
{
   // Use .GetFullPath() here, because the wxFilePickerCtrl does not seem to behave properly with a wxFileName

   // Use wxTextCtrl::ChangeValue(..) instead of SetValue(...) here,
   // because SetValue(...) triggers an event causing ApplyPage() to be called
   // ChangeValue(..) changes the value without triggering an event

   m_file_as_csg->SetPath(DOC()->GetConfigFilePath(ConfigEnums::AS_CSG).GetFullPath());
   m_text_outsub->ChangeValue(DOC()->GetConfigFilePath(ConfigEnums::AS_OUTSUB).GetFullPath());
   m_file_xcsg->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::XCSG).GetFullPath());
   m_file_openscad->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::OPENSCAD).GetFullPath());
   m_viewer_stl_amf->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::STLAMFVIEW).GetFullPath());
   m_viewer_dxf->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::DXFVIEW).GetFullPath());
   m_reader_dxf->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::DXFREADER).GetFullPath());
   m_file_polyfix->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::POLYFIX).GetFullPath());
   m_file_csgfix->SetFileName(DOC()->GetConfigFilePath(ConfigEnums::CSGFIX).GetFullPath());

   if(m_text_outsub->GetValue() == "."){
      m_nosubdir->SetValue(true);
      m_text_outsub->Enable(false);
   }

   wxString docurl = DOC()->GetDocUrl();
   m_text_docurl->ChangeValue(docurl);

   Refresh();
}

void SettingsExternalFiles::ApplyPage()
{
   DOC()->SetConfigFilePath(ConfigEnums::AS_CSG,GetFilePath(ConfigEnums::AS_CSG));
   DOC()->SetConfigFilePath(ConfigEnums::AS_OUTSUB,GetFilePath(ConfigEnums::AS_OUTSUB));
   DOC()->SetConfigFilePath(ConfigEnums::XCSG,GetFilePath(ConfigEnums::XCSG));
   DOC()->SetConfigFilePath(ConfigEnums::OPENSCAD,GetFilePath(ConfigEnums::OPENSCAD));
   DOC()->SetConfigFilePath(ConfigEnums::STLAMFVIEW,GetFilePath(ConfigEnums::STLAMFVIEW));
   DOC()->SetConfigFilePath(ConfigEnums::DXFVIEW,GetFilePath(ConfigEnums::DXFVIEW));
   DOC()->SetConfigFilePath(ConfigEnums::DXFREADER,GetFilePath(ConfigEnums::DXFREADER));
   DOC()->SetConfigFilePath(ConfigEnums::POLYFIX,GetFilePath(ConfigEnums::POLYFIX));
   DOC()->SetConfigFilePath(ConfigEnums::CSGFIX,GetFilePath(ConfigEnums::CSGFIX));

   DOC()->SetDocUrl(m_text_docurl->GetValue());
}

void SettingsExternalFiles::OnText(wxCommandEvent& event)
{
   ApplyPage();
}

void SettingsExternalFiles::OnFileChanged(wxFileDirPickerEvent& event)
{
   ApplyPage();
}

void SettingsExternalFiles::OnNoSubdirClick(wxCommandEvent& event)
{
   if(m_nosubdir->IsChecked()) {
      m_text_outsub->SetValue(".");
      m_text_outsub->Enable(false);
   }
   else {
      m_text_outsub->SetValue("xcsg");
      m_text_outsub->Enable(true);
   }
}
