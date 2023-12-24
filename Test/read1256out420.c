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

#define MAX_SIZE_1256 1000
#define MAX_SIZE_420 1000

int main(void)
{

		static char chAR[MAX_SIZE_1256];
		FILE *file;
		size_t nread;
		int wordLen=0;

		memset(chAR,0,(sizeof(char) * MAX_SIZE_1256));
		file = fopen("/media/sf_shared/1256test.txt", "rb");

		if (file) {
			while ((nread = fread(chAR, 1, sizeof(chAR), file)) > 0)
				       if (ferror(file)) {
				    	   printf("Error reading file\n");
				    	   return 0;
					    }
				    fclose(file);
		}

		char *output;
		int conf=0;

		//output = (char*) malloc(10 * sizeof(char));
		//memset(output,0,(sizeof(char) * 15));

		detectCharSet(chAR,&output,&conf);

		printf("output = %s\n", output);
		printf("confidance = %d\n", conf);

		void free(void *output);


	//char chAR[]={0xEF,0xBB,0xA3,0xEF,0xBA,0xA3,0xEF,0xBB,0xA3,0xD8,0xAF};
		static char final[MAX_SIZE_1256];

		int len=mainConvertUnicodeLEto420(chAR,final,0);

		int gg=0;
		for(int i=0;i<len;i++)
			if(final[i] == 0x3F)
				gg=1;

		char *s="ERROR";
		if(gg==1)
					printf("%s\n",s);
				else
					{
					for(int hh=0;hh<len;hh++)
					printf("%02X ",final[hh] &0xFF);

					printf("\n%s\n",chAR);
					}

		if(gg==1)
		{
			FILE *write_ptr;
	    	write_ptr = fopen("/media/sf_shared/420out","wb");
	    	fwrite(s,sizeof(char),5,write_ptr);
	    	close(write_ptr);
		}

		else
		{
			FILE *write_ptr;
		    write_ptr = fopen("/media/sf_shared/420out","wb");
		    fwrite(final,sizeof(char),len,write_ptr);
		    close(write_ptr);
		}


}



