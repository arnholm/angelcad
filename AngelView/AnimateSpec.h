#ifndef ANIMATESPEC_H
#define ANIMATESPEC_H

#include "AnimateCurve.h"
#include <vector>

class AnimateSpec {
public:
   using curve_vector   = std::vector<std::shared_ptr<AnimateCurve>>;
   using const_iterator = curve_vector::const_iterator;

   AnimateSpec(size_t sectot, size_t fsec);
   virtual ~AnimateSpec();

   void push_back(std::shared_ptr<AnimateCurve> curve) { m_curves.push_back(curve); }

   void finalize();

   size_t millisec_per_frame() const { return 1000*m_sectot/total_frames(); }
   size_t total_frames() const       { return m_sectot*m_fsec; }
   size_t frames_per_second() const  { return m_fsec; }
   size_t total_seconds() const      { return m_sectot; }

   size_t size() const { return m_curves.size(); }
   const_iterator begin() const { return m_curves.begin(); }
   const_iterator end() const { return m_curves.end(); }

   void prepare_animation();

   std::shared_ptr<AnimateCurve> get_current_curve();
   void increment_current_curve() { m_curve_index++; }

   size_t frame_counter() const { return m_frame_counter; }
   void increment_frame_counter() { m_frame_counter++; }

private:
   size_t        m_sectot;    // total number of seconds in animation
   size_t        m_fsec;      // Frames per second
   curve_vector  m_curves;
   size_t        m_curve_index; // keeps track of current curve during animation
   size_t        m_frame_counter; // animation frame counter
};

#endif // ANIMATESPEC_H
