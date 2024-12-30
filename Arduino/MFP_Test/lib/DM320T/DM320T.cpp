#include "DM320T.h"
#include "Arduino.h"

inline DM320T::DM320T(int pulsePin, int directionPin, int microstepSize, int homePin)
  : m_pulsePin {pulsePin}, m_directionPin {directionPin}, m_microstepSize {microstepSize}, m_homePin {homePin}
{
  pinMode(m_pulsePin, OUTPUT);
  pinMode(m_directionPin, OUTPUT);
  pinMode(m_homePin, INPUT);
  digitalWrite(m_pulsePin, 0);
  digitalWrite(m_direction, 0);
  Serial.println("Motor Object Created");
}

inline void DM320T::setDirection(Direction direction)
{
  m_direction = direction;
  digitalWrite(m_directionPin, direction);
}

inline void DM320T::moveMotor(int steps = 1)
{
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(m_pulsePin, LOW);
    delayMicroseconds(10);
    digitalWrite(m_pulsePin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_pulsePin, LOW);
    delay(1);
  }
}

inline void DM320T::homeMotor()
{
  setDirection(down);
  while (!digitalRead(m_homePin))
  {
    moveMotor();
  }
  m_motorHome = true;
}