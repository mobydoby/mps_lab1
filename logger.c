#ifndef __LOGGER_H
#define __LOGGER_H

#include "init.h"

void logger(){
	//inputs first print flag, line to print error messages
	int ins = 0, npp = 12;
	while(1){
		//to change entire terminal, print this inside loop ?? don't really understand why.
		printf("\033[0;33;44m");
		fflush(stdout);
		if (ins == 0){
			printf("\n                         PRESS <ESC> OR <CTL>+[ TO QUIT\n\n\n\r\n");
			ins = 1;
		}

		char choice;
		choice = getchar();

		//    	if the inputted string is an acceptable string - print - TASK1
		if (choice == 0x1b){
			//    		printf("escape\r\n");
			break;
		}
		else if (choice < 0x20 && choice<0x7F){

			printf("\033[%d;0H", npp);
			npp++;
			if (npp >= 25){
				//set cursor to 12
				//    			printf("\033[24;0H");
				//erase line
				//    			printf("\033[2K");
				//set scroll section line 12-24
				printf("\033[12;24r");
				//scroll up section
				printf("\033M");
				//go to line 24
				printf("\033[25;0H");

			}
			printf("\r\n\033[5mThe key board character $%X is \033[4m'not printable'\a", choice);
		}
		else{
			printf("\033[6;0H");
			printf("The keyboard character is \033[31m%c\r\n", choice);
		}
	}
}
#endif
