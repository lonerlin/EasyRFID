/*
Created by Lin Jungui
July,2017
*/
#include <EasyRFID.h>

EasyRFID rfid(10,5);   //D10--读卡器MOSI引脚、D5--读卡器RST引脚
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop()
{
  //找卡
  if (rfid.isCard()) {
    Serial.println("Find the card!");
    //读取卡序列号
    Serial.println(rfid.getSerialNumber());
     //选卡，可返回卡容量（锁定卡片，防止多数读取），去掉本行将连续读卡
     rfid.selectTag(rfid.serNum);
    }
  rfid.halt();
}
