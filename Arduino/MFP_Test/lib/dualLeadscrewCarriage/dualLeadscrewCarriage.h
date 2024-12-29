#pragma once
#include "DM320T.h"

class dualLeadscrewCarriage
{
  DM320T m_motor1 {};
  DM320T m_motor2 {};
  PID m_pid {0.5, 0.1, 0.01};

  public:
  dualLeadscrewCarriage(DM320T motor1, DM320T motor2);
  bool outOfRange(double currentPosition, double targetDisplacement, double delta);
  void linearMove(int pulses);
  void linearMove(double linearDisplacement);
  void rotationalMove(int pulses);
};