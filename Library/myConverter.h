/*
 * myConverter.h
 *
 *  Created on: Nov 30, 2017
 *      Author: Mohammad AlSabah
 
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

#ifndef MYCONVERTER_H_
#define MYCONVERTER_H_

int mainAllConverterNames(void);
int detectCharSet(const char *input, char **output, int *confidance);

int mainConvertUnicodeLEto420(const char* input,char *output,int returnNil);
int mainConvertutf8to420(const char *input,char *output,int returnNil);
int mainConvert420to420(const char *input,char *output,int returnNil);
int mainConvert420toUnicodeBE(const char *input,char *output,int returnNil);
int mainConvert420toUnicodeLE(const char *input,char *output,int returnNil);
int mainConvert420toutf8(const char *input,char *output,int returnNil);
int mainConvertutf8to037(const char *input,char *output,int returnNil);
int mainConvert037toutf8(const char *input,char *output,int returnNil);


int maing2h(int day,int month,int year,int *rday,int *rmonth,int *ryear);

#endif /* MYCONVERTER_H_ */
