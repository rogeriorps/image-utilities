#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int arg_content;

int process_cmdline(int argc, char **argv)
{
        int i;

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-w") == 0) {
                        arg_content = atoi(argv[++i]);
                }
                else if (strcmp(argv[i], "-h") == 0) {
                        arg_content = atoi(argv[++i]);
                }
                else if (strcmp(argv[i], "-f") == 0) {
                        arg_content = atoi(argv[++i]);
                }
                else if (strcmp(argv[i], "-o") == 0) {
                        arg_content = atoi(argv[++i]);
                }
                if (strcmp(argv[i], "-p") == 0) {
                        arg_content = atoi(argv[++i]);
                }
                else if (strcmp(argv[i], "-cp") == 0) {
                        arg_content = atoi(argv[++i]);
                }
                else if (strcmp(argv[i], "-help") == 0) {
                        printf("\nCreate raw image for image processing tests\n\n" \
                               " -w <image width>\n -h <image height>\n" \
                               " -f <image format>\n -o <output filename>\n"	\
                               " -p <pattern>\n -cp <custom patern for RGB variants>\n\n");
                        return -1;
                }
        }

       // printf("g_display_width = %d, g_display_height = %d\n", arg_content, arg_content);
       // printf("g_display_top = %d, g_display_left = %d\n", arg_content, arg_content);

       // if ((g_display_width == 0) || (g_display_height == 0)) {
       //         return -1;
       // }
        return 0;
}

int main(int argc, char **argv)
{

unsigned int a;
int file1,file2,file3,file4,out;
int filesize;
unsigned short *raw1,*raw2,*raw3,*raw4;
unsigned char *output;
FILE * file_out = NULL;

        if (process_cmdline(argc, argv) < 0) {
                return -1;
        }

	printf("Creating a RGBA32 240x480 file\n");

	if ((file_out = fopen("rgba32_1024x768.raw", "wb")) < 0) {
		printf("Cannot open output file");
		return 0;
	}

	//1024*768x4 = 3145728 bytes = 786432 pixels
	filesize = 3145728;
	output = (unsigned char *) malloc(3145728);

	for (a=0; a<(786432/4); a++)
	{
		*(output+(a*4)) = 0xff;
		*(output+(a*4)+1) = 0x00;
		*(output+(a*4)+2) = 0x00;
		*(output+(a*4)+3) = 0x33;

	}

	for (a=(786432/4); a<(786432/2); a++)
	{
		*(output+(a*4)) = 0x00;
		*(output+(a*4)+1) = 0xff;
		*(output+(a*4)+2) = 0x00;
		*(output+(a*4)+3) = 0x33;

	}

	for (a=(786432/2); a<(3*(786432/4)); a++)
	{
		*(output+(a*4)) = 0x00;
		*(output+(a*4)+1) = 0x00;
		*(output+(a*4)+2) = 0xff;
		*(output+(a*4)+3) = 0x33;

	}

	for (a=(3*(786432/4)); a<786432; a++)
	{
		*(output+(a*4)) = 0xff;
		*(output+(a*4)+1) = 0xff;
		*(output+(a*4)+2) = 0xff;
		*(output+(a*4)+3) = 0x33;

	}


	fwrite(output, 1, 3145728, file_out);

	fclose(file_out); 

//printing to check the operation
/*	printf("image 1\n\n");
	for (a=0; a<32; a++)
	{

		printf("%x ",*raw1+a);

	}
*/
	printf("output\n\n");

}

