/*
   Owner Node

   Receives LoRa alerts
   Controls Lock / Unlock
*/

bool parkingMode = true;
bool lockMode = false;

void setup()
{
  Serial.begin(115200);

  Serial.println("Owner Node Started");
}

void showMenu()
{
  Serial.println();
  Serial.println("===== Vehicle Menu =====");
  Serial.println("1 -> Parking");
  Serial.println("2 -> Lock");
  Serial.println("3 -> Unlock");
}

void loop()
{
  showMenu();

  if(Serial.available())
  {
    char ch = Serial.read();

    switch(ch)
    {
      case '1':

        parkingMode=true;

        Serial.println("Parking Mode Enabled");

      break;

      case '2':

        lockMode=true;

        Serial.println("Vehicle Locked");

      break;

      case '3':

        lockMode=false;

        Serial.println("Vehicle Unlocked");

      break;
    }
  }

  delay(500);
}
