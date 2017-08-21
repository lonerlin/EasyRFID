#include <EasyRFID.h>

EasyRFID nhedu_RFID( 10,5 );

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(nhedu_RFID.checkCard())
  {	
    Serial.print("Card ID:");
    Serial.print(" ");
    Serial.print(nhedu_RFID.getSerialNumber());
    Serial.print(" ");
    Serial.println();
    if (nhedu_RFID.writeCard(1,0,"Hello World!"))
    {
      Serial.print("Read Card:");
      Serial.print(" ");
      Serial.print(nhedu_RFID.readCard(1,0));
      Serial.print(" ");
      Serial.println();
    }
    else
    {
      Serial.print("Write card failed.");
      Serial.print(" ");
      Serial.println();
    }
    nhedu_RFID.halt();
  }

}


