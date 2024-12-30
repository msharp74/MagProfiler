#pragma once
#include "DM320T.h"

class dualLeadscrewCarriage
{
  DM320T m_motor1 {};
  DM320T m_motor2 {};
  const static double m_leadscrewPitch {8};   //mm/rev

  struct Position
  {
    double linear {0.0};    //millimeters
    double angular {0.0};   //degrees
    double home {0.0};
  } m_position {};

  public:
  dualLeadscrewCarriage(const DM320T& motor1, const DM320T& motor2);
  bool outOfRange(double currentPosition, double targetDisplacement, double delta);
  void linearMove(int pulses);
  void linearMove(double linearDisplacement);
  void rotationalMove(int pulses);
  Position getPosition() const;
};