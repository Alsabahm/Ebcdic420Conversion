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

#define MAX_SIZE_UTF 100000
#define MAX_SIZE_420 100000

int main(void)
{
		char chAR[MAX_SIZE_UTF];
		FILE *file;
		size_t nread;
		int wordLen=0;

	memset(chAR,0,(sizeof(char) * MAX_SIZE_UTF));
		file = fopen("/media/sf_shared/420in", "rb");  // change to relative path

		if (file) {
			while ((nread = fread(chAR, 1, sizeof(chAR), file)) > 0)
				       if (ferror(file)) {
				    	   printf("Error reading file\n");
				    	   return 0;
					    }
				    fclose(file);
		}




		char final[MAX_SIZE_UTF];


		//int len=mainConvert420to1256(chAR,final,0);
		int len=mainConvert420toUnicodeLE(chAR,final,0);

		int gg=0;
		for(int i=0;i<len;i++)
			if(final[i] == 0x3F)
				gg=1;

		char *s="ERROR";

		if(gg==1)
			printf("%s\n",s);
		else
		{
			printf("FF ");
			printf("FE ");

			for(int hh=0;hh<len;hh++)
				printf("%02X ",final[hh] &0xFF);

			printf("\n%s\n",final);
		}

		/*
		if(gg==1)
		{
			FILE *write_ptr;
	    	write_ptr = fopen("/media/sf_shared/utfout.txt","wb"); // change to relative path
	    	fwrite(s,sizeof(char),5,write_ptr);
	    	close(write_ptr);
		}

		else
		{
			FILE *write_ptr;
		    write_ptr = fopen("/media/sf_shared/utfout.txt","wb"); // change to relative path
		    fwrite(final,sizeof(char),len,write_ptr);
		    close(write_ptr);
		}
*/


		FILE *write_ptr;
		write_ptr = fopen("/media/sf_shared/1256out.txt","wb"); // change to relative path
		fwrite(final,sizeof(char),len,write_ptr);
		close(write_ptr);
}





