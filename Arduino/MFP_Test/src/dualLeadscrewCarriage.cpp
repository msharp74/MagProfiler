#include "Arduino.h"
#include "dualLeadscrewCarriage.h"
#include "DM320T.h"

dualLeadscrewCarriage::dualLeadscrewCarriage(DM320T& motor1, DM320T& motor2)
    : m_motor1 {motor1}, m_motor2 {motor2}
{
    // m_motor1.homeMotor();
    // m_motor2.homeMotor();
}

bool dualLeadscrewCarriage::outOfRange(double currentPosition, double targetDisplacement, double delta)
{
    bool evaluation {currentPosition < targetDisplacement*(1 - delta) || currentPosition < targetDisplacement*(1 + delta)};
    return evaluation;
}

void dualLeadscrewCarriage::linearMove(int pulses)
{
  if (pulses < 0)
  {
    m_motor1.setDirection(DM320T::down);
    m_motor2.setDirection(DM320T::down);
    pulses *= -1;
  } else {
    m_motor1.setDirection(DM320T::up);
    m_motor2.setDirection(DM320T::up);
  }
  for (int i {0}; i < pulses; i++)
  {
    m_motor1.moveMotor();
    m_motor2.moveMotor();
  }
}

void dualLeadscrewCarriage::linearMove(double linearDisplacement)
{
  while (outOfRange(m_motor1.getPosition(), linearDisplacement, 0.05) && outOfRange(m_motor2.getPosition(), linearDisplacement, 0.05))
  {
    m_motor1.moveMotor();
    m_motor2.moveMotor();
  }
}

void dualLeadscrewCarriage::rotationalMove(int pulses)
{
  if (pulses < 0)
  {
    m_motor1.setDirection(DM320T::up);
    m_motor2.setDirection(DM320T::down);
    pulses *= -1;
  } else {
    m_motor1.setDirection(DM320T::down);
    m_motor2.setDirection(DM320T::up);
  }

  for (int i {0}; i < pulses; i++)
  {
    m_motor1.moveMotor();
    m_motor2.moveMotor();
  }
}

void dualLeadscrewCarriage::calcPosition()
{
  Position position {};
  int maxPulses {max(m_motor1.getPosition(),m_motor2.getPosition())};
  int minPulses {min(m_motor1.getPosition(),m_motor2.getPosition())};
  position.linear = ((minPulses + (maxPulses - minPulses)/2)*m_leadscrewPitch/m_motor1.getPulsePerRev()) - m_homePosition.linear;
  position.angular = ((m_motor1.getPosition() - m_motor2.getPosition())/2.0)*180*m_leadscrewPitch*2/(m_wormgearDiameter*m_motor1.getPulsePerRev()*3.14159) - m_homePosition.angular;
  m_currentPosition = position;
}

void dualLeadscrewCarriage::printCurrentPosition()
{
  calcPosition();
  Serial.print("Linear Position: ");
  Serial.println(m_currentPosition.linear);
  Serial.print("Angular Position: ");
  Serial.println(m_currentPosition.angular);
  // Serial.print("Motor 1 Position: ");
  // Serial.println(m_motor1.getPosition());
  // Serial.print("Motor 2 Position: ");
  // Serial.println(m_motor2.getPosition());
  Serial.println();
}

dualLeadscrewCarriage::Position dualLeadscrewCarriage::getCurrentPosition()
{
  calcPosition();
  return m_currentPosition;
}

void dualLeadscrewCarriage::setHomePosition(double linearHome, double angularHome)
{
  m_homePosition.linear = linearHome;
  m_homePosition.angular = angularHome;
  // m_homePosition = {linearHome, angularHome};
}

void dualLeadscrewCarriage::setHomePosition(Position position)
{
  m_homePosition = position;
  // m_homePosition = {linearHome, angularHome};
}

int dualLeadscrewCarriage::calcPulses(double linearDisplacement)
{
  int pulses {};
  pulses = linearDisplacement * m_
}
