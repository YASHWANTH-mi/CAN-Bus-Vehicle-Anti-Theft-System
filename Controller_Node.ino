/*
  Controller Node
  ESP32 #2

  Receives CAN messages
  Sends LoRa alerts
  Controls Relay
*/

#include <ESP32-TWAI-CAN.hpp>

#define RELAY_PIN 23

bool vehicleLocked = false;

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  TWAI.begin();
  TWAI.setSpeed(500000);

  Serial.println("Controller Node Started");
}

void sendAlert(String msg)
{
  Serial.print("LoRa Alert : ");
  Serial.println(msg);
}

void loop()
{
  CanFrame frame;

  if(TWAI.read(frame))
  {
    if(frame.identifier==0x100)
    {
      Serial.println("Intrusion Detected");
      sendAlert("WARNING : Door Intrusion");
    }

    if(frame.identifier==0x101)
    {
      Serial.println("Ignition Attempt");
      sendAlert("WARNING : Engine Start Attempt");
    }
  }

  if(vehicleLocked)
  {
    digitalWrite(RELAY_PIN,HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN,LOW);
  }

  delay(100);
}
