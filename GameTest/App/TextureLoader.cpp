/*!
 * OpenGL 3.2 Utils - Extension to the Angel library (from the book Interactive Computer Graphics 6th ed
 * https://github.com/mortennobel/OpenGL_3_2_Utils
 *
 * New BSD License
 *
 * Copyright (c) 2011, Morten Nobel-Joergensen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "stdafx.h"
#include "TextureLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight, bool flipY)
{
	printf("Reading image %s\n", imagepath);
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file)							    {printf("Image could not be opened\n"); return NULL;}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 byes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){ 
		printf("Not a correct BMP file\n");
		return NULL;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return NULL;
	}
	// Make sure this is a 24bpp file
	//if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return NULL;}
	//if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return NULL;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
    imageSize *= 8;
	outWidth      = *(int*)&(header[0x12]);
	outHeight     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	imageSize=outWidth*outHeight*4; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
    fseek(file, dataPos, 0);
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);
    unsigned char *colorData = data;
    for (unsigned int i = 0; i < imageSize ; i += 4)
    {
        unsigned char b = colorData[0];        
        unsigned char g = colorData[1];
        unsigned char r = colorData[2];        
        unsigned char a = colorData[3];
        colorData[0] = r;        
        colorData[1] = g;
        colorData[2] = b;
        colorData[3] = a;
        colorData += 4;
        
    }

	if (flipY)
    {
		// swap y-axis
		unsigned char * tmpBuffer = new unsigned char[outWidth*4];
		int size = outWidth*4;
		for (unsigned int i=0; i < (outHeight/2);i++){
			// copy row i to tmp
			memcpy_s(tmpBuffer,size,data+outWidth*4*i,size);
			// copy row h-i-1 to i
			memcpy_s(data+outWidth*4*i, size, data+outWidth*4*(outHeight-i-1), size);
			// copy tmp to row h-i-1
			memcpy_s(data+outWidth*4*(outHeight-i-1), size,tmpBuffer, size);
		}
		delete [] tmpBuffer;
	}

	return data;
}

