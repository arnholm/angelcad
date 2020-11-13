#include "PolyfixPanel.h"
#include <sstream>

//(*InternalHeaders(PolyfixPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PolyfixPanel)
const long PolyfixPanel::ID_CHECKBOX1 = wxNewId();
const long PolyfixPanel::ID_TEXTCTRL1 = wxNewId();
const long PolyfixPanel::ID_CHECKBOX4 = wxNewId();
const long PolyfixPanel::ID_TEXTCTRL3 = wxNewId();
const long PolyfixPanel::ID_CHECKBOX5 = wxNewId();
const long PolyfixPanel::ID_CHECKBOX2 = wxNewId();
const long PolyfixPanel::ID_CHECKBOX3 = wxNewId();
const long PolyfixPanel::ID_TEXTCTRL2 = wxNewId();
const long PolyfixPanel::ID_CHECKBOX6 = wxNewId();
const long PolyfixPanel::ID_CHECKBOX7 = wxNewId();
const long PolyfixPanel::ID_CHOICE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PolyfixPanel,wxPanel)
	//(*EventTable(PolyfixPanel)
	//*)
END_EVENT_TABLE()

static size_t icount=0;

PolyfixPanel::PolyfixPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{

	//(*Initialize(PolyfixPanel)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Heal"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	m_dtol_check = new wxCheckBox(this, ID_CHECKBOX1, _("Distance tolerance [mm] (-dtol)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_dtol_check->SetValue(false);
	BoxSizer2->Add(m_dtol_check, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_dtol_ctrl = new wxTextCtrl(this, ID_TEXTCTRL1, _("1.0E-2"), wxDefaultPosition, wxSize(100,-1), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	m_dtol_ctrl->Disable();
	BoxSizer2->Add(m_dtol_ctrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer2, 1, wxEXPAND, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	m_atol_check = new wxCheckBox(this, ID_CHECKBOX4, _("Area tolerance [mm^2] (-atol)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_atol_check->SetValue(false);
	BoxSizer6->Add(m_atol_check, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_atol_ctrl = new wxTextCtrl(this, ID_TEXTCTRL3, _("1.0E-6"), wxDefaultPosition, wxSize(100,-1), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	m_atol_ctrl->Disable();
	BoxSizer6->Add(m_atol_ctrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer6, 1, wxEXPAND, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	m_lumps_check = new wxCheckBox(this, ID_CHECKBOX5, _("Split into lumps (-lumps)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	m_lumps_check->SetValue(false);
	BoxSizer7->Add(m_lumps_check, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer7, 1, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	m_flip_check = new wxCheckBox(this, ID_CHECKBOX2, _("Flip inward faces (-nflip)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_flip_check->SetValue(false);
	BoxSizer3->Add(m_flip_check, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer3, 1, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Output"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	m_remesh_check = new wxCheckBox(this, ID_CHECKBOX3, _("Remesh [mm] (-remesh)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	m_remesh_check->SetValue(false);
	BoxSizer4->Add(m_remesh_check, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_remesh_ctrl = new wxTextCtrl(this, ID_TEXTCTRL2, _("2.0"), wxDefaultPosition, wxSize(100,-1), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	m_remesh_ctrl->Disable();
	BoxSizer4->Add(m_remesh_ctrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer4, 0, wxEXPAND, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	m_overwrite_check = new wxCheckBox(this, ID_CHECKBOX6, _("Overwrite input file (-overwrite)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	m_overwrite_check->SetValue(false);
	BoxSizer5->Add(m_overwrite_check, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer5, 0, wxEXPAND, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	m_out_check = new wxCheckBox(this, ID_CHECKBOX7, _("Output type (-out)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	m_out_check->SetValue(false);
	BoxSizer8->Add(m_out_check, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_out_choice = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	m_out_choice->Append(_("OBJ"));
	m_out_choice->SetSelection( m_out_choice->Append(_("OFF")) );
	m_out_choice->Append(_("AMF"));
	m_out_choice->Append(_("STL"));
	m_out_choice->Append(_("ASTL"));
	BoxSizer8->Add(m_out_choice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer8, 0, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnDtolCheck);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PolyfixPanel::OnDtolText);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnAtolCheck);
	Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PolyfixPanel::OnAtolText);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnLumpsCheck);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnFlipCheck);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnRemeshCheck);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PolyfixPanel::OnRemeshText);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnOverwriteCheck);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PolyfixPanel::OnOutCheck);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&PolyfixPanel::OnChoiceSelect);
	//*)

	++icount;

	// WORK_AROUND:
	// see https://forums.wxwidgets.org/viewtopic.php?t=43131
	// The controls do not really work under MSW when used in a
	// dialog extra panel, so we keep the values in separate
	// variables and capture user changes in events

   m_out    = m_out_choice->GetStringSelection();

   m_dtol   = m_dtol_ctrl->GetLabelText();
   m_atol   = m_atol_ctrl->GetLabelText();
   m_remesh = m_remesh_ctrl->GetLabelText();

   m_dtol_checked      = m_dtol_check->IsChecked();
   m_atol_checked      = m_atol_check->IsChecked();
   m_remesh_checked    = m_remesh_check->IsChecked();
   m_out_checked       = m_out_check->IsChecked();
   m_flip_checked      = m_flip_check->IsChecked();
   m_overwrite_checked = m_overwrite_check->IsChecked();
   m_lumps_checked     = m_lumps_check->IsChecked();

}

PolyfixPanel::~PolyfixPanel()
{
	//(*Destroy(PolyfixPanel)
	//*)
}


wxString PolyfixPanel::GetOptions()
{
   wxString options;
   std::ostringstream out;
   if(m_dtol_checked) {
      double dtol=-1.0;
      if(m_dtol.ToCDouble(&dtol)) {
         out << " -dtol="<<dtol;
      }
   }

   if(m_atol_checked) {
      double atol=-1.0;
      if(m_atol.ToCDouble(&atol)) {
         out << " -atol="<<atol;
      }
   }

   if(m_lumps_checked) out << " -lumps";
   if(m_flip_checked) out << " -nflip";
   if(m_remesh_checked) {
      double dist=-1.0;
      if(m_remesh.ToCDouble(&dist)) {
         out << " -remesh="<<dist;
      }
   }

   if(m_overwrite_checked) out << " -overwrite";
   if(m_out_checked) {
      out << " -out=" << m_out.ToStdString();
   }

   options = out.str();

   return options;
}

void PolyfixPanel::OnChoiceSelect(wxCommandEvent& event)
{
   m_out    = event.GetString();
}

void PolyfixPanel::OnDtolText(wxCommandEvent& event)
{
   m_dtol   = event.GetString();
}

void PolyfixPanel::OnAtolText(wxCommandEvent& event)
{
   m_atol   = event.GetString();
}

void PolyfixPanel::OnRemeshText(wxCommandEvent& event)
{
   m_remesh = event.GetString();
}

void PolyfixPanel::OnDtolCheck(wxCommandEvent& event)
{
   m_dtol_checked = event.IsChecked();
   m_dtol_ctrl->Enable(m_dtol_checked);
}

void PolyfixPanel::OnAtolCheck(wxCommandEvent& event)
{
   m_atol_checked = event.IsChecked();
   m_atol_ctrl->Enable(m_atol_checked);
}

void PolyfixPanel::OnLumpsCheck(wxCommandEvent& event)
{
   m_lumps_checked = event.IsChecked();
}

void PolyfixPanel::OnFlipCheck(wxCommandEvent& event)
{
   m_flip_checked = event.IsChecked();
}

void PolyfixPanel::OnRemeshCheck(wxCommandEvent& event)
{
   m_remesh_checked = event.IsChecked();
   m_remesh_ctrl->Enable(m_remesh_checked);
}

void PolyfixPanel::OnOverwriteCheck(wxCommandEvent& event)
{
   m_overwrite_checked = event.IsChecked();
}

void PolyfixPanel::OnOutCheck(wxCommandEvent& event)
{
   m_out_checked = event.IsChecked();
   m_out_choice->Enable(m_out_checked);
}
