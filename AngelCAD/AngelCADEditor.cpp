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

#include "AngelCADEditor.h"
#include <wx/log.h>
#include <wx/msgdlg.h>
#include "AngelCADDropTarget.h"

wxBEGIN_EVENT_TABLE(AngelCADEditor, wxStyledTextCtrl)
    EVT_STC_MARGINCLICK(wxID_ANY, AngelCADEditor::OnMarginClick)
    EVT_STC_CHANGE(wxID_ANY, AngelCADEditor::OnChange)
    EVT_STC_CHARADDED(wxID_ANY, AngelCADEditor::OnCharAdded)
    EVT_STC_UPDATEUI(wxID_ANY, AngelCADEditor::OnUpdateUI)
    EVT_FSWATCHER(wxID_ANY,AngelCADEditor::OnFileEvent)
wxEND_EVENT_TABLE()

AngelCADEditor::AngelCADEditor(wxWindow* parent, wxWindowID id, const wxPoint& pos,const wxSize& size,long style, const wxString& name)
: wxStyledTextCtrl(parent, id,pos,size)
, m_indent(3)
{
   SetLexerCPP();

   SetMarginType(margin_id_lineno, wxSTC_MARGIN_NUMBER);
   SetMarginWidth(margin_id_lineno, 40);

   // Marker for "debugger"

   // http://proton-ce.sourceforge.net/rc/scintilla/pyframe/www.pyframe.com/stc/margins.html#setmask
   SetMarginType(margin_id_marker, wxSTC_MARGIN_SYMBOL);
   SetMarginWidth(margin_id_marker, 16);
   MarkerDefine(marker_error, wxSTC_MARK_SHORTARROW, *wxRED,*wxRED);
   SetMarginMask(1,0x1);


   // Folding follows
   SetProperty(wxT("fold"), wxT("1"));
   SetProperty(wxT("fold.comment"), wxT("1"));
   SetProperty(wxT("fold.compact"), wxT("1"));
   SetProperty(wxT("fold.preprocessor"), wxT("1"));
   SetProperty(wxT("fold.html"), wxT("1"));
   SetProperty(wxT("fold.html.preprocessor"), wxT("1"));

   MarkerDefine(wxSTC_MARKNUM_FOLDER,        wxSTC_MARK_BOXPLUS,           wxT("WHITE"), wxT("BLACK"));
   MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_BOXMINUS,          wxT("WHITE"), wxT("BLACK"));
   MarkerDefine(wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_VLINE,             wxT("WHITE"), wxT("BLACK"));
   MarkerDefine(wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_BOXPLUSCONNECTED,  wxT("WHITE"), wxT("BLACK"));
   MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUSCONNECTED, wxT("WHITE"), wxT("BLACK"));
   MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER,           wxT("WHITE"), wxT("BLACK"));
   MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_LCORNER,           wxT("WHITE"), wxT("BLACK"));

   SetMarginMask(margin_id_fold, wxSTC_MASK_FOLDERS);
   SetMarginWidth(margin_id_fold, 12);
   SetMarginSensitive(margin_id_fold, true);
//   SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
   SetFoldFlags(wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

   // Folding ends

   SetTabWidth(3);
   SetUseTabs(false);
//   SetWrapMode(wxSTC_WRAP_WORD);
//   SetWrapVisualFlags(wxSTC_WRAPVISUALFLAG_END);

   // switch off line wrapping
   SetWrapMode(wxSTC_WRAP_NONE);

   // Indicator for brace highlighting
   bool useBraceHighlightIndicator = true;
   int indicator  = 1;
   IndicatorSetStyle(indicator,wxSTC_INDIC_STRAIGHTBOX);
   IndicatorSetForeground(indicator,*wxRED);
   BraceHighlightIndicator(useBraceHighlightIndicator,indicator);

   // Drag & drop support
   SetDropTarget(new AngelCADDropTarget());
}

