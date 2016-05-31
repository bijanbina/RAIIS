#include "backend.h"

void shatter_debug(QString message)
{
    if (SHATTER_DEBUG)
    {
        qDebug() << message;
    }
}

void shatter_debug(char *message)
{
    if (SHATTER_DEBUG)
    {
        qDebug() << message;
    }
}

//print message, then data in hex format which is length is "len"
void shatter_debug_hex(const char *message, char *data, int len)
{
    if (SHATTER_DEBUG)
    {
        printf(message);
        int i;
        for ( i = 0 ; i < len ; i++ )
        {
            printf ("%02x ",(int)(data[i] & 0xFF));
        }
        printf ("\n");
    }
}

//code written by M. Drafshian
//CRC Code: D5
uint8_t MakeCRC(char *BitString)
{

    char CRC[8];
    int  i;
    char DoInvert;
    char x=0;
    uint8_t returnValue=0;

    for (i=0; i<8; ++i)  CRC[i] = 0;                    // Init before calculation


    for (i=0; i<56; ++i)
    {
        if((bitreader(BitString,i))==1)
        {
            x=1;
        }
        else
        {
            x=0;
        }
        DoInvert =x ^ CRC[7];

        CRC[7] = CRC[6] ^ DoInvert ;
        CRC[6] = CRC[5] ^ DoInvert;
        CRC[5] = CRC[4];
        CRC[4] = CRC[3] ^ DoInvert;
        CRC[3] = CRC[2];
        CRC[2] = CRC[1] ^ DoInvert;
        CRC[1] = CRC[0];
        CRC[0] = DoInvert;
    }

    for (i=0; i<8; ++i)
    {
        if (CRC[i]==1)
        {
            // Res[7-i]='1';
            returnValue=returnValue+1*((uint8_t)pow(2,(double)(i)));
        }
    }

    return returnValue;
}

/* test code:
 * char test[2];
 * test[0] = 0b00100000;
 * printf("%d\n",bitreader(test,5)); */
bool bitreader(const char *data, int offset)
{
    int index = offset/8;
    uint8_t byte = data[index];
    bool returnValue =  byte & (0x01 << (7 - offset%8));
    return returnValue;
}


QString getStrCommand(QString command)
{
    FILE *fp;
    QString returnData;
    char path[1035];

    /* Open the command for reading. */
    fp = popen(command.toStdString().c_str(), "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      return returnData;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      returnData = QString(path);
    }

    returnData.remove('\n');

    /* close */
    pclose(fp);
    return returnData;
}


void runCommand(QString command)
{
    FILE *fp;
    QString returnData;

    /* Open the command for reading. */
    fp = popen(command.toStdString().c_str(), "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      return;
    }

    /* close */
    pclose(fp);
}

