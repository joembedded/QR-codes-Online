//---------------------------------------------------------------------------

#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "QR_Encode.h"

//---------------------------------------------------------------------------

int main(int argc, char* argv[]){
	int i,j;
	char text[256]="HelloWorld";
	int version=0;
	int level=QR_LEVEL_H;
	int err=0,verbose=1;
	int format=0;   // 0:C-Standard 1:ASCII

	for(i=1;i<argc;i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'l':
				switch(toupper(argv[i][2])){
				case 'L': level=QR_LEVEL_L; break; //0
				case 'M': level=QR_LEVEL_M; break; //1
				case 'Q': level=QR_LEVEL_Q; break; //2
				case 'H': level=QR_LEVEL_H; break; //3
				default:
					err=1;
				}
				break;
			case 'f':
				format=atoi(&argv[i][2]);
				if(format<0 || format>1) err=1;
				break;
			case 's':
				verbose=0;
				break;
			default:
				printf("Unknown Option: '%s'\n",argv[i]);
				err=1;
			}
		}else strncpy(text,argv[i],255);
	}
	if(err || verbose) printf("*** qr2_cmd (C)2018 joembedded.de ***\n");
	int sl=strlen(text);
	if(sl<1) err=1; // Minimum-text-Length
	if(err){
		printf("Arguments: TEXT [-l(L,M,Q,H)] [-s] [-f(0,1)]\n");
		return -1;
	}
	char f=(char)"LMQH"[level];
	if(verbose) printf("Input:'%s' (Len:%d, Level:'%c')\n",text,sl,f);

	// Replace '|' with \nl
	for(i=0;i<sl;i++) if(text[i]=='|') text[i]='\n';

	unsigned char encoded[MAX_BITDATA];
	memset(encoded, 0, sizeof(encoded));
	int width = EncodeData(level, version, text, 0, encoded);
	int size = ((width*width)/8) + (((width*width)%8)?1:0);

	if(format==0){
		printf("#define QR_WIDTH %d\n",width);
		printf("unsigned char qr[%d]={",size);
		for(i=0;i<size;i++){
			printf("%u",encoded[i]);
			if(i!=size-1) printf(",");
		}
		printf("};\n");
	}else if(format==1){
		for (i = 0; i < width; i++) {
			for (j = 0; j < width; j++) {
				int idx=i * width + j;
				int byte = (idx) / 8;
				int bit = (idx) % 8;
				if (encoded[byte] & (0x80 >> bit)){
					printf("*");
				}else printf("-");
			}
			printf("\n");
		}

	}

}