void AngelCADEditor::SetLexerCPP()
{
 //  StyleClearAll();
   SetLexer(wxSTC_LEX_CPP);

   wxFont font(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New"));
   SetFont(font);

   StyleSetForeground (wxSTC_C_DEFAULT, *wxBLACK);
   StyleSetForeground (wxSTC_C_STRING,            wxColour(00,100,250));
   StyleSetForeground (wxSTC_C_PREPROCESSOR,      wxTheColourDatabase->Find(wxT("MAGENTA")));
   StyleSetForeground (wxSTC_C_IDENTIFIER,        wxColour(40,0,60));
   StyleSetForeground (wxSTC_C_NUMBER,            wxTheColourDatabase->Find(wxT("VIOLET RED")));
   StyleSetForeground (wxSTC_C_CHARACTER,         wxColour(150,0,0));
   StyleSetForeground (wxSTC_C_WORD,              wxColour(0,0,255));
   StyleSetForeground (wxSTC_C_WORD2,             wxColour(140,0,0));
   StyleSetForeground (wxSTC_C_GLOBALCLASS,       wxTheColourDatabase->Find(wxT("DARK ORCHID"))); //   wxColour(0,120,0));
   StyleSetForeground (wxSTC_C_COMMENT,           wxColour(135,160,255));
   StyleSetForeground (wxSTC_C_COMMENTLINE,       wxColour(0,100,0));  // wxColour(100,100,255));
   StyleSetForeground (wxSTC_C_COMMENTDOC,        wxColour(150,150,150));
   StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, wxColour(0,0,200));
   StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(0,0,200));
   StyleSetBold(wxSTC_C_WORD, true);
   StyleSetBold(wxSTC_C_WORD2, true);
   StyleSetBold(wxSTC_C_COMMENT, true);
   StyleSetBold(wxSTC_C_COMMENTLINE, true);
   StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD, true);

  // wxString sets = DescribeKeyWordSets();

   SetKeyWords(0, wxT("@ auto class interface mixin if return funcdef for while break enum continue array dictionary map unordered_map switch case const double float void string bool sin cos tan atan2 int8 int16 int int64 uint8 uint16 uint uint64"));
   SetKeyWords(1, wxT("shape shape2d circle square rectangle polygon offset2d spline2d hull2d fill2d union2d difference2d intersection2d pos2d vec2d solid sphere cone cube cuboid cylinder polyhedron pface hull3d union3d difference3d difference3d intersection3d linear_extrude spline_path sweep rotate_extrude transform_extrude pos3d vec3d locsys3d spline3d boundingbox"));
   SetKeyWords(3, wxT("tmatrix mirror rotate_x rotate_y rotate_z scale translate hmatrix"));
}

AngelCADEditor::~AngelCADEditor()
{
   //dtor
}

bool AngelCADEditor::SetFont(const wxFont& font)
{
  StyleSetFont(wxSTC_STYLE_DEFAULT, (wxFont&)font);
  return wxStyledTextCtrl::SetFont(font);
}


void AngelCADEditor::OnMarginClick(wxStyledTextEvent &event)
{
    if (event.GetMargin() == margin_id_fold)
    {
        int lineClick = LineFromPosition(event.GetPosition());
        int levelClick = GetFoldLevel(lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0)
        {
            ToggleFold(lineClick);
        }
    }
}

void AngelCADEditor::OnChange(wxStyledTextEvent& event)
{
    wxLogDebug(wxT("Modified"));
    event.Skip();
}

int AngelCADEditor::GetLineIndent(const wxString& line)
{
   int ni = 0;
   for(size_t ipos=0; ipos<line.length(); ipos++) {
      wxChar c = line[ipos];
      if(c!= ' ' && c!= '\t') return ipos;
   }
   return ni;
}


