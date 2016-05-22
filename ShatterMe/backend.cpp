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

short MakeCRC(char *BitString)
   {

   char CRC[8];
   int  i;
   char DoInvert;
   char x=0;
   short oo=0;

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
      DoInvert =x ^ CRC[7];//('1'==BitString[i]) ^ CRC[7];         // XOR required?

      CRC[7] = CRC[6] ^ DoInvert;
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
     oo=oo+1*((short)pow(2,(double)(i)));
    }
    else
    {
    // Res[7-i]='0';
    }
   }

   //Res[8] = 0;                                         // Set string terminator

   return oo;
  // return(Res);
}

//d5

char bitreader(char *data, int offset)
{
    int index = offset/8;
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

