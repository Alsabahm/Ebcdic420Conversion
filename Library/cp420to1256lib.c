
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

/* print all available converters

	UErrorCode err = U_ZERO_ERROR;
	         UEnumeration *u_enum = ucnv_openAllNames(&err);
	         const char *name = Nil;
	         while(u_enum) {
	             err = U_ZERO_ERROR;
	             int32_t len = 0;
	             name = uenum_next(u_enum, &len, &err);
	             if(name)
	             {
	            	 printf("%s\n",name);
	                 UErrorCode myError = U_ZERO_ERROR;
	             }
	             else
	            	 break;

	         }
 *
 *
 *
 */



#include <string.h>

// ICU HEADER files
#include <unicode/ushape.h>
#include <unicode/ucnv.h>
#include <unicode/ustring.h>

#include <unicode/ucsdet.h>
#include <unicode/uclean.h>

/* for calendar functions */
#include <unicode/ucal.h>

// Arabic shaping options
uint32_t opt= U_SHAPE_TAIL_NEW_UNICODE
			| U_SHAPE_LETTERS_SHAPE
			| U_SHAPE_TEXT_DIRECTION_VISUAL_RTL
			| U_SHAPE_DIGITS_AN2EN;



const char  punc420[]={0x50,0x60,0xC0,0xD0,0xE0,0x61,
						0xA1,0x44,0x45,0x79,0x4A,0x5A,
						0x6A,0x7A,0x4B,0x5B,0x6B,0x7B,
						0x4C,0x5C,0x6C,0x7C,0x4D,0x5D,
						0x6D,0x7D,0x4E,0x5E,0x6E,0x7E,
						0x4F,0x5F,0x6F,0x7F,0xDF};

const char  letters420[]={0x70,0x80,0x90,0xA0,0xB0,0x51,
						  0x71,0xB1,0x52,0x62,0x72,0xB2,
						  0x63,0x73,0xB3,0x64,0x74,0xB4,
						  0x55,0x65,0x75,0xB5,0x46,0x56,
						  0x66,0x76,0x47,0x57,0x67,0x77,
						  0x48,0x58,0x67,0x78,0xB8,0x49,
						  0x59,0x69,0xB9,0x8A,0x9A,0xAA,
						  0xBA,0xDA,0x8B,0x9B,0xAB,0xBB,
						  0xCB,0xDB,0x8C,0x9C,0xAC,0xBC,
						  0xDC,0x8D,0x9D,0xAD,0xBD,0xCD,
						  0xDD,0x8E,0x9E,0xAE,0xBE,0xDE,
						  0x8F,0x9F,0xAF,0xBF,0xCF,0x44};


const char tashkeel420[]={0x42,0x43};

const UChar punchUnicode[]={0x0026,0x002d,0x061b,0x061f,
						0x00d7,0x002f,0x00f7,0x0651,0xfe7d,
						0x640,0x200b,0x060c,0x00a2,0x0021,
						0x00a6,0x003a,0x002e,0x0024,0x002c,
						0x0023,0x003c,0x002a,0x0025,0x0040,
						0x0028,0x0029,0x005f,0x0027,0x002b,
						0x003b,0x003e,0x003d,0x007c,0x00ac,
						0x003f,0x0022,0x0660,0x0661,0x0662,
						0x0663,0x0664,0x0665,0x0666,0x0667,
						0x0668,0x0669,0x009f,0x0030,0x0031,
						0x0032,0x0033,0x0034,0x0035,0x0036,
						0x0037,0x0038,0x0039 };


// fixUnshaped Unicode

int fixUnshaped(UChar *strInput,int inLength,UChar *strOutput)
{
	int i=0,j=0;
	int count=0;



	while(strInput[i] !='\0')
	{
		if(strInput[i] == 0x0644)
		{
			strOutput[j]=strInput[i];

			i++;

			if(strInput[i] != 0x0644)  // avoid two recurring LAMs
			{
				switch(strInput[i])
							{
							case (0x0622):
									strOutput[j]=0xFEF5;
									break;
							case (0x0623):
									strOutput[j]=0xFEF7;
									break;
							case (0x0625):
									strOutput[j]=0xFEF9;
									break;
							case (0x0627):
									strOutput[j]=0xFEFB;
									break;

							default:

								j++;
								strOutput[j]=strInput[i];
								count++;


							}


			}


			else     // when another LAM is detected1
			{
				j++;
				strOutput[j]=strInput[i];
				strInput++;

				if(strInput[i] != 0x0644)
							{
								switch(strInput[i])
											{
											case (0x0622):
													strOutput[j]=0xFEF5;
													break;
											case (0x0623):
													strOutput[j]=0xFEF7;
													break;
											case (0x0625):
													strOutput[j]=0xFEF9;
													break;
											case (0x0627):
													strOutput[j]=0xFEFB;
													break;

											default:

												j++;
												strOutput[j]=strInput[i];
												count++;


											}


							}



			}
		}

		else
			strOutput[j]=strInput[i];

		i++;
		j++;

	}
	strOutput[j]=strInput[i];


	return count;

}


// prints all Converters
int AllConverterNames(void)
{
	UErrorCode errorCode = U_ZERO_ERROR;
    UEnumeration *u_enum = ucnv_openAllNames(&errorCode);
    const char *name = NULL;
    int intTotalNumber=0;


    while(u_enum)
    {
    	errorCode = U_ZERO_ERROR;
		int32_t len = 0;

		name = uenum_next(u_enum, &len, &errorCode);

		// if error return -1
		if(!(errorCode == U_ZERO_ERROR || errorCode ==U_STRING_NOT_TERMINATED_WARNING))
		  	return -1;

		if(name)
		{
			printf("%s\n",name);
			intTotalNumber++;
		}

		else
		    break;

     }

    return intTotalNumber;
}



