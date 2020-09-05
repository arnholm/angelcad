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

#ifndef AngelCADEDITOR_H
#define AngelCADEDITOR_H

#include <wx/stc/stc.h>
#include <wx/filename.h>

class AngelCADEditor : public wxStyledTextCtrl
{
   enum {
      margin_id_lineno = 0,
      margin_id_marker=1,
      margin_id_fold=2
   };

   enum {
      marker_error
   };

   struct find_item {
      find_item() : valid(false),pos(-1),fwd(true),txt("") {}
      find_item(bool _valid, int _pos, bool _fwd, wxString _txt) : valid(_valid),pos(_pos),fwd(_fwd),txt(_txt) {}
      bool     valid; // true if item is valid
      int      pos;   // start of text found   (always at start, regardless of search direction)
      bool     fwd;   // true = forward search
      wxString txt;   // the text we searched for
   };

public:
   AngelCADEditor(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize,long style = wxTAB_TRAVERSAL, const wxString& name ="AngelCADEditor");
   virtual ~AngelCADEditor();

   bool OpenFile(const wxFileName& fname);
   bool SaveFileAs(const wxFileName& fname);

   wxFileName FileName() const;

   void DeleteErrorMarkers();
   void InsertErrorMarker(int line);

   // Find looks for the text, highlights it angs saves the result
   bool Find(const wxString& txt, bool fwd);

   // Replace replaces the text found by Find
   bool Replace(const wxString& newtxt);

   // ReplaceAll does its own search & replace
   int ReplaceAll(const wxString& txt, const wxString& newtxt);

protected:
   void SetLexerCPP();

   void OnMarginClick(wxStyledTextEvent&);
   void OnChange(wxStyledTextEvent&);
   void OnCharAdded(wxStyledTextEvent&);
   void OnUpdateUI(wxStyledTextEvent&);

   virtual bool SetFont(const wxFont& font);

   int GetLineIndent(const wxString& line);

   void HighlightBraces();

   wxDECLARE_EVENT_TABLE();
private:
   size_t     m_indent;  // number of spaces for one indent level
   wxFileName m_fname;
   find_item  m_find;
};

#endif // AngelCADEDITOR_H
