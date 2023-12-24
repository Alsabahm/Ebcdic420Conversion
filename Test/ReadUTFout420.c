/*
	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <myConverter.h>
#include <string.h>

#define MAX_SIZE_UTF 400
#define MAX_SIZE_420 100000

int main(void)
{

		char chAR[MAX_SIZE_UTF];
		FILE *file;
		size_t nread;
		int wordLen=0;

		memset(chAR,0,(sizeof(char) * MAX_SIZE_UTF));
		file = fopen("/media/sf_shared/araFix.txt", "rb");

		if (file) {
			while ((nread = fread(chAR, 1, sizeof(chAR), file)) > 0)
				       if (ferror(file)) {
				    	   printf("Error reading file\n");
				    	   return 0;
					    }
				    fclose(file);
		}



		//EF BB BF D8 A7 D9 86 D9 87 D9 8A D8 A7 D8 B1
//		memset(chAR,0,(sizeof(char) * MAX_SIZE_UTF));

//		chAR[0]=0x00;
//		chAR[1]=0x01;
//		chAR[2]=0xEF;
//		chAR[3]=0xBB;
//		chAR[4]=0xBF;
//		chAR[5]=0xD8;
//		chAR[6]=0xA7;
//		chAR[7]=0xD9;
//		chAR[8]=0x86;
//		chAR[9]=0xD9;
//		chAR[10]=0x87;
//		chAR[11]=0xD9;
//		chAR[12]=0x8A;
//		chAR[13]=0xD8;
//		chAR[14]=0xA7;
//		chAR[15]=0xD8;
//		chAR[16]=0xB1;

//		char is420=chAR[0];          // 0x00 from 420
//		char whichFormat=chAR[1];    // 0x00 to UTF-8 0x01 to unicode
//
//
//		for(int i=0;i<sizeof(chAR)-2;i++)
//			chAR[i] = chAR[i+2];
//
//		chAR[sizeof(chAR)-2]= 0x00;
//		chAR[sizeof(chAR) -1]= 0x00;

		char final[MAX_SIZE_420];
		int len=mainConvert420to420(chAR,final,0);





//			char *output;
//			int conf=0;
//
//			detectCharSet(chAR,&output,&conf);
//
//			printf("\n%s\n",output);
//			printf("confidance = %d\n", conf);
//
//			if( strcmp(output, "UTF-8") == 0)
//			{
//				len=mainConvertutf8to420(chAR,final,0);
//			}
//			else if(strcmp(output, "UTF-16LE") == 0)
//			{
//				len=mainConvertUnicodeLEto420(chAR,final,0);
//			}
//
//			else
//			{
//				printf("unknown encoding");
//				return 0;
//			}
//
//
//			void free(void *output);
//
//		//char chAR[]={0xEF,0xBB,0xA3,0xEF,0xBA,0xB3,0xEF,0xBB,0x9F,0xD9,0x85};




			int gg=0;
			for(int i=0;i<len;i++)
				if(final[i] == 0x3F)
					gg=i;

			for(int hh=0;hh<len;hh++)
				printf("%02X ",final[hh] &0xFF);

				printf("\n%s\n",chAR);
				printf("\n%d\n",len);


			char *s="ERROR";

			if(gg==1)
				printf("\n%s %d\n",s,gg);




				FILE *write_ptr;
				write_ptr = fopen("/media/sf_shared/420out","wb");
				fwrite(final,sizeof(char),len,write_ptr);
				close(write_ptr);


}






