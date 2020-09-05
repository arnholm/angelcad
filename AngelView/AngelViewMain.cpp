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

/***************************************************************
 * Name:      AngelViewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#include "AngelViewMain.h"
#include "AngelViewApp.h"

#include <wx/msgdlg.h>
#include <wx/filedlg.h>

#include "AngelViewDropTarget.h"
#include "wxConfigSaveRestore.h"
#include "AngelViewBitmapLibrary.h"

//(*InternalHeaders(AngelViewFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)


#include <wx/tglbtn.h>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(AngelViewFrame)
const long AngelViewFrame::ID_CUSTOM1 = wxNewId();
const long AngelViewFrame::ID_PANEL1 = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_FILEOPEN = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARSPACER1 = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWRESET = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWXNEG = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWZPOS = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWZNEG = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWXPOS = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWYNEG = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_VIEWYPOS = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_BACKGROUND = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_ROTATE_RMB = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_SHOW_AXES = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_SHOW_MARKERS = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_SHOWCENTER = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_SHOWFILLED = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_SHOWEDGES = wxNewId();
const long AngelViewFrame::ID_AUITOOLBARITEM_SHOWBACK = wxNewId();
const long AngelViewFrame::ID_AUITOOLBAR1 = wxNewId();
const long AngelViewFrame::ID_MENUITEM1 = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FILERELOAD = wxNewId();
const long AngelViewFrame::ID_MENUITEM2 = wxNewId();
const long AngelViewFrame::idMenuQuit = wxNewId();
const long AngelViewFrame::ID_MENUITEM_SHOWFILLED = wxNewId();
const long AngelViewFrame::ID_MENUITEM_SHOWEDGES = wxNewId();
const long AngelViewFrame::ID_MENUITEM_SHOWBACK = wxNewId();
const long AngelViewFrame::ID_MENUITEM_SHOWAXES = wxNewId();
const long AngelViewFrame::ID_MENUITEM_SHOWMARKERS = wxNewId();
const long AngelViewFrame::ID_MENUITEM_SHOWCENTER = wxNewId();
const long AngelViewFrame::ID_MENUITEM_RESETVIEW = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FROM_XNEG = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FROMXPOS = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FROMYNEG = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FROMYPOS = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FROMZNEG = wxNewId();
const long AngelViewFrame::ID_MENUITEM_FROMZPOS = wxNewId();
const long AngelViewFrame::idMenuAbout = wxNewId();
const long AngelViewFrame::ID_STATUSBAR1 = wxNewId();
const long AngelViewFrame::ID_TIMER1 = wxNewId();
//*)


BEGIN_EVENT_TABLE(AngelViewFrame,wxFrame)
   //(*EventTable(AngelViewFrame)
   //*)
   EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, AngelViewFrame::OnMRUFile)
   EVT_FSWATCHER(wxID_ANY,AngelViewFrame::OnFileEvent)
   EVT_UPDATE_UI(wxID_ANY,AngelViewFrame::OnUpdateUI)
END_EVENT_TABLE()

AngelViewFrame* AngelViewFrame::m_self=0;

AngelViewFrame::AngelViewFrame(wxWindow* parent,wxWindowID id)
: m_config(0)
, m_jdn_filemod(0.0)
{
   m_self = this;
   m_watcher.SetOwner(this);

   //(*Initialize(AngelViewFrame)
   wxBoxSizer* BoxSizer1;
   wxMenu* Menu1;
   wxMenu* Menu2;
   wxMenuItem* MenuItem1;
   wxMenuItem* MenuItem2;

   Create(parent, id, _("AngelView - STL/AMF/OBJ/OFF viewer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
   SetClientSize(wxSize(1100,800));
   AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
   m_center = new wxPanel(this, ID_PANEL1, wxPoint(222,354), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
   BoxSizer1 = new wxBoxSizer(wxVERTICAL);
   m_canvas = new AngelGLUICanvas(m_center,ID_CUSTOM1,0,wxDefaultPosition,wxDefaultSize,0,_T("ID_CUSTOM1"));
   BoxSizer1->Add(m_canvas, 1, wxEXPAND, 5);
   m_center->SetSizer(BoxSizer1);
   BoxSizer1->Fit(m_center);
   BoxSizer1->SetSizeHints(m_center);
   AuiManager1->AddPane(m_center, wxAuiPaneInfo().Name(_T("CenterPane")).CenterPane().Caption(_("Pane caption")));
   AuiToolBar1 = new wxAuiToolBar(this, ID_AUITOOLBAR1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_FILEOPEN, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Open File"), _("Open File"), NULL);
   AuiToolBar1->AddSpacer(15);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWRESET, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Default View"), _("Default View"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWXNEG, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View from -X"), _("View from -X"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWZPOS, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View from +Z"), _("View from +Z"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWZNEG, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View from -Z"), _("View from -Z"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWXPOS, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View from +X"), _("View from +X"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWYNEG, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View from -Y"), _("View from -Y"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_VIEWYPOS, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("View from +Y"), _("View from +Y"), NULL);
   AuiToolBar1->AddSeparator();
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_BACKGROUND, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Dark/Bright background"), _("Dark/Bright background"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_ROTATE_RMB, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("RMB rotate"), _("RMB rotate"), NULL);
   AuiToolBar1->AddSeparator();
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SHOW_AXES, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Show Axes"), _("Show Axes"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SHOW_MARKERS, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Show Markers"), _("Show Markers"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SHOWCENTER, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Show center of rotation"), _("Show center of rotation"), NULL);
   AuiToolBar1->AddSeparator();
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SHOWFILLED, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Show filled"), _("Show filled"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SHOWEDGES, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Show edges"), _("Show edges"), NULL);
   AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SHOWBACK, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Show backside faces"), _("Show backside faces"), NULL);
   AuiToolBar1->Realize();
   AuiManager1->AddPane(AuiToolBar1, wxAuiPaneInfo().Name(_T("PaneName")).ToolbarPane().Caption(_("Pane caption")).Layer(10).Top().Resizable().Gripper());
   AuiManager1->Update();
   MenuBar1 = new wxMenuBar();
   Menu1 = new wxMenu();
   MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Open..."), wxEmptyString, wxITEM_NORMAL);
   Menu1->Append(MenuItem3);
   MenuItem18 = new wxMenuItem(Menu1, ID_MENUITEM_FILERELOAD, _("Reload\tF6"), _("Reload Current File"), wxITEM_NORMAL);
   Menu1->Append(MenuItem18);
   MenuItem18->Enable(false);
   Menu1->AppendSeparator();
   MenuItem17 = new wxMenuItem(Menu1, ID_MENUITEM2, _("Save Image ..."), wxEmptyString, wxITEM_NORMAL);
   Menu1->Append(MenuItem17);
   Menu1->AppendSeparator();
   MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
   Menu1->Append(MenuItem1);
   MenuBar1->Append(Menu1, _("&File"));
   Menu3 = new wxMenu();
   MenuItem11 = new wxMenuItem(Menu3, ID_MENUITEM_SHOWFILLED, _("Show Filled"), wxEmptyString, wxITEM_CHECK);
   Menu3->Append(MenuItem11);
   MenuItem11->Check(true);
   MenuItem12 = new wxMenuItem(Menu3, ID_MENUITEM_SHOWEDGES, _("Show Wireframe"), wxEmptyString, wxITEM_CHECK);
   Menu3->Append(MenuItem12);
   MenuItem16 = new wxMenuItem(Menu3, ID_MENUITEM_SHOWBACK, _("Show Backside Faces"), wxEmptyString, wxITEM_CHECK);
   Menu3->Append(MenuItem16);
   Menu3->AppendSeparator();
   MenuItem13 = new wxMenuItem(Menu3, ID_MENUITEM_SHOWAXES, _("Show Axes"), wxEmptyString, wxITEM_CHECK);
   Menu3->Append(MenuItem13);
   MenuItem14 = new wxMenuItem(Menu3, ID_MENUITEM_SHOWMARKERS, _("Show Markers"), wxEmptyString, wxITEM_CHECK);
   Menu3->Append(MenuItem14);
   MenuItem15 = new wxMenuItem(Menu3, ID_MENUITEM_SHOWCENTER, _("Show Center"), wxEmptyString, wxITEM_CHECK);
   Menu3->Append(MenuItem15);
   Menu3->AppendSeparator();
   MenuItem4 = new wxMenuItem(Menu3, ID_MENUITEM_RESETVIEW, _("Default View"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem4);
   MenuItem5 = new wxMenuItem(Menu3, ID_MENUITEM_FROM_XNEG, _("From -X"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem5);
   MenuItem6 = new wxMenuItem(Menu3, ID_MENUITEM_FROMXPOS, _("From +X"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem6);
   MenuItem7 = new wxMenuItem(Menu3, ID_MENUITEM_FROMYNEG, _("From -Y"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem7);
   MenuItem8 = new wxMenuItem(Menu3, ID_MENUITEM_FROMYPOS, _("From +Y"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem8);
   MenuItem9 = new wxMenuItem(Menu3, ID_MENUITEM_FROMZNEG, _("From -Z"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem9);
   MenuItem10 = new wxMenuItem(Menu3, ID_MENUITEM_FROMZPOS, _("From +Z"), wxEmptyString, wxITEM_NORMAL);
   Menu3->Append(MenuItem10);
   MenuBar1->Append(Menu3, _("View"));
   Menu2 = new wxMenu();
   MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
   Menu2->Append(MenuItem2);
   MenuBar1->Append(Menu2, _("Help"));
   SetMenuBar(MenuBar1);
   StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
   int __wxStatusBarWidths_1[1] = { -1 };
   int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
   StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
   StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
   SetStatusBar(StatusBar1);
   Timer1.SetOwner(this, ID_TIMER1);

   Connect(ID_AUITOOLBARITEM_FILEOPEN,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnFileOpen);
   Connect(ID_AUITOOLBARITEM_VIEWRESET,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewReset);
   Connect(ID_AUITOOLBARITEM_VIEWXNEG,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewXneg);
   Connect(ID_AUITOOLBARITEM_VIEWZPOS,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewZpos);
   Connect(ID_AUITOOLBARITEM_VIEWZNEG,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewZneg);
   Connect(ID_AUITOOLBARITEM_VIEWXPOS,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewXpos);
   Connect(ID_AUITOOLBARITEM_VIEWYNEG,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewYneg);
   Connect(ID_AUITOOLBARITEM_VIEWYPOS,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnViewYpos);
   Connect(ID_AUITOOLBARITEM_BACKGROUND,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnBackground);
   Connect(ID_AUITOOLBARITEM_ROTATE_RMB,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnRMBrotate);
   Connect(ID_AUITOOLBARITEM_SHOW_AXES,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnShowAxesToolBar);
   Connect(ID_AUITOOLBARITEM_SHOW_MARKERS,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnShowAxesToolBar);
   Connect(ID_AUITOOLBARITEM_SHOWCENTER,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnShowCenterToolbar);
   Connect(ID_AUITOOLBARITEM_SHOWFILLED,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnShowPolygonsToolbar);
   Connect(ID_AUITOOLBARITEM_SHOWEDGES,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnShowPolygonsToolbar);
   Connect(ID_AUITOOLBARITEM_SHOWBACK,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&AngelViewFrame::OnShowBacksideToolbar);
   Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnFileOpen);
   Connect(ID_MENUITEM_FILERELOAD,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnFileReload);
   Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnFileSaveImage);
   Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnQuit);
   Connect(ID_MENUITEM_SHOWFILLED,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnShowPolygonsMenuBar);
   Connect(ID_MENUITEM_SHOWEDGES,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnShowPolygonsMenuBar);
   Connect(ID_MENUITEM_SHOWBACK,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnShowBackSideMenuBar);
   Connect(ID_MENUITEM_SHOWAXES,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnShowAxesMenuBar);
   Connect(ID_MENUITEM_SHOWMARKERS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnShowAxesMenuBar);
   Connect(ID_MENUITEM_SHOWCENTER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnShowCenterMenuBar);
   Connect(ID_MENUITEM_RESETVIEW,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewReset);
   Connect(ID_MENUITEM_FROM_XNEG,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewXneg);
   Connect(ID_MENUITEM_FROMXPOS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewXpos);
   Connect(ID_MENUITEM_FROMYNEG,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewYneg);
   Connect(ID_MENUITEM_FROMYPOS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewYpos);
   Connect(ID_MENUITEM_FROMZNEG,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewZneg);
   Connect(ID_MENUITEM_FROMZPOS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnViewZpos);
   Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&AngelViewFrame::OnAbout);
   Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&AngelViewFrame::OnTimer1Trigger);
   Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AngelViewFrame::OnClose);
   //*)

   // do all bitmap work using bitmap library
   InitBitmaps();

    // Drag & drop support
   SetDropTarget(new AngelViewDropTarget());

   m_config = new wxConfig(wxT("AngelView"),wxT("angelcad"));
   m_mru.Load(*m_config);
   m_mru.UseMenu(Menu1);
   m_mru.AddFilesToMenu();

   // model where we keep the defaults
   PolyhedronGL& model = wxGetApp().GetModel();

   // declare the flags to restore, set default values
   wxConfigBooleans flags;
   flags.SetFlag("background_dark",model.get_background_dark());
   flags.SetFlag("rmb_is_rotate",model.get_rmb_is_rotate());
   flags.SetFlag("draw_axes",model.get_draw_axes());
   flags.SetFlag("draw_markers",model.get_draw_markers());
   flags.SetFlag("highlight_backside",model.get_highlight_backside());

   // restore settings
   wxConfigSaveRestore helper(this,m_config);
   helper.SaveRestoreWindowSize(false);
   helper.SaveRestoreFlags(false,flags);

   // apply settings back to model so they become active in this session
   model.set_background_dark(flags.GetFlag("background_dark"));
   model.set_rmb_is_rotate(flags.GetFlag("rmb_is_rotate"));
   model.set_axes(flags.GetFlag("draw_axes"),flags.GetFlag("draw_markers"));
   model.set_highlight_backside(flags.GetFlag("highlight_backside"));

   m_filename = "*.stl";

   // fire the one-shot timer to get file watcher running + show any input from command line
   Timer1.StartOnce();
}

AngelViewFrame::~AngelViewFrame()
{
   m_mru.Save(*m_config);
   delete m_config;
   AuiManager1->UnInit();

   //(*Destroy(AngelViewFrame)
   //*)
}

void AngelViewFrame::OnClose(wxCloseEvent& event)
{
   // save setting to config
   wxConfigSaveRestore helper(this,m_config);
   helper.SaveRestoreWindowSize(true);

   PolyhedronGL& model = wxGetApp().GetModel();
   wxConfigBooleans flags;
   flags.SetFlag("background_dark",model.get_background_dark());
   flags.SetFlag("rmb_is_rotate",model.get_rmb_is_rotate());
   flags.SetFlag("draw_axes",model.get_draw_axes());
   flags.SetFlag("draw_markers",model.get_draw_markers());
   flags.SetFlag("highlight_backside",model.get_highlight_backside());
   helper.SaveRestoreFlags(true,flags);

   event.Skip();
}

void  AngelViewFrame::DoUpdateUI()
{
   // prevent updates to happen only when required. Do NOT perform Refresh() here
   PolyhedronGL& model = wxGetApp().GetModel();
   if(model.is_changed()) {

      // set as unchanged, as we will now implement the setting in the UI
      model.set_changed(false);

      // unique for toolbar
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_BACKGROUND,model.get_background_dark());
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_ROTATE_RMB,model.get_rmb_is_rotate());

      // common items for toolbar an menu follows
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOW_AXES,model.get_draw_axes());
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOW_MARKERS,model.get_draw_markers());
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOWFILLED,model.get_filled());
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOWEDGES,model.get_wireframe());
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOWBACK,model.get_highlight_backside());
      AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOWCENTER,model.get_draw_center());

      MenuBar1->Check(ID_MENUITEM_SHOWAXES,model.get_draw_axes());
      MenuBar1->Check(ID_MENUITEM_SHOWMARKERS,model.get_draw_markers());
      MenuBar1->Check(ID_MENUITEM_SHOWFILLED,model.get_filled());
      MenuBar1->Check(ID_MENUITEM_SHOWEDGES,model.get_wireframe());
      MenuBar1->Check(ID_MENUITEM_SHOWBACK,model.get_highlight_backside());
      MenuBar1->Check(ID_MENUITEM_SHOWCENTER,model.get_draw_center());
   }
}

void  AngelViewFrame::OnUpdateUI(wxUpdateUIEvent& event)
{
   DoUpdateUI();
}

void AngelViewFrame::OnQuit(wxCommandEvent& event)
{
   Close();
   event.Skip();
}

void AngelViewFrame::InitBitmaps()
{
   AngelViewBitmapLibrary  bitmaps;
   bitmaps.LoadBitmaps();



   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_FILEOPEN)->SetBitmap(bitmaps.GetBitmap("wxSTD_FILE_OPEN"));

   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWRESET)->SetBitmap(bitmaps.GetBitmap("view_reset"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWXNEG)->SetBitmap(bitmaps.GetBitmap("view_xneg"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWXPOS)->SetBitmap(bitmaps.GetBitmap("view_xpos"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWYNEG)->SetBitmap(bitmaps.GetBitmap("view_yneg"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWYPOS)->SetBitmap(bitmaps.GetBitmap("view_ypos"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWZNEG)->SetBitmap(bitmaps.GetBitmap("view_zneg"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_VIEWZPOS)->SetBitmap(bitmaps.GetBitmap("view_zpos"));

   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_SHOWFILLED)->SetBitmap(bitmaps.GetBitmap("show_filled"));
   AuiToolBar1->ToggleTool(ID_AUITOOLBARITEM_SHOWFILLED,true);
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_SHOWEDGES)->SetBitmap(bitmaps.GetBitmap("show_edges"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_SHOWBACK)->SetBitmap(bitmaps.GetBitmap("show_backside"));

   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_BACKGROUND)->SetBitmap(bitmaps.GetBitmap("background"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_SHOW_AXES)->SetBitmap(bitmaps.GetBitmap("show_axes"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_SHOW_MARKERS)->SetBitmap(bitmaps.GetBitmap("show_markers"));
   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_SHOWCENTER)->SetBitmap(bitmaps.GetBitmap("show_center"));

   AuiToolBar1->FindTool(ID_AUITOOLBARITEM_ROTATE_RMB)->SetBitmap(bitmaps.GetBitmap("rmb_is_rotate"));

   wxIconBundle icons;
   icons.AddIcon(bitmaps.GetIcon("angelview_16x16"));
   icons.AddIcon(bitmaps.GetIcon("angelview_32x32"));
   icons.AddIcon(bitmaps.GetIcon("angelview_64x64"));
   SetIcons(icons);
}


void AngelViewFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void  AngelViewFrame::DoBeginWatch()
{
   if(m_watcher.BeginWatch()) {
      wxDateTime dtmod = m_filename.GetModificationTime();
      wxString status = m_filename.GetFullPath()+ " - Modified: " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime();
      if(m_watcher.IsWatching()) {
         status += " (Monitoring)";
      }
      StatusBar1->SetStatusText(status);
   }
}

void AngelViewFrame::OnMRUFile(wxCommandEvent& event)
{
   wxString file_path(m_mru.GetHistoryFile(event.GetId() - wxID_FILE1));
   if (!file_path.empty()) {
      DoFileOpen(file_path,true);
      DoBeginWatch();
   }
}

void AngelViewFrame::DoFileOpen(const wxFileName& filename, bool init_projection)
{
   wxBusyCursor cursor;
   try {
      if(wxGetApp().GetModel().read(filename)) {

         m_filename = filename;
         m_mru.AddFileToHistory(m_filename.GetFullPath());

         wxDateTime dtmod = m_filename.GetModificationTime();
         m_jdn_filemod = dtmod.GetJDN();  // set the modification time at the time we read the file

         // signal whether the viewing transformation should be re-initialized or not
         PolyhedronGL& model = wxGetApp().GetModel();
         model.set_init_projection(init_projection);

         // Update file system watcher for the folder where the file resides.
         // There is no support for monitoring the single file directly (wx3.1)
         // so we watch the folder instead and take note of the file modification time.

         m_watcher.DefineWatchFile(m_filename);

         wxString status = m_filename.GetFullPath()+ " - Modified : " + dtmod.FormatISODate() + " " + dtmod.FormatISOTime();
         if(m_watcher.IsWatching()) status += " (Monitoring)";
         StatusBar1->SetStatusText(status);

         MenuBar1->Enable(ID_MENUITEM_FILERELOAD,true);
      }
      else {
         // file failed to load, remove from history
         for(size_t i=0; i<m_mru.GetCount(); i++) {
            if(m_mru.GetHistoryFile(i) == filename.GetFullPath()) {
               m_mru.RemoveFileFromHistory(i);
               break;
            }
         }

         StatusBar1->SetStatusText(filename.GetFullPath()+ " FAILED");
      }
      Refresh();
   }
   catch (std::exception ex) {
      wxString msg(m_filename.GetFullName());
      msg += '\n' +ex.what();
      wxMessageBox(msg, "Error Reading file");
   }
}

void AngelViewFrame::OnFileEvent(wxFileSystemWatcherEvent& event)
{
   if(event.GetChangeType() == wxFSW_EVENT_MODIFY) {

      // we received a file system event for the folder,
      // but we do not know for sure if the file we are viewing was changed,
      // it could be some other file in the same folder.
      // Therefore we check the modification time now and compare
      if(m_filename.Exists()) {
         double jdn = m_filename.GetModificationTime().GetJDN();
         if( m_jdn_filemod < jdn) {

            // ok, we must refresh, but keep current viewing transformation
            bool init_projection = false;
            m_jdn_filemod = jdn;

            // add 2 seconds as protection in case we get several watcher events in successiom
            m_jdn_filemod += 2.0/86400.0;

            // sleep 1.5 second hoping the file write completes (other process)
            wxMilliSleep(1500);
            DoFileOpen(m_filename,init_projection);
         }
      }
   }
}

void AngelViewFrame::OnFileOpen(wxCommandEvent& event)
{
 //  wxString defaultfile = "*." + m_filename.GetExt();
   wxString defaultfile = wxEmptyString;

   wxFileDialog dlg(this,wxT("Select surface mesh file"),m_filename.GetPath(),defaultfile,wxT("STL/AMF/OBJ/OFF files (*.stl;*.amf;*.obj;*.off)|*.stl;*.amf;*.obj;*.off|STL file (*.stl)|*.stl|AMF Files (*.amf)|*.amf|OBJ Files (*.obj)|*.obj|OFF Files (*.off)|*.off|All files (*.*)|*.*"),wxFD_OPEN|wxFD_FILE_MUST_EXIST);
   if(dlg.ShowModal() == wxID_OK) {

      wxArrayString paths;
      dlg.GetPaths(paths);
      m_filename = wxFileName(paths[0]);
      DoFileOpen(m_filename,true);
      DoBeginWatch();
   }
}


void AngelViewFrame::OnFileReload(wxCommandEvent& event)
{
   if(m_filename.Exists()) {
      DoFileOpen(m_filename,false);
   }
}

void AngelViewFrame::OnTimer1Trigger(wxTimerEvent& event)
{
   m_filename = wxGetApp().GetCmdLineFileName();
   if(m_filename.Exists()) {
      DoFileOpen(m_filename,true);
      DoBeginWatch();
   }
   DoUpdateUI();
   Timer1.Stop();
   Refresh();
}

void AngelViewFrame::OnFileSaveImage(wxCommandEvent& event)
{
   // refresh seems to be required
   Refresh();

   wxFileDialog dlg(this,wxT("AngelView image"),m_filename.GetPath(),m_filename.GetName(),wxT("PNG file (*.png)|*.png"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
   if(dlg.ShowModal() == wxID_OK) {
      wxFileName path(dlg.GetPath());
      if(path.GetFullPath().Length() > 0) {
         wxImage image;
         if(m_canvas->GetCurrentContext()->GetScreenImage(image)) {
            image.SaveFile(path.GetFullPath(),wxBITMAP_TYPE_PNG);
         }
      }
   }
}

void AngelViewFrame::OnViewXneg(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewFrom(vec3d(-1,0,0),vec3d(0,0,1));
   Refresh();
}

void AngelViewFrame::OnViewZpos(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewFrom(vec3d(0,0,+1),vec3d(0,+1,0));
   Refresh();
}

void AngelViewFrame::OnViewZneg(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewFrom(vec3d(0,0,-1),vec3d(0,-1,0));
   Refresh();
}

void AngelViewFrame::OnViewXpos(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewFrom(vec3d(+1,0,0),vec3d(0,0,1));
   Refresh();
}

void AngelViewFrame::OnViewYneg(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewFrom(vec3d(0,-1,0),vec3d(0,0,1));
   Refresh();
}

void AngelViewFrame::OnViewYpos(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewFrom(vec3d(0,+1,0),vec3d(0,0,1));
   Refresh();
}

void AngelViewFrame::OnViewReset(wxCommandEvent& event)
{
   m_canvas->GetCurrentContext()->SetViewDefault(true);
   Refresh();
}

void AngelViewFrame::DoShowAxes(bool axes_on, bool markers_on)
{
   PolyhedronGL& model = wxGetApp().GetModel();
   model.set_axes(axes_on,markers_on);
}

void AngelViewFrame::DoShowCenter(bool center_on)
{
   PolyhedronGL& model = wxGetApp().GetModel();
   model.set_draw_center(center_on);
}

void AngelViewFrame::DoShowPolygons(bool filled_on, bool edges_on, bool backside_on)
{
   PolyhedronGL& model = wxGetApp().GetModel();
   model.set_filled(filled_on);
   model.set_wireframe(edges_on);
   model.set_highlight_backside(backside_on);
}


void AngelViewFrame::OnShowAxesToolBar(wxCommandEvent& event)
{
   bool axes_on     = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOW_AXES);
   bool markers_on  = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOW_MARKERS);
   DoShowAxes(axes_on,markers_on);
   Refresh();
}

void AngelViewFrame::OnShowAxesMenuBar(wxCommandEvent& event)
{
   bool axes_on     =  MenuBar1->IsChecked(ID_MENUITEM_SHOWAXES);
   bool markers_on  =  MenuBar1->IsChecked(ID_MENUITEM_SHOWMARKERS);
   DoShowAxes(axes_on,markers_on);
   Refresh();
}

void AngelViewFrame::OnShowPolygonsToolbar(wxCommandEvent& event)
{
   bool filled_on    = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWFILLED);
   bool edges_on     = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWEDGES);
   bool backside_on  = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWBACK);
   if((!filled_on) && (!edges_on)) {
      filled_on = true;
   }
   DoShowPolygons(filled_on,edges_on,backside_on);
   Refresh();
}

void AngelViewFrame::OnShowPolygonsMenuBar(wxCommandEvent& event)
{
   bool filled_on    =  MenuBar1->IsChecked(ID_MENUITEM_SHOWFILLED);
   bool edges_on     =  MenuBar1->IsChecked(ID_MENUITEM_SHOWEDGES);
   bool backside_on  =  MenuBar1->IsChecked(ID_MENUITEM_SHOWBACK);
   if((!filled_on) && (!edges_on)) {
      filled_on = true;
   }
   DoShowPolygons(filled_on,edges_on,backside_on);
   Refresh();
}

void AngelViewFrame::OnShowBacksideToolbar(wxCommandEvent& event)
{
   bool filled_on    = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWFILLED);
   bool edges_on     = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWEDGES);
   bool backside_on  = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWBACK);

   if(backside_on)filled_on=true;
   if((!filled_on) && (!edges_on)) {
      filled_on = true;
   }
   DoShowPolygons(filled_on,edges_on,backside_on);
   Refresh();
}


void AngelViewFrame::OnShowBackSideMenuBar(wxCommandEvent& event)
{
   bool filled_on    =  MenuBar1->IsChecked(ID_MENUITEM_SHOWFILLED);
   bool edges_on     =  MenuBar1->IsChecked(ID_MENUITEM_SHOWEDGES);
   bool backside_on  =  MenuBar1->IsChecked(ID_MENUITEM_SHOWBACK);

   if(backside_on)filled_on=true;
   if((!filled_on) && (!edges_on)) {
      filled_on = true;
   }
   DoShowPolygons(filled_on,edges_on,backside_on);
   Refresh();
}


void AngelViewFrame::OnShowCenterToolbar(wxCommandEvent& event)
{
   bool center_on = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_SHOWCENTER);
   DoShowCenter(center_on);
   Refresh();
}

void AngelViewFrame::OnShowCenterMenuBar(wxCommandEvent& event)
{
   bool center_on = MenuBar1->IsChecked(ID_MENUITEM_SHOWCENTER);
   DoShowCenter(center_on);
   Refresh();
}

void AngelViewFrame::OnBackground(wxCommandEvent& event)
{
   bool background_dark = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_BACKGROUND);

   // set the value on the model
   // the DoSceneDraw() function will pick it up on next draw
   PolyhedronGL& model = wxGetApp().GetModel();
   model.set_background_dark(background_dark);

   // we can do this here, since the window is shown
   // for some reason, sending a wxPaintEvent does not have the same effect
   m_canvas->GetCurrentContext()->DoSceneDraw();
   Refresh();
}

void AngelViewFrame::OnRMBrotate(wxCommandEvent& event)
{
   bool rmb_is_rotate = AuiToolBar1->GetToolToggled(ID_AUITOOLBARITEM_ROTATE_RMB);

   // simply set the flag on the canvas which will use it on next mouse event
   m_canvas->SetRmbRotate(rmb_is_rotate);

   PolyhedronGL& model = wxGetApp().GetModel();
   model.set_rmb_is_rotate(rmb_is_rotate);
   Refresh();
}

