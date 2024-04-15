#pragma once
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#pragma pack(push, 1)
typedef struct{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixelArrOffset;
} BitmapFileHeader;
typedef struct{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int xPixelsPerMeter;
	unsigned int yPixelsPerMeter;
	unsigned int colorsInColorTable;
	unsigned int importantColorCount;
} BitmapInfoHeader;
typedef struct{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;
#pragma pack(pop)
typedef struct{
	BitmapFileHeader bfh;
	BitmapInfoHeader bih;
	Rgb **arr;
	int error_signal;
	int file_error;
} BMP;
typedef struct{
	char** tvalues_n;
	char **tvalues_o;
	int error_flag;
} tokens;