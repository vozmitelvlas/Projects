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
void printFileHeader(BitmapFileHeader header){
	printf("signature:\t%x (%hu)\n", header.signature, header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}
void printInfoHeader(BitmapInfoHeader header){
	printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
	printf("width: \t%x (%u)\n", header.width, header.width);
	printf("height: \t%x (%u)\n", header.height, header.height);
	printf("planes: \t%x (%hu)\n", header.planes, header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
	printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}
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
//void printHelp();
int color_replacement(tokens tmp, BMP data){	
	char** tvalues_n = tmp.tvalues_n;
	char** tvalues_o = tmp.tvalues_o;
	int cnt1 = 0;
	while(tvalues_n[cnt1]){
		cnt1 += 1;
	}
	if(cnt1 < 3){
		printf("\nEnter the argument and ALL THREE rgb components are correct(0 to 255 and without spaces beetween values). Ex: -n/--newcolors value1,value2,value3\n");
		printf("Use --help\n\n");
		//printHelp();
		return 0;
	}

	int cnt2 = 0;
	while(tvalues_o[cnt2]){
		cnt2 += 1;
	}
	if(cnt2 < 3){
		printf("\nEnter the argument and ALL THREE rgb components are correct(0 to 255 and without spaces beetween values). Ex: -o/--oldcolors value1,value2,value3\n");
		printf("Use --help\n\n");
		//printHelp();
		return 0;
	}
	if(atoi(tvalues_o[0]) > 255 || atoi(tvalues_o[1]) > 255 || atoi(tvalues_o[2]) > 255 || atoi(tvalues_n[0]) > 255 || atoi(tvalues_n[1]) > 255 || atoi(tvalues_n[2]) > 255){
		printf("\nEnter the argument and ALL THREE rgb components are correct(0 to 255 and without spaces beetween values). Ex: -o/--oldcolors value1,value2,value3\n");
		printf("Use --help\n\n");
		return 0;
	}

	Rgb **arr = data.arr;
	unsigned int H = data.bih.height;
	unsigned int W = data.bih.width;

	for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j++){
			if( (arr[i][j].r == atoi(tvalues_o[0])) && (arr[i][j].g == atoi(tvalues_o[1])) && (arr[i][j].b == atoi(tvalues_o[2])) ){
				arr[i][j].r = atoi(tvalues_n[0]);
				arr[i][j].g = atoi(tvalues_n[1]);
				arr[i][j].b = atoi(tvalues_n[2]);
			}
		}
	}
	return 1;
}
int filter_rgb_component(char** rgb_value, BMP data){
	char* component = rgb_value[0];
	char* value = rgb_value[1];

	Rgb **arr = data.arr;
	unsigned int H = data.bih.height;
	unsigned int W = data.bih.width;

	if(strcmp(component, "-r") == 0){
		for(int i = 0; i < H; i++){
			for(int j = 0; j < W; j++){
				arr[i][j].r = atoi(value);
			}
		}
		return 1;
	}
	if(strcmp(component, "-g") == 0){
		for(int i = 0; i < H; i++){
			for(int j = 0; j < W; j++){
				arr[i][j].g = atoi(value);
			}
		}
		return 1;
	}
	if(strcmp(component, "-b") == 0){
		for(int i = 0; i < H; i++){
			for(int j = 0; j < W; j++){
				arr[i][j].b = atoi(value);
			}
		}
		return 1;
	}
	printf("\nEnter the data correctly( -//-.bmp -r 255 -//-.bmp)\n");
	printf("Use --help\n");
	return 0;
	//printHelp();
}
int correct(int x){
	if(x%2 == 0) return 1;
	return 0;
}
int cut_on_lines(char **array, BMP data){
	char **rgb = calloc(3, sizeof(char*));

	char* token = strtok(array[3], ",");
	int j = 0;
	while (token){
		rgb[j] = token;
		j++;
		token = strtok(NULL, ",");
	}
	
	int cnt = 0;
	while(rgb[cnt]){
		cnt += 1;
	}
	if(cnt < 3){
		printf("\nEnter the argument and ALL THREE rgb components are correct(0 to 255 and without spaces beetween values). Ex: -C/--colors value1,value2,value3\n");
		printf("Use --help\n\n");
		//printHelp();
		return 0;
	}
	for(int i = 0; i < 3; i++){
		if( !atoi(rgb[i]) && strcmp(rgb[i], "0") && strcmp(rgb[i], "00") && strcmp(rgb[i], "000") ){;
			printf("\nEnter the correct data for -C(--colors)\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
	}

	Rgb **arr = data.arr;
	unsigned int H = data.bih.height;
	unsigned int W = data.bih.width;
	int N = atoi(array[0]);
	int M = atoi(array[1]);
	int T = atoi(array[2]);

	for(int h = 1; h < N; h++){
		for(int h1 = ((h*H)/N) - (T/2-correct(T)); h1 <= ((h*H)/N)+T/2; h1++ ){
			for(int w1 = 0; w1 <= W; w1++){
				arr[h1][w1].r = atoi(rgb[0]);
				arr[h1][w1].g = atoi(rgb[1]);
				arr[h1][w1].b = atoi(rgb[2]);
			}
		}
	}
	for(int w = 1; w < M; w++){
		for(int w1 = ((w*W)/M) - (T/2-correct(T)); w1 <= ((w*W)/M)+T/2; w1++ ){
			for(int h1 = 0; h1 < H; h1++){
				arr[h1][w1].r = atoi(rgb[0]);
				arr[h1][w1].g = atoi(rgb[1]);
				arr[h1][w1].b = atoi(rgb[2]);
			}
		}
	}
}
BMP new_lines(BMP data, char **array){
	BMP n_img;

	char **rgb = calloc(3, sizeof(char*));

	char* token = strtok(array[3], ",");
	int j = 0;
	while (token){
		rgb[j] = token;
		j++;
		token = strtok(NULL, ",");
	}
	
	int cnt = 0;
	while(rgb[cnt]){
		cnt += 1;
	}
	if(cnt < 3){
		printf("\nEnter the argument and ALL THREE rgb components are correct(0 to 255 and without spaces beetween values). Ex: -C/--colors value1,value2,value3\n");
		printf("Use --help\n\n");
		//printHelp();
		n_img.error_signal = 1;
		return n_img;
	}
	for(int i = 0; i < 3; i++){
		if( !atoi(rgb[i]) && strcmp(rgb[i], "0") && strcmp(rgb[i], "00") && strcmp(rgb[i], "000") ){;
			printf("\nEnter the correct data for -C(--colors)\n");
			printf("Use --help\n\n");
			//printHelp();
			n_img.error_signal = 1;
			return n_img;
		}
	}
	int r = atoi(rgb[0]);
	int g = atoi(rgb[1]);
	int b = atoi(rgb[2]);
	int n = atoi(array[0]);
	int m = atoi(array[1]);
	int t = atoi(array[2]);

    int o_H = data.bih.height;
    int o_W = data.bih.width;
 
    n_img.bih = data.bih;
    n_img.bfh = data.bfh;
    n_img.bih.height += t * (n-1);
    n_img.bih.width += t * (m-1);
 
    int n_H = n_img.bih.height;
    int n_W = n_img.bih.width;
	int offset = (n_W * sizeof(Rgb))%4;
	offset = offset ? 4-offset : 0;
 
 
    n_img.arr = malloc(n_H * sizeof(Rgb*) + offset);
    for(int i = 0; i < n_H; i++){
        n_img.arr[i] = malloc(n_W * sizeof(Rgb) + offset);
    }
 
    for (int h = 0; h < o_H; h++){
        for (int w = 0; w < o_W; w++){
            n_img.arr[h][w] = data.arr[h][w];
        }
    }
 
    for(int ph = 1; ph < n; ph++){
        for (int h = o_H - 1 + t * ph; h > (ph * o_H) / n + t * (ph-1); h--){
            for (int w = 0; w < o_W; w++){
                if (h + t < n_H)
                    n_img.arr[h + t][w] = n_img.arr[h][w];
            }
        }
        for (int h = 0; h < t; h++){
            for (int w = 0; w < n_W; w++){
                n_img.arr[(ph * o_H)/n + t * (ph - 1) + 1 + h][w].r = r;
                n_img.arr[(ph * o_H)/n + t * (ph - 1) + 1 + h][w].g = g;
                n_img.arr[(ph * o_H)/n + t * (ph - 1) + 1 + h][w].b = b;
            }
        }
    }
 
    for(int pw = 1; pw < m; pw++){
        for (int w = o_W - 1 + t * pw; w > (pw*o_W)/m + t * (pw - 1); w--){
            for (int h = 0; h < n_H; h++){
                if (w + t < n_W)
                    n_img.arr[h][w + t] = n_img.arr[h][w];
            }
        }
        for (int w = 0; w < t; w++){
            for (int h = 0; h < n_H; h++){
                n_img.arr[h][(pw * o_W)/m + t * (pw - 1) + 1 + w].r = r;
                n_img.arr[h][(pw * o_W)/m + t * (pw - 1) + 1 + w].g = g;
                n_img.arr[h][(pw * o_W)/m + t * (pw - 1) + 1 + w].b = b;
            }
        }
    }
	return n_img;
}
void DESCRIPTIONS(){
	printf("\n[DESCRIPTIONS]\n");	
	printf("	Program supports CLI and only works with version 3 BMP files");
	printf("\n	Bmp files with color table are not supported");
	printf("\n	The program only supports files with a depth of 24 pixels per bit");
	printf("\n	File must not be compressed\n");
}
void printHelp(){
	printf("\n[FUNCTIONS]\n");
	printf("	(1) - replace color\n");
	printf("	Replace one color to another\n");
	printf("	Required arguments:\n");
	printf("		-o/--oldcolors\n");
	printf("		-n/--newcolors\n");
	printf("\n	(2) - filter for RGB component\n");
	printf("	Sets rgb component from 0 to 255\n");
	printf("	Required arguments:\n");
	printf("		-r/--red\n");
	printf("		-g/--green\n");
	printf("		-b/--blue\n");
	printf("\n	(3) - Splitting the picture into parts\n");
	printf("	Draw the lines, separating image\n");
	printf("	Required arguments:\n");
	printf("		-y/--ylines\n");
	printf("		-x/--xlines\n");
	printf("		-t/--thickness\n");
	printf("		-c/--linecolor\n\n");
	printf("[KEYS]\n");
	printf("		-o/--oldcolors/-n/--newcolors <red>,<green>,<blue>		sets color in RGB format\n");
	printf("		-r/--red/-g/--green/-b/--blue <value>				sets RGB component <from 0 to 255>\n");
	printf("		-y/--ylines <value>						number of parts(lines+1) along the 'Y'\n");
	printf("		-x/--xlines <value>						number of parts(lines+1) along the 'X'\n");
	printf("		-t/--thickness <value>						line's thickness\n");
	printf("		-c/--linecolor <red>,<green>,<blue>				line color\n");
	printf("		-h/-?/--help							instructions\n");
}
tokens checking_values(char** argv, int argc){
	tokens tmp;
	int values_o;
	int values_n;
	char** tvalues_n = calloc(3, sizeof(char*));
	char** tvalues_o = calloc(3, sizeof(char*));
	int j = 0;
	int k = 0;
	int okN = 1;
	int okO = 1;
	for(int i = 0; i < argc; i++){
		if(okN == 1 && (!strcmp(argv[i],"-n") || !strcmp(argv[i],"--newcolors"))){
			okN = 0;
			values_n = i+1;
			char* token = strtok(argv[values_n], ",");
			while (token){
				tvalues_n[j] = token;
				j++;
				token = strtok(NULL, ",");
			}

		}
		if(okO == 1 && (!strcmp(argv[i],"-o") || !strcmp(argv[i],"--oldcolors"))){
			okO = 0;
			values_o = i+1;
			char* token = strtok(argv[values_o], ",");
			while (token){
				tvalues_o[k] = token;
				k++;
				token = strtok(NULL, ",");
			}
		}
	}
	for(int i = 0; i < j; i++){
		if( !atoi(tvalues_n[i]) && strcmp(tvalues_n[i], "0") && strcmp(tvalues_n[i], "00") && strcmp(tvalues_n[i], "000") ){
			printf("\nEnter the correct data for -n(--newcolors)\n");
			printf("Use --help\n\n");
			tmp.error_flag = 1;
			return tmp;
		}
	}
	for(int i = 0; i < k; i++){
		if(!atoi(tvalues_o[i]) && strcmp(tvalues_o[i], "0") && strcmp(tvalues_o[i], "00") && strcmp(tvalues_o[i], "000")){
			printf("\nEnter the correct data for -o(--oldcolors)\n");
			printf("Use --help\n\n");
			tmp.error_flag = 1;
			return tmp;
		}
	}
	tmp.tvalues_n = tvalues_n;
	tmp.tvalues_o = tvalues_o;
	tmp.error_flag = 0;
	return tmp;
}
int main(int argc, char* argv[]){
	char *opts = "Zo:n:r:g:b:y:x:t:c:h?";
	
	struct option longOpts[]={
		{"oldcolors", 1, NULL, 'o'},
		{"newcolors", 1, NULL, 'n'},
		{"red", 1, NULL, 'r'},
		{"green", 1, NULL, 'g'},
		{"blue", 1, NULL, 'b'},
		{"xlines", 1, NULL, 'x'},
		{"ylines", 1, NULL, 'y'},
		{"thickness", 1, NULL, 't'},
		{"linecolor", 1, NULL, 'c'},
		{"help", no_argument, NULL, 'h'},
		{ NULL, 0, NULL, 0}
	};

	int opt;
	int longIndex;
	opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	
	char** rgb_value = calloc(2, sizeof(char*));
	char** lines = calloc(4, sizeof(char*));
	
	int z11 = 0;
	int z12 = 0;
	int z2 = 0;
	int z30 = 0;
	int z31 = 0;
	int z32 = 0;
	int z33 = 0;
	int i = 0;
	int Z = 0;
	while(opt != -1){
		switch(opt){
			case 'o':
				z11 = 1;
				break;
			case 'n':
				z12 = 1;
				break;
			case 'r':
				z2 += 1;
				rgb_value[0] = "-r"/*argv[optind-2]*/;
				rgb_value[1] = optarg;
				if(!atoi(rgb_value[1]) && strcmp(rgb_value[1], "0") && strcmp(rgb_value[1], "00") && strcmp(rgb_value[1], "000") ){
					printf("\nIncorrect input, argument '-r/--red' must have a numeric value. Try again\n");
					printf("Use --help\n\n");
					//printHelp();
					return 0;
				}
				break;
			case 'g':
				z2 += 1;
				rgb_value[0] = "-g"/*argv[optind-2]*/;
				rgb_value[1] = optarg;
				if(!atoi(rgb_value[1]) && strcmp(rgb_value[1], "0") && strcmp(rgb_value[1], "00") && strcmp(rgb_value[1], "000") ){
					printf("\nIncorrect input, argument '-g/--green' must have a numeric value. Try again\n");
					printf("Use --help\n\n");
					//printHelp();
					return 0;
				}
				break;
			case 'b':
				z2 += 1;
				rgb_value[0] = "-b"/*argv[optind-2]*/;
				rgb_value[1] = optarg;
				if(!atoi(rgb_value[1]) && strcmp(rgb_value[1], "0") && strcmp(rgb_value[1], "00") && strcmp(rgb_value[1], "000") ){
					printf("\nIncorrect input, argument '-b/--blue' must have a numeric value. Try again\n");
					printf("Use --help\n\n");
					//printHelp();
					return 0;
				}
				break;
			case 'y':
				z30 += 1;
				lines[0] = optarg;
				if(!atoi(lines[0]) && strcmp(lines[0], "0") && strcmp(lines[0], "00") && strcmp(lines[0], "000") ){
					printf("\nIncorrect input, argument '-y/--ylines' must have a numeric value. Try again\n");
					printf("Use --help\n\n");
					//printHelp();
					return 0;
				}
				break;
			case 'x':
				z31 += 1;
				lines[1] = optarg;
				if(!atoi(lines[1]) && strcmp(lines[1], "0") && strcmp(lines[1], "00") && strcmp(lines[1], "000") ){
					printf("\nIncorrect input, argument '-x/--xlines' must have a numeric value. Try again\n");
					printf("Use --help\n\n");
					//printHelp();
					return 0;
				}
				break;
			case 't':
				z32 += 1;
				lines[2] = optarg;
				if(!atoi(lines[2]) && strcmp(lines[2], "0") && strcmp(lines[2], "00") && strcmp(lines[2], "000") ){
					printf("\nIncorrect input, argument '-t/--thicness' must have a numeric value. Try again\n");
					printf("Use --help\n\n");
					//printHelp();
					return 0;
				}
				break;
			case 'c':
				z33 += 1;
				lines[3] = optarg;
				break;

			case 'h':
				DESCRIPTIONS();
				printHelp();
				return 0;
			case '?':
				DESCRIPTIONS();
				printHelp();
				return 0;
			
			case 'Z':
				Z = 1;
				printf("calm");
				break;
		}
		opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	}
	
	tokens ch = checking_values(argv, argc);
	argc -= optind;
	argv += optind;
	char* path_in = argv[0];
	char* path_out = argv[argc-1];
	

	BMP img = read_image(path_in);
	if(img.file_error == 1){
		return 0;
	}

	for(int i = 0; i < argc; i++){
		if(!strstr(argv[i], ".bmp")){
			printf("\nEnter the data correctly, without unnecessary and unknown keys for the program. Use --help\n\n");
			//printHelp();
			return 0;
		}
	}
	
	if( (!path_out) || (!path_in) || (img.error_signal == 1) || (!strstr(path_out, ".bmp")) || (strcmp(path_in, path_out) == 0)){  //проверка на ошибки file
		if((img.error_signal == 1) && strstr(path_in, ".bmp")){
			printf("\n%s - Error in reading the file. There is no such file, or check its rights", path_in);
			printf("\nBy default, the first argument should be passed the name of the bmp file to be read\n");
			printf("The last to be passed is the name of the bmp file to which the changes will be written\n");
			printf("Try again(Ex: -//-.bmp)\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		printf("\nBy default, the first argument should be passed the name of the bmp file to be read\n");
		printf("The last to be passed is the name of the bmp file to which the changes will be written\n");
		printf("Try again(Ex: -//-.bmp)\n");
		printf("Use --help\n\n");
		//printHelp();
		return 0;
	}

	if( (z11 == 1) || (z12 == 1) ){
		if((z2 == 1) || (z30 == 1) || (z31 == 1) || (z32 == 1) || (z33 == 1)){
			printf("\nEnter only the arguments that are specified for this function\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		if((z11 == 1) && (z12 == 0)){
			printf("\nNot enough arguments. Try again\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		if((z11 == 0) && (z12 == 1)){
			printf("\nNot enough arguments. Try again\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		if(ch.error_flag == 0){
			if(color_replacement(ch, img)){
				write_image(path_out, img);
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	if(z2 > 0){
		if((z11 == 1) || (z12 == 1) || (z30 == 1) || (z31 == 1) || (z32 == 1) || (z33 == 1)){
			printf("\nEnter only the arguments that are specified for this function\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;	
		}
		if(z2 > 1){
			printf("\nYou can enter only one rgb component\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		int filter = filter_rgb_component(rgb_value, img);
		if(filter == 0){
			return 0;
		}
		write_image(path_out, img);
	}
	if(z30 > 0 || z31 > 0 || z32 > 0 || z33 > 0){
		if((z11 == 1) || (z12 == 1) || (z2 == 1)){
			printf("\nEnter only the arguments that are specified for this function\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		if(z30 == 0 || z31 == 0 || z32 == 0 || z33 == 0){
			printf("\nError entering arguments, any argument is used once. Try again\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		
		if(z30 + z31 + z32 + z33 < 4){
			printf("\nNot enough arguments. Try again\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		if(z30 + z31 + z32 + z33 > 4){
			printf("\nError entering arguments, any argument is used once. Try again\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		//int cur = cut_on_lines(lines, img);
		BMP new_img = new_lines(img, lines);
		if(new_img.error_signal == 1){
			return 0;
		}
		write_image(path_out, new_img);
	}
	if((z11 == 0) && (z12 == 0) && (z2 == 0) && (z30 == 0) && (z31 == 0) && (z32 == 0) && (z33 == 0)){
		write_image(path_out, img);
	}

	printf("\nThe result has been successfully written to a file - %s.\n\n", path_out);

	free(rgb_value);
	free(lines);
	free(img.arr);
	free(ch.tvalues_n);
	free(ch.tvalues_o);
	return 0;
}