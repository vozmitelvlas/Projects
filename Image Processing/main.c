#include "read_image.h"
#include "write_image.h"
#include "print_help.h"
#include "checking_values.h"
#include "correct.h"
#include "color_replacement.h" 
#include "filter_rgb_component.h"
#include "cut_on_lines.h"

int main(int argc, char* argv[]){
	char *opts = "o:n:r:g:b:y:x:t:c:h?";
	
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
		if((z11 == 1) && (z12 == 0) && ch.error_flag != 1){
			printf("\nNot enough arguments. Try again\n");
			printf("Use --help\n\n");
			//printHelp();
			return 0;
		}
		if((z11 == 0) && (z12 == 1) && ch.error_flag != 1){
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
		BMP new_img = cut_on_lines(img, lines);
		if(new_img.error_signal == 1){
			return 0;
		}
		write_image(path_out, new_img);
	}
	if((z11 == 0) && (z12 == 0) && (z2 == 0) && (z30 == 0) && (z31 == 0) && (z32 == 0) && (z33 == 0)){
		write_image(path_out, img);
	}

	printf("\nThe result has been successfully written to a file - %s.\n\n", path_out);

	return 0;
}