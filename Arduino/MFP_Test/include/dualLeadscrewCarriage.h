#pragma once
#include "DM320T.h"

class dualLeadscrewCarriage
{
  DM320T m_motor1 {};
  DM320T m_motor2 {};
  constexpr static double m_leadscrewPitch {8.0};   //mm/rev
  constexpr static double m_wormgearDiameter {35.0};  //mm

  struct Position
  {
    double linear {0.0};    //millimeters
    double angular {0.0};   //degrees
  };
  Position m_homePosition {};
  Position m_currentPosition {};

  public:
  dualLeadscrewCarriage(DM320T& motor1, DM320T& motor2);

  Position getCurrentPosition();
  Position getHomePosition() const {return m_homePosition;}

  bool outOfRange(double currentPosition, double targetDisplacement, double delta);
  void linearMove(int pulses);
  void linearMove(double linearDisplacement);
  void rotationalMove(int pulses);
  void setHomePosition(Position position);
  void setHomePosition(double linearHome = 0.0, double angularHome = 0.0);
  void setCurrentPosition(const Position& currentPosition) {m_currentPosition = currentPosition;}
  void calcPosition();
  void printCurrentPosition();
  int calcPulses(double linearDisplacement); //linearDisplacement is in mm
};