// Insert item to array
void insertItem(char array[],int position,int size,char value)
{
int c;
	 for (c = size - 1; c >= position - 1; c--)
	      array[c+1] = array[c];

	   array[position-1] = value;

}


// remove item from array
void removeItem(char array[],int position,int size)
{
int c;

	for ( c = position - 1 ; c < size - 1 ; c++ )
	         array[c] = array[c+1];


}

// fix UTF8 chars Yeyhamza
int fixUTF8(char finalString[],int finalStringLength)
{

	/////////////////////////////////////////////////
	char utfYeyhamza1=0xD8;
	char utfYeyhamza2=0xA6;

	char utfSpace=0x20;

	char utfnYey1=0xEF;
	char utfnYey2=0xBA;
	char utfnYey3=0x8B;

	char utfYeyMqsoora1=0xEF;
	char utfYeyMqsoora2=0xBB;
	char utfYeyMqsoora3=0xB0;

	char utfHamza1=0xD8;
	char utfHamza2=0xA1;

	char utfNewYehHamza1=0xEF;
	char utfNewYehHamza2=0XBA;
	char utfNewYehHamza3=0X8A;


	int i;

	for(i=0;i<finalStringLength;i++)
		{
			if(finalString[i] == utfYeyhamza1 && finalString[i+1] == utfYeyhamza2)
				if(finalString[i+1]!= utfSpace)
					{
						removeItem(finalString,i+1,finalStringLength);
						removeItem(finalString,i+1,finalStringLength);

						insertItem(finalString,i+1,finalStringLength,utfnYey3);
						insertItem(finalString,i+1,finalStringLength,utfnYey2);
						insertItem(finalString,i+1,finalStringLength,utfnYey1);
						finalStringLength++;



					}

			if(finalString[i] == utfYeyMqsoora1 && finalString[i+1] == utfYeyMqsoora2 && finalString[i+2] == utfYeyMqsoora3 &&
					finalString[i+3] == utfHamza1 && finalString[i+4] == utfHamza2 )
			{

				removeItem(finalString,i+1,finalStringLength);
				removeItem(finalString,i+1,finalStringLength);
				removeItem(finalString,i+1,finalStringLength);
				removeItem(finalString,i+1,finalStringLength);
				removeItem(finalString,i+1,finalStringLength);

				insertItem(finalString,i+1,finalStringLength,utfNewYehHamza3);
				insertItem(finalString,i+1,finalStringLength,utfNewYehHamza2);
				insertItem(finalString,i+1,finalStringLength,utfNewYehHamza1);

				finalStringLength= finalStringLength - 2;


			}


		}

	return finalStringLength;

}


// search for punctuation chars in Unicode
int searchPuncUnicode(UChar input)
{
	int found=0;
	// Length of UChar= char * 2
	int puncLength=sizeof(punchUnicode) / 2;

	for(int i=0;i<puncLength;i++)
	{
		if(input == punchUnicode[i])
		{
			found=1;

		}
	}

	return found;

}


// fix unicode chars when converting from 420
int fix1256String(UChar finalString[],int sourceLen)
{


	for(int i=0;i<sourceLen;i++)
		{
			if(finalString[i] == 0x0626)   // handle yeh hamza
				if(finalString[i+1]!= 0x0020 && (searchPuncUnicode(finalString[i+1]) == 0 ))
					finalString[i]=0xfe8c;

			if(finalString[i] == 0x0621)
					if(finalString[i+1]!= 0x0020)
					{
						for (int c = sourceLen - 1; c >= i ; c--)
							finalString[c+1] = finalString[c];

						finalString[i+1] = 0x0020;


					}
		}

	return 1;
}

// handle unicode string word by word
int checkShape(UChar *strInput,int inLength,UChar *strOutput,int outLength)
{
	UChar *strBegin=strInput;
	UChar *strCheck=strInput;
	int wordLength=0;
	int result=1;
	int totalLength=0;
	int i;
	UErrorCode errorCode= U_ZERO_ERROR;


	while(*strBegin != '\0')
	{
		wordLength=0;
		errorCode= U_ZERO_ERROR;

		while(*strCheck != (0x20) && *strCheck != 0x00)
		{
			wordLength++;
			strCheck++;
			totalLength++;
		}


		result=u_shapeArabic(strBegin,wordLength +1,strOutput,outLength,opt,&errorCode);


		// if error return -1
		if(!(errorCode == U_ZERO_ERROR || errorCode ==U_STRING_NOT_TERMINATED_WARNING))
		    	return -1;

		errorCode= U_ZERO_ERROR;

		outLength=outLength-result;

		strOutput=strOutput + result  ;

		if(result == 0)
			{
				for(i=0;i<wordLength;i++)
				{
					//	printf("%x",strInput);
						strInput++;
				}
				//printf("\n");
				return result;
			}


		if (*strCheck != 0x00)
		{
			strCheck++;
			strBegin = strCheck;
			totalLength++;
		}
		else
			strBegin = strCheck;

	}


	return totalLength;

}

// ibm420 letter search converted from utf8
int searchutf8(char inputChar)
{
	if ((inputChar & 0xFF) == 0x8d)    // thaad
	    return 1;

	else if ((inputChar & 0xFF)== 0x8b) // saad
	    return 2;

	else if ((inputChar & 0xFF)== 0x77)  //seen
	   	 return 3;

	else if ((inputChar & 0xFF)== 0x80)  // sheen
	   	return 4;

	else if ((inputChar & 0xFF)== 0x55)  // yey hamza
		   	return 5;

	else if ((inputChar & 0xFF)== 0x25)  // 0x25
	        return 6;

	else
		return -1;

}

