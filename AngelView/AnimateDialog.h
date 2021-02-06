#ifndef ANIMATEDIALOG_H
#define ANIMATEDIALOG_H

#include "AnimateSpec.h"
#include <list>

//(*Headers(AnimateDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include <wx/filename.h>
#include <wx/image.h>

class AnimateDialog: public wxDialog {
public:

   AnimateDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
   virtual ~AnimateDialog();

   std::shared_ptr<AnimateSpec> animate_spec() const { return m_aspec; }

   void add_image(const wxFileName& fname, const wxImage& image);

   //(*Declarations(AnimateDialog)
   wxButton* Button1;
   wxSpinCtrl* m_framerate;
   wxSpinCtrl* m_total_sec;
   wxStaticText* StaticText1;
   wxStaticText* StaticText2;
   wxStaticText* StaticText3;
   wxStaticText* StaticText4;
   wxTextCtrl* m_spec_text;
   //*)

protected:

   //(*Identifiers(AnimateDialog)
   static const long ID_STATICTEXT1;
   static const long ID_STATICTEXT2;
   static const long ID_TEXTCTRL1;
   static const long ID_STATICTEXT3;
   static const long ID_SPINCTRL1;
   static const long ID_STATICTEXT4;
   static const long ID_SPINCTRL2;
   static const long ID_BUTTON1;
   //*)

   bool parse();

private:
   struct line_spec {
      pos3d                  pos;
      std::shared_ptr<vec3d> xdir;
      std::shared_ptr<vec3d> zdir;
      bool has_dir() const { return (xdir.get() && zdir.get()); }
      quaternion get_quat() const;
   };

   bool get_line_spec(long iline, line_spec& lspec);

   //(*Handlers(AnimateDialog)
   void OnAnimateButton(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()

private:
   std::shared_ptr<AnimateSpec>             m_aspec;
   std::list<std::pair<wxFileName,wxImage>> m_images;  // processed animation images
};

#endif
