#include <Arduino.h>

class PID
{
  double m_Kp {};
  double m_Ki {};
  double m_Kd {};
  double m_ep {};
  double m_ei {};
  double m_ed {};

  public:
  PID(double Kp, double Ki, double Kd)
    : m_Kp {Kp}, m_Ki {Ki}, m_Kd {Kd}
  {}

  double calcPID(double targetPosition, double currentPosition)
  {
    double previous_ep {m_ep};
    m_ep = {currentPosition - targetPosition};
    m_ei += m_ep;
    m_ed = (m_ep - previous_ep);
    double delta = m_Kp*m_ep + m_Ki*m_ei + m_Kd*m_ed;
    return delta;
  }
};

class DM320T
{
  private:
  int m_pulsePin {};
  int m_directionPin {};
  int m_homePin {};
  bool m_direction {};
  int m_position {};
  int m_microstepSize {};
  int m_motorHome {};

  enum Direction
  {
    down,
    up
  };

  public:
  DM320T()
  {}

  DM320T(int pulsePin, int directionPin, int microstepSize, int homePin)
    : m_pulsePin {pulsePin}, m_directionPin {directionPin}, m_microstepSize {microstepSize}, m_homePin {homePin}
  {
    pinMode(m_pulsePin, OUTPUT);
    pinMode(m_directionPin, OUTPUT);
    pinMode(m_homePin, INPUT);
    digitalWrite(m_pulsePin, 0);
    digitalWrite(m_direction, 0);
  }

  int getPosition() const {return m_position;}
  bool getDirection() const {return m_direction;}
  int getMicrostepSize() const {return m_microstepSize;}
  
  void setDirection(bool direction) 
  {
    m_direction = direction;
    digitalWrite(m_directionPin, direction);
  }

  void moveMotor(int steps = 1)
  {
    for (int i = 0; i < steps; i++)
    {
      digitalWrite(m_pulsePin, LOW);
      digitalWrite(m_pulsePin, HIGH);
      digitalWrite(m_pulsePin, LOW);
    }
  }

  void homeMotor()
  {
    setDirection(down);
    while (!digitalRead(m_homePin))
    {
      moveMotor();
    }
    m_motorHome = true;
  }
};

class dualLeadscrewCarriage
{
  DM320T m_motor1 {};
  DM320T m_motor2 {};
  PID m_pid {0.5, 0.1, 0.01};

  public:
  dualLeadscrewCarriage(DM320T motor1, DM320T motor2)
    : m_motor1 {motor1}, m_motor2 {motor2}
  {
    m_motor1.homeMotor();
    m_motor2.homeMotor();
  }

  bool outOfRange(double currentPosition, double targetDisplacement, double delta)
  {
    bool evaluation {currentPosition < targetDisplacement*(1 - delta) || currentPosition < targetDisplacement*(1 + delta)};
    return evaluation;
  }

  void linearMove(double linearDisplacement)
  {
    while (outOfRange(m_motor1.getPosition(), linearDisplacement, 0.05) && outOfRange(m_motor2.getPosition(), linearDisplacement, 0.05))
    {
      m_motor1.moveMotor();
      m_motor2.moveMotor();
    }
  }

  void rotationalMove()
  {
    
  }

};

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