// ibm420 letter search converted from 1256
int search1256(char inputChar)
{

	if ((inputChar & 0xFF) == 0x8d)    // thaad
	    return 1;

	else if ((inputChar & 0xFF)== 0x8b) // saad
	    return 2;

	else if ((inputChar & 0xFF)== 0x77)  //seen
	   	 return 3;

	else if ((inputChar & 0xFF)== 0x80)  // sheen
	   	return 4;

	else if ((inputChar & 0xFF)== 0x55)  // yey hamza
		   	return 5;


	else
		return -1;

}

// get the number of chars that will be added e.g. seen family tail or yeh hamza
int charCount(const char *strSource,int strLen)
{
	int i=0;
	int addedchars=0;

			for (i=0;i<strLen;i++,*strSource++)
			{
				if (( *strSource & 0xFF) == 0x8d)    // thaad
					addedchars++;

				else if ((*strSource & 0xFF)== 0x8b) // saad
					addedchars++;

				else if ((*strSource & 0xFF)== 0x77)  //seen
					addedchars++;

				else if ((*strSource & 0xFF)== 0x80)  // sheen
					addedchars++;

				else if ((*strSource & 0xFF)== 0x55)  // yeh hamza
					addedchars++;
			}

return addedchars;

}

// Convert UTF8 to Unicode then IBM420

// DOES NOT WORK WITH UTF-8 CHARS ONLY WINDOWS-1256
int convert1256To420(const char *source,char *strFinalFix,int preflight)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	int findLen=0;

	while(!(source[findLen] == 0 && source[findLen+1]==0) )
		findLen=findLen+2;



	int arabicUnshapedLen=(findLen );

	//create and zero UChar array
	//UChar strArabicUnShaped[arabicUnshapedLen];
	static UChar* strArabicUnShaped;
	strArabicUnShaped = malloc(arabicUnshapedLen * sizeof(UChar));
	memset(strArabicUnShaped,0,(arabicUnshapedLen) * sizeof(UChar));


	// convert UTF-8 to Unicode using Unicode into UChararray
	UConverter *convUTF16;
	convUTF16= ucnv_open("UTF-16LE", &errorCode);
	ucnv_toUChars(convUTF16,strArabicUnShaped,arabicUnshapedLen ,source,findLen, &errorCode);
	ucnv_close(convUTF16);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
	    	return -1;

	// Preflight to detemine the length of the converted bytes

	int strArabicShapedLen=u_shapeArabic(strArabicUnShaped,arabicUnshapedLen,NULL,0,opt,&errorCode);
	errorCode=U_ZERO_ERROR;


	// fix arabic letters before shaping
	//UChar strArabicUnShapedFixed[strArabicShapedLen];
	static UChar* strArabicUnShapedFixed;
	strArabicUnShapedFixed = malloc(strArabicShapedLen * sizeof(UChar));
	memset(strArabicUnShapedFixed,0,(strArabicShapedLen) * sizeof(UChar));
	int intCharChanged=fixUnshaped(strArabicUnShaped,arabicUnshapedLen,strArabicUnShapedFixed);

	// create and zero the array
	//UChar strArabicShaped[strArabicShapedLen];
	static UChar* strArabicShaped;
	strArabicShaped = malloc(strArabicShapedLen * sizeof(UChar));
	memset(strArabicShaped,0,(strArabicShapedLen) * sizeof(UChar));

	int convChars=checkShape(strArabicUnShapedFixed,arabicUnshapedLen,strArabicShaped,strArabicShapedLen);

	 // if error return -1
	 	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
	 	    	return -1;

	// Preflight to detemine the length of the converted bytes
    UConverter *conv = ucnv_open("IBM-420", &errorCode);
    int ibm420StringLen = ucnv_fromUChars(conv, NULL, 0, strArabicShaped, convChars, &errorCode);
    errorCode=U_ZERO_ERROR;


    // setup conversion pointers
    ibm420StringLen++; // +1 for NILL Termination
    if(preflight != 1)
    	ucnv_setFallback(conv,TRUE);


    // create and zero the array
    char ibm420String[ibm420StringLen];
    memset(ibm420String,0,(ibm420StringLen) * sizeof(char));

    // convert Unicode to IBM-420 Ebcdic Arabic
	ucnv_fromUChars(conv, ibm420String, ibm420StringLen, strArabicShaped, convChars, &errorCode);
	ucnv_close(conv);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
		    return -1;

    // construct new arrays to carry fixed ibm-420 arabic data
    int strFinalFixLen=(ibm420StringLen + charCount(ibm420String,ibm420StringLen));

    if(preflight == 1)
    	return strFinalFixLen;


    //zero the output array
    memset(strFinalFix,0,strFinalFixLen);

    // loop through the original ibm-420 data find the characters that needs handling and
    // handles them.    IBM-420 letter handling
    int i=0,j=0;
    int incPunc=0;

    for(i=0,j=0;i<ibm420StringLen && ibm420String[i] != (0x00 & 0x00)  ;i++,j++)
	   {

		 switch(search1256(ibm420String[i]))
		 {
		 	 case 1:    // thaad
		 		strFinalFix[j]=ibm420String[i];
		 		j++;
		 		strFinalFix[j]=(0xFF & 0x45);
		 		break;

		 	 case 2:      // saad
		 		strFinalFix[j]=ibm420String[i];
		 		j++;
		 		strFinalFix[j]=(0xFF & 0x45);
		 		break;

		 	 case 3:           //seen
			 	strFinalFix[j]=ibm420String[i];
			 	j++;
		 		strFinalFix[j]=(0xFF & 0x45);
			 	break;

		 	 case 4:                 // sheen
			 	strFinalFix[j]=ibm420String[i];
			 	j++;
		 		strFinalFix[j]=(0xFF & 0x45);

			 	break;

		 	 case 5:            // yey hamza
		 		incPunc=0;
		 		for(int punLoop=0;punLoop<sizeof(punc420);punLoop++)
		 		{
		 			if(ibm420String[i+1] == punc420[punLoop])
		 				incPunc=1;

		 	 	}

		 		int incLetter=0;
		 		for(int letLoop=0;letLoop<sizeof(letters420);letLoop++)
		 		{
		 			if(ibm420String[i+1] == letters420[letLoop])
		 				incLetter=1;

		 		}

		 		// if next char space or EOF or a punctuation end yey hamza
		 		 //if((ibm420String[i+1] == (0xFF & 0x40) || ibm420String[i+1] == (0x00 & 0x00 ) || incPunc))
		 		// if next char is NOT a LETTER or undefined Char
		 		if(incLetter == 0)
		 		 {
		 			strFinalFix[j]   = (0xFF & 0xDB);
		 			strFinalFix[j+1] = (0xFF & 0x46);
		 			j++;
		 		 }

		 		 else
		 			strFinalFix[j]=ibm420String[i];

		 		 break;

		 	 case -1:
		 		 strFinalFix[j]=ibm420String[i];
		 		 break;
		 }
	   }


    // search for duplicate endings
    for(i=0;i<j+1;i++)
    	if(strFinalFix[i] == 0x45)
    		if(strFinalFix[i+1] == 0x45)
    			strFinalFix[i+1]= 0x40;

    //free's
    free(strArabicUnShaped);
    free(strArabicUnShapedFixed);
    free(strArabicShaped);

    // return true length of array +1 for NILL termination
	return j+1;

}



