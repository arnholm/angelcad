#ifndef AS_INITIALIZER_LIST_H
#define AS_INITIALIZER_LIST_H

#include <vector>
#include <stdexcept>
#include <string.h>
#include "ce_angelscript/ce_angelscript.h"

// basic initializer list for fundamental types, ilel T=double or int

template <class T>
class as_initializer_vector {
public:

   // this constructor throws exception if initializer list is not of required length
   as_initializer_vector(size_t required_length, void* initlist);

   // this constructor accepts any length
   as_initializer_vector(void* initlist);

   // destructor
   virtual ~as_initializer_vector();

   // size of vector after construction
   size_t size() const { return m_data.size(); }

   // read only operator
   const T operator[](size_t index) const { return m_data[index]; }

protected:

private:
   std::vector<T> m_data;
};

template <class T>
as_initializer_vector<T>::as_initializer_vector(size_t required_length, void* initlist)
{
   // Determine the length of the initializer list
   asUINT length = *(asUINT*)initlist;
   if(length != required_length) {
      ::memset(((asUINT*)initlist), 0, 1+length*sizeof(T) );
      throw std::logic_error("Initializer list has length="+ std::to_string(length) + ", required length=" + std::to_string(required_length));
   }

   m_data.reserve(length);
   T* value = reinterpret_cast<T*>(((asUINT*)initlist)+1);
   for(size_t i=0;i<length;i++) {
      m_data.push_back(*value++);
   }
   ::memset(((asUINT*)initlist), 0, 1+length*sizeof(T) );
}

template <class T>
as_initializer_vector<T>::as_initializer_vector(void* initlist)
{
   // Determine the length of the initializer list
   asUINT length = *(asUINT*)initlist;
   m_data.reserve(length);
   T* value = reinterpret_cast<T*>(((asUINT*)initlist)+1);
   for(size_t i=0;i<length;i++) {
      m_data.push_back(*value++);
   }
   ::memset(((asUINT*)initlist), 0, 1+length*sizeof(T) );
}

template <class T>
as_initializer_vector<T>::~as_initializer_vector()
{}


#endif // AS_INITIALIZER_LIST_H
