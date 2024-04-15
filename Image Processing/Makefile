

all: main.o checking_values.o color_replacement.o correct.o filter_rgb_component.o cut_on_lines.o print_help.o read_image.o write_image.o
	gcc main.o checking_values.o color_replacement.o correct.o filter_rgb_component.o cut_on_lines.o print_help.o read_image.o write_image.o -o a.out

main.o:	main.c checking_values.h color_replacement.h correct.h filter_rgb_component.h cut_on_lines.h print_help.h read_image.h write_image.h
	gcc -c main.c

checking_values.o: checking_values.c checking_values.h bmp.h
	gcc -c checking_values.c

color_replacement.o: color_replacement.c color_replacement.h bmp.h
	gcc -c color_replacement.c

correct.o: correct.c correct.h bmp.h
	gcc -c correct.c

filter_rgb_component.o: filter_rgb_component.c filter_rgb_component.h bmp.h
	gcc -c filter_rgb_component.c

cut_on_lines.o: cut_on_lines.c cut_on_lines.h bmp.h
	gcc -c cut_on_lines.c

print_help.o: print_help.c print_help.h bmp.h
	gcc -c print_help.c

read_image.o: read_image.c read_image.h bmp.h
	gcc -c read_image.c

write_image.o: write_image.c write_image.h bmp.h
	gcc -c write_image.c

clean:
	rm -rf *.o main

