
/// Intput stream (usable in console window only)
class IStream {
public:
   /*!  \return IStream& */
  IStream&  clearbuffer();

   /*!  \param szString string&
   \n  \return IStream& */
  IStream&  getline(string&out szString);

   /*!  \param szString string&
   \n  \param szDelim const string&
   \n  \return IStream& */
  IStream&  getline(string&out szString, const string&in szDelim);

   /*!  \param n int64
   \n  \param szDelim const string&
   \n  \return IStream& */
  IStream&  ignore(int64 n = 1, const string&in szDelim = EOF);

   /*!  \param fValue bool
   \n  \return IStream& */
  IStream&  opShr(bool&out fValue);

   /*!  \param flValue double
   \n  \return IStream& */
  IStream&  opShr(double&out flValue);

   /*!  \param flValue float
   \n  \return IStream& */
  IStream&  opShr(float&out flValue);

   /*!  \param iValue int
   \n  \return IStream& */
  IStream&  opShr(int&out iValue);

   /*!  \param iValue int16
   \n  \return IStream& */
  IStream&  opShr(int16&out iValue);

   /*!  \param iValue int64
   \n  \return IStream& */
  IStream&  opShr(int64&out iValue);

   /*!  \param szString string&
   \n  \return IStream& */
  IStream&  opShr(string&out szString);

   /*!  \param uiValue uint
   \n  \return IStream& */
  IStream&  opShr(uint&out uiValue);

   /*!  \param uiValue uint16
   \n  \return IStream& */
  IStream&  opShr(uint16&out uiValue);

   /*!  \param uiValue uint64
   \n  \return IStream& */
  IStream&  opShr(uint64&out uiValue);

   /*!  \param iOffset int64
   \n  \param way seekdir
   \n  \return IStream& */
  IStream&  seekg(int64 iOffset, seekdir way);

   /*!  \param iPos int64
   \n  \return IStream& */
  IStream&  seekg(int64 iPos);

   /*!  \return bool */
  bool  bad() const;

   /*!  \return bool */
  bool  eof() const;

   /*!  \return bool */
  bool  fail() const;

   /*!  \return bool */
  bool  good() const;

   /*!  \return bool */
  bool  opImplConv() const;

   /*!  \return int64 */
  int64  tellg() const;

  void  clear();

};

/// Output stream allowing expressions like: cout << "Hello World!" << endl;
class OStream {
public:
   /*!  \return OStream& */
  OStream&  flush();

   /*!  \param fValue bool
   \n  \return OStream& */
  OStream&  opShl(bool fValue);

   /*!  \param szString const string&
   \n  \return OStream& */
  OStream&  opShl(const string&in szString);

   /*!  \param flValue double
   \n  \return OStream& */
  OStream&  opShl(double flValue);

   /*!  \param flValue float
   \n  \return OStream& */
  OStream&  opShl(float flValue);

   /*!  \param iValue int64
   \n  \return OStream& */
  OStream&  opShl(int64 iValue);

   /*!  \param uiValue uint64
   \n  \return OStream& */
  OStream&  opShl(uint64 uiValue);

   /*!  \param iOffset int64
   \n  \param way seekdir
   \n  \return OStream& */
  OStream&  seekp(int64 iOffset, seekdir way);

   /*!  \param iPos int64
   \n  \return OStream& */
  OStream&  seekp(int64 iPos);

   /*!  \return bool */
  bool  bad() const;

   /*!  \return bool */
  bool  eof() const;

   /*!  \return bool */
  bool  fail() const;

   /*!  \return bool */
  bool  good() const;

   /*!  \return bool */
  bool  opImplConv() const;

   /*!  \return int64 */
  int64  tellp() const;

  void  clear();

};

/// Array of values or references
/*! Arrays by examples
\n array of double values : array<double>
\n array of pos3d references : array<pos3d@ >, may also be written as pos3d@[]
\n reference to array of pos3d references : array<pos3d@ >@, may also be written as pos3d@[]@*/
class array {
public:
   /*!  \param  int */
   array(int&in);

   /*!  \param  int
   \n  \param length uint */
   array(int&in, uint length);

   /*!  \param  int
   \n  \param length uint
   \n  \param value const T& */
   array(int&in, uint length, const T&in value);

   /*!  \param index uint
   \n  \return T& */
  T&  opIndex(uint index);

   /*!  \param  const array&@
   \n  \return array&@ */
  T[]&  opAssign(const T[]&in);

   /*!  \return bool */
  bool  empty() const;

   /*!  \return bool */
  bool  isEmpty() const;

   /*!  \param  const array&@
   \n  \return bool */
  bool  opEquals(const T[]&in) const;

   /*!  \param index uint
   \n  \return const T& */
  const  T& opIndex(uint index) const;

   /*!  \param value const T&
   \n  \return int */
  int  find(const T&in value) const;

   /*!  \param startAt uint
   \n  \param value const T&
   \n  \return int */
  int  find(uint startAt, const T&in value) const;

   /*!  \param value const T&
   \n  \return int */
  int  findByRef(const T&in value) const;

   /*!  \param startAt uint
   \n  \param value const T&
   \n  \return int */
  int  findByRef(uint startAt, const T&in value) const;

   /*!  \return uint */
  uint  get_length() const;

   /*!  \return uint */
  uint  length() const;

   /*!  \return uint */
  uint  size() const;

   /*!  \param  uint */
  void  erase(uint);

   /*!  \param  uint
   \n  \param  const T& */
  void  insert(uint, const T&in);

   /*!  \param index uint
   \n  \param value const T& */
  void  insertAt(uint index, const T&in value);

   /*!  \param value const T& */
  void  insertLast(const T&in value);

  void  pop_back();

   /*!  \param  const T& */
  void  push_back(const T&in);

   /*!  \param index uint */
  void  removeAt(uint index);

  void  removeLast();

   /*!  \param length uint */
  void  reserve(uint length);

   /*!  \param length uint */
  void  resize(uint length);

  void  reverse();

   /*!  \param  uint */
  void  set_length(uint);

  void  sortAsc();

   /*!  \param startAt uint
   \n  \param count uint */
  void  sortAsc(uint startAt, uint count);

  void  sortDesc();

   /*!  \param startAt uint
   \n  \param count uint */
  void  sortDesc(uint startAt, uint count);

};

/// bounding box aligned with system axes
/*! A bounding box representes the range of an object in x,y and z*/
class boundingbox {
public:
   /// create an empty/uninitialised bounding box
   boundingbox();

   /// True when no points have been enclosed
   /*!  \return bool */
  bool  is_empty() const;

   /// Distance between p1 and p2
   /*!  \return double */
  double  diagonal() const;

   /// bounding box extent
   /*!  \return double, bounding box extent in x-direction */
  double  dx() const;

   /// bounding box extent
   /*!  \return double, bounding box extent in y-direction */
  double  dy() const;

   /// bounding box extent
   /*!  \return double, bounding box extent in z-direction */
  double  dz() const;

   /// center position
   /*!  \return pos3d@, bounding box geometric center */
  pos3d*  center() const;

   /// low position
   /*!  \return pos3d@, position containing minimum x,y,z */
  pos3d*  p1() const;

   /// high position
   /*!  \return pos3d@, position containing maximum x,y,z */
  pos3d*  p2() const;

   /// enclose a new position, this may extend the boundingbox
   /*!  \param p pos3d@, position to enclose */
  void  enclose(pos3d@ p);

};

