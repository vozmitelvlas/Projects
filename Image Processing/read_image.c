#include "read_image.h"

BMP read_image(char* path){
	
	BMP image;
	BitmapFileHeader bfh;
	BitmapInfoHeader bih;

	FILE* img = fopen(path, "rb");
	if( (!img) || (!strstr(path, ".bmp")) ){
		image.error_signal = 1;
		return image;
	}
	fread(&bfh, 1, sizeof(BitmapFileHeader), img);
	fread(&bih, 1, sizeof(BitmapInfoHeader), img);
	if(bih.headerSize != 40){
		printf("FILE ERROR\n");
		image.file_error = 1;
		return image;

	}
	unsigned int H = bih.height;
	unsigned int W = bih.width;

	Rgb **arr = malloc(H*sizeof(Rgb*));
	int offset = (W * sizeof(Rgb))%4;
	offset = offset ? 4-offset : 0;
	for(int i = 0 ; i < H; i++){
		arr[i] = malloc(W * sizeof(Rgb) + offset);
		fread(arr[i], 1, W * sizeof(Rgb) + offset, img);
	}

	fclose(img);

	image.bfh = bfh;
	image.bih = bih;
	image.arr = arr;
	image.error_signal = 0; 
	return image;

}