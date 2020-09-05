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

#ifndef XCSG_VECTOR_H
#define XCSG_VECTOR_H

#include <string>
#include "spaceio/xml_node.h"

template <typename T>
class xcsg_vector {
public:
   xcsg_vector(T& vec, const std::string& tag = ""): m_vec(vec), m_tag(tag) {}
   virtual ~xcsg_vector() {}

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent)
   {
      spaceio::xml_node xml_this = (m_tag.length() > 0)? xml_parent.add_child(m_tag) : xml_parent;
      for(size_t i=0;i<m_vec.size(); i++) {
         if(m_vec[i]) m_vec[i]->to_xcsg(xml_this);
      }
      return xml_this;
   }

private:
   T&    m_vec;
   std::string m_tag;
};



#endif // XCSG_VECTOR_H