/// circle, centered at origin
/*! A 2d object defined by its radius. Centered on origin.*/
class circle : public shape2d {
public:
   /// Construct a circle from 3 points on the circumference
   /*!  \param p1 pos2d@
   \n  \param p2 pos2d@
   \n  \param p3 pos2d@ */
   circle(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3);

   /// Create a circle with a given radius
   /*!  \param r double, radius of circle */
   circle(double r);

   /// radius of circle
   /*!  \return double, radius of circle */
  double  r() const;

   /// radius of circle
   /*!  \return double, radius of circle */
  double  radius() const;

};

/// cone with axis in z-direction, by default extending from origin
/*! A cone extends in the z-direction.
\n By default the bottom is at origin*/
class cone : public solid {
public:
   /// Create cone extending in z direction
   /*!  \param h double, height of cone
   \n  \param r1 double, bottom radius of cone
   \n  \param r2 double, top radius of cone
   \n  \param center bool, true if cone is centered in z-direction */
   cone(double h, double r1, double r2, bool center = false);

   /// height of cone
   /*!  \return double, height of cone */
  double  h() const;

   /// height of cone
   /*!  \return double, height of cone */
  double  height() const;

   /// bottom radius
   /*!  \return double, bottom radius */
  double  r1() const;

   /// top radius
   /*!  \return double, top radius */
  double  r2() const;

   /// bottom radius
   /*!  \return double, bottom radius */
  double  radius1() const;

   /// top radius
   /*!  \return double, top radius */
  double  radius2() const;

};

/// cube, by default in 1st octant with one corner toucing origin
class cube : public solid {
public:
   /*!  \param size double
   \n  \param center bool */
   cube(double size, bool center = false);

   /*!  \return double */
  double  size() const;

};

/// cuboid, by default in 1st octant with one corner toucing origin
/*! A cuboid is like a cube, but with separate dimensions in x,y and z.
\n By default the cuboid touches the origin, and extends along positive x,y,z.*/
class cuboid : public solid {
public:
   /// Create cuboid
   /*!  \param dx double, extent in x-drection
   \n  \param dy double, extent of y-direction
   \n  \param dz double, extent of z-direction
   \n  \param center bool, true if cuboid is centered on origin */
   cuboid(double dx, double dy, double dz, bool center = false);

   /// extent in x-drection
   /*!  \return double, extent in x-drection */
  double  dx() const;

   /// extent in y-drection
   /*!  \return double, extent in y-drection */
  double  dy() const;

   /// extent in z-drection
   /*!  \return double, extent in z-drection */
  double  dz() const;

};

/// cylinder with axis in z-direction, by default extending from origin
/*! A cylinder is defined by height and radius.
\n By default the cuboid extends from the origin, in z-direction.*/
class cylinder : public solid {
public:
   /// Create cylinder
   /*!  \param h double, height of cylinder
   \n  \param r double, radius of cylinder
   \n  \param center bool, true if cylinder is centered on origin in z-direction */
   cylinder(double h, double r, bool center = false);

   /// Height of cylnder
   /*!  \return double, height of cylnder */
  double  h() const;

   /// Height of cylnder
   /*!  \return double, height of cylnder */
  double  height() const;

   /// Radius of cylnder
   /*!  \return double, radius of cylnder */
  double  r() const;

   /// Radius of cylnder
   /*!  \return double, radius of cylnder */
  double  radius() const;

};

/// 2d difference boolean operation
/*! difference2d is a 2-dimensional boolean operation. It can be invoked either
\n explicitly or using subtraction operator:
\n explicit: shape2d@ object = difference2d(circle(100),circle(50));
\n using subtraction operator: shape2d@ object = circle(100) - circle(50);*/
class difference2d : public shape2d {
public:
   /// Compute boolean difference for 2d objects
   /*!  \param incl shape2d@, object to be included
   \n  \param excl shape2d@, object to be excluded (subtracted) */
   difference2d(shape2d@ incl, shape2d@ excl);

};

/// 3d difference boolean operation
/*! difference3d is a 3-dimensional boolean operation. It can be invoked either
\n explicitly or using subtraction operator:
\n explicit: solid@ object = difference3d(sphere(100),sphere(50));
\n using subtraction operator: solid@ object = sphere(100) - sphere(50);*/
class difference3d : public solid {
public:
   /// Compute boolean difference for 3d objects
   /*!  \param incl solid@, objects to be included
   \n  \param excl solid@, objects to be excluded (subtracted) */
   difference3d(solid@ incl, solid@ excl);

};

/// 2d fill operation, filling holes in input shapes
/*! fill2d is a 2-dimensional boolean operation that removes internal holes
\n in in 2d shapes, but leaves a possibly concave outer contour intact.
\n fill2d can be invoked either on a single shape2d or an array.*/
class fill2d : public shape2d {
public:
   /// Fill internal holes on a 2d object
   /*!  \param s1 shape2d@, 2d shape */
   fill2d(const shape2d@ s1);

   /// Fill internal voids of 2d objects in an array
   /*!  \param arr array@ */
   fill2d(array<shape2d@>@ arr);

};

/// Homogeneous transformation matrix
/*! hmatrix is a transformation expressed as homogenous transformation matrix.*/
class hmatrix : public tmatrix {
public:
   /// Create 4x4 homogenous matrix from x and y direction vectors and an optional origin positio
   /*!  \param xvec vec3d@
   \n  \param yvec vec3d@
   \n  \param pos pos3d@ */
   hmatrix(const vec3d@ xvec, const vec3d@ yvec, const pos3d@ pos = pos3d ( 0 , 0 , 0 ));

   /// Create 4x4 homogenous matrix from 3 direction vectors and an optional origin position
   /*!  \param xvec vec3d@, 1st matrix column
   \n  \param yvec vec3d@, 2nd matrix column
   \n  \param zvec vec3d@, 3rd matrix column
   \n  \param pos pos3d@, 4rd matrix column */
   hmatrix(const vec3d@ xvec, const vec3d@ yvec, const vec3d@ zvec, const pos3d@ pos = pos3d ( 0 , 0 , 0 ));

};

/// 2d hull operation, enclosing the input shapes
/*! hull2d is a 2-dimensional boolean operation. It encapsulates
\n the input objects with a convex shape. It can for example be used
\n to create a rectangle with rounded cornes using 4 circles.*/
class hull2d : public shape2d {
public:
   /// Compute 2d convex hull from 2 shapes
   /*!  \param s1 shape2d@, shape
   \n  \param s2 shape2d@, shape */
   hull2d(const shape2d@ s1, const shape2d@ s2);

   /// Compute 2d convex hull from 3 shapes
   /*!  \param s1 shape2d@, shape
   \n  \param s2 shape2d@, shape
   \n  \param s3 shape2d@, shape */
   hull2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3);

   /// Compute 2d convex hull from 4 shapes
   /*!  \param s1 shape2d@, shape
   \n  \param s2 shape2d@, shape
   \n  \param s3 shape2d@, shape
   \n  \param s4 shape2d@, shape */
   hull2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4);

   /// Compute 2d convex hull from 5 shapes
   /*!  \param s1 shape2d@, shape
   \n  \param s2 shape2d@, shape
   \n  \param s3 shape2d@, shape
   \n  \param s4 shape2d@, shape
   \n  \param s5 shape2d@, shape */
   hull2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4, const shape2d@ s5);

   /// Compute 2d convex hull from an array of 2d shapes
   /*!  \param arr array@ */
   hull2d(array<shape2d@>@ arr);

};

