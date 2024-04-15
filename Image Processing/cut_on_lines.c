#include "cut_on_lines.h"

BMP cut_on_lines(BMP data, char **array){
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
	for(int i = 0; i < j; i++){
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