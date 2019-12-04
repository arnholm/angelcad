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

#include "pointcloud.h"
// #include <sstream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "ce_angelscript_ex/as_vector.h"
#include "pos3.h"
#include "spacemath/pos3d.h"



static void tokenize(const std::string& input,
                     const std::string& delimiters,
                     std::vector<std::string>& tokens)
{
   using namespace std;
   string::size_type last_pos = 0;
   string::size_type pos = 0;
   while(true) {
      pos = input.find_first_of(delimiters, last_pos);
      if( pos == string::npos ) {
         if(input.length()-last_pos > 0)tokens.push_back(input.substr(last_pos));
         break;
      }
      else {
         if(pos-last_pos > 0)tokens.push_back(input.substr(last_pos, pos - last_pos));
         last_pos = pos + 1;
      }
   }
}


void pointcloud::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted pointcloud type
   DeclareType<pointcloud>(engine,"pointcloud, contains pos3d@ cloud");

   // Declare the pointcloud constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique pointcloud methods
   pointcloud::DeclareMethods<pointcloud>(engine);
}

as_reftype* pointcloud::clone_scoped()
{
   return new pointcloud(*this);
}

pointcloud::pointcloud(const CScriptArray* points)
: as_reftype(as_typeid<pointcloud>())
{
   as_vector<pos3*> other(points);

   vector<pos3d> tmp_pos;
   tmp_pos.reserve(other.size());

   for(size_t i=0; i<other.size(); i++) {
      pos3* pnt = other[i];
      if(!pnt) {
         string message = "pointcloud exception: NULL element detected in pointcloud points, index=" + std::to_string(i);
         throw logic_error(message);
      }
      tmp_pos.push_back(pos3d(pnt->x(),pnt->y(),pnt->z()));
   }

    m_arr = create_array(tmp_pos);
}

pointcloud::pointcloud(const string& file, int skip_lines, int xtok, int ytok, int ztok, const string& delimiters)
: as_reftype(as_typeid<pointcloud>())
{
   std::ifstream in(file.c_str());
   if(!in.is_open()) throw logic_error("pointcloud: file could not be opened: " + file );

   vector<pos3d> tmp_pos;
   tmp_pos.reserve(1024);

   // read the file line by line
   size_t line_number=0;
   std::string line;
   while(std::getline(in,line)) {

      // increment the line number (useful in error reporting)
      line_number++;

      if(line_number > skip_lines) {
         vector<string> tokens;
         tokenize(line,delimiters,tokens);
         size_t ntok = tokens.size();
         if(ntok > 0) {
            // it is possible to read a subset of coordinates, the others will default to zero
            bool read_x = xtok<ntok && xtok>=0;
            bool read_y = ytok<ntok && ytok>=0;
            bool read_z = ztok<ntok && ztok>=0;
            if(read_x || read_y || read_z) {
               double x = (read_x)? boost::lexical_cast<double>(tokens[xtok]) : 0.0;
               double y = (read_y)? boost::lexical_cast<double>(tokens[ytok]) : 0.0;
               double z = (read_z)? boost::lexical_cast<double>(tokens[ztok]) : 0.0;
               tmp_pos.push_back(pos3d(x,y,z));
            }
         }
      }
   }

   if(tmp_pos.size() == 0) throw logic_error("pointcloud: no points read from file, please check parameters and file format");

   m_arr = create_array(tmp_pos);
}

pointcloud::~pointcloud()
{
   m_arr->Resize(0);
   m_arr->Release();
}

size_t pointcloud::size() const
{
   return m_arr->GetSize();
}

bbox3d pointcloud::get_box() const
{
   as_vector<pos3*> points(m_arr);

   bbox3d box;
   for(size_t ivert=0; ivert<points.size(); ivert++) {
      const pos3* p = points[ivert];
      box.enclose(p->pos());
   }
   return box;
}

CScriptArray* pointcloud::create_array(const vector<pos3d>& pos)
{
   CScriptArray* arr = CreateScriptArrayEmpty("pos3d@",pos.size());
   for(size_t i=0; i<pos.size(); i++) {

      // create script object and assign to array
      pos3* p = new pos3(pos[i]);
      arr->SetValue((asUINT)i,const_cast<pos3**>(&p));

      // assigning the pos3 object to the array increases the reference count,
      // so we must decrement here because we don't keep the original
      p->Release();
   }
   return arr;
}

CScriptArray* pointcloud::points_array() const
{
   return m_arr;
}