/// 3d hull operation, enclosing the input solids
/*! hull3d is a 3-dimensional boolean operation. It encapsulates
\n the input objects with a convex shape. It can for example be used
\n to create a cuboid with rounded cornes using 8 spheres.*/
class hull3d : public solid {
public:
   /// Compute 3d convex hull from 2 solids
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid */
   hull3d(const solid@ s1, const solid@ s2);

   /// Compute 3d convex hull from 3 solids
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid
   \n  \param s3 solid@, solid */
   hull3d(const solid@ s1, const solid@ s2, const solid@ s3);

   /// Compute 3d convex hull from 4 solids
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid
   \n  \param s3 solid@, solid
   \n  \param s4 solid@, solid */
   hull3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4);

   /// Compute 3d convex hull from 5 solids
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid
   \n  \param s3 solid@, solid
   \n  \param s4 solid@, solid
   \n  \param s5 solid@, solid */
   hull3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4, const solid@ s5);

   /// Compute 3d convex hull from an array of solids
   /*!  \param arr array@ */
   hull3d(array<solid@>@ arr);

};

/// 2d intersection boolean operation
/*! intersection2d is a 2-dimensional boolean operation. It can be invoked either
\n explicitly or using & operator:
\n explicit: shape2d@ object = intersection2d(circle(100),translate(75,0,0)*circle(50));
\n using & operator: shape2d@ object = circle(100) & translate(75,0,0)*circle(50);*/
class intersection2d : public shape2d {
public:
   /// Compute boolean intersection between 2 objects.
   /*!  \param s1 shape2d@
   \n  \param s2 shape2d@ */
   intersection2d(const shape2d@ s1, const shape2d@ s2);

   /// Compute boolean intersection between 3 objects.
   /*!  \param s1 shape2d@
   \n  \param s2 shape2d@
   \n  \param s3 shape2d@ */
   intersection2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3);

   /// Compute boolean intersection between 4 objects.
   /*!  \param s1 shape2d@
   \n  \param s2 shape2d@
   \n  \param s3 shape2d@
   \n  \param s4 shape2d@ */
   intersection2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4);

   /// Compute boolean intersection between 4 objects.
   /*!  \param s1 shape2d@
   \n  \param s2 shape2d@
   \n  \param s3 shape2d@
   \n  \param s4 shape2d@
   \n  \param s5 shape2d@ */
   intersection2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4, const shape2d@ s5);

   /// Compute boolean intersection between all objects in the array.
   /*!  \param arr array@ */
   intersection2d(array<shape2d@>@ arr);

};

/// 3d intersection boolean operation
/*! intersection3d is a 2-dimensional boolean operation. It can be invoked either
\n explicitly or using & operator:
\n explicit: solid@ object = intersection3d(sphere(100),translate(75,0,0)*sphere(50));
\n using & operator: solid@ object = sphere(100) & translate(75,0,0)*sphere(50);*/
class intersection3d : public solid {
public:
   /// Compute boolean intersection between 2 objects.
   /*!  \param s1 solid@
   \n  \param s2 solid@ */
   intersection3d(const solid@ s1, const solid@ s2);

   /// Compute boolean intersection between 3 objects.
   /*!  \param s1 solid@
   \n  \param s2 solid@
   \n  \param s3 solid@ */
   intersection3d(const solid@ s1, const solid@ s2, const solid@ s3);

   /// Compute boolean intersection between 4 objects.
   /*!  \param s1 solid@
   \n  \param s2 solid@
   \n  \param s3 solid@
   \n  \param s4 solid@ */
   intersection3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4);

   /// Compute boolean intersection between 5 objects.
   /*!  \param s1 solid@
   \n  \param s2 solid@
   \n  \param s3 solid@
   \n  \param s4 solid@
   \n  \param s5 solid@ */
   intersection3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4, const solid@ s5);

   /// Compute boolean intersection between all objects in the array.
   /*!  \param arr array@ */
   intersection3d(array<solid@>@ arr);

};

/// 2d line
class line2d {
public:
   /// Construct line segment from p1 to p2
   /*!  \param p1 pos2d@
   \n  \param p2 pos2d@ */
   line2d(const pos2d@ p1, const pos2d@ p2);

   /// Compute length of line segment
   /*!  \return double */
  double  length() const;

   /// Project point onto line segment and return line parameter of projetion point
   /*!  \param point pos2d@
   \n  \return double */
  double  project(pos2d@ point) const;

   /// Return 1st end point on line segment
   /*!  \return pos2d@ */
  pos2d*  end1() const;

   /// Return 2nd end point on line segment
   /*!  \return pos2d@ */
  pos2d*  end2() const;

   /// Compute point on (infinite) line given line segment parameter (0=end1, 1=end2)
   /*!  \param par double
   \n  \return pos2d@ */
  pos2d*  interpolate(double par) const;

};

/// 3d line
class line3d {
public:
   /// Construct line segment from p1 to p2
   /*!  \param p1 pos3d@
   \n  \param p2 pos3d@ */
   line3d(const pos3d@ p1, const pos3d@ p2);

   /// Compute length of line segment.
   /*!  \return double */
  double  length() const;

   /// Project point onto line segment and return line parameter of projetion point
   /*!  \param point pos3d@
   \n  \return double */
  double  project(pos3d@ point) const;

   /// Return 1st end point on line segment.
   /*!  \return pos3d@ */
  pos3d*  end1() const;

   /// Return 2nd end point on line segment.
   /*!  \return pos3d@ */
  pos3d*  end2() const;

   /// Compute point on (infinite) line given line segment parameter (0=end1, 1=end2)
   /*!  \param par double
   \n  \return pos3d@ */
  pos3d*  interpolate(double par) const;

};

/// Extrude 2d shape in z direction into 3d solid
/*! linear_extrude extrudes a 2d shape in z-direction, creating a solid.*/
class linear_extrude : public solid {
public:
   /// Compute linear extrusion of 2d shape
   /*!  \param shape shape2d@, 2d profile to be extruded
   \n  \param height double, distance in z direction to extrude */
   linear_extrude(const shape2d@ shape, double height);

   /// extrusion height
   /*!  \return double, extrusion height */
  double  height() const;

};

/// 3d localsystem
/*! a locsys3d represents local coordinate system directions.*/
class locsys3d {
public:
   /// Compute local system from local x and z vectors
   /*!  \param xvec vec3d@, local x-direction vector
   \n  \param zvec vec3d@, local z-direction vector */
   locsys3d(const vec3d@ xvec, const vec3d@ zvec);

   /// local x-direction vector
   /*!  \return vec3d@, local x-direction vector */
  vec3d*  x() const;

   /// local y-direction vector
   /*!  \return vec3d@, local y-direction vector */
  vec3d*  y() const;

   /// local z-direction vector
   /*!  \return vec3d@, local z-direction vector */
  vec3d*  z() const;

};

/// Template container storing sorted keys and values: map<T_key,T_value>
/*! basic use:
\n map<int,string> cont;
\n cont.insert(2,"bb");
\n cont.insert(1,"aa");
\n cont.insert(3,"cc");
\n for(auto it = cont.begin(); it++;) cout << it.key << it.value << endl;*/
class map {
public:
   /*!  \param  int */
   map(int&in);

   /*!  \param  int
   \n  \param  map@ */
   map(int&in, map<T_key,T_value>@);

   /*!  \param  const T_key&
   \n  \return T_value& */
  T_value&  find(const T_key&in);

   /*!  \param  const T_key&
   \n  \param  bool
   \n  \return T_value& */
  T_value&  find(const T_key&in, bool&out);

