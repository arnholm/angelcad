
class IStream {
   /*
    \return IStream&
   */
  IStream& clearbuffer();
   /*
    \param szString string&
    \return IStream&
   */
  IStream& getline(string&out szString);
   /*
    \param szString string&
    \param szDelim const string&
    \return IStream&
   */
  IStream& getline(string&out szString, const string&in szDelim);
   /*
    \param n int64
    \param szDelim const string&
    \return IStream&
   */
  IStream& ignore(int64 n = 1, const string&in szDelim = EOF);
   /*
    \param fValue bool
    \return IStream&
   */
  IStream& opShr(bool&out fValue);
   /*
    \param flValue double
    \return IStream&
   */
  IStream& opShr(double&out flValue);
   /*
    \param flValue float
    \return IStream&
   */
  IStream& opShr(float&out flValue);
   /*
    \param iValue int
    \return IStream&
   */
  IStream& opShr(int&out iValue);
   /*
    \param iValue int16
    \return IStream&
   */
  IStream& opShr(int16&out iValue);
   /*
    \param iValue int64
    \return IStream&
   */
  IStream& opShr(int64&out iValue);
   /*
    \param szString string&
    \return IStream&
   */
  IStream& opShr(string&out szString);
   /*
    \param uiValue uint
    \return IStream&
   */
  IStream& opShr(uint&out uiValue);
   /*
    \param uiValue uint16
    \return IStream&
   */
  IStream& opShr(uint16&out uiValue);
   /*
    \param uiValue uint64
    \return IStream&
   */
  IStream& opShr(uint64&out uiValue);
   /*
    \param iOffset int64
    \param way seekdir
    \return IStream&
   */
  IStream& seekg(int64 iOffset, seekdir way);
   /*
    \param iPos int64
    \return IStream&
   */
  IStream& seekg(int64 iPos);
   /*
    \return bool
   */
  bool bad() const;
   /*
    \return bool
   */
  bool eof() const;
   /*
    \return bool
   */
  bool fail() const;
   /*
    \return bool
   */
  bool good() const;
   /*
    \return bool
   */
  bool opImplConv() const;
   /*
    \return int64
   */
  int64 tellg() const;
  void clear();
};

class OStream {
   /*
    \return OStream&
   */
  OStream& flush();
   /*
    \param fValue bool
    \return OStream&
   */
  OStream& opShl(bool fValue);
   /*
    \param szString const string&
    \return OStream&
   */
  OStream& opShl(const string&in szString);
   /*
    \param flValue double
    \return OStream&
   */
  OStream& opShl(double flValue);
   /*
    \param flValue float
    \return OStream&
   */
  OStream& opShl(float flValue);
   /*
    \param iValue int64
    \return OStream&
   */
  OStream& opShl(int64 iValue);
   /*
    \param uiValue uint64
    \return OStream&
   */
  OStream& opShl(uint64 uiValue);
   /*
    \param iOffset int64
    \param way seekdir
    \return OStream&
   */
  OStream& seekp(int64 iOffset, seekdir way);
   /*
    \param iPos int64
    \return OStream&
   */
  OStream& seekp(int64 iPos);
   /*
    \return bool
   */
  bool bad() const;
   /*
    \return bool
   */
  bool eof() const;
   /*
    \return bool
   */
  bool fail() const;
   /*
    \return bool
   */
  bool good() const;
   /*
    \return bool
   */
  bool opImplConv() const;
   /*
    \return int64
   */
  int64 tellp() const;
  void clear();
};

class aatc_funcpointer {
   aatc_funcpointer();
   /*
    \param  string
    \return bool
   */
  bool Set(string);
   /*
    \param  string
    \return bool
   */
  bool Set(string, ?&in);
  void Call();
};

class array {
   /*
    \param  int
   */
   array(int&in);
   /*
    \param  int
    \param length uint
   */
   array(int&in, uint length);
   /*
    \param  int
    \param length uint
    \param value const T&
   */
   array(int&in, uint length, const T&in value);
   /*
    \param index uint
    \return T&
   */
  T& opIndex(uint index);
   /*
    \param  const array&@
    \return array&@
   */
  T[]& opAssign(const T[]&in);
   /*
    \return bool
   */
  bool empty() const;
   /*
    \return bool
   */
  bool isEmpty() const;
   /*
    \param  const array&@
    \return bool
   */
  bool opEquals(const T[]&in) const;
   /*
    \param index uint
    \return const T&
   */
  const T& opIndex(uint index) const;
   /*
    \param value const T&
    \return int
   */
  int find(const T&in value) const;
   /*
    \param startAt uint
    \param value const T&
    \return int
   */
  int find(uint startAt, const T&in value) const;
   /*
    \param value const T&
    \return int
   */
  int findByRef(const T&in value) const;
   /*
    \param startAt uint
    \param value const T&
    \return int
   */
  int findByRef(uint startAt, const T&in value) const;
   /*
    \return uint
   */
  uint get_length() const;
   /*
    \return uint
   */
  uint length() const;
   /*
    \return uint
   */
  uint size() const;
   /*
    \param  uint
   */
  void erase(uint);
   /*
    \param  uint
    \param  const T&
   */
  void insert(uint, const T&in);
   /*
    \param index uint
    \param value const T&
   */
  void insertAt(uint index, const T&in value);
   /*
    \param value const T&
   */
  void insertLast(const T&in value);
  void pop_back();
   /*
    \param  const T&
   */
  void push_back(const T&in);
   /*
    \param index uint
   */
  void removeAt(uint index);
  void removeLast();
   /*
    \param length uint
   */
  void reserve(uint length);
   /*
    \param length uint
   */
  void resize(uint length);
  void reverse();
   /*
    \param  uint
   */
  void set_length(uint);
  void sortAsc();
   /*
    \param startAt uint
    \param count uint
   */
  void sortAsc(uint startAt, uint count);
  void sortDesc();
   /*
    \param startAt uint
    \param count uint
   */
  void sortDesc(uint startAt, uint count);
};

class as_reftype {
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return string
   */
  string Type() const;
};

/* 
 A bounding box representes the range of an object in x,y and z
*/ 
class boundingbox {
   /*
   constructor
   creates an empty/uninitialised bounding box
   */
   boundingbox();
   /*
    \return bool
   */
  bool is_empty() const;
   /*
    \return double
   */
  double diagonal() const;
   /*
   bounding box extent
    \return double, bounding box extent in x-direction
   */
  double dx() const;
   /*
   bounding box extent
    \return double, bounding box extent in y-direction
   */
  double dy() const;
   /*
   bounding box extent
    \return double, bounding box extent in z-direction
   */
  double dz() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   center position
    \return pos3d@, bounding box geometric center
   */
  pos3d@ center() const;
   /*
   low position
    \return pos3d@, position containing minimum x,y,z
   */
  pos3d@ p1() const;
   /*
   high position
    \return pos3d@, position containing maximum x,y,z
   */
  pos3d@ p2() const;
   /*
    \return string
   */
  string Type() const;
   /*
   enclose a new position, this may extend the boundingbox
    \param p pos3d@, position to enclose
   */
  void enclose(pos3d@ p);
};