int convert420To1256(const char *source,UChar *strFinalFix,int preflight)
{


	UErrorCode errorCode= U_ZERO_ERROR;

		int sourceLen=strlen(source);

		int arabicUnshapedLen=sourceLen; // NUL-termination
		UChar strArabicUnShaped[arabicUnshapedLen];

		memset(strArabicUnShaped,0,(sizeof(UChar) * arabicUnshapedLen));

		// Convert from 420 to Unicode
	    UConverter *conv420 = ucnv_open("IBM-420", &errorCode);
	    int arabicUcharLen=ucnv_toUChars(conv420, strArabicUnShaped, arabicUnshapedLen, source, sourceLen, &errorCode);
	    ucnv_close(conv420);

	    // if error return -1
	    if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
	    	return -1;

	    errorCode=U_ZERO_ERROR;


	// Preflight to detemine the length of the converted bytes
    UConverter *conv = ucnv_open("IBM-420", &errorCode);

    int ibm420StringLen = ucnv_toUChars(conv, NULL, 0, source, sourceLen, &errorCode);
    errorCode=U_ZERO_ERROR;


    if(preflight == 1)
        	return ibm420StringLen;


    //ibm420StringLen++; // +1 for NILL Termination


    if(preflight != 1)
    	ucnv_setFallback(conv,TRUE);


    //zero the output array
       memset(strFinalFix,0,ibm420StringLen);

    // convert IBM-420 to Unicode BE Arabic
    ucnv_toUChars(conv, strFinalFix, sourceLen, source, sourceLen, &errorCode);
	ucnv_close(conv);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
		    return -1;

	// fix Unicode characters
	fix1256String(strFinalFix,ibm420StringLen);


	return ibm420StringLen;

}


