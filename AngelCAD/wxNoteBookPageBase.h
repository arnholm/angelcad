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

#ifndef WXNOTEBOOKPAGEBASE_H
#define WXNOTEBOOKPAGEBASE_H


class wxNoteBookPageBase {
public:
   wxNoteBookPageBase();
   virtual ~wxNoteBookPageBase();

   // init page fills the data from data store -> GUI controls
   virtual void InitPage() = 0;

   // ApplyPage applies the from GUI controls ->  data store
   virtual void ApplyPage() = 0;

};

#endif // WXNOTEBOOKPAGEBASE_H
