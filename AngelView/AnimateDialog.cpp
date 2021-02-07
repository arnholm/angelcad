#include "AnimateDialog.h"
#include <wx/tokenzr.h>
#include <wx/msgdlg.h>
#include "AngelViewMain.h"
//(*InternalHeaders(AnimateDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(AnimateDialog)
const long AnimateDialog::ID_STATICTEXT1 = wxNewId();
const long AnimateDialog::ID_STATICTEXT2 = wxNewId();
const long AnimateDialog::ID_TEXTCTRL1 = wxNewId();
const long AnimateDialog::ID_CHECKBOX1 = wxNewId();
const long AnimateDialog::ID_SPINCTRL3 = wxNewId();
const long AnimateDialog::ID_STATICTEXT3 = wxNewId();
const long AnimateDialog::ID_SPINCTRL1 = wxNewId();
const long AnimateDialog::ID_STATICTEXT4 = wxNewId();
const long AnimateDialog::ID_SPINCTRL2 = wxNewId();
const long AnimateDialog::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AnimateDialog,wxDialog)
	//(*EventTable(AnimateDialog)
	//*)
END_EVENT_TABLE()

AnimateDialog::AnimateDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AnimateDialog)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, _("Create Animation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Specify spline curve(s) for animation.\nPoints may have local xdir/zdir orientations.  \nLocal xdir/zdir orientations always appear at curve ends."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 0, wxALL|wxEXPAND, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("           point           [    xdir                       zdir     ]\n      0      0      0         1   0    0                 0    0   1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	BoxSizer1->Add(StaticText2, 0, wxALL|wxEXPAND, 5);
	m_spec_text = new wxTextCtrl(this, ID_TEXTCTRL1, _("0       0    0\n100    50   50\n200   100  100\n250   250  200\n150   300  250\n-150  300  300\n-300    0  350   -1   0   1    0 -1 1\n-250 -250  390\n0    -300  410    0  -1   1    1  0 1\n300  -250  390\n150  -150  380  0.6  0.9 0.5  -1  0 1\n0       0  350 \n0       0  300 -0.6 -0.6 0.5   1  0 1\n0       0  100    1 -0.5  0  -0.2 0 1\n0       0   0"), wxDefaultPosition, wxSize(380,300), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont m_spec_textFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	m_spec_text->SetFont(m_spec_textFont);
	BoxSizer1->Add(m_spec_text, 1, wxALL|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	m_orbit = new wxCheckBox(this, ID_CHECKBOX1, _("Orbit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_orbit->SetValue(false);
	BoxSizer3->Add(m_orbit, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_orbit_deg = new wxSpinCtrl(this, ID_SPINCTRL3, _T("360"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT, 0, 3600, 360, _T("ID_SPINCTRL3"));
	m_orbit_deg->SetValue(_T("360"));
	BoxSizer3->Add(m_orbit_deg, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Duration [sec ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_total_sec = new wxSpinCtrl(this, ID_SPINCTRL1, _T("30"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT, 2, 600, 30, _T("ID_SPINCTRL1"));
	m_total_sec->SetValue(_T("30"));
	BoxSizer3->Add(m_total_sec, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Frames/Sec"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer3->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_framerate = new wxSpinCtrl(this, ID_SPINCTRL2, _T("10"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT, 1, 25, 10, _T("ID_SPINCTRL2"));
	m_framerate->SetValue(_T("10"));
	BoxSizer3->Add(m_framerate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2->Add(-1,-1,3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	AnimateButton = new wxButton(this, ID_BUTTON1, _("Animate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(AnimateButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AnimateDialog::OnAnimateButton);
	//*)
}

AnimateDialog::~AnimateDialog()
{
	//(*Destroy(AnimateDialog)
	//*)
}

static  std::vector<wxString> tokenize(const wxString& text)
{
   std::vector<wxString> tokens;
   wxStringTokenizer tokenizer(text);
   while ( tokenizer.HasMoreTokens() ) tokens.push_back(tokenizer.GetNextToken());
   return std::move(tokens);
}



bool AnimateDialog::get_line_spec(long iline, line_spec& lspec)
{
   std::vector<wxString> tokens = tokenize(m_spec_text->GetLineText(iline));
   std::vector<double> vals;
   for( auto& s : tokens) {
      double v = 0.0;
      if(s.ToCDouble(&v)) vals.push_back(v);
      else {
         wxMessageBox(s + " is not a number", "Error in line " + std::to_string(iline+1));
         return false;
      }
   }


   if(vals.size() == 0) {
      // creates invalid lspec that is silently ignored
   }
   else if(vals.size() < 3) {
      wxMessageBox("At least 3 values must be specified", "Error in line " + std::to_string(iline+1));
      return false;
   }
   else {
      lspec.is_valid = true;
      lspec.pos = pos3d(vals[0],vals[1],vals[2]);
   }
   if(vals.size() >= 9) {
      lspec.xdir = std::make_shared<vec3d>(vals[3],vals[4],vals[5]);
      lspec.zdir = std::make_shared<vec3d>(vals[6],vals[7],vals[8]);
   }
   else if(vals.size() > 3) {
      wxMessageBox("At least 9 values must be specified for directions", "Error in line " + std::to_string(iline+1));
      return false;
   }

   return true;
}

quaternion AnimateDialog::line_spec::get_quat() const
{
   quaternion q;
   if(has_dir()) {
      locsys3d lsys(*xdir,*zdir);
      q = quaternion(lsys.matrix());
   }
   return q;
}


bool AnimateDialog::parse()
{
   m_aspec = nullptr;

   // intermediary line specs
   std::vector<line_spec> lspecs;

   int nlines = m_spec_text->GetNumberOfLines();
   if(nlines > 1) {
      for(long iline=0; iline<nlines; iline++) {
         line_spec lspec;
         if(get_line_spec(iline,lspec)) {
            if(lspec.is_valid)lspecs.push_back(lspec);
         }
         else return false;
      }
   }
   else {
      wxMessageBox("At least 2 lines must be specified", "Error in input");
      return false;
   }
   // no syntax errors, convert to curves

   size_t sectot = m_total_sec->GetValue();
   size_t fsec   = m_framerate->GetValue();
   auto orbit = std::make_pair<bool,double>(m_orbit->IsChecked(),m_orbit_deg->GetValue());
   auto aspec = std::make_shared<AnimateSpec>(sectot,fsec,orbit);

   std::shared_ptr<AnimateCurve> curve = nullptr;

   std::vector<pos3d> points;

   for(size_t ispec=0; ispec<lspecs.size(); ispec++) {

      line_spec& lspec = lspecs[ispec];
      bool last_spec = (ispec == lspecs.size()-1);

      // we always extract point
      points.push_back(lspec.pos);

      if(!curve) {
         // new curve
         curve = std::make_shared<AnimateCurve>();
         curve->set_q0(lspec.get_quat());
      }
      else {
         if(lspec.has_dir() || last_spec) {

            // terminate this curve
            curve->set_q1(lspec.get_quat());
            curve->set_path(spline3d(points));
            points.clear();
            aspec->push_back(curve);

            // new curve, starting where the last one ended
            curve = std::make_shared<AnimateCurve>();
            points.push_back(lspec.pos);
            curve->set_q0(lspec.get_quat());
         }
      }
   }

   if(aspec->size() > 0) {
      // compute number of steps per curve
      aspec->finalize();
      m_aspec = aspec;
   }

   return m_aspec.get();
}

void AnimateDialog::OnAnimateButton(wxCommandEvent& event)
{
   if(parse()) {

      // hide only if parsing was successful
      Hide();

      AngelViewFrame* frame = (AngelViewFrame*)GetParent();
      frame->DoAnimate();
   }
}

