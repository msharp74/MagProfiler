#include "Arduino.h"
#include "dualLeadscrewCarriage.h"
#include "DM320T.h"

dualLeadscrewCarriage::dualLeadscrewCarriage(const DM320T& motor1, const DM320T& motor2)
    : m_motor1 {motor1}, m_motor2 {motor2}
{
    // m_motor1.homeMotor();
    // m_motor2.homeMotor();
}

inline bool dualLeadscrewCarriage::outOfRange(double currentPosition, double targetDisplacement, double delta)
{
    bool evaluation {currentPosition < targetDisplacement*(1 - delta) || currentPosition < targetDisplacement*(1 + delta)};
    return evaluation;
}

inline void dualLeadscrewCarriage::linearMove(int pulses)
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
    digitalWrite(m_motor1.getPulsePin(), LOW);
    digitalWrite(m_motor2.getPulsePin(), LOW);
    delayMicroseconds(10);
    digitalWrite(m_motor1.getPulsePin(), HIGH);
    digitalWrite(m_motor2.getPulsePin(), HIGH);
    delayMicroseconds(10);
    m_motor1.incrementPosition();
    m_motor2.incrementPosition();
    // digitalWrite(m_motor1.getPulsePin(), LOW);
    // digitalWrite(m_motor2.getPulsePin(), LOW);
    delay(1);
  }
}

inline void dualLeadscrewCarriage::linearMove(double linearDisplacement)
{
  while (outOfRange(m_motor1.getPosition(), linearDisplacement, 0.05) && outOfRange(m_motor2.getPosition(), linearDisplacement, 0.05))
  {
    m_motor1.moveMotor();
    m_motor2.moveMotor();
  }
}

inline void dualLeadscrewCarriage::rotationalMove(int pulses)
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
    digitalWrite(m_motor1.getPulsePin(), LOW);
    digitalWrite(m_motor2.getPulsePin(), LOW);
    delayMicroseconds(10);
    digitalWrite(m_motor1.getPulsePin(), HIGH);
    digitalWrite(m_motor2.getPulsePin(), HIGH);
    delayMicroseconds(10);
    m_motor1.incrementPosition();
    m_motor2.incrementPosition();
    // digitalWrite(m_motor1.getPulsePin(), LOW);
    // digitalWrite(m_motor2.getPulsePin(), LOW);
    delay(1);
  }
}

inline dualLeadscrewCarriage::Position dualLeadscrewCarriage::getPosition() const
{
  Position position {max(m_motor1.getPosition(),m_motor2.getPosition())};
  int maxPulses {max(m_motor1.getPosition(),m_motor2.getPosition())};
  int minPulses {min(m_motor1.getPosition(),m_motor2.getPosition())};
  position.linear = ((minPulses + (maxPulses - minPulses)/2)*m_leadscrewPitch/m_motor1.getPulsePerRev());
  position.angular = (abs)
}