void AngelCADEditor::OnCharAdded(wxStyledTextEvent& event)
{
   // the character just added is the one before the current position
   int currPos      = GetCurrentPos();
   wxChar ch        = GetCharAt(currPos-1);
   int  curLine     = GetCurrentLine();

   if(ch=='\r' || ch== '\n')  {

      // new line opened. Set proper indent
      int lineLength  = LineLength(curLine);  // length of line, including end of line characters
      if(curLine>0  &&  lineLength<=2) {

         // previous and this line (=the one we have just opened)
         wxString prev_line = GetLine(curLine-1);
         wxString this_line;

         // indent of previous line
         int ni = GetLineIndent(prev_line);
         for(int i=0; i<ni; i++) this_line += ' ';

         // Find the last character of the previous line.
         // If opening brace found as last character on previous line increas indent one level.
         // Use int for indexing, so as to not wrap around
         int prev_line_length = static_cast<int>(prev_line.length());
         if(prev_line_length > 1) {
            for(int ipos=prev_line_length-1; ipos>=0; ipos--) {
               wxChar c = prev_line[ipos];
               if(c!=' ' && c!='\r' && c!='\n') {
                  if(c== '{')  {
                     // add one extra indentation level to this line
                     for(size_t i=0; i<m_indent; i++) this_line += ' ';
                  }
                  break;
               }
            }
         }

         // Apply indentation of this line by insering blanks before current position
         if(this_line.length() > 0) {
            wxStyledTextCtrl::Replace(currPos,currPos,this_line);
            SetAnchor(currPos+this_line.Length());
            SetCurrentPos(currPos+this_line.Length());
         }
      }
   }
   else if(ch== '}') {

      // possibly a closing brace requiring unindent
      wxString this_line = GetLine(curLine);
      if(this_line.length() > m_indent) {

          // we should unindent only if the single character on the line is '}'
         size_t nclose = 0;  // number of closing braces
         size_t nnb    = 0;  // number of non-blanks
         for(size_t i=0; i<this_line.length(); i++) {
            wxChar c = this_line[i];
            if(c!=' ' && c!='\r' && c!='\n') {
               if(c== '}')  {
                  nclose++;
               }
               nnb++;
            }
         }
         if( (nclose==1) && (nnb==1) ) {

            // unindent the line
            this_line = "";
            int ni = GetLineIndent(GetLine(curLine-1));
            for(int i=0; i<ni; i++) this_line += ' ';
            int pos0  = PositionFromLine(curLine); // get position corresponding to start of line
            int pos1  = currPos-1;
            wxStyledTextCtrl::Replace(pos0,pos1,this_line);
            currPos = pos0 + this_line.length();;
            SetAnchor(currPos);
            SetCurrentPos(currPos);
         }
      }
   }
}


void  AngelCADEditor::OnUpdateUI(wxStyledTextEvent& event)
{
   HighlightBraces();
}

void AngelCADEditor::HighlightBraces()
{
   // Brace highlighting
   int currPos = GetCurrentPos();
   int newPos = BraceMatch(currPos);
   if (newPos == wxSTC_INVALID_POSITION) {
      if (currPos > 0) currPos--;
      newPos = BraceMatch(currPos);
   }

   // get character at current position and if it is a brace, do the matching
   wxChar ch = GetCharAt(currPos);
   if (ch == _T('{') || ch == _T('[') || ch == _T('(') ||
       ch == _T('}') || ch == _T(']') || ch == _T(')')) {
      if (newPos != wxSTC_INVALID_POSITION) {
         BraceHighlight(currPos, newPos);
         const int currColum = GetColumn(currPos);
         const int newColum = GetColumn(newPos);
         SetHighlightGuide((currColum < newColum) ? currColum :newColum);
      }
      else {
         BraceBadLight(currPos);
      }
   }
   else {
      BraceHighlight(-1, -1);
   }
}

bool AngelCADEditor::OpenFile(const wxFileName& fname)
{
   m_fname = "";
   m_fs_watcher = nullptr;
   m_fs_jdn     = 0;
   if(LoadFile(fname.GetFullPath())) {
      m_fname = fname;
      m_fs_watcher = std::make_shared<wxFileSystemWatcher>();
      m_fs_watcher->SetOwner(this);
      m_fs_watcher->Add(m_fname.GetPath(),wxFSW_EVENT_MODIFY);
      wxDateTime dtmod = m_fname.GetModificationTime();
      m_fs_jdn = dtmod.GetJDN();
      return true;
   }
   return false;
}


