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
   
#ifndef AS_ASSERT_H
#define AS_ASSERT_H

#include <assert.h>
#include <stdexcept>
#include <sstream>
using namespace std;

// the do {} while(false) is there to allow using semicolons after the macro
#define  as_assert(condition) \
         do { \
            if(! (condition)) { \
               ostringstream err; \
               err << " ***ERROR " << __FILE__  << " line " << __LINE__ << ": as_assert(" << #condition << ") failed." << std::endl; \
               throw std::logic_error(err.str()); \
            } \
         } while(false)


#endif // AS_ASSERT_H