/* 
 A 2d object defined by its radius. Centered on origin.
*/ 
class circle : public shape2d {
   /*
    \param p1 pos2d@
    \param p2 pos2d@
    \param p3 pos2d@
   */
   circle(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3);
   /*
   constructor
    \param r double, radius of circle
   */
   circle(double r);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   radius of circle
    \return double, radius of circle
   */
  double r() const;
   /*
   radius of circle
    \return double, radius of circle
   */
  double radius() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 A cone extends in the z-direction.
 By default the bottom is at origin
*/ 
class cone : public solid {
   /*
   constructor
    \param h double, height of cone
    \param r1 double, bottom radius of cone
    \param r2 double, top radius of cone
    \param center bool, true if cone is centered in z-direction
   */
   cone(double h, double r1, double r2, bool center = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   height of cone
    \return double, height of cone
   */
  double h() const;
   /*
   height of cone
    \return double, height of cone
   */
  double height() const;
   /*
   bottom radius
    \return double, bottom radius
   */
  double r1() const;
   /*
   top radius
    \return double, top radius
   */
  double r2() const;
   /*
   bottom radius
    \return double, bottom radius
   */
  double radius1() const;
   /*
   top radius
    \return double, top radius
   */
  double radius2() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

class cube : public solid {
   /*
    \param size double
    \param center bool
   */
   cube(double size, bool center = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return double
   */
  double size() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
    \param b solid@
    \return solid@
   */
  solid@ opAdd(solid@ b);
   /*
    \param b solid@
    \return solid@
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
    \param b solid@
    \return solid@
   */
  solid@ opSub(solid@ b);
   /*
    \return string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \param path string
   */
  void write_csg(string path);
   /*
    \param path string
    \param secant_tolerance double
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 A cuboid is like a cube, but with separate dimensions in x,y and z.
 By default the cuboid touches the origin, and extends along positive x,y,z.
*/ 
class cuboid : public solid {
   /*
   constructor
    \param dx double, length in x-drection
    \param dy double, length of y-direction
    \param dz double, length of z-direction
    \param center bool, true if cuboid is centered on origin
   */
   cuboid(double dx, double dy, double dz, bool center = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   length in x-drection
    \return double, length in x-drection
   */
  double dx() const;
   /*
   length in y-drection
    \return double, length in x-drection
   */
  double dy() const;
   /*
   length in z-drection
    \return double, length in x-drection
   */
  double dz() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 A cylinder is defined by height and radius.
 By default the cuboid extends from the origin, in z-direction.
*/ 
class cylinder : public solid {
   /*
   constructor
    \param h double, height of cylinder
    \param r double, radius of cylinder
    \param center bool, true if cylinder is centered on origin in z-direction
   */
   cylinder(double h, double r, bool center = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   Height of cylnder
    \return double, height of cylnder
   */
  double h() const;
   /*
   Height of cylnder
    \return double, height of cylnder
   */
  double height() const;
   /*
   Radius of cylnder
    \return double, radius of cylnder
   */
  double r() const;
   /*
   Radius of cylnder
    \return double, radius of cylnder
   */
  double radius() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

class dictionary {
   dictionary();
   /*
    \param  const string&
    \return bool
   */
  bool delete(const string&in);
   /*
    \return bool
   */
  bool empty() const;
   /*
    \param  const string&
    \return bool
   */
  bool exists(const string&in) const;
   /*
    \param  const string&
    \return bool
   */
  bool get(const string&in, ?&out) const;
   /*
    \param  const string&
    \param  double
    \return bool
   */
  bool get(const string&in, double&out) const;
   /*
    \param  const string&
    \param  int64
    \return bool
   */
  bool get(const string&in, int64&out) const;
   /*
    \return bool
   */
  bool isEmpty() const;
   /*
    \param  const string&
    \return const dictionaryValue&
   */
  const dictionaryValue& opIndex(const string&in) const;
   /*
    \param  const dictionary&@
    \return dictionary&@
   */
  dictionary& opAssign(const dictionary&in);
   /*
    \param  const string&
    \return dictionaryValue&
   */
  dictionaryValue& opIndex(const string&in);
   /*
    \return array@
   */
  string[]@ getKeys() const;
   /*
    \return uint
   */
  uint getSize() const;
   /*
    \return uint
   */
  uint size() const;
  void clear();
  void deleteAll();
   /*
    \param  const string&
   */
  void erase(const string&in);
   /*
    \param  const string&
   */
  void set(const string&in, const ?&in);
   /*
    \param  const string&
    \param  double
   */
  void set(const string&in, const double&in);
   /*
    \param  const string&
    \param  int64
   */
  void set(const string&in, const int64&in);
};

class dictionaryValue {
   /*
    \return dictionaryValue&
   */
  dictionaryValue& opAssign(const ?&in);
   /*
    \param  const dictionaryValue&
    \return dictionaryValue&
   */
  dictionaryValue& opAssign(const dictionaryValue&in);
   /*
    \param  double
    \return dictionaryValue&
   */
  dictionaryValue& opAssign(double);
   /*
    \param  int64
    \return dictionaryValue&
   */
  dictionaryValue& opAssign(int64);
   /*
    \return dictionaryValue&
   */
  dictionaryValue& opHndlAssign(const ?&in);
   /*
    \return double
   */
  double opConv();
   /*
    \return int64
   */
  int64 opConv();
  void opCast(?&out);
  void opConv(?&out);
};

/* 
 difference2d is a 2-dimensional boolean operation. It can be invoked either
 explicitly or using subtraction operator:
 explicit: shape2d@ object = difference2d(circle(100),circle(50));
 using subtraction operator: shape2d@ object = circle(100) - circle(50);
*/ 
class difference2d : public shape2d {
   /*
   constructor
    \param incl shape2d@, object to be included
    \param excl shape2d@, object to be excluded (subtracted)
   */
   difference2d(shape2d@ incl, shape2d@ excl);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 difference3d is a 3-dimensional boolean operation. It can be invoked either
 explicitly or using subtraction operator:
 explicit: solid@ object = difference3d(sphere(100),sphere(50));
 using subtraction operator: solid@ object = sphere(100) - sphere(50);
*/ 
class difference3d : public solid {
   /*
   constructor
    \param incl solid@, objects to be included
    \param excl solid@, objects to be excluded (subtracted)
   */
   difference3d(solid@ incl, solid@ excl);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 fill2d is a 2-dimensional boolean operation that removes internal holes
 in in 2d shapes, but leaves a possibly concave outer contour intact.
 fill2d can be invoked either on a single shape2d or an array.
*/ 
class fill2d : public shape2d {
   /*
   constructor
    \param s1 shape2d@, 2d shape
   */
   fill2d(const shape2d@ s1);
   /*
    \param arr array@
   */
   fill2d(shape2d@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param b shape2d@
    \return shape2d@
   */
  shape2d@ opAdd(shape2d@ b);
   /*
    \param b shape2d@
    \return shape2d@
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
    \param b shape2d@
    \return shape2d@
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \param path string
   */
  void write_csg(string path);
   /*
    \param path string
    \param secant_tolerance double
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 hmatrix is a transformation expressed as homogenous transformation matrix.
*/ 
class hmatrix : public tmatrix {
   /*
    \param xvec vec3d@
    \param yvec vec3d@
    \param pos pos3d@
   */
   hmatrix(const vec3d@ xvec, const vec3d@ yvec, const pos3d@ pos = pos3d ( 0 , 0 , 0 ));
   /*
   constructor, 4 column values
    \param xvec vec3d@, 1st matrix column
    \param yvec vec3d@, 2nd matrix column
    \param zvec vec3d@, 3rd matrix column
    \param pos pos3d@, 4rd matrix column
   */
   hmatrix(const vec3d@ xvec, const vec3d@ yvec, const vec3d@ zvec, const pos3d@ pos = pos3d ( 0 , 0 , 0 ));
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
    \return string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 hull2d is a 2-dimensional boolean operation. It encapsulates
 the input objects with a convex shape. It can for example be used
 to create a rectangle with rounded cornes using 4 circles.
*/ 
class hull2d : public shape2d {
   /*
   constructor
    \param s1 shape2d@, shape
    \param s2 shape2d@, shape
   */
   hull2d(const shape2d@ s1, const shape2d@ s2);
   /*
   constructor
    \param s1 shape2d@, shape
    \param s2 shape2d@, shape
    \param s3 shape2d@, shape
   */
   hull2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3);
   /*
   constructor
    \param s1 shape2d@, shape
    \param s2 shape2d@, shape
    \param s3 shape2d@, shape
    \param s4 shape2d@, shape
   */
   hull2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4);
   /*
   constructor
    \param s1 shape2d@, shape
    \param s2 shape2d@, shape
    \param s3 shape2d@, shape
    \param s4 shape2d@, shape
    \param s5 shape2d@, shape
   */
   hull2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4, const shape2d@ s5);
   /*
    \param arr array@
   */
   hull2d(shape2d@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 hull3d is a 3-dimensional boolean operation. It encapsulates
 the input objects with a convex shape. It can for example be used
 to create a cuboid with rounded cornes using 8 spheres.
*/ 
class hull3d : public solid {
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
   */
   hull3d(const solid@ s1, const solid@ s2);
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
    \param s3 solid@, solid
   */
   hull3d(const solid@ s1, const solid@ s2, const solid@ s3);
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
    \param s3 solid@, solid
    \param s4 solid@, solid
   */
   hull3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4);
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
    \param s3 solid@, solid
    \param s4 solid@, solid
    \param s5 solid@, solid
   */
   hull3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4, const solid@ s5);
   /*
    \param arr array@
   */
   hull3d(solid@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 intersection2d is a 2-dimensional boolean operation. It can be invoked either
 explicitly or using & operator:
 explicit: shape2d@ object = intersection2d(circle(100),translate(75,0,0)*circle(50));
 using & operator: shape2d@ object = circle(100) & translate(75,0,0)*circle(50);
*/ 
class intersection2d : public shape2d {
   /*
    \param s1 shape2d@
    \param s2 shape2d@
   */
   intersection2d(const shape2d@ s1, const shape2d@ s2);
   /*
    \param s1 shape2d@
    \param s2 shape2d@
    \param s3 shape2d@
   */
   intersection2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3);
   /*
    \param s1 shape2d@
    \param s2 shape2d@
    \param s3 shape2d@
    \param s4 shape2d@
   */
   intersection2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4);
   /*
    \param s1 shape2d@
    \param s2 shape2d@
    \param s3 shape2d@
    \param s4 shape2d@
    \param s5 shape2d@
   */
   intersection2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4, const shape2d@ s5);
   /*
    \param arr array@
   */
   intersection2d(shape2d@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 intersection3d is a 2-dimensional boolean operation. It can be invoked either
 explicitly or using & operator:
 explicit: solid@ object = intersection3d(sphere(100),translate(75,0,0)*sphere(50));
 using & operator: solid@ object = sphere(100) & translate(75,0,0)*sphere(50);
*/ 
class intersection3d : public solid {
   /*
    \param s1 solid@
    \param s2 solid@
   */
   intersection3d(const solid@ s1, const solid@ s2);
   /*
    \param s1 solid@
    \param s2 solid@
    \param s3 solid@
   */
   intersection3d(const solid@ s1, const solid@ s2, const solid@ s3);
   /*
    \param s1 solid@
    \param s2 solid@
    \param s3 solid@
    \param s4 solid@
   */
   intersection3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4);
   /*
    \param s1 solid@
    \param s2 solid@
    \param s3 solid@
    \param s4 solid@
    \param s5 solid@
   */
   intersection3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4, const solid@ s5);
   /*
    \param arr array@
   */
   intersection3d(solid@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

class line2d {
   /*
    \param p1 pos2d@
    \param p2 pos2d@
   */
   line2d(const pos2d@ p1, const pos2d@ p2);
   /*
    \return double
   */
  double length() const;
   /*
    \param point pos2d@
    \return double
   */
  double project(pos2d@ point) const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return pos2d@
   */
  pos2d@ end1() const;
   /*
    \return pos2d@
   */
  pos2d@ end2() const;
   /*
    \param par double
    \return pos2d@
   */
  pos2d@ interpolate(double par) const;
   /*
    \return string
   */
  string Type() const;
};

class line3d {
   /*
    \param p1 pos3d@
    \param p2 pos3d@
   */
   line3d(const pos3d@ p1, const pos3d@ p2);
   /*
    \return double
   */
  double length() const;
   /*
    \param point pos3d@
    \return double
   */
  double project(pos3d@ point) const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return pos3d@
   */
  pos3d@ end1() const;
   /*
    \return pos3d@
   */
  pos3d@ end2() const;
   /*
    \param par double
    \return pos3d@
   */
  pos3d@ interpolate(double par) const;
   /*
    \return string
   */
  string Type() const;
};

/* 
 linear_extrude extrudes a 2d shape in z-direction, creating a solid.
*/ 
class linear_extrude : public solid {
   /*
   constructor
    \param shape shape2d@, 2d profile to be extruded
    \param height double, distance in z direction to extrude
   */
   linear_extrude(const shape2d@ shape, double height);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   extrusion height
    \return double, extrusion height
   */
  double height() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting 2d shape
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 a locsys3d represents local coordinate system directions.
*/ 
class locsys3d {
   /*
   constructor
    \param xvec vec3d@, local x-direction vector
    \param zvec vec3d@, local z-direction vector
   */
   locsys3d(const vec3d@ xvec, const vec3d@ zvec);
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
   local x-direction vector
    \return vec3d@, local x-direction vector
   */
  vec3d@ x() const;
   /*
   local y-direction vector
    \return vec3d@, local y-direction vector
   */
  vec3d@ y() const;
   /*
   local z-direction vector
    \return vec3d@, local z-direction vector
   */
  vec3d@ z() const;
};

class map {
   /*
    \param  int
   */
   map(int&in);
   /*
    \param  int
    \param  map@
   */
   map(int&in, map<T_key,T_value>@);
   /*
    \param  const T_key&
    \return T_value&
   */
  T_value& find(const T_key&in);
   /*
    \param  const T_key&
    \param  bool
    \return T_value&
   */
  T_value& find(const T_key&in, bool&out);
   /*
    \param  const T_key&
    \return bool
   */
  bool contains(const T_key&in);
   /*
    \return bool
   */
  bool empty();
   /*
    \param  const map_iterator&
    \return bool
   */
  bool erase(const map_iterator<T_key,T_value>&in);
   /*
    \param  const T_key&
    \return const T_value&
   */
  const T_value& get_opIndex(const T_key&in) const;
   /*
    \param  const map_iterator&
    \param  const map_iterator&
    \return int
   */
  int erase(const map_iterator<T_key,T_value>&in, const map_iterator<T_key,T_value>&in);
   /*
    \return int
   */
  int size();
   /*
    \param  map@
    \return map&@
   */
  map<T_key,T_value>& opAssign(map<T_key,T_value>@);
   /*
    \param  map&@
    \return map&@
   */
  map<T_key,T_value>& swap(map<T_key,T_value>&inout);
   /*
    \return map_iterator
   */
  map_iterator<T_key,T_value> begin();
   /*
    \return map_iterator
   */
  map_iterator<T_key,T_value> end();
   /*
    \param  const T_key&
    \return map_iterator
   */
  map_iterator<T_key,T_value> find_iterator(const T_key&in);
   /*
    \param  bool
   */
  void SetDirectcomp(bool);
  void clear();
   /*
    \param  const T_key&
   */
  void erase(const T_key&in);
   /*
    \param  const T_key&
    \param  const T_value&
   */
  void insert(const T_key&in, const T_value&in);
   /*
    \param  const T_key&
    \param  const T_value&
   */
  void set_opIndex(const T_key&in, const T_value&in);
};

class map_iterator {
   /*
    \return T_value&
   */
  T_value& current_value();
   /*
    \return T_value&
   */
  T_value& get_value();
   /*
    \return bool
   */
  bool IsEnd();
   /*
    \return bool
   */
  bool IsValid();
   /*
    \return bool
   */
  bool next();
   /*
    \param  const map_iterator&
    \return bool
   */
  bool opEquals(const map_iterator<T_key,T_value>&in);
   /*
    \return bool
   */
  bool opPostInc();
   /*
    \return bool
   */
  bool opPreInc();
   /*
    \return const T_key&
   */
  const T_key& current_key();
   /*
    \return const T_key&
   */
  const T_key& get_key();
   /*
    \param  const map_iterator&
    \return map_iterator&
   */
  map_iterator<T_key,T_value>& opAssign(const map_iterator<T_key,T_value>&in);
   /*
    \param  const T_value&
   */
  void set_value(const T_value&in);
};

/* 
 minkowski2d is a 2-dimensional boolean operation requiring exactly
 2 parameters, a and b. The first parameter (a) is generally the larger
 and can be concave or convex. The second parameter (b) is assumed smaller
 and convex (such as a circle). Typical use of the minkowski sum is to
 create an object with rounded corners.
*/ 
class minkowski2d : public shape2d {
   /*
   constructor
    \param a shape2d@, convex/concave object to be modified
    \param b shape2d@, convex 'tool' object
   */
   minkowski2d(const shape2d@ a, const shape2d@ b);
   /*
   return bounding box
    \return boundingbox@, The bounding box of the minkowski sum
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param b shape2d@
    \return shape2d@
   */
  shape2d@ opAdd(shape2d@ b);
   /*
    \param b shape2d@
    \return shape2d@
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
    \param b shape2d@
    \return shape2d@
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \param path string
   */
  void write_csg(string path);
   /*
    \param path string
    \param secant_tolerance double
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 minkowski3d is a 3-dimensional boolean operation requiring exactly
 2 parameters, a and b. The first parameter (a) is generally the larger
 and can be concave or convex. The second parameter (b) is assumed smaller
 and convex (such as a circle). Typical use of the minkowski sum is to
 create an object with rounded edges.
*/ 
class minkowski3d : public solid {
   /*
    \param a solid@
    \param b solid@
   */
   minkowski3d(const solid@ a, const solid@ b);
   /*
   return bounding box
    \return boundingbox@, The bounding box of the minkowski sum
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
    \param b solid@
    \return solid@
   */
  solid@ opAdd(solid@ b);
   /*
    \param b solid@
    \return solid@
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
    \param b solid@
    \return solid@
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \param path string
   */
  void write_csg(string path);
   /*
    \param path string
    \param secant_tolerance double
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 mirror is a transformation creating mirror images of 2d or 3d objects.
*/ 
class mirror : public tmatrix {
   /*
   constructor, mirror around origin
    \param dx double, x-component of mirror plane normal
    \param dy double, y-component of mirror plane normal
    \param dz double, z-component of mirror plane normal
   */
   mirror(double dx, double dy, double dz);
   /*
   constructor, mirror around given point
    \param normal vec3d@, mirror plane normal vector
    \param point pos3d@, point in mirror plane
   */
   mirror(vec3d@ normal, pos3d@ point = pos3d ( 0 , 0 , 0 ));
   /*
   mirror transform normal vector, x-component
    \return double, normal vector, x-component
   */
  double dx() const;
   /*
   mirror transform normal vector, y-component
    \return double, normal vector, y-component
   */
  double dy() const;
   /*
   mirror transform normal vector, z-component
    \return double, normal vector,z-component
   */
  double dz() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
    \return string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 offset2d is a special 2d operation used for inflating or shrinking a 2d shape,
 optionally creating rounded corners and chamfers.
*/ 
class offset2d : public shape2d {
   /*
   constructor
    \param profile shape2d@, 2d profile to be offset
    \param r double, radius if rounded offset required (cannot be combined with delta)
    \param delta double, straight offset if shart corners required (cannot be combined with r)
    \param chamfer bool, true if sharp corners to be chamfered (relevant with delta only)
   */
   offset2d(const shape2d@ profile, double r = 0x7fc00000, double delta = 0x7fc00000, bool chamfer = false);
   /*
    \param arr array@
    \param r double
    \param delta double
    \param chamfer bool
   */
   offset2d(shape2d@[]@ arr, double r = 0x7fc00000, double delta = 0x7fc00000, bool chamfer = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 pface represents a single face of a polyhedron. It contains integer indices
 referring to the polyhedron vertices. When viewed from outside the polyhedron,
 a pface should list its vertices in CCW sequence.
*/ 
class pface {
   /*
   polyhedron face constructor
    \param iv1 uint, polyhedron vertex index
    \param iv2 uint, polyhedron vertex index
    \param iv3 uint, polyhedron vertex index
   */
   pface(uint iv1, uint iv2, uint iv3);
   /*
   polyhedron face constructor
    \param iv1 uint, polyhedron vertex index
    \param iv2 uint, polyhedron vertex index
    \param iv3 uint, polyhedron vertex index
    \param iv4 uint, polyhedron vertex index
   */
   pface(uint iv1, uint iv2, uint iv3, uint iv4);
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
   number of vertices in face
    \return uint, number of vertices in face
   */
  uint nvert() const;
   /*
   polyhedron vertex index for face index
    \param iv uint, face index
    \return uint, polyhedron face index
   */
  uint vindex(uint iv) const;
};

/* 
 a polygon is a 2d object. It is defined by vertex positions listed in CCW sequence.
*/ 
class polygon : public shape2d {
   /*
   constructor (triangle), points must be given in CCW order
    \param p1 pos2d@, position
    \param p2 pos2d@, position
    \param p3 pos2d@, position
   */
   polygon(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3);
   /*
   constructor (quadrilateral), points must be given in CCW order
    \param p1 pos2d@, position
    \param p2 pos2d@, position
    \param p3 pos2d@, position
    \param p4 pos2d@, position
   */
   polygon(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3, const pos2d@ p4);
   /*
   constructor (pentagon), points must be given in CCW order
    \param p1 pos2d@, position
    \param p2 pos2d@, position
    \param p3 pos2d@, position
    \param p4 pos2d@, position
    \param p5 pos2d@, position
   */
   polygon(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3, const pos2d@ p4, const pos2d@ p5);
   /*
   constructor (spline), points must be given in CCW order
    \param spline spline2d@, 2d spline curve defining polygon profile
    \param nseg uint, number of straight segments for spline
   */
   polygon(const spline2d@ spline, uint nseg = 30);
   /*
    \param r double
    \param np uint
   */
   polygon(double r, uint np);
   /*
    \param points array@
    \param check bool
   */
   polygon(pos2d@[]@ points, bool check = true);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   Polygon area
   return computed area of polygon
    \return double
   */
  double area() const;
   /*
   Signed polygon area, return negative area for polygons oriented CW
   return signed computed area of polygon
    \return double
   */
  double signed_area() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param iv uint
    \return pos2d@
   */
  pos2d@ vertex(uint iv) const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   number of polygon points
    \return uint, number of polygon points
   */
  uint size() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 a polyhedron is a general 3d object, defined by its vertices and polyhedron faces.
 It is useful in many contexts. It can be constructed directly or by reference to an input file.
*/ 
class polyhedron : public solid {
   /*
    \param points array@
   */
   polyhedron(pos3d@[]@ points);
   /*
    \param points array@
    \param faces array@
   */
   polyhedron(pos3d@[]@ points, pface@[]@ faces);
   /*
    \param file string
    \param id int
   */
   polyhedron(string file, int id = - 1);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   polyhedron face area
    \param iface uint, index of polyhedron face
    \return double, computed area of polyhedron face
   */
  double face_area(uint iface) const;
   /*
   polyhedron volume
    \return double, computed volume of polyhedron
   */
  double volume() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   polyhedron face
    \param iface uint, index of polyhedron face
    \return pface@, polyhedron face
   */
  pface@ face(uint iface) const;
   /*
   polyhedron vertex
    \param iv uint, index of polyhedron vertex
    \return pos3d@, polyhedron vertex position
   */
  pos3d@ vertex(uint iv) const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@, object to union with this object
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@, object to intersect with this object
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@, object to subtract from this object
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Number of faces
    \return uint, number of faces in polyhedron
   */
  uint nface() const;
   /*
   Number of vertices
    \return uint, number of vertices in polyhedron
   */
  uint nvert() const;
   /*
   Flip polyhedron face normal
    \param iface uint, index of polyhedron face
   */
  void flip_face(uint iface);
   /*
   Flip all polyhedron face normals
   */
  void flip_faces();
   /*
   Set vertex position
    \param iv uint, index of polyhedron vertex
    \param pos pos3d@, new position of vertex
   */
  void set_vertex(uint iv, pos3d@ pos);
  void verify() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 a pos2d is a position in 2d space. It is used with 2d objects.
*/ 
class pos2d {
   /*
    \param other pos2d@
   */
   pos2d(const pos2d@ other);
   /*
   constructor
    \param x double, coordinate
    \param y double, coordinate
   */
   pos2d(double x, double y);
   /*
   distance from other position
    \param pos pos2d@, other position
    \return double, distance from pos
   */
  double dist(const pos2d@ pos) const;
   /*
   x coordinate
    \return double, x coordinate
   */
  double x() const;
   /*
   y coordinate
    \return double, y coordinate
   */
  double y() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param p1 pos2d@
    \return pos2d@
   */
  pos2d@ opAdd(pos2d@ p1);
   /*
    \param v1 vec2d@
    \return pos2d@
   */
  pos2d@ opAdd(vec2d@ v1);
   /*
    \param v1 vec2d@
    \return pos2d@
   */
  pos2d@ opAdd_r(vec2d@ v1);
   /*
    \param f1 double
    \return pos2d@
   */
  pos2d@ opMul(double f1);
   /*
    \param f1 double
    \return pos2d@
   */
  pos2d@ opMul_r(double f1);
   /*
    \param v1 vec2d@
    \return pos2d@
   */
  pos2d@ opSub(vec2d@ v1);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
};

/* 
 a pos3d is a position in 3d space. It is used with 3d objects.
*/ 
class pos3d {
   /*
    \param other pos3d@
   */
   pos3d(const pos3d@ other);
   /*
   constructor
    \param x double, coordinate
    \param y double, coordinate
    \param z double, coordinate
   */
   pos3d(double x, double y, double z);
   /*
   distance from other position
    \param pos pos3d@, other position
    \return double, distance from pos
   */
  double dist(const pos3d@ pos) const;
   /*
   x coordinate
    \return double, x coordinate
   */
  double x() const;
   /*
   y coordinate
    \return double, y coordinate
   */
  double y() const;
   /*
   z coordinate
    \return double, z coordinate
   */
  double z() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param p1 pos3d@
    \return pos3d@
   */
  pos3d@ opAdd(pos3d@ p1);
   /*
    \param v1 vec3d@
    \return pos3d@
   */
  pos3d@ opAdd(vec3d@ v1);
   /*
    \param v1 vec3d@
    \return pos3d@
   */
  pos3d@ opAdd_r(vec3d@ v1);
   /*
    \param f1 double
    \return pos3d@
   */
  pos3d@ opMul(double f1);
   /*
    \param f1 double
    \return pos3d@
   */
  pos3d@ opMul_r(double f1);
   /*
    \param v1 vec3d@
    \return pos3d@
   */
  pos3d@ opSub(vec3d@ v1);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
};

/* 
 a rectangle is a 2d object defined by its extent in x and y. By default it touches the
 origin and extends along positive x and y.
*/ 
class rectangle : public shape2d {
   /*
   constructor
    \param dx double, extent in x direction
    \param dy double, extent in y direction
    \param center bool, true if rectangle should be centered on origin
   */
   rectangle(double dx, double dy, bool center = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   extent in x direction
    \return double, extent in x direction
   */
  double dx() const;
   /*
   extent in y direction
    \return double, extent in y direction
   */
  double dy() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 rotate_extrude allows extruding a 2d shape along a circular path. A positive
 angle rotates the object around the y axis (CCW direction).
 solid@ object = rotate_extrude(translate(100,0)*circle(10),deg:60);
*/ 
class rotate_extrude : public solid {
   /*
   constructor
    \param shape shape2d@, 2d profile shape to extrude
    \param deg double, rotation in degrees. Rotation is CCW around y axis.
    \param pitch double, distance to offset profile in y direction for each revolution
   */
   rotate_extrude(const shape2d@ shape, double deg, double pitch = 0.0);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   extrusion angle in degrees
    \return double, extrusion angle in degrees
   */
  double deg() const;
   /*
   extrusion angle in radians
    \return double, extrusion angle in radians
   */
  double rad() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 rotate_x is a transformation rotating around the x-axis. Positive angle according to right hand rule.
*/ 
class rotate_x : public tmatrix {
   /*
   constructor (rotate around x)
    \param deg double, rotation specified in degrees (cannot be combined with rad)
    \param rad double, rotation specified in radians (cannot be combined with deg)
   */
   rotate_x(double deg = 0x7fc00000, double rad = 0x7fc00000);
   /*
   rotation angle in degrees
    \return double, rotation angle in degrees
   */
  double deg() const;
   /*
   rotation angle in radians
    \return double, rotation angle in radians
   */
  double rad() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 rotate_y is a transformation rotating around the y-axis. Positive angle according to right hand rule.
*/ 
class rotate_y : public tmatrix {
   /*
   constructor (rotate around y)
    \param deg double, rotation specified in degrees (cannot be combined with rad)
    \param rad double, rotation specified in radians (cannot be combined with deg)
   */
   rotate_y(double deg = 0x7fc00000, double rad = 0x7fc00000);
   /*
   rotation angle in degrees
    \return double, rotation angle in degrees
   */
  double deg() const;
   /*
   rotation angle in radians
    \return double, rotation angle in radians
   */
  double rad() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 rotate_z is a transformation rotating around the z-axis. Positive angle according to right hand rule.
*/ 
class rotate_z : public tmatrix {
   /*
   constructor (rotate around z)
    \param deg double, rotation specified in degrees (cannot be combined with rad)
    \param rad double, rotation specified in radians (cannot be combined with deg)
   */
   rotate_z(double deg = 0x7fc00000, double rad = 0x7fc00000);
   /*
   rotation angle in degrees
    \return double, rotation angle in degrees
   */
  double deg() const;
   /*
   rotation angle in radians
    \return double, rotation angle in radians
   */
  double rad() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 scale is a transformation scaling an object, either uniformly or with different factors in different directions.
*/ 
class scale : public tmatrix {
   /*
   constructor
    \param s double, scale factor in x,y and z
   */
   scale(double s);
   /*
   constructor
    \param sx double, scale factor in x
    \param sy double, scale factor in y
    \param sz double, scale factor in z
   */
   scale(double sx, double sy, double sz = 1.0);
   /*
   scale factor in x direction
    \return double, scale factor in x direction
   */
  double sx() const;
   /*
   scale factor in y direction
    \return double, scale factor in y direction
   */
  double sy() const;
   /*
   scale factor in z direction
    \return double, scale factor in z direction
   */
  double sz() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

class shape {
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return circle@
   */
  circle@ opCast();
   /*
    \return cone@
   */
  cone@ opCast();
   /*
    \return cube@
   */
  cube@ opCast();
   /*
    \return cuboid@
   */
  cuboid@ opCast();
   /*
    \return cylinder@
   */
  cylinder@ opCast();
   /*
    \return difference2d@
   */
  difference2d@ opCast();
   /*
    \return difference3d@
   */
  difference3d@ opCast();
   /*
    \return fill2d@
   */
  fill2d@ opCast();
   /*
    \return hull2d@
   */
  hull2d@ opCast();
   /*
    \return hull3d@
   */
  hull3d@ opCast();
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return intersection2d@
   */
  intersection2d@ opCast();
   /*
    \return intersection3d@
   */
  intersection3d@ opCast();
   /*
    \return linear_extrude@
   */
  linear_extrude@ opCast();
   /*
    \return minkowski2d@
   */
  minkowski2d@ opCast();
   /*
    \return minkowski3d@
   */
  minkowski3d@ opCast();
   /*
    \return offset2d@
   */
  offset2d@ opCast();
   /*
    \return polygon@
   */
  polygon@ opCast();
   /*
    \return polyhedron@
   */
  polyhedron@ opCast();
   /*
    \return rectangle@
   */
  rectangle@ opCast();
   /*
    \return rotate_extrude@
   */
  rotate_extrude@ opCast();
   /*
    \return shape2d@
   */
  shape2d@ opCast();
   /*
    \return solid@
   */
  solid@ opCast();
   /*
    \return sphere@
   */
  sphere@ opCast();
   /*
    \return square@
   */
  square@ opCast();
   /*
    \return string
   */
  string Type() const;
   /*
    \return sweep@
   */
  sweep@ opCast();
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \return transform_extrude@
   */
  transform_extrude@ opCast();
   /*
    \return union2d@
   */
  union2d@ opCast();
   /*
    \return union3d@
   */
  union3d@ opCast();
   /*
    \param path string
   */
  void write_csg(string path);
   /*
    \param path string
    \param secant_tolerance double
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 shape2d is an abstract base class for all 2d objects.
*/ 
class shape2d : public shape {
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return circle@
   */
  circle@ opCast();
   /*
    \return difference2d@
   */
  difference2d@ opCast();
   /*
    \return fill2d@
   */
  fill2d@ opCast();
   /*
    \return hull2d@
   */
  hull2d@ opCast();
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return intersection2d@
   */
  intersection2d@ opCast();
   /*
    \return minkowski2d@
   */
  minkowski2d@ opCast();
   /*
    \return offset2d@
   */
  offset2d@ opCast();
   /*
    \return polygon@
   */
  polygon@ opCast();
   /*
    \return rectangle@
   */
  rectangle@ opCast();
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
    \return square@
   */
  square@ opCast();
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \return union2d@
   */
  union2d@ opCast();
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 solid is an abstract base class for all 3d objects.
*/ 
class solid : public shape {
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return cone@
   */
  cone@ opCast();
   /*
    \return cube@
   */
  cube@ opCast();
   /*
    \return cuboid@
   */
  cuboid@ opCast();
   /*
    \return cylinder@
   */
  cylinder@ opCast();
   /*
    \return difference3d@
   */
  difference3d@ opCast();
   /*
    \return hull3d@
   */
  hull3d@ opCast();
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return intersection3d@
   */
  intersection3d@ opCast();
   /*
    \return linear_extrude@
   */
  linear_extrude@ opCast();
   /*
    \return minkowski3d@
   */
  minkowski3d@ opCast();
   /*
    \return polyhedron@
   */
  polyhedron@ opCast();
   /*
    \return rotate_extrude@
   */
  rotate_extrude@ opCast();
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
    \return sphere@
   */
  sphere@ opCast();
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return sweep@
   */
  sweep@ opCast();
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \return transform_extrude@
   */
  transform_extrude@ opCast();
   /*
    \return union3d@
   */
  union3d@ opCast();
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 a sphere is a 3d object defined by its radius.
*/ 
class sphere : public solid {
   /*
   constructor
    \param r double, radius
   */
   sphere(double r);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   sphere radius
    \return double, radius
   */
  double r() const;
   /*
   sphere radius
    \return double, radius
   */
  double radius() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 a spline2d is a 2d cubic spline curve.
*/ 
class spline2d {
   /*
    \param points array@
   */
   spline2d(pos2d@[]@ points);
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
};

/* 
 a spline3d is a 3d cubic spline curve.
*/ 
class spline3d {
   /*
    \param points array@
   */
   spline3d(pos3d@[]@ points);
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
};

/* 
 a spline_path defines a cubic spline sweep path.
*/ 
class spline_path {
   /*
    \param p array@
    \param v array@
   */
   spline_path(pos3d@[]@ p, vec3d@[]@ v);
   /*
    \param p array@
    \param v vec3d@
   */
   spline_path(pos3d@[]@ p, vec3d@ v);
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
};

/* 
 a square is a 2d quadrilateral with equal dimensions in x and y.
 By default it touches the origin and extend along positive x and y.
*/ 
class square : public shape2d {
   /*
   constructor
    \param size double, extent in x and y
    \param center bool, true if square to be centered on origon
   */
   square(double size, bool center = false);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
   size of square
    \return double, size of square
   */
  double size() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

class string {
   /*
    \return bool
   */
  bool empty() const;
   /*
    \return bool
   */
  bool isEmpty() const;
   /*
    \param  const string&
    \return bool
   */
  bool opEquals(const string&in) const;
   /*
    \param  uint
    \return uint8
   */
  const uint8& opIndex(uint) const;
   /*
    \param  const string&
    \param start uint
    \return int
   */
  int find(const string&in, uint start = 0) const;
   /*
    \param  const string&
    \param start uint
    \return int
   */
  int findFirst(const string&in, uint start = 0) const;
   /*
    \param  const string&
    \param start int
    \return int
   */
  int findLast(const string&in, int start = - 1) const;
   /*
    \param  const string&
    \return int
   */
  int opCmp(const string&in) const;
   /*
    \param  const string&
    \param start int
    \return int
   */
  int rfind(const string&in, int start = - 1) const;
   /*
    \param  bool
    \return string&
   */
  string& opAddAssign(bool);
   /*
    \param  const string&
    \return string&
   */
  string& opAddAssign(const string&in);
   /*
    \param  double
    \return string&
   */
  string& opAddAssign(double);
   /*
    \param  float
    \return string&
   */
  string& opAddAssign(float);
   /*
    \param  int64
    \return string&
   */
  string& opAddAssign(int64);
   /*
    \param  uint64
    \return string&
   */
  string& opAddAssign(uint64);
   /*
    \param  bool
    \return string&
   */
  string& opAssign(bool);
   /*
    \param  const string&
    \return string&
   */
  string& opAssign(const string&in);
   /*
    \param  double
    \return string&
   */
  string& opAssign(double);
   /*
    \param  float
    \return string&
   */
  string& opAssign(float);
   /*
    \param  int64
    \return string&
   */
  string& opAssign(int64);
   /*
    \param  uint64
    \return string&
   */
  string& opAssign(uint64);
   /*
    \param  bool
    \return string
   */
  string opAdd(bool) const;
   /*
    \param  const string&
    \return string
   */
  string opAdd(const string&in) const;
   /*
    \param  double
    \return string
   */
  string opAdd(double) const;
   /*
    \param  float
    \return string
   */
  string opAdd(float) const;
   /*
    \param  int64
    \return string
   */
  string opAdd(int64) const;
   /*
    \param  uint64
    \return string
   */
  string opAdd(uint64) const;
   /*
    \param  bool
    \return string
   */
  string opAdd_r(bool) const;
   /*
    \param  double
    \return string
   */
  string opAdd_r(double) const;
   /*
    \param  float
    \return string
   */
  string opAdd_r(float) const;
   /*
    \param  int64
    \return string
   */
  string opAdd_r(int64) const;
   /*
    \param  uint64
    \return string
   */
  string opAdd_r(uint64) const;
   /*
    \param start uint
    \param count int
    \return string
   */
  string substr(uint start = 0, int count = - 1) const;
   /*
    \param  uint
    \return uint8
   */
  uint8& opIndex(uint);
   /*
    \return uint
   */
  uint get_length() const;
   /*
    \return uint
   */
  uint length() const;
   /*
    \return uint
   */
  uint size() const;
   /*
    \param  uint
   */
  void resize(uint);
   /*
    \param  uint
   */
  void set_length(uint);
};

/* 
 a sweep creates a solid by sweeping a 2d profile along a path curve
*/ 
class sweep : public solid {
   /*
   constructor
    \param shape shape2d@, 2d profile shape to sweep
    \param path spline_path@, The path cirve to sweep along
   */
   sweep(const shape2d@ shape, const spline_path@ path);
   /*
   return bounding box
    \return boundingbox@, The bounding box of the sweep
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
    \param b solid@
    \return solid@
   */
  solid@ opAdd(solid@ b);
   /*
    \param b solid@
    \return solid@
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
    \param b solid@
    \return solid@
   */
  solid@ opSub(solid@ b);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
    \param path string
   */
  void write_csg(string path);
   /*
    \param path string
    \param secant_tolerance double
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 a tmatrix an abstract base class for all transformations.
*/ 
class tmatrix {
   /*
    \return hmatrix@
   */
  hmatrix@ opCast();
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return mirror@
   */
  mirror@ opCast();
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
    \return rotate_x@
   */
  rotate_x@ opCast();
   /*
    \return rotate_y@
   */
  rotate_y@ opCast();
   /*
    \return rotate_z@
   */
  rotate_z@ opCast();
   /*
    \return scale@
   */
  scale@ opCast();
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return translate@
   */
  translate@ opCast();
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 transform_extrude is a special extrision operation, defined by two 2d shapes,
 representing bottom and top of extrusion.
*/ 
class transform_extrude : public solid {
   /*
    \param bottom shape2d@
    \param top shape2d@
   */
   transform_extrude(const shape2d@ bottom, const shape2d@ top);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 translate is a transformation translating a 2d or 3d object.
*/ 
class translate : public tmatrix {
   /*
    \param v vec3d@
   */
   translate(const vec3d@ v);
   /*
   constructor
    \param dx double, translation in x direction
    \param dy double, translation in y direction
    \param dz double, translation in z direction
   */
   translate(double dx, double dy, double dz = 0.0);
   /*
   translation in x direction
    \return double, translation in x direction
   */
  double dx() const;
   /*
   translation in y direction
    \return double, translation in y direction
   */
  double dy() const;
   /*
   translation in z direction
    \return double, translation in z direction
   */
  double dz() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \param obj pos2d@
    \return pos2d@
   */
  pos2d@ opMul(pos2d@ obj);
   /*
   transform a point: pos3d@ p = T*obj;
    \param obj pos3d@, position to be transformed
    \return pos3d@, transformed position
   */
  pos3d@ opMul(pos3d@ obj);
   /*
    \return pos3d@
   */
  pos3d@ origin() const;
   /*
   transform a 2d shape: shape2d@ s = T*obj;
    \param obj shape2d@, object to be transformed
    \return shape2d@, transformed object
   */
  shape2d@ opMul(shape2d@ obj);
   /*
   transform a solid: solid@ s = T*obj;
    \param obj solid@, object to be transformed
    \return solid@, transformed object
   */
  solid@ opMul(solid@ obj);
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ opImplCast();
   /*
   matrix multiplication: A = T*B
    \param B tmatrix@, matrix to be post-multiplied with this matrix
    \return tmatrix@, resulting matrixt
   */
  tmatrix@ opMul(const tmatrix@ B);
   /*
    \return vec3d@
   */
  vec3d@ xdir() const;
   /*
    \return vec3d@
   */
  vec3d@ ydir() const;
   /*
    \return vec3d@
   */
  vec3d@ zdir() const;
   /*
   dump matrix to console
   */
  void dump() const;
};

/* 
 union2d is a 2-dimensional boolean operation. It can be invoked either
 explicitly or using + operator:
 explicit: shape2d@ object = union2d(circle(100),translate(75,0,0)*circle(50));
 using & operator: shape2d@ object = circle(100) + translate(75,0,0)*circle(50);
*/ 
class union2d : public shape2d {
   /*
   constructor
    \param s1 shape2d@, 2d shape
    \param s2 shape2d@, 2d shape
   */
   union2d(const shape2d@ s1, const shape2d@ s2);
   /*
   constructor
    \param s1 shape2d@, 2d shape
    \param s2 shape2d@, 2d shape
    \param s3 shape2d@, 2d shape
   */
   union2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3);
   /*
   constructor
    \param s1 shape2d@, 2d shape
    \param s2 shape2d@, 2d shape
    \param s3 shape2d@, 2d shape
    \param s4 shape2d@, 2d shape
   */
   union2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4);
   /*
   constructor
    \param s1 shape2d@, 2d shape
    \param s2 shape2d@, 2d shape
    \param s3 shape2d@, 2d shape
    \param s4 shape2d@, 2d shape
    \param s5 shape2d@, 2d shape
   */
   union2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4, const shape2d@ s5);
   /*
    \param arr array@
   */
   union2d(shape2d@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   Boolean union operator+ overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAdd(shape2d@ b);
   /*
   Boolean intersection operator& overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opAnd(shape2d@ b);
   /*
    \return shape2d@
   */
  shape2d@ opImplCast();
   /*
    \param matrix tmatrix@
    \return shape2d@
   */
  shape2d@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b shape2d@
    \return shape2d@, resulting 2d shape
   */
  shape2d@ opSub(shape2d@ b);
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

/* 
 union3d is a 3-dimensional boolean operation. It can be invoked either
 explicitly or using + operator:
 explicit: solid@ object = union3d(sphere(100),translate(75,0,0)*sphere(50));
 using & operator: solid@ object = sphere(100) + translate(75,0,0)*sphere(50);
*/ 
class union3d : public solid {
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
   */
   union3d(const solid@ s1, const solid@ s2);
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
    \param s3 solid@, solid
   */
   union3d(const solid@ s1, const solid@ s2, const solid@ s3);
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
    \param s3 solid@, solid
    \param s4 solid@, solid
   */
   union3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4);
   /*
   constructor
    \param s1 solid@, solid
    \param s2 solid@, solid
    \param s3 solid@, solid
    \param s4 solid@, solid
    \param s5 solid@, solid
   */
   union3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4, const solid@ s5);
   /*
    \param arr array@
   */
   union3d(solid@[]@ arr);
   /*
    \return boundingbox@
   */
  boundingbox@ box() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
    \return shape@
   */
  shape@ opImplCast();
   /*
   Boolean union operator+ overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAdd(solid@ b);
   /*
   Boolean intersection operator& overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opAnd(solid@ b);
   /*
    \return solid@
   */
  solid@ opImplCast();
   /*
    \param matrix tmatrix@
    \return solid@
   */
  solid@ opMul(tmatrix@ matrix);
   /*
   Boolean difference operator- overload
    \param b solid@
    \return solid@, resulting solid
   */
  solid@ opSub(solid@ b);
   /*
   Object type string
    \return string, type name string
   */
  string Type() const;
   /*
    \return tmatrix@
   */
  tmatrix@ transform() const;
   /*
   Write to OpenSCAD .csg file
    \param path string, file path
   */
  void write_csg(string path);
   /*
   Write to AngelCAD .xcsg file
    \param path string, file path
    \param secant_tolerance double, tolerance for geometry precision
   */
  void write_xcsg(string path, double secant_tolerance = - 1.0);
};

class unordered_map {
   /*
    \param  int
   */
   unordered_map(int&in);
   /*
    \param  int
    \param  unordered_map@
   */
   unordered_map(int&in, unordered_map<T_key,T_value>@);
   /*
    \param  const T_key&
    \return T_value&
   */
  T_value& find(const T_key&in);
   /*
    \param  const T_key&
    \param  bool
    \return T_value&
   */
  T_value& find(const T_key&in, bool&out);
   /*
    \param  const T_key&
    \return bool
   */
  bool contains(const T_key&in);
   /*
    \return bool
   */
  bool empty();
   /*
    \param  const unordered_map_iterator&
    \return bool
   */
  bool erase(const unordered_map_iterator<T_key,T_value>&in);
   /*
    \param  const T_key&
    \return const T_value&
   */
  const T_value& get_opIndex(const T_key&in) const;
   /*
    \param  const unordered_map_iterator&
    \param  const unordered_map_iterator&
    \return int
   */
  int erase(const unordered_map_iterator<T_key,T_value>&in, const unordered_map_iterator<T_key,T_value>&in);
   /*
    \return int
   */
  int size();
   /*
    \param  unordered_map@
    \return unordered_map&@
   */
  unordered_map<T_key,T_value>& opAssign(unordered_map<T_key,T_value>@);
   /*
    \param  unordered_map&@
    \return unordered_map&@
   */
  unordered_map<T_key,T_value>& swap(unordered_map<T_key,T_value>&inout);
   /*
    \return unordered_map_iterator
   */
  unordered_map_iterator<T_key,T_value> begin();
   /*
    \return unordered_map_iterator
   */
  unordered_map_iterator<T_key,T_value> end();
   /*
    \param  const T_key&
    \return unordered_map_iterator
   */
  unordered_map_iterator<T_key,T_value> find_iterator(const T_key&in);
   /*
    \param  bool
   */
  void SetDirectcomp(bool);
  void clear();
   /*
    \param  const T_key&
   */
  void erase(const T_key&in);
   /*
    \param  const T_key&
    \param  const T_value&
   */
  void insert(const T_key&in, const T_value&in);
   /*
    \param  const T_key&
    \param  const T_value&
   */
  void set_opIndex(const T_key&in, const T_value&in);
};

class unordered_map_iterator {
   /*
    \return T_value&
   */
  T_value& current_value();
   /*
    \return T_value&
   */
  T_value& get_value();
   /*
    \return bool
   */
  bool IsEnd();
   /*
    \return bool
   */
  bool IsValid();
   /*
    \return bool
   */
  bool next();
   /*
    \param  const unordered_map_iterator&
    \return bool
   */
  bool opEquals(const unordered_map_iterator<T_key,T_value>&in);
   /*
    \return bool
   */
  bool opPostInc();
   /*
    \return bool
   */
  bool opPreInc();
   /*
    \return const T_key&
   */
  const T_key& current_key();
   /*
    \return const T_key&
   */
  const T_key& get_key();
   /*
    \param  const unordered_map_iterator&
    \return unordered_map_iterator&
   */
  unordered_map_iterator<T_key,T_value>& opAssign(const unordered_map_iterator<T_key,T_value>&in);
   /*
    \param  const T_value&
   */
  void set_value(const T_value&in);
};

/* 
 vec2d is a 2-dimensional vector offering useful operations such as dot and cross products.
*/ 
class vec2d {
   /*
   constructor
    \param p1 pos2d@, vector start position
    \param p2 pos2d@, vector end position
   */
   vec2d(const pos2d@ p1, const pos2d@ p2);
   /*
    \param other vec2d@
   */
   vec2d(const vec2d@ other);
   /*
   constructor
    \param x double, vector x component
    \param y double, vector y component
   */
   vec2d(double x, double y);
   /*
   angle between: double rad = v.angle(other);
    \param other vec2d@, vector to compute angle relative to this
    \return double, angle value in radians
   */
  double angle(const vec2d@ other) const;
   /*
   cross product: double cp = v.cross(other);
    \param other vec2d@, vector to multiply with
    \return double, cross product value
   */
  double cross(const vec2d@ other) const;
   /*
   dot product: double cp = v.dot(other);
    \param other vec2d@, vector to multiply with
    \return double, dot product value
   */
  double dot(const vec2d@ other) const;
   /*
   length of vector
    \return double, length of vector
   */
  double length() const;
   /*
   vector x component
    \return double, vector x component
   */
  double x() const;
   /*
   vector y component
    \return double, vector y component
   */
  double y() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
    \param v1 vec2d@
    \return vec2d@
   */
  vec2d@ opAdd(vec2d@ v1);
   /*
    \param f1 double
    \return vec2d@
   */
  vec2d@ opMul(double f1);
   /*
    \param f1 double
    \return vec2d@
   */
  vec2d@ opMul_r(double f1);
   /*
    \param v1 vec2d@
    \return vec2d@
   */
  vec2d@ opSub(vec2d@ v1);
   /*
   normalise vector length
   */
  void normalise();
};

/* 
 vec3d is a 3-dimensional vector offering useful operations such as dot and cross products.
*/ 
class vec3d {
   /*
    \param p1 pos3d@
    \param p2 pos3d@
   */
   vec3d(const pos3d@ p1, const pos3d@ p2);
   /*
    \param other vec3d@
   */
   vec3d(const vec3d@ other);
   /*
   constructor
    \param x double, vector x component
    \param y double, vector y component
    \param z double, vector z component
   */
   vec3d(double x, double y, double z);
   /*
   angle between: double rad = v.angle(other);
    \param other vec3d@, vector to compute angle relative to this
    \return double, angle value in radians
   */
  double angle(const vec3d@ other) const;
   /*
   dot product: double cp = v.dot(other);
    \param other vec3d@, vector to multiply with
    \return double, dot product value
   */
  double dot(const vec3d@ other) const;
   /*
   length of vector
    \return double, length of vector
   */
  double length() const;
   /*
   vector x component
    \return double, vector x component
   */
  double x() const;
   /*
   vector y component
    \return double, vector y component
   */
  double y() const;
   /*
   vector z component
    \return double, vector z component
   */
  double z() const;
   /*
    \return int
   */
  int Refcount() const;
   /*
   class type string
    \return string, string containing type name
   */
  string Type() const;
   /*
   cross product: double cp = v.cross(other);
    \param other vec3d@, vector to multiply with
    \return vec3d@, cross product value
   */
  vec3d@ cross(const vec3d@ other) const;
   /*
    \param v1 vec3d@
    \return vec3d@
   */
  vec3d@ opAdd(vec3d@ v1);
   /*
    \param f1 double
    \return vec3d@
   */
  vec3d@ opMul(double f1);
   /*
    \param f1 double
    \return vec3d@
   */
  vec3d@ opMul_r(double f1);
   /*
    \param v1 vec3d@
    \return vec3d@
   */
  vec3d@ opSub(vec3d@ v1);
   /*
   normalise vector length
   */
  void normalise();
};