void AngelCADEditor::OnFileEvent(wxFileSystemWatcherEvent& event)
{
   if(event.GetChangeType() == wxFSW_EVENT_MODIFY) {

      // we received a file system event for the folder,
      // but we do not know for sure if the file we are viewing was changed,
      // it could be some other file in the same folder.
      // Therefore we check the modification time for our file now and compare
      if(m_fname.Exists()) {
         double jdn = m_fname.GetModificationTime().GetJDN();
         if( m_fs_jdn < jdn) {

            // sleep 2.1 second hoping the file write completes (other process)
            wxMilliSleep(2100);

            bool reload = true;
            if(IsModified()) {
               // the editor contents has been modified
               wxString message = m_fname.GetFullPath().ToStdString() + "\n"
                                + wxString("\nThis file has been modified by another program.")
                                + wxString("\nDo you want to reload it and lose the changes made in AngelCAD?");
               reload = false;
               if(wxYES == wxMessageBox( message, wxT("Reload?"), wxYES_NO | wxICON_WARNING, this)) {
                  reload = true;
               }
            }

            // even if the editor was modified and the user said NO to reload and lose local changes,
            // we update the editor JDN date, to prevent more questions

            m_fs_jdn = jdn;

            // add 2 seconds as protection in case we get several watcher events in successiom
            m_fs_jdn += 2.0/86400.0;

            if(reload) {

               // ok, we must refresh the file
               // reload the editor contents from the external file
               LoadFile(m_fname.GetFullPath());
            }
         }
      }
   }
}


wxFileName AngelCADEditor::FileName() const
{
   return m_fname;
}

bool AngelCADEditor::SaveFileAs(const wxFileName& fname)
{
   if(SaveFile(fname.GetFullPath())) {
      m_fname = fname;
      m_fs_watcher = std::make_shared<wxFileSystemWatcher>();
      m_fs_watcher->SetOwner(this);
      m_fs_watcher->Add(m_fname.GetPath(),wxFSW_EVENT_MODIFY);
      wxDateTime dtmod = m_fname.GetModificationTime();
      m_fs_jdn = dtmod.GetJDN();
      return true;
   }
   return false;
}

void AngelCADEditor::DeleteErrorMarkers()
{
   MarkerDeleteAll(marker_error);
}

void AngelCADEditor::InsertErrorMarker(int line)
{
   MarkerAdd(line-1,marker_error);
}


bool AngelCADEditor::Find(const wxString& txt, bool fwd)
{
   int minpos = 0;
   int curpos = GetCurrentPos();
   int maxpos = GetLastPosition();

   int begpos = curpos;
   int endpos = (fwd)? maxpos : minpos;

   int pos = FindText(begpos, endpos,txt);
   if(pos != -1){
      // found it, so highlight

      // this happens to work by moving the anchor position to the start
      // of the text we just found, then move the caret to the end of the text we found.
      // This creates a visible selection. Easy when you know how....
      if(fwd){
         SetAnchor(pos);
         SetCurrentPos(pos+txt.Length());
      }
      else {
         // in reverse search we must do the opposite
         SetAnchor(pos+txt.Length());
         SetCurrentPos(pos);
      }

      // make sure the line is visible
      ScrollToLine(GetCurrentLine()-5);

      // save the find item
      m_find = find_item(true,pos,fwd,txt);

      return true;
   }

   // clear find item
   m_find = find_item();
   return false;
}


bool  AngelCADEditor::Replace(const wxString& newtxt)
{
   if(!m_find.valid) return false;

   int from = m_find.pos;
   int to   = from+m_find.txt.Length();
   wxStyledTextCtrl::Replace(from,to,newtxt);

   // Replace puts the current insertion point position at to as a side effect.
   to   = from+newtxt.Length();
   if(m_find.fwd) {
      SetAnchor(from);
      SetCurrentPos(to);
   }
   else {
      SetAnchor(from);
      SetCurrentPos(to);
   }

   // clear find item
   m_find = find_item();

   return true;
}


int AngelCADEditor::ReplaceAll(const wxString& txt, const wxString& newtxt)
{
   int minpos = 0;
   int maxpos = GetLastPosition();
   int start  = minpos;
   int pos    = minpos;
   int nrep   = 0;

   while(pos != -1){
      pos = FindText(start, maxpos,txt);
      if(pos != -1){
         wxStyledTextCtrl::Replace(pos, pos + txt.size(), newtxt);
         start = pos + newtxt.size();
         nrep++;
      }
   }
   return nrep;
}
