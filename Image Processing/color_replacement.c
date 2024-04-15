#include "color_replacement.h"

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