int convertUTFTo420(const char *source,char *strFinalFix,int preflight)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	int sourceLen=strlen(source);

	int arabicUnshapedLen=(sourceLen ) +1; // +1 for Nil Termination

	//create and zero UChar array
	UChar strArabicUnShaped[arabicUnshapedLen];
	memset(strArabicUnShaped,0,(arabicUnshapedLen) * sizeof(UChar) );


	// convert UTF-8 to Unicode using Unicode into UChararray
	UConverter *convUTF;
	convUTF= ucnv_open("UTF-8", &errorCode);
	arabicUnshapedLen=ucnv_toUChars(convUTF,strArabicUnShaped,arabicUnshapedLen ,source,sourceLen, &errorCode);
	ucnv_close(convUTF);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
	    	return -1;

	 //UChar *strArabicShaped=(UChar*) malloc(sizeof(*strArabicShaped) * strArabicShapedLen );// for debug
	 //memset(strArabicShaped,0,(sizeof(*strArabicShaped) * strArabicShapedLen)); // for debug

	//create and zero UChar array

	UChar strArabicUnShapedFixed[arabicUnshapedLen];
	memset(strArabicUnShapedFixed,0,(arabicUnshapedLen) * sizeof(UChar));

	// Fix the unicode array for arabic shaping
	int addidFixChar=fixUnshaped(strArabicUnShaped,arabicUnshapedLen,strArabicUnShapedFixed);

	// create arabic Shaped array
	int strArabicShapedLen=arabicUnshapedLen+addidFixChar;
	UChar strArabicShaped[strArabicShapedLen];
	memset(strArabicShaped,0,(strArabicShapedLen) * sizeof(UChar));

	// Preflight to detemine the length of the converted bytes
	 //u_shapeArabic(strArabicUnShaped,arabicUnshapedLen,NULL,0,opt,&errorCode);
	//errorCode=U_ZERO_ERROR;

	// shape letters word by word and get length of converted unicode array
	int convChars=checkShape(strArabicUnShapedFixed,strArabicShapedLen,strArabicShaped,strArabicShapedLen + 1);

	// Preflight to detemine the length of the converted bytes unicode to IBM420
    UConverter *conv420 = ucnv_open("IBM-420", &errorCode);
    int ibm420StringLen = ucnv_fromUChars(conv420, NULL, 0, strArabicShaped, convChars, &errorCode);
    errorCode=U_ZERO_ERROR;

    // setup conversion pointers
    ibm420StringLen++; // +1 for NILL Termination
    if(preflight != 1)
    	ucnv_setFallback(conv420,TRUE);


    // create and zero char array
    char ibm420String[ibm420StringLen];
    memset(ibm420String,0,(ibm420StringLen) * sizeof(char));

    // convert Unicode to IBM420
	ucnv_fromUChars(conv420, ibm420String, ibm420StringLen, strArabicShaped, convChars, &errorCode);
	ucnv_close(conv420);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
		    return -1;

	 // get the Length of output array
	int strFinalFixLen=(ibm420StringLen + charCount(ibm420String,ibm420StringLen));

	if(preflight == 1)
	    	return strFinalFixLen;

	// zero output array
	memset(strFinalFix,0,strFinalFixLen);

    // loop through the original ibm-420 data find the characters that needs handling and
    // handles them.
    int i=0,j=0;
    int incPunc=0;
    for(i=0,j=0; i<ibm420StringLen && (ibm420String[i] != (0x00 & 0x00) )  ;i++,j++)
	   {

    	switch(searchutf8(ibm420String[i]))
		 {
		 	 case 1:    // thaad
		 		strFinalFix[j]=ibm420String[i];
		 		j++;
		 		strFinalFix[j]=(0xFF & 0x45);
		 		break;

		 	 case 2:      // saad
		 		strFinalFix[j]=ibm420String[i];
		 		j++;
		 		strFinalFix[j]=(0xFF & 0x45);
		 		break;

		 	 case 3:           //seen
			 	strFinalFix[j]=ibm420String[i];
			 	j++;
		 		strFinalFix[j]=(0xFF & 0x45);
			 	break;

		 	 case 4:                 // sheen
			 	strFinalFix[j]=ibm420String[i];
			 	j++;
		 		strFinalFix[j]=(0xFF & 0x45);
			 	break;

		 	 case 5:            // yey hamza
		 		incPunc=0;

		 		for(int punLoop=0;i < ibm420StringLen-1 && punLoop<sizeof(punc420);punLoop++)
		 		{
		 			if(ibm420String[i+1] == punc420[punLoop])
		 			incPunc=1;

		 		}

		 		int incLetter=0;
		 		for(int letLoop=0;i < ibm420StringLen-1 && letLoop<sizeof(letters420);letLoop++)
		 		{
		 			if(ibm420String[i+1] == letters420[letLoop])
		 			incLetter=1;
		 		}

		 		// if next char space or EOF or a punctuation end yey hamza
		 		//if((ibm420String[i+1] == (0xFF & 0x40) || ibm420String[i+1] == (0x00 & 0x00 ) || incPunc))
		 		// if next char is NOT a LETTER or undefined Char
		 		if(incLetter == 0)
		 		{
		 			strFinalFix[j]   = (0xFF & 0xDB);
		 			strFinalFix[j+1] = (0xFF & 0x46);
		 			j++;
		 		}

		 		else
		 			strFinalFix[j]=ibm420String[i];

		 		break;

		 	 case 6:
		 		 strFinalFix[j+1]=(0xFF & 0x25);
		 		 strFinalFix[j]=(0xFF & 0x0D);
		 		 j++;
		 		 break;

		 	 case -1:
		 		 strFinalFix[j]=ibm420String[i];
		 		 break;
		 }

	   }


    // output array termination if control chars found
    if(strFinalFix[j]== 0x00 && strFinalFix[j-1] == 0x25 && strFinalFix[j-2] == 0x0D)
    {
    	strFinalFix[j-1]=0x00;
    	strFinalFix[j-2]=0x00;
    	j=j-2;
    }

    // return true length of array +1 for NILL termination
	 return j+1;

}