   /*!  \param  const T_key&
   \n  \return bool */
  bool  contains(const T_key&in);

   /*!  \return bool */
  bool  empty();

   /*!  \param  const map_iterator&
   \n  \return bool */
  bool  erase(const map_iterator<T_key,T_value>&in);

   /*!  \param  const T_key&
   \n  \return const T_value& */
  const  T_value& get_opIndex(const T_key&in) const;

   /*!  \param  const map_iterator&
   \n  \param  const map_iterator&
   \n  \return int */
  int  erase(const map_iterator<T_key,T_value>&in, const map_iterator<T_key,T_value>&in);

   /*!  \return int */
  int  size();

   /*!  \param  map@
   \n  \return map&@ */
  map<T_key,T_value>&  opAssign(map<T_key,T_value>@);

   /*!  \param  map&@
   \n  \return map&@ */
  map<T_key,T_value>&  swap(map<T_key,T_value>&inout);

   /*!  \return map_iterator */
  map_iterator<T_key,T_value>  begin();

   /*!  \return map_iterator */
  map_iterator<T_key,T_value>  end();

   /*!  \param  const T_key&
   \n  \return map_iterator */
  map_iterator<T_key,T_value>  find_iterator(const T_key&in);

   /*!  \param  bool */
  void  SetDirectcomp(bool);

  void  clear();

   /*!  \param  const T_key& */
  void  erase(const T_key&in);

   /*!  \param  const T_key&
   \n  \param  const T_value& */
  void  insert(const T_key&in, const T_value&in);

   /*!  \param  const T_key&
   \n  \param  const T_value& */
  void  set_opIndex(const T_key&in, const T_value&in);

};

/// Container iterator type for map
class map_iterator {
public:
   /*!  \return T_value& */
  T_value&  current_value();

   /*!  \return T_value& */
  T_value&  get_value();

   /*!  \return bool */
  bool  IsEnd();

   /*!  \return bool */
  bool  IsValid();

   /*!  \return bool */
  bool  next();

   /*!  \param  const map_iterator&
   \n  \return bool */
  bool  opEquals(const map_iterator<T_key,T_value>&in);

   /*!  \return bool */
  bool  opPostInc();

   /*!  \return bool */
  bool  opPreInc();

   /*!  \return const T_key& */
  const  T_key& current_key();

   /*!  \return const T_key& */
  const  T_key& get_key();

   /*!  \param  const map_iterator&
   \n  \return map_iterator& */
  map_iterator<T_key,T_value>&  opAssign(const map_iterator<T_key,T_value>&in);

   /*!  \param  const T_value& */
  void  set_value(const T_value&in);

};

/// 2d Minkowski sum operation
/*! minkowski2d is a 2-dimensional boolean operation requiring exactly
\n 2 parameters, a and b. The first parameter (a) is generally the larger
\n and can be concave or convex. The second parameter (b) is assumed smaller
\n and convex (such as a circle). Typical use of the minkowski sum is to
\n create an object with rounded corners.*/
class minkowski2d : public shape2d {
public:
   /// Compute 2d minkowski from a and b
   /*!  \param a shape2d@, convex/concave object to be modified
   \n  \param b shape2d@, convex 'tool' object */
   minkowski2d(const shape2d@ a, const shape2d@ b);

};

/// 3d Minkowski sum operation
/*! minkowski3d is a 3-dimensional boolean operation requiring exactly
\n 2 parameters, a and b. The first parameter (a) is generally the larger
\n and can be concave or convex. The second parameter (b) is assumed smaller
\n and convex (such as a sphere). Typical use of the minkowski sum is to
\n create an object with rounded edges.*/
class minkowski3d : public solid {
public:
   /// Compute minkowski sum between a and b
   /*!  \param a solid@
   \n  \param b solid@ */
   minkowski3d(const solid@ a, const solid@ b);

};

/// Mirror transformation around given point
/*! mirror is a transformation creating mirror images of 2d or 3d objects.*/
class mirror : public tmatrix {
public:
   /// Create a mirror transformation, mirror around origin
   /*!  \param dx double, x-component of mirror plane normal
   \n  \param dy double, y-component of mirror plane normal
   \n  \param dz double, z-component of mirror plane normal */
   mirror(double dx, double dy, double dz);

   /// Create a mirror transformation, mirror around given point
   /*!  \param normal vec3d@, mirror plane normal vector
   \n  \param point pos3d@, point in mirror plane */
   mirror(vec3d@ normal, pos3d@ point = pos3d ( 0 , 0 , 0 ));

   /// mirror transform normal vector, x-component
   /*!  \return double, normal vector, x-component */
  double  dx() const;

   /// mirror transform normal vector, y-component
   /*!  \return double, normal vector, y-component */
  double  dy() const;

   /// mirror transform normal vector, z-component
   /*!  \return double, normal vector,z-component */
  double  dz() const;

};

/// 2d profile offset
/*! offset2d is a special 2d operation used for inflating or shrinking a 2d shape,
\n optionally creating rounded corners and chamfers.*/
class offset2d : public shape2d {
public:
   /// Compute 2d offset for a 2d profile
   /*!  \param profile shape2d@, 2d profile to be offset
   \n  \param r double, radius if rounded offset required (cannot be combined with delta)
   \n  \param delta double, straight offset if shart corners required (cannot be combined with r)
   \n  \param chamfer bool, true if sharp corners to be chamfered (relevant with delta only) */
   offset2d(const shape2d@ profile, double r = 0x7fc00000, double delta = 0x7fc00000, bool chamfer = false);

   /// Compute 2d offset for an array of 2d shapes
   /*!  \param arr array@
   \n  \param r double
   \n  \param delta double
   \n  \param chamfer bool */
   offset2d(array<shape2d@>@ arr, double r = 0x7fc00000, double delta = 0x7fc00000, bool chamfer = false);

};

/// Polyhedron face
/*! A pface represents a single face of a polyhedron. It contains 0-based indices referring to the polyhedron vertices.
\n When viewed from outside the polyhedron, a pface must list its vertices in CCW order.*/
class pface {
public:
   /// polyhedron face constructor
   /*!  \param iv1 uint, polyhedron vertex index
   \n  \param iv2 uint, polyhedron vertex index
   \n  \param iv3 uint, polyhedron vertex index */
   pface(uint iv1, uint iv2, uint iv3);

   /// polyhedron face constructor
   /*!  \param iv1 uint, polyhedron vertex index
   \n  \param iv2 uint, polyhedron vertex index
   \n  \param iv3 uint, polyhedron vertex index
   \n  \param iv4 uint, polyhedron vertex index */
   pface(uint iv1, uint iv2, uint iv3, uint iv4);

   /// number of vertices in face
   /*!  \return uint, number of vertices in face */
  uint  nvert() const;

   /// polyhedron vertex index for face index
   /*!  \param iv uint, face index
   \n  \return uint, polyhedron face index */
  uint  vindex(uint iv) const;

};

/// polygon, vertices in CCW order
/*! a polygon is a 2d object. It is defined by vertex positions listed in CCW sequence.*/
class polygon : public shape2d {
public:
   /// Create triangular polygon, points must be given in CCW order
   /*!  \param p1 pos2d@, position
   \n  \param p2 pos2d@, position
   \n  \param p3 pos2d@, position */
   polygon(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3);

   /// Create quadrilateral polygon, points must be given in CCW order
   /*!  \param p1 pos2d@, position
   \n  \param p2 pos2d@, position
   \n  \param p3 pos2d@, position
   \n  \param p4 pos2d@, position */
   polygon(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3, const pos2d@ p4);

