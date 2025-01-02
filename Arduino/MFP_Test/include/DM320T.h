#pragma once

class DM320T
{
  private:
  const int m_pulsePin {};
  const int m_directionPin {};
  const int m_microstepSize {};
  const int m_homePin {};
  bool m_direction {};
  int m_position {};
  int m_motorHome {};
  static constexpr int m_pulsePerRev {400};

  public:
  enum Direction
  {
    up,
    down
  };

  DM320T() {}
  DM320T(int pulsePin, int directionPin, int microstepSize, int homePin);

  int getPosition() const {return m_position;}
  int getPulsePerRev() const {return m_pulsePerRev;}
  bool getDirection() const {return m_direction;}
  int getMicrostepSize() const {return m_microstepSize;}
  int getPulsePin() const {return m_pulsePin;}
  void incrementPosition(int pulses = 1) {m_direction ? (m_position -= pulses) : (m_position += pulses);}
  
  void printPosition();
  void setDirection(Direction direction);
  void moveMotor(int steps = 1, int usDelay = 100);
  void homeMotor();
};
