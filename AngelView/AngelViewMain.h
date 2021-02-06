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
 * Name:      AngelViewMain.h
 * Purpose:   Defines Application Frame
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#ifndef ANGELVIEWMAIN_H
#define ANGELVIEWMAIN_H

#include <wx/docview.h>
#include <wx/config.h>
#include "AngelGLUICanvas.h"
#include <wx/filename.h>
#include "wxConfigBooleans.h"

#include <memory>
#include "AngelFileSystemWatcher.h"
#include "AnimateDialog.h"

//(*Headers(AngelViewFrame)
#include <wx/aui/aui.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
//*)

#include <wx/config.h>

class AngelViewFrame: public wxFrame {
public:
   static AngelViewFrame* singleton() { return m_self; }

   AngelViewFrame(wxWindow* parent,wxWindowID id = -1);
   virtual ~AngelViewFrame();

   void DoFileOpen(const wxFileName& filename, bool init_projection);

   void DoAnimate();
private:

   void OnFileEvent(wxFileSystemWatcherEvent& event);
   void InitBitmaps();

   void DoBeginWatch();

   void DoUpdateUI();
   void DoShowAxes(bool axes_on, bool markers_on);
   void DoShowCenter(bool center_on);
   void DoShowPolygons(bool filled_on, bool edges_on, bool backside_on);


   //(*Handlers(AngelViewFrame)
   void OnQuit(wxCommandEvent& event);
   void OnAbout(wxCommandEvent& event);
   void OnFileOpen(wxCommandEvent& event);
   void OnViewXneg(wxCommandEvent& event);
   void OnViewZpos(wxCommandEvent& event);
   void OnViewZneg(wxCommandEvent& event);
   void OnViewXpos(wxCommandEvent& event);
   void OnViewYneg(wxCommandEvent& event);
   void OnViewYpos(wxCommandEvent& event);
   void OnViewReset(wxCommandEvent& event);
   void OnShowAxesToolBar(wxCommandEvent& event);
   void OnShowAxesMenuBar(wxCommandEvent& event);
   void OnShowPolygonsToolbar(wxCommandEvent& event);
   void OnShowPolygonsMenuBar(wxCommandEvent& event);
   void OnShowCenterToolbar(wxCommandEvent& event);
   void OnShowCenterMenuBar(wxCommandEvent& event);
   void OnFileSaveImage(wxCommandEvent& event);
   void OnBackground(wxCommandEvent& event);
   void OnClose(wxCloseEvent& event);
   void OnRMBrotate(wxCommandEvent& event);
   void OnTimer1Trigger(wxTimerEvent& event);
   void OnFileReload(wxCommandEvent& event);
   void OnShowBacksideToolbar(wxCommandEvent& event);
   void OnShowBackSideMenuBar(wxCommandEvent& event);
   void OnCreateAnumation(wxCommandEvent& event);
   void OnAnimateTimer(wxTimerEvent& event);
   //*)

   void OnMRUFile(wxCommandEvent& event);
   void OnUpdateUI(wxUpdateUIEvent& event);

   //(*Identifiers(AngelViewFrame)
   static const long ID_CUSTOM1;
   static const long ID_PANEL1;
   static const long ID_AUITOOLBARITEM_FILEOPEN;
   static const long ID_AUITOOLBARSPACER1;
   static const long ID_AUITOOLBARITEM_VIEWRESET;
   static const long ID_AUITOOLBARITEM_VIEWXNEG;
   static const long ID_AUITOOLBARITEM_VIEWZPOS;
   static const long ID_AUITOOLBARITEM_VIEWZNEG;
   static const long ID_AUITOOLBARITEM_VIEWXPOS;
   static const long ID_AUITOOLBARITEM_VIEWYNEG;
   static const long ID_AUITOOLBARITEM_VIEWYPOS;
   static const long ID_AUITOOLBARITEM_BACKGROUND;
   static const long ID_AUITOOLBARITEM_ROTATE_RMB;
   static const long ID_AUITOOLBARITEM_SHOW_AXES;
   static const long ID_AUITOOLBARITEM_SHOW_MARKERS;
   static const long ID_AUITOOLBARITEM_SHOWCENTER;
   static const long ID_AUITOOLBARITEM_SHOWFILLED;
   static const long ID_AUITOOLBARITEM_SHOWEDGES;
   static const long ID_AUITOOLBARITEM_SHOWBACK;
   static const long ID_AUITOOLBAR1;
   static const long ID_MENUITEM1;
   static const long ID_MENUITEM_FILERELOAD;
   static const long ID_MENUITEM2;
   static const long ID_MENUITEM_CREATEANIM;
   static const long ID_MENUITEM_SAVEANIM;
   static const long idMenuQuit;
   static const long ID_MENUITEM_SHOWFILLED;
   static const long ID_MENUITEM_SHOWEDGES;
   static const long ID_MENUITEM_SHOWBACK;
   static const long ID_MENUITEM_SHOWAXES;
   static const long ID_MENUITEM_SHOWMARKERS;
   static const long ID_MENUITEM_SHOWCENTER;
   static const long ID_MENUITEM_RESETVIEW;
   static const long ID_MENUITEM_FROM_XNEG;
   static const long ID_MENUITEM_FROMXPOS;
   static const long ID_MENUITEM_FROMYNEG;
   static const long ID_MENUITEM_FROMYPOS;
   static const long ID_MENUITEM_FROMZNEG;
   static const long ID_MENUITEM_FROMZPOS;
   static const long idMenuAbout;
   static const long ID_STATUSBAR1;
   static const long ID_TIMER1;
   static const long ID_TIMER2;
   //*)

   //(*Declarations(AngelViewFrame)
   AngelGLUICanvas* m_canvas;
   wxAuiManager* AuiManager1;
   wxAuiToolBar* AuiToolBar1;
   wxMenu* Menu3;
   wxMenuBar* MenuBar1;
   wxMenuItem* MenuItem10;
   wxMenuItem* MenuItem11;
   wxMenuItem* MenuItem12;
   wxMenuItem* MenuItem13;
   wxMenuItem* MenuItem14;
   wxMenuItem* MenuItem15;
   wxMenuItem* MenuItem16;
   wxMenuItem* MenuItem17;
   wxMenuItem* MenuItem18;
   wxMenuItem* MenuItem19;
   wxMenuItem* MenuItem20;
   wxMenuItem* MenuItem3;
   wxMenuItem* MenuItem4;
   wxMenuItem* MenuItem5;
   wxMenuItem* MenuItem6;
   wxMenuItem* MenuItem7;
   wxMenuItem* MenuItem8;
   wxMenuItem* MenuItem9;
   wxPanel* m_center;
   wxStatusBar* StatusBar1;
   wxTimer Timer1;
   wxTimer m_animate_timer;
   //*)

   DECLARE_EVENT_TABLE()

private:
   wxFileName             m_filename;
   double                 m_jdn_filemod;  // JDN for the file modification time
   AngelFileSystemWatcher m_watcher;
   wxConfig*              m_config;
   wxFileHistory          m_mru;

   AnimateDialog*         m_animate_dlg;

private:
   static AngelViewFrame* m_self;
};

#endif // ANGELVIEWMAIN_H