int convert420To420(const char *source,char *strFinalFix,int preflight)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	int sourceLen=strlen(source);

	int arabicUnshapedLen=(sourceLen ) +1; // +1 for Nil Termination

	//create and zero UChar array
	UChar strArabicUnShaped[arabicUnshapedLen];
	memset(strArabicUnShaped,0,(arabicUnshapedLen) * sizeof(UChar) );


	// convert UTF-8 to Unicode using Unicode into UChararray
	UConverter *convUTF;
	convUTF= ucnv_open("IBM-420", &errorCode);
	arabicUnshapedLen=ucnv_toUChars(convUTF,strArabicUnShaped,arabicUnshapedLen ,source,sourceLen, &errorCode);
	ucnv_close(convUTF);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
	    	return -1;

	 //UChar *strArabicShaped=(UChar*) malloc(sizeof(*strArabicShaped) * strArabicShapedLen );// for debug
	 //memset(strArabicShaped,0,(sizeof(*strArabicShaped) * strArabicShapedLen)); // for debug

	//create and zero UChar array

	UChar strArabicUnShapedFixed[arabicUnshapedLen];
	memset(strArabicUnShapedFixed,0,(arabicUnshapedLen) * sizeof(UChar));

	// Fix the unicode array for arabic shaping
	int addidFixChar=fixUnshaped(strArabicUnShaped,arabicUnshapedLen,strArabicUnShapedFixed);

	// create arabic Shaped array
	int strArabicShapedLen=arabicUnshapedLen+addidFixChar;
	UChar strArabicShaped[strArabicShapedLen];
	memset(strArabicShaped,0,(strArabicShapedLen) * sizeof(UChar));

	// Preflight to detemine the length of the converted bytes
	 //u_shapeArabic(strArabicUnShaped,arabicUnshapedLen,NULL,0,opt,&errorCode);
	//errorCode=U_ZERO_ERROR;

	// shape letters word by word and get length of converted unicode array
	int convChars=checkShape(strArabicUnShapedFixed,strArabicShapedLen,strArabicShaped,strArabicShapedLen + 1);

	// Preflight to detemine the length of the converted bytes unicode to IBM420
    UConverter *conv420 = ucnv_open("IBM-420", &errorCode);
    int ibm420StringLen = ucnv_fromUChars(conv420, NULL, 0, strArabicShaped, convChars, &errorCode);
    errorCode=U_ZERO_ERROR;

    // setup conversion pointers
    ibm420StringLen++; // +1 for NILL Termination
    if(preflight != 1)
    	ucnv_setFallback(conv420,TRUE);


    // create and zero char array
    char ibm420String[ibm420StringLen];
    memset(ibm420String,0,(ibm420StringLen) * sizeof(char));

    // convert Unicode to IBM420
	ucnv_fromUChars(conv420, ibm420String, ibm420StringLen, strArabicShaped, convChars, &errorCode);
	ucnv_close(conv420);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
		    return -1;

	 // get the Length of output array
	int strFinalFixLen=(ibm420StringLen + charCount(ibm420String,ibm420StringLen));

	if(preflight == 1)
	    	return strFinalFixLen;

	// zero output array
	memset(strFinalFix,0,strFinalFixLen);

    // loop through the original ibm-420 data find the characters that needs handling and
    // handles them.
    int i=0,j=0;
    int incPunc=0;
    for(i=0,j=0; i<ibm420StringLen && (ibm420String[i] != (0x00 & 0x00) )  ;i++,j++)
	   {

    	switch(searchutf8(ibm420String[i]))
		 {
		 	 case 1:    // thaad
		 		strFinalFix[j]=ibm420String[i];
		 		j++;
		 		strFinalFix[j]=(0xFF & 0x45);
		 		break;

		 	 case 2:      // saad
		 		strFinalFix[j]=ibm420String[i];
		 		j++;
		 		strFinalFix[j]=(0xFF & 0x45);
		 		break;

		 	 case 3:           //seen
			 	strFinalFix[j]=ibm420String[i];
			 	j++;
		 		strFinalFix[j]=(0xFF & 0x45);
			 	break;

		 	 case 4:                 // sheen
			 	strFinalFix[j]=ibm420String[i];
			 	j++;
		 		strFinalFix[j]=(0xFF & 0x45);
			 	break;

		 	 case 5:            // yey hamza
		 		incPunc=0;

		 		for(int punLoop=0;i < ibm420StringLen-1 && punLoop<sizeof(punc420);punLoop++)
		 		{
		 			if(ibm420String[i+1] == punc420[punLoop])
		 			incPunc=1;

		 		}

		 		int incLetter=0;
		 		for(int letLoop=0;i < ibm420StringLen-1 && letLoop<sizeof(letters420);letLoop++)
		 		{
		 			if(ibm420String[i+1] == letters420[letLoop])
		 			incLetter=1;
		 		}

		 		// if next char space or EOF or a punctuation end yey hamza
		 		//if((ibm420String[i+1] == (0xFF & 0x40) || ibm420String[i+1] == (0x00 & 0x00 ) || incPunc))
		 		// if next char is NOT a LETTER or undefined Char
		 		if(incLetter == 0)
		 		{
		 			strFinalFix[j]   = (0xFF & 0xDB);
		 			strFinalFix[j+1] = (0xFF & 0x46);
		 			j++;
		 		}

		 		else
		 			strFinalFix[j]=ibm420String[i];

		 		break;

		 	 case 6:
		 		 strFinalFix[j+1]=(0xFF & 0x25);
		 		 strFinalFix[j]=(0xFF & 0x0D);
		 		 j++;
		 		 break;

		 	 case -1:
		 		 strFinalFix[j]=ibm420String[i];
		 		 break;
		 }

	   }


    // output array termination if control chars found
    if(strFinalFix[j]== 0x00 && strFinalFix[j-1] == 0x25 && strFinalFix[j-2] == 0x0D)
    {
    	strFinalFix[j-1]=0x00;
    	strFinalFix[j-2]=0x00;
    	j=j-2;
    }

    // return true length of array +1 for NILL termination
	 return j+1;

}




int convert420Toutf8(const char *source,char *strFinalFix,int preflight)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	int sourceLen=strlen(source);

	int arabicUnshapedLen=sourceLen; // NUL-termination
	UChar strArabicUnShaped[arabicUnshapedLen];

	memset(strArabicUnShaped,0,(sizeof(UChar) * arabicUnshapedLen));

	// Convert from 420 to Unicode
    UConverter *conv420 = ucnv_open("IBM-420", &errorCode);
    int arabicUcharLen=ucnv_toUChars(conv420, strArabicUnShaped, arabicUnshapedLen, source, sourceLen, &errorCode);
    ucnv_close(conv420);

    // if error return -1
    if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
    	return -1;

    errorCode=U_ZERO_ERROR;


    // Preflight to detemine the length of the converted bytes
    UConverter *convUTF;
    convUTF= ucnv_open("UTF-8", &errorCode);
    int arabicutf8Len=ucnv_fromUChars(convUTF,NULL,0 ,strArabicUnShaped,arabicUcharLen, &errorCode);
    errorCode=U_ZERO_ERROR;

    if(preflight == 1)
            	return arabicutf8Len;

    // Convert from Unicode to UTF8
    arabicutf8Len=ucnv_fromUChars(convUTF,strFinalFix,sourceLen * 3 ,strArabicUnShaped,arabicUcharLen, &errorCode);

    // if error return -1
    if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
       	return -1;

    errorCode=U_ZERO_ERROR;
    ucnv_close(convUTF);

    // UTF8 char handling
    arabicutf8Len=fixUTF8(strFinalFix,arabicutf8Len);

    // add Nil termination
    *(strFinalFix + arabicutf8Len) = 0x00;
    arabicutf8Len++;

