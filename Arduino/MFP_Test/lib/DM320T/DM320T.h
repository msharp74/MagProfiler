#pragma once

class DM320T
{
  private:
  int m_pulsePin {};
  int m_directionPin {};
  int m_microstepSize {};
  int m_homePin {};
  bool m_direction {};
  int m_position {};
  int m_motorHome {};

  public:
  enum Direction
  {
    down,
    up
  };

  DM320T() {}
  DM320T(int pulsePin, int directionPin, int microstepSize, int homePin);
  int getPosition() const {return m_position;}
  int incrementPosition(int pulses = 1) {m_direction ? (m_position += pulses) : (m_position -= pulses);}
  bool getDirection() const {return m_direction;}
  int getMicrostepSize() const {return m_microstepSize;}
  int getPulsePin() const {return m_pulsePin;}
  
  void setDirection(Direction direction);
  void moveMotor(int steps = 1);
  void homeMotor();
};
