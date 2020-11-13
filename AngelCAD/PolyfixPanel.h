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
   void OnCheckBoxClick(wxCommandEvent& event);
   void OnChoiceSelect(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()

   wxString m_out;
};

#endif