return arabicutf8Len;

}

// utf8 to 037
int convertUTFTo037(const char *source,char *strFinalFix,int preflight)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	int sourceLen=strlen(source);

	int UTFLen=(sourceLen ); // +1 for Nil Termination

	//create and zero UChar array
	UChar UTFUnicode[UTFLen];
	memset(UTFUnicode,0,(UTFLen) * sizeof(UChar));


	// convert UTF-8 to Unicode using Unicode into UChararray
	UConverter *convUTF;
	convUTF= ucnv_open("UTF-8", &errorCode);
	UTFLen=ucnv_toUChars(convUTF,UTFUnicode,UTFLen ,source,sourceLen, &errorCode);
	ucnv_close(convUTF);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
	    	return -1;

	// Preflight to detemine the length of the converted bytes unicode to IBM420
    UConverter *conv037 = ucnv_open("IBM-037", &errorCode);
    int ibm420StringLen = ucnv_fromUChars(conv037, NULL, 0, UTFUnicode, UTFLen, &errorCode);
    errorCode=U_ZERO_ERROR;

    // setup conversion pointers
    ibm420StringLen++; // +1 for NILL Termination
    if(preflight != 1)
    	ucnv_setFallback(conv037,TRUE);


    // create and zero char array
    char ibm420String[ibm420StringLen];
    memset(ibm420String,0,(ibm420StringLen) * sizeof(char));

    // convert Unicode to IBM420
	int j=ucnv_fromUChars(conv037, strFinalFix, ibm420StringLen, UTFUnicode, UTFLen, &errorCode);
	ucnv_close(conv037);

	// if error return -1
	if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
		    return -1;



    // return true length of array +1 for NILL termination
	 return j+1;

}


int convert037Toutf8(const char *source,char *strFinalFix,int preflight)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	int sourceLen=strlen(source);

	int arabicUnshapedLen=sourceLen; // NUL-termination
	UChar strArabicUnShaped[arabicUnshapedLen];

	memset(strArabicUnShaped,0,(sizeof(UChar) * arabicUnshapedLen));

	// Convert from 420 to Unicode
    UConverter *conv420 = ucnv_open("IBM-037", &errorCode);
    int arabicUcharLen=ucnv_toUChars(conv420, strArabicUnShaped, arabicUnshapedLen, source, sourceLen, &errorCode);
    ucnv_close(conv420);

    // if error return -1
    if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
    	return -1;

    errorCode=U_ZERO_ERROR;


    // Preflight to detemine the length of the converted bytes
    UConverter *convUTF;
    convUTF= ucnv_open("UTF-8", &errorCode);
    int arabicutf8Len=ucnv_fromUChars(convUTF,NULL,0 ,strArabicUnShaped,arabicUcharLen, &errorCode);
    errorCode=U_ZERO_ERROR;

    if(preflight == 1)
            	return arabicutf8Len;

    // Convert from Unicode to UTF8
    arabicutf8Len=ucnv_fromUChars(convUTF,strFinalFix,sourceLen * 3 ,strArabicUnShaped,arabicUcharLen, &errorCode);

    // if error return -1
    if(!(errorCode == U_ZERO_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING))
       	return -1;

    errorCode=U_ZERO_ERROR;
    ucnv_close(convUTF);

    // UTF8 char handling
    arabicutf8Len=fixUTF8(strFinalFix,arabicutf8Len);

    // add Nil termination
    *(strFinalFix + arabicutf8Len) = 0x00;
    arabicutf8Len++;

return arabicutf8Len;

}

// 1256 to 420
int mainConvertUnicodeLEto420(const char *input, char *output,int returnNil)
{

	int outputLength=0;
	// convert
	outputLength=convert1256To420(input,output,0);

	// return array without Nil termination
	char chrNil=0x00;
	if(returnNil == 0)
	{
		int i=0;
		for (i=0;i<outputLength;i++,output++)
			if(*output == chrNil)
				break;

		return i;
	}

	return outputLength;
}



int mainConvert420toUnicodeLE(const char *input,char *output,int returnNil)
{

	int len=strlen(input);

	UChar output1256[len];
	int output1256Length=0;

	int outputLength=0;

	// convert
	output1256Length=convert420To1256(input,output1256,0);

	// convert 16 bit UChar array to 8 bit char array MSB
	int k=0;

	for(int m=0;m<output1256Length;m++)
	{

			output[k]=((output1256[m] >> 0) & 0xFF);
			k++;

			output[k]=((output1256[m] >> 8) & 0xFF);
			k++;



	}

		if(returnNil == 0)
			outputLength=k ;

		else
			outputLength=k + 1 ; // + 1 Nil termination

		return outputLength;
}

// 420 to 1256
int mainConvert420toUnicodeBE(const char *input,char *output,int returnNil)
{

	int len=strlen(input);

	UChar output1256[len];
	int output1256Length=0;

	int outputLength=0;

	// convert
	output1256Length=convert420To1256(input,output1256,0);

	// convert 16 bit UChar array to 8 bit char array MSB
	int k=0;

	for(int m=0;m<output1256Length;m++)
	{

			output[k]=((output1256[m] >> 8) & 0xFF);
			k++;

			output[k]=((output1256[m] >> 0) & 0xFF);
			k++;

	}

		if(returnNil == 0)
			outputLength=k ;

		else
			outputLength=k + 1 ; // + 1 Nil termination

		return outputLength;
}

// utf8 to 420
int mainConvertutf8to420(const char *input,char *output,int returnNil)
{

	int outputLength=0;
	// convert
	outputLength=convertUTFTo420(input,output,0);

	// return array without Nil termination
	char chrNil=0x00;
	if(returnNil == 0)
		{
			int i=0;
			for (i=0;i<outputLength;i++,output++)
				if(*output == chrNil)
					break;

			return i;
		}

	return outputLength;

}


