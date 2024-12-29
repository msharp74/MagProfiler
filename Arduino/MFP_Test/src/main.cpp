#include <Arduino.h>
#include "DM320T.h"

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



class dualLeadscrewCarriage
{
  DM320T m_motor1 {};
  DM320T m_motor2 {};
  PID m_pid {0.5, 0.1, 0.01};

  public:
  dualLeadscrewCarriage(DM320T motor1, DM320T motor2)
    : m_motor1 {motor1}, m_motor2 {motor2}
  {
    // m_motor1.homeMotor();
    // m_motor2.homeMotor();
  }

  bool outOfRange(double currentPosition, double targetDisplacement, double delta)
  {
    bool evaluation {currentPosition < targetDisplacement*(1 - delta) || currentPosition < targetDisplacement*(1 + delta)};
    return evaluation;
  }

  void linearMove(int pulses)
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

  void linearMove(double linearDisplacement)
  {
    while (outOfRange(m_motor1.getPosition(), linearDisplacement, 0.05) && outOfRange(m_motor2.getPosition(), linearDisplacement, 0.05))
    {
      m_motor1.moveMotor();
      m_motor2.moveMotor();
    }
  }

  void rotationalMove(int pulses)
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
};

void setup() {
  Serial.begin(115200);
  DM320T motor1 {3, 2, 400, 5};
  DM320T motor2 {7, 8, 400, 5};
  dualLeadscrewCarriage dlc {motor1, motor2};

  while (true)
  {
    // motor.setDirection(false);
    // Serial.println("false");
    // motor.moveMotor(4000);
    // delay(500);
    // motor.setDirection(true);
    // Serial.println("true");
    // motor.moveMotor(4000);
    // delay(500);
    dlc.linearMove(-8000);
    dlc.rotationalMove(4000);
    dlc.linearMove(4000);
    dlc.rotationalMove(-4000);
    dlc.linearMove(4000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