   /// Create 5-sided polygon, points must be given in CCW order
   /*!  \param p1 pos2d@, position
   \n  \param p2 pos2d@, position
   \n  \param p3 pos2d@, position
   \n  \param p4 pos2d@, position
   \n  \param p5 pos2d@, position */
   polygon(const pos2d@ p1, const pos2d@ p2, const pos2d@ p3, const pos2d@ p4, const pos2d@ p5);

   /// Create polygon from spline curve and number of straight segments, points must be given in CCW order
   /*!  \param spline spline2d@, 2d spline curve defining polygon profile
   \n  \param nseg uint, number of straight segments for spline */
   polygon(const spline2d@ spline, uint nseg = 30);

   /// Create a circular polygon from a radius and np points
   /*!  \param r double
   \n  \param np uint */
   polygon(double r, uint np);

   /// Create a polygon from an array of points.
   /*!  \param points array@
   \n  \param check bool */
   polygon(array<pos2d@>@ points, bool check = true);

   /// Polygon area
   /*! return computed area of polygon   */
   /*!  \return double */
  double  area() const;

   /// Signed polygon area, return negative area for polygons oriented CW
   /*! return signed computed area of polygon   */
   /*!  \return double */
  double  signed_area() const;

   /// Return polygon vertex from zero based vertex index iv.
   /*!  \param iv uint
   \n  \return pos2d@ */
  pos2d*  vertex(uint iv) const;

   /// number of polygon points
   /*!  \return uint, number of polygon points */
  uint  size() const;

};

/// Closed polyhedron volume defined by vertices and planar faces
/*! a polyhedron is a general 3d object, defined by its vertices and polyhedron faces.
\n It is useful in many contexts. It can be constructed directly or by reference to an input file.*/
class polyhedron : public solid {
public:
   /// Construct polyhedron from a point cloud. The result is the convex hull polyhedron.
   /*!  \param points array@ */
   polyhedron(array<pos3d@>@ points);

   /// Construct polyhedron from arrays of points and faces. Face normals must point out.
   /*!  \param points array@
   \n  \param faces array@ */
   polyhedron(array<pos3d@>@ points, array<pface@>@ faces);

   /// Read polyhedron from file (AMF;OBJ or OFF formats)
   /*!  \param file string
   \n  \param id int */
   polyhedron(string file, int id = - 1);

   /// polyhedron face area
   /*!  \param iface uint, index of polyhedron face
   \n  \return double, computed area of polyhedron face */
  double  face_area(uint iface) const;

   /// polyhedron volume
   /*!  \return double, computed volume of polyhedron */
  double  volume() const;

   /// polyhedron face
   /*!  \param iface uint, index of polyhedron face
   \n  \return pface@, polyhedron face */
  pface*  face(uint iface) const;

   /// polyhedron vertex
   /*!  \param iv uint, index of polyhedron vertex
   \n  \return pos3d@, polyhedron vertex position */
  pos3d*  vertex(uint iv) const;

   /// Number of faces
   /*!  \return uint, number of faces in polyhedron */
  uint  nface() const;

   /// Number of vertices
   /*!  \return uint, number of vertices in polyhedron */
  uint  nvert() const;

   /// Flip polyhedron face normal
   /*!  \param iface uint, index of polyhedron face */
  void  flip_face(uint iface);

   /// Flip all polyhedron face normals
  void  flip_faces();

   /// Set vertex position
   /*!  \param iv uint, index of polyhedron vertex
   \n  \param pos pos3d@, new position of vertex */
  void  set_vertex(uint iv, pos3d@ pos);

   /// Verify that the polyhedron is closed and without errors.
  void  verify() const;

};

/// 2d position coordinates
/*! a pos2d is a position in 2d space. It is used with 2d objects.*/
class pos2d {
public:
   /// Construct position as copy of other position
   /*!  \param other pos2d@ */
   pos2d(const pos2d@ other);

   /// Create 2d position from x and y coordinates
   /*!  \param x double, coordinate
   \n  \param y double, coordinate */
   pos2d(double x, double y);

   /// distance from other position
   /*!  \param pos pos2d@, other position
   \n  \return double, distance from pos */
  double  dist(const pos2d@ pos) const;

   /// x coordinate
   /*!  \return double, x coordinate */
  double  x() const;

   /// y coordinate
   /*!  \return double, y coordinate */
  double  y() const;

   /// Add 2 positions, return new position: p = p1 + p2
   /*!  \param p1 pos2d@
   \n  \return pos2d@ */
  pos2d*  opAdd(pos2d@ p1);

   /// Add position and vector, return new position: p = p1 + v1
   /*!  \param v1 vec2d@
   \n  \return pos2d@ */
  pos2d*  opAdd(vec2d@ v1);

   /// Add vector and position, return new position: p = v1 + p1
   /*!  \param v1 vec2d@
   \n  \return pos2d@ */
  pos2d*  opAdd_r(vec2d@ v1);

   /// Multiply position by factor, return new position: p = p1 * f1
   /*!  \param f1 double
   \n  \return pos2d@ */
  pos2d*  opMul(double f1);

   /// Multiply position by factor, return new position: p = f1 * p1
   /*!  \param f1 double
   \n  \return pos2d@ */
  pos2d*  opMul_r(double f1);

   /// Subtract vector from position, return new position: p = p1 - v1
   /*!  \param v1 vec2d@
   \n  \return pos2d@ */
  pos2d*  opSub(vec2d@ v1);

};

/// 3d position coordinates
/*! a pos3d is a position in 3d space. It is used with 3d objects.*/
class pos3d {
public:
   /// Construct position as copy of other position.
   /*!  \param other pos3d@ */
   pos3d(const pos3d@ other);

   /// Create 3d position from x,y and z coordinates
   /*!  \param x double, x coordinate
   \n  \param y double, y coordinate
   \n  \param z double, z coordinate */
   pos3d(double x, double y, double z);

   /// distance from other position
   /*!  \param pos pos3d@, other position
   \n  \return double, distance from pos */
  double  dist(const pos3d@ pos) const;

   /// x coordinate
   /*!  \return double, x coordinate */
  double  x() const;

   /// y coordinate
   /*!  \return double, y coordinate */
  double  y() const;

   /// z coordinate
   /*!  \return double, z coordinate */
  double  z() const;

   /// Add 2 positions, return new position: p = p1 + p2.
   /*!  \param p1 pos3d@
   \n  \return pos3d@ */
  pos3d*  opAdd(pos3d@ p1);

   /// Add position and vector, return new position: p = p1 + v1.
   /*!  \param v1 vec3d@
   \n  \return pos3d@ */
  pos3d*  opAdd(vec3d@ v1);

   /// Add vector and position, return new position: p = v1 + p1.
   /*!  \param v1 vec3d@
   \n  \return pos3d@ */
  pos3d*  opAdd_r(vec3d@ v1);

   /// Multiply position by factor, return new position: p = p1 * f1.
   /*!  \param f1 double
   \n  \return pos3d@ */
  pos3d*  opMul(double f1);

   /// Multiply position by factor, return new position: p = f1 * p1.
   /*!  \param f1 double
   \n  \return pos3d@ */
  pos3d*  opMul_r(double f1);

   /// Subtract vector from position, return new position: p = p1 - v1.
   /*!  \param v1 vec3d@
   \n  \return pos3d@ */
  pos3d*  opSub(vec3d@ v1);

};