// 420 to 420 fix shape
int mainConvert420to420(const char *input,char *output,int returnNil)
{

	int outputLength=0;
	// convert
	outputLength=convert420To420(input,output,0);

	// return array without Nil termination
	char chrNil=0x00;
	if(returnNil == 0)
		{
			int i=0;
			for (i=0;i<outputLength;i++,output++)
				if(*output == chrNil)
					break;

			return i;
		}

	return outputLength;

}

// 420 to utf8
int mainConvert420toutf8(const char *input,char *output,int returnNil)
{
	int outputLength=0;

	// convert
	outputLength=convert420Toutf8(input,output,0);

	// return array without Nil termination
	char chrNil=0x00;
	if(returnNil == 0)
		{
			int i=0;
			for (i=0;i<outputLength;i++,output++)
				if(*output == chrNil)
					break;

			return i;
		}

	return outputLength;
}

int mainConvertutf8to037(const char *input,char *output,int returnNil)
{

	int outputLength=0;
	// convert
	outputLength=convertUTFTo037(input,output,0);

	// return array without Nil termination
	char chrNil=0x00;
	if(returnNil == 0)
		{
			int i=0;
			for (i=0;i<outputLength;i++,output++)
				if(*output == chrNil)
					break;

			return i;
		}

	return outputLength;

}

int mainConvert037toutf8(const char *input,char *output,int returnNil)
{
	int outputLength=0;

	// convert
	outputLength=convert037Toutf8(input,output,0);

	// return array without Nil termination
	char chrNil=0x00;
	if(returnNil == 0)
		{
			int i=0;
			for (i=0;i<outputLength;i++,output++)
				if(*output == chrNil)
					break;

			return i;
		}

	return outputLength;
}

int detectCharSet(const char *input, char **output, int *confidance)
{

	UErrorCode errorCode= U_ZERO_ERROR;

	UCharsetDetector *ucd = ucsdet_open ( &errorCode );
	ucsdet_setText(ucd, input, strlen(input), &errorCode);
	UCharsetMatch const * match = ucsdet_detect(ucd, &errorCode);

	*output = ucsdet_getName(match, &errorCode);
	*confidance=ucsdet_getConfidence(match, &errorCode);

	//printf("Name: %s\n", ucsdet_getName(match, &errorCode));
	//printf("Name: %s\n", ucsdet_getName(match, &errorCode));
	//printf("Confidence: %u\n", ucsdet_getConfidence(match, &errorCode));

	ucsdet_close(ucd);
	u_cleanup();
	return 0;

}


int mainAllConverterNames(void)
{
	return AllConverterNames();
}

///////////////////////// DATE PROCESSING ////////////////


int g2h(int day,int month,int year,int *rday,int *rmonth,int *ryear)
{
	UErrorCode status = U_ZERO_ERROR;
	UDate time;
	UCalendar *cal1, *cal2;

	// Create a new Gregorian Calendar.
	cal1 = ucal_open(NULL, -1, "en_US@calendar=gregorian", UCAL_TRADITIONAL, &status);

	if (U_FAILURE(status)) {
	    //printf("Couldn't create Gregorian Calendar.");
	    return -1;
	}

	// Set the Gregorian Calendar to a specific date for testing.


	//ucal_setDate(cal1, 2017, UCAL_JUNE, 5, &status);


	ucal_setDate(cal1, year, month - 1, day, &status);

	if (U_FAILURE(status)) {
	    //printf("Error setting date.");
	    return -1;
	}

	// Display the date.
	//printf("Gregorian Calendar:\t%d/%d/%d\n",
	//							ucal_get(cal1, UCAL_DATE, &status),
	 //                           ucal_get(cal1, UCAL_MONTH, &status) + 1,
	  //                          ucal_get(cal1, UCAL_YEAR, &status));
	if (U_FAILURE(status)) {
	    //printf("Error getting Gregorian date.");
	    return -2;
	}

	// Create a Japanese Calendar.
	//cal2 = ucal_open(NULL, -1, "ja_J@calendar=japanese", UCAL_TRADITIONAL, &status);
	cal2 = ucal_open(NULL, -1, "ar_KW@calendar=islamic", UCAL_TRADITIONAL, &status);
	if (U_FAILURE(status)) {
	    //printf("Couldn't create Islamic Calendar.");
	    return -2;
	}

	// Set the date.
	time = ucal_getMillis(cal1, &status);
	if (U_FAILURE(status)) {
	    //printf("Error getting time.\n");
	    return -3;
	}
	ucal_setMillis(cal2, time, &status);
	if (U_FAILURE(status)) {
	    //printf("Error setting time.\n");
	    return -3;
	}

	// Display the date.
	//printf("Hijri Calendar:\t\t%d/%d/%d\n",
	//							ucal_get(cal2, UCAL_DATE, &status),
	//                          ucal_get(cal2, UCAL_MONTH, &status) + 1,
	//	                        ucal_get(cal2, UCAL_YEAR, &status));
	*rday=ucal_get(cal2, UCAL_DATE, &status);
	*rmonth=ucal_get(cal2, UCAL_MONTH, &status) + 1;
	*ryear=ucal_get(cal2, UCAL_YEAR, &status);

	if (U_FAILURE(status)) {
	    //printf("Error getting Islamic date.");
	    return -4;
	}

	ucal_close(cal1);
	ucal_close(cal2);

	return 1;
}


int maing2h(int day,int month,int year,int *rday,int *rmonth,int *ryear)
{

	int success=g2h(day,month,year,rday,rmonth,ryear);

	return  success;


}




/////////////////////////////////////////////////////////
