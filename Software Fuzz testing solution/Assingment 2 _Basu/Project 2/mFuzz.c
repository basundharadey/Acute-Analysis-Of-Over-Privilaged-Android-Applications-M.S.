#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>


static int crashNum=0;

int main()
 {
	int fSize, j, status, ret, retCode;
	char filename[20], comBuff[200];
	FILE *fin, *fout, *fnew;
	time_t t;
	srand((unsigned) time(&t));
	char hex1[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
	char hex2[16] = {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0};
        char hex3[16] = {0x20,0x21,0x22,0x23,0x24,0X25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F};
      

	for(j = 0; j < 10000; j++) 
                 {
                        int value1 = rand()%16;
			int value2 = rand()%16;
                        int value3 = rand()%16;
			int index = rand()%fSize;

                        unsigned char iBuff[fSize];

			fin = fopen("./sample.jpg", "rb");
			fout = fopen("./test.jpg", "wb");
			fseek(fin,0,SEEK_END);
			fSize=ftell(fin);
			fseek(fin,0,SEEK_SET);
			fread(iBuff,1,fSize,fin);
			fclose(fin);
			
                        iBuff[index]= hex1[value1] | hex2[value2] | hex3[value3] ; /*ORed the values generated randomly in both arrays to get values in range 0x00 to 0xFF*/
			fwrite(iBuff, 1, fSize, fout);
			fclose(fout);

			sprintf(comBuff, "./jpegconv -ppm -outfile foo.ppm test.jpg");
			ret = system(comBuff);
			wait(&status);
			retCode= WEXITSTATUS(ret);

			if(retCode == 139)
                          {
				crashNum++;
				sprintf(filename, "./crashed-%d.jpg", crashNum);
				fnew = fopen(filename, "wb");
				fwrite(iBuff, 1, fSize, fnew);
				fclose(fnew);
			  }
						
                }

	return 0;
}