/// rectangle, by default located in 1st quadrant touching origin
/*! a rectangle is a 2d object defined by its extent in x and y. By default it touches the
\n origin and extends along positive x and y.*/
class rectangle : public shape2d {
public:
   /// Create rectangle with extent in x and y
   /*!  \param dx double, extent in x direction
   \n  \param dy double, extent in y direction
   \n  \param center bool, true if rectangle should be centered on origin */
   rectangle(double dx, double dy, bool center = false);

   /// extent in x direction
   /*!  \return double, extent in x direction */
  double  dx() const;

   /// extent in y direction
   /*!  \return double, extent in y direction */
  double  dy() const;

};

/// Extrude 2d shape CCW in XZ plane into 3d solid
/*! rotate_extrude allows extruding a 2d shape along a circular path. A positive
\n angle rotates the object around the y axis (CCW direction).
\n solid@ object = rotate_extrude(translate(100,0)*circle(10),deg:60);*/
class rotate_extrude : public solid {
public:
   /// Construct solid by rotating shape on positive x axis around y axis, counter-clockwise
   /*!  \param shape shape2d@, 2d profile shape to extrude
   \n  \param deg double, rotation in degrees. Rotation is CCW around y axis.
   \n  \param pitch double, distance to offset profile in y direction for each revolution */
   rotate_extrude(const shape2d@ shape, double deg, double pitch = 0.0);

   /// extrusion angle in degrees
   /*!  \return double, extrusion angle in degrees */
  double  deg() const;

   /// extrusion angle in radians
   /*!  \return double, extrusion angle in radians */
  double  rad() const;

};

/// Rotation around x
/*! rotate_x is a transformation rotating around the x-axis. Positive angle according to right hand rule.*/
class rotate_x : public tmatrix {
public:
   /// Create transformation as rotation around x-axis
   /*!  \param deg double, rotation specified in degrees (cannot be combined with rad)
   \n  \param rad double, rotation specified in radians (cannot be combined with deg) */
   rotate_x(double deg = 0x7fc00000, double rad = 0x7fc00000);

   /// rotation angle in degrees
   /*!  \return double, rotation angle in degrees */
  double  deg() const;

   /// rotation angle in radians
   /*!  \return double, rotation angle in radians */
  double  rad() const;

};

/// Rotation around y
/*! rotate_y is a transformation rotating around the y-axis. Positive angle according to right hand rule.*/
class rotate_y : public tmatrix {
public:
   /// Create transformation as rotation around y-axis
   /*!  \param deg double, rotation specified in degrees (cannot be combined with rad)
   \n  \param rad double, rotation specified in radians (cannot be combined with deg) */
   rotate_y(double deg = 0x7fc00000, double rad = 0x7fc00000);

   /// rotation angle in degrees
   /*!  \return double, rotation angle in degrees */
  double  deg() const;

   /// rotation angle in radians
   /*!  \return double, rotation angle in radians */
  double  rad() const;

};

/// Rotation around z
/*! rotate_z is a transformation rotating around the z-axis. Positive angle according to right hand rule.*/
class rotate_z : public tmatrix {
public:
   /// Create transformation as rotation around z-axis
   /*!  \param deg double, rotation specified in degrees (cannot be combined with rad)
   \n  \param rad double, rotation specified in radians (cannot be combined with deg) */
   rotate_z(double deg = 0x7fc00000, double rad = 0x7fc00000);

   /// rotation angle in degrees
   /*!  \return double, rotation angle in degrees */
  double  deg() const;

   /// rotation angle in radians
   /*!  \return double, rotation angle in radians */
  double  rad() const;

};

/// Scaling transformation
/*! scale is a transformation scaling an object, either uniformly or with different factors in different directions.*/
class scale : public tmatrix {
public:
   /// Create scaling transformation, same scaling in x,y and z
   /*!  \param s double, scale factor in x,y and z */
   scale(double s);

   /// Create scaling transformation, individual scaling in x,y and z
   /*!  \param sx double, scale factor in x
   \n  \param sy double, scale factor in y
   \n  \param sz double, scale factor in z */
   scale(double sx, double sy, double sz = 1.0);

   /// scale factor in x direction
   /*!  \return double, scale factor in x direction */
  double  sx() const;

   /// scale factor in y direction
   /*!  \return double, scale factor in y direction */
  double  sy() const;

   /// scale factor in z direction
   /*!  \return double, scale factor in z direction */
  double  sz() const;

};

/// Abstract base for all primitives and booleans
class shape {
public:
   /// Return bounding box of object
   /*!  \return boundingbox@ */
  boundingbox*  box() const;

   /// Return transformation matrix of object
   /*!  \return tmatrix@ */
  tmatrix*  transform() const;

   /// Write object to OpenSCAD .csg file
   /*!  \param path string */
  void  write_csg(string path);

   /// Write object to .xcsg file for processing by xcsg program.
   /*!  \param path string
   \n  \param secant_tolerance double */
  void  write_xcsg(string path, double secant_tolerance = - 1.0);

};

/// Abstract base for 2d primitives and booleans
/*! shape2d is an abstract base class for all 2d objects.*/
class shape2d : public shape {
public:
   /// Boolean union operator+ overload
   /*!  \param b shape2d@
   \n  \return shape2d@, resulting 2d shape */
  shape2d*  opAdd(shape2d@ b);

   /// Boolean intersection operator& overload
   /*!  \param b shape2d@
   \n  \return shape2d@, resulting 2d shape */
  shape2d*  opAnd(shape2d@ b);

   /// Transform object by matrix multiplication: shape2d@ o2 = T * o1
   /*!  \param matrix tmatrix@
   \n  \return shape2d@ */
  shape2d*  opMul(tmatrix@ matrix);

   /// Boolean difference operator- overload
   /*!  \param b shape2d@
   \n  \return shape2d@, resulting 2d shape */
  shape2d*  opSub(shape2d@ b);

};

/// Abstract base for 3d primitives and booleans
/*! solid is an abstract base class for all 3d objects.*/
class solid : public shape {
public:
   /// Boolean union operator+ overload
   /*!  \param b solid@
   \n  \return solid@, resulting solid */
  solid*  opAdd(solid@ b);

   /// Boolean intersection operator& overload
   /*!  \param b solid@
   \n  \return solid@, resulting solid */
  solid*  opAnd(solid@ b);

   /// Transform object by matrix multiplication: solid@ o2 = T * o1
   /*!  \param matrix tmatrix@
   \n  \return solid@ */
  solid*  opMul(tmatrix@ matrix);

   /// Boolean difference operator- overload
   /*!  \param b solid@
   \n  \return solid@, resulting solid */
  solid*  opSub(solid@ b);

};

/// sphere, centered at origin
/*! a sphere is a 3d object defined by its radius.*/
class sphere : public solid {
public:
   /// Create sphere with radius r
   /*!  \param r double, radius */
   sphere(double r);

   /// sphere radius
   /*!  \return double, radius */
  double  r() const;

   /// sphere radius
   /*!  \return double, radius */
  double  radius() const;

};

/// 2d cubic spline curve
/*! a spline2d is a 2d cubic spline curve.*/
class spline2d {
public:
   /// Compute 2d spline curve from an array of positions on curve.
   /*!  \param points array@ */
   spline2d(array<pos2d@>@ points);

};

/// 3d cubic spline curve
/*! a spline3d is a 3d cubic spline curve.*/
class spline3d {
public:
   /// Compute 3d spline curve from an array of positions on curve
   /*!  \param points array@ */
   spline3d(array<pos3d@>@ points);

};

