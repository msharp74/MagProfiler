#include "DM320T.h"
#include "Arduino.h"

DM320T::DM320T(int pulsePin, int directionPin, int microstepSize, int homePin)
  : m_pulsePin {pulsePin}, m_directionPin {directionPin}, m_microstepSize {microstepSize}, m_homePin {homePin}
{
  pinMode(m_pulsePin, OUTPUT);
  pinMode(m_directionPin, OUTPUT);
  pinMode(m_homePin, INPUT);
  digitalWrite(m_pulsePin, 0);
  digitalWrite(m_direction, 0);
  Serial.println("Motor Object Created");
}

void DM320T::setDirection(Direction direction)
{
  m_direction = direction;
  digitalWrite(m_directionPin, direction);
}

void DM320T::moveMotor(int steps, int usDelay)
{
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(m_pulsePin, LOW);
    delayMicroseconds(10);
    digitalWrite(m_pulsePin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_pulsePin, LOW);
    delayMicroseconds(usDelay);
    incrementPosition();
  }
}

void DM320T::homeMotor()
{
  setDirection(down);
  while (!digitalRead(m_homePin))
  {
    moveMotor();
  }
  m_motorHome = true;
}

void DM320T::printPosition()
{
  Serial.println(m_position);
}