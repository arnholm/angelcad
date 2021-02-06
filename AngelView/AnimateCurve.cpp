#include "AnimateCurve.h"

AnimateCurve::AnimateCurve()
: m_nstep(0)
{}

AnimateCurve::AnimateCurve(const spline3d& path,
                           const quaternion& q0,
                           const quaternion& q1,
                           size_t nstep
                           )
: m_path(path)
, m_q0(q0)
, m_q1(q1)
, m_nstep(nstep)
, m_istep(0)
{}

AnimateCurve::~AnimateCurve()
{}

HTmatrix AnimateCurve::interpolate(double par)
{
   pos3d      p = m_path.pos(par);
   quaternion q = quaternion::interpolate(m_q0,m_q1,par);
   HTmatrix   T = q.to_homogeneous_HTmatrix();
   T(0,3) = p.x();
   T(1,3) = p.y();
   T(2,3) = p.z();
   return std::move(T);
}

double AnimateCurve::length() const
{
   return m_path.polylen();
}