/// spline_path for sweep
/*! a spline_path defines a cubic spline sweep path.*/
class spline_path {
public:
   /// Construct path for use with sweep from array of points and the normal directions for each point.
   /*!  \param p array@
   \n  \param v array@ */
   spline_path(array<pos3d@>@ p, array<vec3d@>@ v);

   /// Construct path for use with sweep from array of points and a single, common normal direction.
   /*!  \param p array@
   \n  \param v vec3d@ */
   spline_path(array<pos3d@>@ p, vec3d@ v);

};

/// square, by default located in 1st quadrant touching origin
/*! a square is a 2d quadrilateral with equal dimensions in x and y.
\n By default it touches the origin and extend along positive x and y.*/
class square : public shape2d {
public:
   /// Create square with given side length
   /*!  \param size double, extent in x and y
   \n  \param center bool, true if square to be centered on origon */
   square(double size, bool center = false);

   /// size of square
   /*!  \return double, size of square */
  double  size() const;

};

/// String type similar to C++ strings.
class string {
public:
   /*!  \return bool */
  bool  empty() const;

   /*!  \return bool */
  bool  isEmpty() const;

   /*!  \param  const string&
   \n  \return bool */
  bool  opEquals(const string&in) const;

   /*!  \param  uint
   \n  \return uint8 */
  const  uint8& opIndex(uint) const;

   /*!  \param  const string&
   \n  \param start uint
   \n  \return int */
  int  find(const string&in, uint start = 0) const;

   /*!  \param  const string&
   \n  \param start uint
   \n  \return int */
  int  findFirst(const string&in, uint start = 0) const;

   /*!  \param  const string&
   \n  \param start int
   \n  \return int */
  int  findLast(const string&in, int start = - 1) const;

   /*!  \param  const string&
   \n  \return int */
  int  opCmp(const string&in) const;

   /*!  \param  const string&
   \n  \param start int
   \n  \return int */
  int  rfind(const string&in, int start = - 1) const;

   /*!  \param  bool
   \n  \return string& */
  string&  opAddAssign(bool);

   /*!  \param  const string&
   \n  \return string& */
  string&  opAddAssign(const string&in);

   /*!  \param  double
   \n  \return string& */
  string&  opAddAssign(double);

   /*!  \param  float
   \n  \return string& */
  string&  opAddAssign(float);

   /*!  \param  int64
   \n  \return string& */
  string&  opAddAssign(int64);

   /*!  \param  uint64
   \n  \return string& */
  string&  opAddAssign(uint64);

   /*!  \param  bool
   \n  \return string& */
  string&  opAssign(bool);

   /*!  \param  const string&
   \n  \return string& */
  string&  opAssign(const string&in);

   /*!  \param  double
   \n  \return string& */
  string&  opAssign(double);

   /*!  \param  float
   \n  \return string& */
  string&  opAssign(float);

   /*!  \param  int64
   \n  \return string& */
  string&  opAssign(int64);

   /*!  \param  uint64
   \n  \return string& */
  string&  opAssign(uint64);

   /*!  \param  bool
   \n  \return string */
  string  opAdd(bool) const;

   /*!  \param  const string&
   \n  \return string */
  string  opAdd(const string&in) const;

   /*!  \param  double
   \n  \return string */
  string  opAdd(double) const;

   /*!  \param  float
   \n  \return string */
  string  opAdd(float) const;

   /*!  \param  int64
   \n  \return string */
  string  opAdd(int64) const;

   /*!  \param  uint64
   \n  \return string */
  string  opAdd(uint64) const;

   /*!  \param  bool
   \n  \return string */
  string  opAdd_r(bool) const;

   /*!  \param  double
   \n  \return string */
  string  opAdd_r(double) const;

   /*!  \param  float
   \n  \return string */
  string  opAdd_r(float) const;

   /*!  \param  int64
   \n  \return string */
  string  opAdd_r(int64) const;

   /*!  \param  uint64
   \n  \return string */
  string  opAdd_r(uint64) const;

   /*!  \param start uint
   \n  \param count int
   \n  \return string */
  string  substr(uint start = 0, int count = - 1) const;

   /*!  \param  uint
   \n  \return uint8 */
  uint8&  opIndex(uint);

   /*!  \return uint */
  uint  get_length() const;

   /*!  \return uint */
  uint  length() const;

   /*!  \return uint */
  uint  size() const;

   /*!  \param  uint */
  void  resize(uint);

   /*!  \param  uint */
  void  set_length(uint);

};

/// Sweep 2d shape along path curve to create 3d solid
/*! a sweep creates a solid by sweeping a 2d profile along a path curve*/
class sweep : public solid {
public:
   /// Construct 3d object by sweeping 2d shape along spline path.
   /*!  \param shape shape2d@, 2d profile shape to sweep
   \n  \param path spline_path@, The path cirve to sweep along */
   sweep(const shape2d@ shape, const spline_path@ path);

};

/// Abstract base matrix for transformations
/*! a tmatrix an abstract base class for all transformations.*/
class tmatrix {
public:
   /// Multiply a position with transformation and return a new position.
   /*!  \param obj pos2d@
   \n  \return pos2d@ */
  pos2d*  opMul(pos2d@ obj);

   /// transform a point: pos3d@ p = T*obj;
   /*!  \param obj pos3d@, position to be transformed
   \n  \return pos3d@, transformed position */
  pos3d*  opMul(pos3d@ obj);

   /// Return origin of transformation (4th column)
   /*!  \return pos3d@ */
  pos3d*  origin() const;

   /// transform a 2d shape: shape2d@ s = T*obj;
   /*!  \param obj shape2d@, object to be transformed
   \n  \return shape2d@, transformed object */
  shape2d*  opMul(shape2d@ obj);

   /// transform a solid: solid@ s = T*obj;
   /*!  \param obj solid@, object to be transformed
   \n  \return solid@, transformed object */
  solid*  opMul(solid@ obj);

   /// matrix multiplication: A = T*B
   /*!  \param B tmatrix@, matrix to be post-multiplied with this matrix
   \n  \return tmatrix@, resulting matrixt */
  tmatrix*  opMul(const tmatrix@ B);

   /// Return x direction vector
   /*!  \return vec3d@ */
  vec3d*  xdir() const;

   /// Return y direction vector
   /*!  \return vec3d@ */
  vec3d*  ydir() const;

   /// Return z direction vector
   /*!  \return vec3d@ */
  vec3d*  zdir() const;

   /// dump matrix to console
  void  dump() const;

};

/// Extrude from botton to top shapes using transform
/*! transform_extrude is a special extrusion operation, defined by two 2d shapes, representing bottom and top of extrusion.*/
class transform_extrude : public solid {
public:
   /// Create solid by extruding from bottom to top
   /*! The top shape should be multiplied with a translation in z-direction   */
   /*!  \param bottom shape2d@
   \n  \param top shape2d@ */
   transform_extrude(const shape2d@ bottom, const shape2d@ top);

};

/// Translation in x, y and z
/*! translate is a transformation translating a 2d or 3d object.*/
class translate : public tmatrix {
public:
   /// Specify translation as a 3d vector
   /*!  \param v vec3d@ */
   translate(const vec3d@ v);

   /// Create transformation specifying translation in x, y and z
   /*!  \param dx double, translation in x direction
   \n  \param dy double, translation in y direction
   \n  \param dz double, translation in z direction */
   translate(double dx, double dy, double dz = 0.0);

   /// translation in x direction
   /*!  \return double, translation in x direction */
  double  dx() const;

   /// translation in y direction
   /*!  \return double, translation in y direction */
  double  dy() const;

