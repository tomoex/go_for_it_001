/*
 * commandLineOption.c
 *
 *  Created on: 2014/07/07
 *      Author: tomoe
 */

#include "../commandLineOption.h"
#include "../../common/emttype.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void CommandLineOptions_initialize(CommandLineOptions* target){
	target->b = 0;
	target->b_enable = BOOL_FALSE;
	target->l = 0;
	target->l_enable = BOOL_FALSE;
	target->n = 0;
	target->n_enable = BOOL_FALSE;
}


CommandLineOptions commandLineParser(int argc, char *argv[]){
	CommandLineOptions option;
	int opt;

	CommandLineOptions_initialize(&option);

	while((opt = getopt (argc, argv, "b:l:n:")) != -1){
		switch(opt){
		case 'b':
			option.b = atoi(optarg);
			option.b_enable = BOOL_TRUE;
//			printf("-b %s\n", optarg);
			break;
		case 'l':
//			printf("-l %s\n", optarg);
			option.l = atoi(optarg);
			option.l_enable = BOOL_TRUE;
			break;
		case 'n':
//			printf("-n %s\n", optarg);
			option.n = atoi(optarg);
			option.n_enable = BOOL_TRUE;
			break;
		default:
//			printf("no opt.\n");
			break;
		}
	}

	return option;
}
