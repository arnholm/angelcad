#ifndef POLYFIXPANEL_H
#define POLYFIXPANEL_H

//(*Headers(PolyfixPanel)
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
//*)

class PolyfixPanel: public wxPanel {
public:

   static wxWindow* CreatePanel(wxWindow* parent) { return new PolyfixPanel(parent); }

   PolyfixPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
   virtual ~PolyfixPanel();

   wxString GetOptions();


   //(*Declarations(PolyfixPanel)
   wxCheckBox* m_atol_check;
   wxCheckBox* m_dtol_check;
   wxCheckBox* m_flip_check;
   wxCheckBox* m_lumps_check;
   wxCheckBox* m_out_check;
   wxCheckBox* m_overwrite_check;
   wxCheckBox* m_remesh_check;
   wxChoice* m_out_choice;
   wxTextCtrl* m_atol_ctrl;
   wxTextCtrl* m_dtol_ctrl;
   wxTextCtrl* m_remesh_ctrl;
   //*)

protected:

   //(*Identifiers(PolyfixPanel)
   static const long ID_CHECKBOX1;
   static const long ID_TEXTCTRL1;
   static const long ID_CHECKBOX4;
   static const long ID_TEXTCTRL3;
   static const long ID_CHECKBOX5;
   static const long ID_CHECKBOX2;
   static const long ID_CHECKBOX3;
   static const long ID_TEXTCTRL2;
   static const long ID_CHECKBOX6;
   static const long ID_CHECKBOX7;
   static const long ID_CHOICE1;
   //*)

private:

   //(*Handlers(PolyfixPanel)
   void OnChoiceSelect(wxCommandEvent& event);
   void OnDtolText(wxCommandEvent& event);
   void OnAtolText(wxCommandEvent& event);
   void OnRemeshText(wxCommandEvent& event);
   void OnDtolCheck(wxCommandEvent& event);
   void OnAtolCheck(wxCommandEvent& event);
   void OnLumpsCheck(wxCommandEvent& event);
   void OnFlipCheck(wxCommandEvent& event);
   void OnRemeshCheck(wxCommandEvent& event);
   void OnOverwriteCheck(wxCommandEvent& event);
   void OnOutCheck(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()

   bool     m_dtol_checked;
   wxString m_dtol;

   bool     m_atol_checked;
   wxString m_atol;

   bool     m_remesh_checked;
   wxString m_remesh;

   bool     m_out_checked;
   wxString m_out;

   bool     m_flip_checked;
   bool     m_overwrite_checked;
   bool     m_lumps_checked;
};

#endif
