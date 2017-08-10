/* EasyRFID.h - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Based on code  Miguel Balboa (circuitito.com), Jan, 2012. (�����ߣ����͹���bg1lsy (lsy@sogou.com))
 * Ϊ�˼�RFID��ʹ�ã�ʹѧ����Ƭ��רҵ֪ʶ����Ҳ����RFID�����������Library
 * Created by Lin JUNGUI��July��2017
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
        bool writeCard(int index,String value);
        bool checkCard();
        String readCard(int index);
        String readTest();
        bool writeTest();
    protected:

    private:
        unsigned char sectorKeyA[6]= {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        bool writeSection(int index,char value[3][16]);
};

#endif // EASYRFID_H
