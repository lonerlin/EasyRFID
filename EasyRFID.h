/* EasyRFID.h - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Based on code  Miguel Balboa (circuitito.com), Jan, 2012. (整理者：极客工坊bg1lsy (lsy@sogou.com))
 * 为了简化RFID的使用，使学过单片机专业知识的人也能玩RFID，开发了这个Library
 * Created by Lin JUNGUI，July，2017
 */
#ifndef EASYRFID_H
#define EASYRFID_H
#include<Arduino.h>
#include <RFID.h>


class EasyRFID : public RFID
{
    public:
        EasyRFID(int chipSelectPin, int NRSTPD);
        String  getSerialNumber();
        bool writeCard(int section,int block,String value);
        bool checkCard();
        String readCard(int section,int block);
        String readTest();
        bool writeTest();
    protected:

    private:
        unsigned char sectorKeyA[6]= {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        bool writeSection(int index,char *value);
};

#endif // EASYRFID_H
