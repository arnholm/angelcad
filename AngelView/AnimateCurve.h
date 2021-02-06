#ifndef ANIMATECURVE_H
#define ANIMATECURVE_H

#include <memory>
#include "spacemath/locsys3d.h"
#include "spacemath/spline3d.h"
#include "spacemath/quaternion.h"
#include "spacemath/HTmatrix.h"
using namespace spacemath;

class AnimateCurve {
public:
   AnimateCurve();

   AnimateCurve(const spline3d& path,
                const quaternion& q0,
                const quaternion& q1,
                size_t nstep
                );
   virtual ~AnimateCurve();

   void set_path(const spline3d& path) { m_path = path; }
   void set_q0(const quaternion& q0)   { m_q0 = q0; }
   void set_q1(const quaternion& q1)   { m_q1 = q1; }

   // set/get number of steps
   void   set_nstep(size_t nstep) { m_nstep = nstep; }
   size_t get_nstep()             { return m_nstep; }

   void   set_istep(size_t istep) { m_istep = istep; }
   size_t get_istep()             { return m_istep; }
   void   increment_istep()       { m_istep++; }

   // return length of curve;
   double length() const;

   // obtain interpolated matrix at parameter p = [0,1]
   HTmatrix interpolate(double par);

private:
   spline3d   m_path;
   quaternion m_q0;
   quaternion m_q1;
   size_t     m_nstep; // number of steps to animate for this curve
   size_t     m_istep; // step number during animation
};

#endif // ANIMATECURVE_H
