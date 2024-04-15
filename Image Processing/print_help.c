#include "print_help.h"

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