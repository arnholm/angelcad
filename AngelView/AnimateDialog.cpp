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
	m_spec_text = new wxTextCtrl(this, ID_TEXTCTRL1, _("  0   0   0  1 0  0      0  0 1\n 50  50 100\n100 100 200\n 50  50 300  \n  0   0 400  0 1 0.5   -0.2 0 1"), wxDefaultPosition, wxSize(380,150), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont m_spec_textFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	m_spec_text->SetFont(m_spec_textFont);
	BoxSizer1->Add(m_spec_text, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Animation time [sec ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_total_sec = new wxSpinCtrl(this, ID_SPINCTRL1, _T("10"), wxDefaultPosition, wxDefaultSize, 0, 2, 600, 10, _T("ID_SPINCTRL1"));
	m_total_sec->SetValue(_T("10"));
	BoxSizer3->Add(m_total_sec, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Frames/Sec"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer3->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_framerate = new wxSpinCtrl(this, ID_SPINCTRL2, _T("10"), wxDefaultPosition, wxDefaultSize, 0, 1, 25, 10, _T("ID_SPINCTRL2"));
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

   if(vals.size() < 3) {
      wxMessageBox("At least 3 values must be specified", "Error in line " + std::to_string(iline+1));
      return false;
   }

   if(vals.size() >= 3) {
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
            lspecs.push_back(lspec);
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
   auto aspec = std::make_shared<AnimateSpec>(sectot,fsec);

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
   m_images.clear();
   if(parse()) {

      // hide only if parsing was successful
      Hide();

      AngelViewFrame* frame = (AngelViewFrame*)GetParent();
      frame->DoAnimate();
   }
}

void AnimateDialog::add_image(const wxFileName& fname, const wxImage& image)
{
   m_images.push_back(std::make_pair(fname,image));
}
