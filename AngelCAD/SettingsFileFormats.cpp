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

#include "SettingsFileFormats.h"
#include "AngelCADDoc.h"

//(*InternalHeaders(SettingsFileFormats)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(SettingsFileFormats)
const long SettingsFileFormats::ID_CHECKBOX1 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX2 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX3 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX4 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX6 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX7 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX5 = wxNewId();
const long SettingsFileFormats::ID_CHECKBOX8 = wxNewId();
const long SettingsFileFormats::ID_DIRPICKERCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SettingsFileFormats,wxPanel)
	//(*EventTable(SettingsFileFormats)
	//*)
END_EVENT_TABLE()

SettingsFileFormats::SettingsFileFormats(wxWindow* parent,wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	//(*Initialize(SettingsFileFormats)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer1->Add(0,10,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_stl = new wxCheckBox(this, ID_CHECKBOX1, _("STL - (3D) - STereoLitography "), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_stl->SetValue(false);
	BoxSizer1->Add(m_stl, 0, wxALL|wxEXPAND, 5);
	m_amf = new wxCheckBox(this, ID_CHECKBOX2, _("AMF - (3D) - Additive Manufacturing Format"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_amf->SetValue(false);
	BoxSizer1->Add(m_amf, 0, wxALL|wxEXPAND, 5);
	m_obj = new wxCheckBox(this, ID_CHECKBOX3, _("OBJ - (3D) - Wavefront file format"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	m_obj->SetValue(false);
	BoxSizer1->Add(m_obj, 0, wxALL|wxEXPAND, 5);
	m_off = new wxCheckBox(this, ID_CHECKBOX4, _("OFF - (3D) - Geomview Object File Format"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_off->SetValue(false);
	BoxSizer1->Add(m_off, 0, wxALL|wxEXPAND, 5);
	m_dxf = new wxCheckBox(this, ID_CHECKBOX6, _("DXF - (2D) - AutCAD DXF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	m_dxf->SetValue(false);
	BoxSizer1->Add(m_dxf, 0, wxALL|wxEXPAND, 5);
	m_svg = new wxCheckBox(this, ID_CHECKBOX7, _("SVG - (2D) - Scalar Vector Graphics"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	m_svg->SetValue(false);
	BoxSizer1->Add(m_svg, 0, wxALL|wxEXPAND, 5);
	m_csg = new wxCheckBox(this, ID_CHECKBOX5, _("CSG - OpenSCAD Constructive Solid Geometry"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	m_csg->SetValue(false);
	BoxSizer1->Add(m_csg, 0, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(-1,-1,1, wxALL|wxEXPAND, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Export output files to directory"));
	m_enable_export_dir = new wxCheckBox(this, ID_CHECKBOX8, _("Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	m_enable_export_dir->SetValue(false);
	StaticBoxSizer1->Add(m_enable_export_dir, 1, wxALL|wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	m_export_dir = new wxDirPickerCtrl(this, ID_DIRPICKERCTRL1, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
	BoxSizer2->Add(m_export_dir, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer1->Add(BoxSizer2, 0, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxTOP|wxBOTTOM|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SettingsFileFormats::OnCheckClick);
	Connect(ID_DIRPICKERCTRL1,wxEVT_COMMAND_DIRPICKER_CHANGED,(wxObjectEventFunction)&SettingsFileFormats::OnExportDirChanged);
	//*)
}

SettingsFileFormats::~SettingsFileFormats()
{
	//(*Destroy(SettingsFileFormats)
	//*)
}

void SettingsFileFormats::InitPage()
{
   m_stl->SetValue(DOC()->GetFileFormatFlag("stl"));
   m_amf->SetValue(DOC()->GetFileFormatFlag("amf"));
   m_obj->SetValue(DOC()->GetFileFormatFlag("obj"));
   m_off->SetValue(DOC()->GetFileFormatFlag("off"));
   m_dxf->SetValue(DOC()->GetFileFormatFlag("dxf"));
   m_svg->SetValue(DOC()->GetFileFormatFlag("svg"));
   m_csg->SetValue(DOC()->GetFileFormatFlag("csg"));

   std::pair<bool,wxString> exp_dir = DOC()->GetExportDir();
   m_enable_export_dir->SetValue(exp_dir.first);
   m_export_dir->SetPath(exp_dir.second);
}

void SettingsFileFormats::ApplyPage()
{
   DOC()->SetFileFormatFlag("stl",m_stl->GetValue());
   DOC()->SetFileFormatFlag("amf",m_amf->GetValue());
   DOC()->SetFileFormatFlag("obj",m_obj->GetValue());
   DOC()->SetFileFormatFlag("off",m_off->GetValue());
   DOC()->SetFileFormatFlag("dxf",m_dxf->GetValue());
   DOC()->SetFileFormatFlag("svg",m_svg->GetValue());
   DOC()->SetFileFormatFlag("csg",m_csg->GetValue());

   auto exp_dir = std::make_pair(m_enable_export_dir->GetValue(),m_export_dir->GetPath());
   DOC()->SetExportDir(exp_dir);
}


void SettingsFileFormats::OnCheckClick(wxCommandEvent& event)
{
   ApplyPage();
}

void SettingsFileFormats::OnExportDirChanged(wxFileDirPickerEvent& event)
{
   m_enable_export_dir->SetValue( (m_export_dir->GetPath().Length() > 0)? true : false);
   ApplyPage();
}
