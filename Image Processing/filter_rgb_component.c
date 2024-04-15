#include "filter_rgb_component.h"

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