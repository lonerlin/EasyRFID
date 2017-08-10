/* EasyRFID.h - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Based on code  Miguel Balboa (circuitito.com), Jan, 2012. (整理者：极客工坊bg1lsy (lsy@sogou.com))
 * 为了简化RFID的使用，使学过单片机专业知识的人也能玩RFID，开发了这个Library
 * Created by Lin JUNGUI，July，2017
 */
#include <Arduino.h>
#include "EasyRFID.h"


EasyRFID::EasyRFID(int chipSelectPin, int NRSTPD):RFID(chipSelectPin,NRSTPD)
{
    SPI.begin();
     init();
}


bool EasyRFID:: checkCard()
{
    bool state=false;
    if(isCard())
    {
        Serial.println("isCard");
        if(readCardSerial())
        {
            Serial.println("readSucceed");
            state= true;
        }else
        {
            state= false;
            Serial.println("readfaile");
           // init();
        }
         selectTag(serNum);
    }
    else
    {
        state= false;
    }
    return state;
}
/******************************************************************************
 * 函 数 名：getSerialNumber
 * 功能描述：提供字符串形式的卡编号
 * 输入参数：无
 * 返 回 值：成功返回卡编号 失败返回空字符串
 ******************************************************************************/
String EasyRFID:: getSerialNumber()
{
    unsigned char str[10];
    unsigned char dst[10];

    int i=0;
    String value="";
    //16进制转字符串，方便阅读
    for(i=0;i<5;i++)
    {
        str[2*i]=serNum[i]>>4;
        str[2*i+1]=serNum[i]&0xf;
    }
    for(i = 0; i<10;i++)
    {
        sprintf(&dst[i],"%X",str[i]);
    }
    value=dst;

    return value;
}
bool EasyRFID::writeTest()
{
    unsigned char writeDate[16] ={'T', 'h', 'i', 's', ',', 'W', 'o', 'r', 'l', 'd', '!', 0, 0, 0, 0, 0};
    if (auth(PICC_AUTHENT1A, 1, sectorKeyA, serNum) == MI_OK)
        {
                Serial.println("Pass");
                unsigned char status;
                status=write(1,writeDate);
                if(status!= MI_OK)
                {
                    return false;
                }
        }
        else
        {
                Serial.println("Not Auth");
                return false;
        }


    return true;
}

String EasyRFID::readTest()
{
    if (auth(PICC_AUTHENT1A, 1, sectorKeyA, serNum) == MI_OK)
        {

                unsigned char status;

                 unsigned char str[MAX_LEN];

                status=read(1,str);


                if(status== MI_OK)
                {

                  String value=str;
                  return value;

                }
                else
                {
                    return "";
                }
        }else
        {
            return "";
        }
}
bool EasyRFID::writeCard(int section,int block,String value)
{
    if(block>2 || block<0)return false;
    if(section >15 || section<0) return false;
    if(section==0 || block==0)return false;
    int len=value.length();

    if(len>0)
    {
         char blockValue[16];
         int i,j;
         if (len>16)len=16;

            for(i=0;i<16;i++)
            {
                if(i<len)
                {
                    blockValue[i]=value.charAt(i);
                }
                else
                {
                    blockValue[i]="";
                }

            }



         return writeSection(4*section+block,blockValue);
        //Serial.println(blockValue[2]);
    }

    return false;
}
bool EasyRFID::writeSection(int index,char *value)
{

            if (auth(PICC_AUTHENT1A, index, sectorKeyA, serNum) == MI_OK)
            {
                Serial.println("Pass");
                unsigned char status;
                status=write(index,value);
                if(status!= MI_OK)
                {
                    return false;
                }
            }
            else
            {
                Serial.println("Not Auth");
                return false;
            }


    return true;
}
String EasyRFID::readCard(int section,int block)
{
         if(block>2 || block<0)return "";
    if(section >15 || section<0) return "";
    if(section==0 || block==0)return "";
        String value="";
        int i;
    if (auth(PICC_AUTHENT1A, section*4+block, sectorKeyA, serNum) == MI_OK)
    {

        unsigned char status;

        unsigned char str[MAX_LEN];

        status=read(section*4+block,str);


        if(status== MI_OK)
        {
            value=str;
            value=value.substring(0,16);
            value.trim();

        }
    }

    return value;
}




