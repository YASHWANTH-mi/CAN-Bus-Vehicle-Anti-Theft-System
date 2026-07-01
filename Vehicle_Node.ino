/*
   Vehicle Node (ESP32 #1)

   Functions:
   - Read IR Sensor
   - Read Ignition Switch
   - Send CAN Messages to Controller Node
*/

#include <ESP32-TWAI-CAN.hpp>

#define IR_SENSOR_PIN 15
#define IGNITION_PIN 4

bool intrusionDetected = false;
bool ignitionDetected = false;

void setup() {

  Serial.begin(115200);

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(IGNITION_PIN, INPUT_PULLUP);

  TWAI.begin();
  TWAI.setSpeed(500000);

  Serial.println("Vehicle Node Started");
}

void sendCAN(uint32_t id, uint8_t value)
{
  CanFrame frame;

  frame.identifier = id;
  frame.extd = 0;
  frame.data_length_code = 1;
  frame.data[0] = value;

  TWAI.write(frame);
}

void loop() {

  intrusionDetected = digitalRead(IR_SENSOR_PIN);

  if (intrusionDetected)
  {
    Serial.println("Intrusion Detected");

    sendCAN(0x100,1);

    delay(1000);
  }

  ignitionDetected = digitalRead(IGNITION_PIN)==LOW;

  if (ignitionDetected)
  {
    Serial.println("Ignition Attempt");

    sendCAN(0x101,1);

    delay(1000);
  }

  delay(100);
}
