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
//*)

BEGIN_EVENT_TABLE(SettingsFileFormats,wxPanel)
	//(*EventTable(SettingsFileFormats)
	//*)
END_EVENT_TABLE()

SettingsFileFormats::SettingsFileFormats(wxWindow* parent,wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	//(*Initialize(SettingsFileFormats)
	wxBoxSizer* BoxSizer1;

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
}


void SettingsFileFormats::OnCheckClick(wxCommandEvent& event)
{
   ApplyPage();
}
