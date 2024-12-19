#include <Arduino.h>

class DM320T
{
  private:
  int m_pulsePin {};
  int m_directionPin {};
  bool m_direction {};
  int m_position {};
  int m_microstepSize {};

  public:
  DM320T(int pulsePin, int directionPin, int microstepSize)
    : m_pulsePin {pulsePin}, m_directionPin {directionPin}, m_microstepSize {microstepSize}
  {}

  int getPosition() {return m_position;}
  bool getDirection() {return m_direction;}
  void setDirection(bool direction) {m_direction = direction;}
  int getMicrostepSize() {return m_microstepSize;}

  void setPosition(int targetPosition)
  {
  }
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
