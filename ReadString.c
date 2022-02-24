#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAXLENGTH  100 
#define MAXLINE    20 
#define LINELENGHTLIMIT 40

int PrintLine(char *strLine, int nLength, unsigned char ResulstHex[]);
bool ParseHexLine( unsigned char *strLine, int nLength);

int getVal(char c);

unsigned char ResulstHex[MAXLENGTH], nHexLength;

int main(int argc, char *argv[])
{
   int num;
   FILE *fptr;
   
   char strLogFile[MAXLENGTH] ="timer1_01.hex";

   unsigned char strLine1[MAXLENGTH];

   
   
   int line = 0;
   if(argc > 1)   
      strcpy(strLogFile,argv[1]);

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen(strLogFile,"r");

   if(fptr == NULL)
   {
      printf("Can't open the file: %s", strLogFile);   
      exit(1);             
   }

   while(fgets(strLine1, MAXLENGTH, fptr) != NULL)
   {
     // printf("\n%s",strLine1);
      nHexLength =  PrintLine(strLine1, strlen(strLine1), ResulstHex);
      bool bTest = ParseHexLine(ResulstHex, nHexLength);

   }
 
   /* fgets() returned NULL.  Now you can check why.... */
   if(feof(fptr))
   {
      printf ("\nRead to the end of file : %s", strLogFile);      
   }
   else 
   {
      /* Error */
      printf ("\nThe line is too long in File : %s", strLogFile);      
   }

   fclose(fptr);

   return 0;
}

int PrintLine(char *strLine, int nLength, unsigned char ResulstHex[])
{
   unsigned char c1, c2, sum;
 //  unsigned char ResulstHex[MAXLENGTH];

   if (strLine[0] != ':') 
          return 0;
   int i = 1, j = 0;

   while( i < nLength-1) // -1 since the Length includes '\n'
   {
      c1 = getVal(strLine[i++]);
      c2 = getVal(strLine[i++]);
      
      sum = c1<<4| c2;
      ResulstHex[j++] = sum;
      printf(" %02x", sum);
   }
   printf("\n");


   return j;

}



int getVal(char c)
   {
       int rtVal = 0;

       if(c >= '0' && c <= '9')
       {
           rtVal = c - '0';
       }
       else
       {
           rtVal = c - 'a' + 10;
       }

       return rtVal;
   }

bool ParseHexLine( unsigned char *strLine, int nLength)
{
		int data_index = 0;
		unsigned  char char_to_put;

      unsigned char nData[MAXLENGTH];
		

		//To hold file hex values.
		unsigned  char  nByteCount;
		unsigned  char  nHighAddress;
		unsigned  char  nLowAddress;
      unsigned  int   nAddress;
		unsigned  char  nRecordType;
		unsigned  char  nCheckSum;

		//BYTE COUNT
      
		nByteCount = strLine[0]; 

		// No need to read, if no data.
		if (nByteCount == 0)
               return false;

		//ADDRESS1 
		nHighAddress = strLine[1];

		//ADDRESS2
		nLowAddress = strLine[2];

		//RECORD TYPE
		nRecordType = strLine[3];

		// No need to read, if not data.
		if (nRecordType != 0)
            return false;

		nAddress = ((unsigned int)nHighAddress << 8) | nLowAddress;

		// DATA
		while(data_index < nByteCount)
		{
			nData[data_index] = strLine[4+ data_index];
			data_index++;
		}
		
		// CHECKSUM
		nCheckSum = strLine[nLength - 1];

		return true;
}