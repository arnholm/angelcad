#include "AnimateSpec.h"

AnimateSpec::AnimateSpec(size_t sectot, size_t fsec, const std::pair<bool,double>& orbit)
: m_sectot(sectot)
, m_fsec(fsec)
, m_orbit(orbit)
, m_curve_index(0)
, m_frame_counter(0)
{}

AnimateSpec::~AnimateSpec()
{}

void AnimateSpec::finalize()
{
   // sum of curve lengths
   double sumlen = 0.0;
   for(auto& c : m_curves) sumlen += c->length();

   // total number of steps
   size_t nstep_tot = m_sectot*m_fsec;

   for(auto& c : m_curves) {
      double frac = c->length()/sumlen;
      size_t nstep = std::max(1,static_cast<int>(frac*nstep_tot));
      c->set_nstep(nstep);
      c->set_istep(0);
   }
   m_curve_index = 0;
}

void AnimateSpec::prepare_animation()
{
   for(auto& c : m_curves) {
      c->set_istep(0);
   }
   m_curve_index = 0;
   m_frame_counter = 0;
}

std::shared_ptr<AnimateCurve> AnimateSpec::get_current_curve()
{
   std::shared_ptr<AnimateCurve> curve;
   if(m_curve_index < m_curves.size()) curve = m_curves[m_curve_index];
   return curve;
}
