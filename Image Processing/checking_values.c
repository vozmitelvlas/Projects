#include "checking_values.h"
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
			printf("\nEnter the correct data\n");
			printf("Use --help\n\n");
			tmp.error_flag = 1;
			return tmp;
		}
	}
	for(int i = 0; i < k; i++){
		if(!atoi(tvalues_o[i]) && strcmp(tvalues_o[i], "0") && strcmp(tvalues_o[i], "00") && strcmp(tvalues_o[i], "000")){
			printf("\nEnter the correct data\n");
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