   /// translation in z direction
   /*!  \return double, translation in z direction */
  double  dz() const;

};

/// 2d union boolean operation
/*! union2d is a 2-dimensional boolean operation. It can be invoked either
\n explicitly or using + operator:
\n explicit: shape2d@ object = union2d(circle(100),translate(75,0,0)*circle(50));
\n using & operator: shape2d@ object = circle(100) + translate(75,0,0)*circle(50);*/
class union2d : public shape2d {
public:
   /// Compute union of 2 objects
   /*!  \param s1 shape2d@, 2d shape
   \n  \param s2 shape2d@, 2d shape */
   union2d(const shape2d@ s1, const shape2d@ s2);

   /// Compute union of 3 objects
   /*!  \param s1 shape2d@, 2d shape
   \n  \param s2 shape2d@, 2d shape
   \n  \param s3 shape2d@, 2d shape */
   union2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3);

   /// Compute union of 4 objects
   /*!  \param s1 shape2d@, 2d shape
   \n  \param s2 shape2d@, 2d shape
   \n  \param s3 shape2d@, 2d shape
   \n  \param s4 shape2d@, 2d shape */
   union2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4);

   /// Compute union of 5 objects
   /*!  \param s1 shape2d@, 2d shape
   \n  \param s2 shape2d@, 2d shape
   \n  \param s3 shape2d@, 2d shape
   \n  \param s4 shape2d@, 2d shape
   \n  \param s5 shape2d@, 2d shape */
   union2d(const shape2d@ s1, const shape2d@ s2, const shape2d@ s3, const shape2d@ s4, const shape2d@ s5);

   /*!  \param arr array@ */
   union2d(array<shape2d@>@ arr);

};

/// 3d union boolean operation
/*! union3d is a 3-dimensional boolean operation. It can be invoked either
\n explicitly or using + operator:
\n explicit: solid@ object = union3d(sphere(100),translate(75,0,0)*sphere(50));
\n using & operator: solid@ object = sphere(100) + translate(75,0,0)*sphere(50);*/
class union3d : public solid {
public:
   /// Compute union of 2 objects
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid */
   union3d(const solid@ s1, const solid@ s2);

   /// Compute union of 3 objects
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid
   \n  \param s3 solid@, solid */
   union3d(const solid@ s1, const solid@ s2, const solid@ s3);

   /// Compute union of 4 objects
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid
   \n  \param s3 solid@, solid
   \n  \param s4 solid@, solid */
   union3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4);

   /// Compute union of 5 objects
   /*!  \param s1 solid@, solid
   \n  \param s2 solid@, solid
   \n  \param s3 solid@, solid
   \n  \param s4 solid@, solid
   \n  \param s5 solid@, solid */
   union3d(const solid@ s1, const solid@ s2, const solid@ s3, const solid@ s4, const solid@ s5);

   /*!  \param arr array@ */
   union3d(array<solid@>@ arr);

};

/// 2d direction vector
/*! vec2d is a 2-dimensional vector offering useful operations such as dot and cross products.*/
class vec2d {
public:
   /// Create direction vector from p1 to p2
   /*!  \param p1 pos2d@, vector start position
   \n  \param p2 pos2d@, vector end position */
   vec2d(const pos2d@ p1, const pos2d@ p2);

   /// Construct direction vector from other vector
   /*!  \param other vec2d@ */
   vec2d(const vec2d@ other);

   /// Construct direction vector from x and y components
   /*!  \param x double, vector x component
   \n  \param y double, vector y component */
   vec2d(double x, double y);

   /// angle between: double rad = v.angle(other);
   /*!  \param other vec2d@, vector to compute angle relative to this
   \n  \return double, angle value in radians */
  double  angle(const vec2d@ other) const;

   /// cross product: double cp = v.cross(other);
   /*!  \param other vec2d@, vector to multiply with
   \n  \return double, cross product value */
  double  cross(const vec2d@ other) const;

   /// dot product: double cp = v.dot(other);
   /*!  \param other vec2d@, vector to multiply with
   \n  \return double, dot product value */
  double  dot(const vec2d@ other) const;

   /// length of vector
   /*!  \return double, length of vector */
  double  length() const;

   /// vector x component
   /*!  \return double, vector x component */
  double  x() const;

   /// vector y component
   /*!  \return double, vector y component */
  double  y() const;

   /// Add vector to vector, return new vector: vec2d@ v = v0 + v1
   /*!  \param v1 vec2d@
   \n  \return vec2d@ */
  vec2d*  opAdd(vec2d@ v1);

   /// Multiply vector with factor, return new vector: vec2d@ v = v0 * f1
   /*!  \param f1 double
   \n  \return vec2d@ */
  vec2d*  opMul(double f1);

   /// Multiply vector with factor, return new vector: vec2d@ v = f1 * v0
   /*!  \param f1 double
   \n  \return vec2d@ */
  vec2d*  opMul_r(double f1);

   /// Subtract vector from vector, return new vector: vec2d@ v = v0 - v1
   /*!  \param v1 vec2d@
   \n  \return vec2d@ */
  vec2d*  opSub(vec2d@ v1);

   /// normalise vector length
  void  normalise();

};

/// 3d direction vector
/*! vec3d is a 3-dimensional vector offering useful operations such as dot and cross products.*/
class vec3d {
public:
   /// Construct direction vector as direction from p1 to p2
   /*!  \param p1 pos3d@
   \n  \param p2 pos3d@ */
   vec3d(const pos3d@ p1, const pos3d@ p2);

   /// Construct direction vector from other vector.
   /*!  \param other vec3d@ */
   vec3d(const vec3d@ other);

   /// Create direction vector from x,y and z components.
   /*!  \param x double, vector x component
   \n  \param y double, vector y component
   \n  \param z double, vector z component */
   vec3d(double x, double y, double z);

   /// angle between: double rad = v.angle(other);
   /*!  \param other vec3d@, vector to compute angle relative to this
   \n  \return double, angle value in radians */
  double  angle(const vec3d@ other) const;

   /// dot product: double cp = v.dot(other);
   /*!  \param other vec3d@, vector to multiply with
   \n  \return double, dot product value */
  double  dot(const vec3d@ other) const;

   /// length of vector
   /*!  \return double, length of vector */
  double  length() const;

   /// vector x component
   /*!  \return double, vector x component */
  double  x() const;

   /// vector y component
   /*!  \return double, vector y component */
  double  y() const;

   /// vector z component
   /*!  \return double, vector z component */
  double  z() const;

   /// cross product: double cp = v.cross(other);
   /*!  \param other vec3d@, vector to multiply with
   \n  \return vec3d@, cross product value */
  vec3d*  cross(const vec3d@ other) const;

   /// Add vector to vector, return new vector: vec3d@ v = v0 + v1.
   /*!  \param v1 vec3d@
   \n  \return vec3d@ */
  vec3d*  opAdd(vec3d@ v1);

   /// Multiply vector with factor, return new vector: vec3d@ v = v0 * f1
   /*!  \param f1 double
   \n  \return vec3d@ */
  vec3d*  opMul(double f1);

   /// Multiply vector with factor, return new vector: vec3d@ v = f1 * v0.
   /*!  \param f1 double
   \n  \return vec3d@ */
  vec3d*  opMul_r(double f1);

   /// Subtract vector from vector, return new vector: vec3d@ v = v0 - v1.
   /*!  \param v1 vec3d@
   \n  \return vec3d@ */
  vec3d*  opSub(vec3d@ v1);

   /// normalise vector length
  void  normalise();

};
