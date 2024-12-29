#include <Arduino.h>
#include "DM320T.h"
#include "dualLeadscrewCarriage.h"

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


void setup() {
  Serial.begin(115200);
  DM320T motor1 {3, 2, 400, 5};
  DM320T motor2 {7, 8, 400, 5};
  dualLeadscrewCarriage dlc {motor1, motor2};

  while (true)
  {
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
