// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017 Carsten Arnholm
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

#ifndef CONFIGENUMS_H
#define CONFIGENUMS_H


class ConfigEnums {
public:
   enum ExtFile {
      AS_CSG,     // as_csg executable
      AS_OUTSUB,  // as_csg output subdirectory (for xcsg files)
      XCSG,       // xcsg executable
      OPENSCAD,   // OpenSCAD executable
      STLAMFVIEW, // STL/AMF viewer executable
      DXFVIEW,    // DXF viewer executable
      DXFREADER   // DXF reader executable
   };

};

#endif // CONFIGENUMS_H
