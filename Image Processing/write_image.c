#include "write_image.h"

void write_image(char *path, BMP data){
	BitmapFileHeader bfh = data.bfh;
	BitmapInfoHeader bih = data.bih;
	Rgb **arr = data.arr;

	unsigned int H = bih.height;
	unsigned int W = bih.width;

	FILE *f_out = fopen(path, "wb");
	fwrite(&bfh, 1, sizeof(BitmapFileHeader), f_out);
	fwrite(&bih, 1, sizeof(BitmapInfoHeader), f_out);
	int offset = (W * sizeof(Rgb))%4;
	offset = offset ? 4-offset : 0;
	for(int i = 0; i < H; i++){
		fwrite(arr[i], 1, W * sizeof(Rgb) + offset, f_out);
	}
	fclose(f_out);
}