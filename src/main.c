/*
 * main.c
 *
 *  Created on: 2014/07/06
 *      Author: tomoe
 */

#include <stdio.h>
#include "../commandLineOption/commandLineOption.h"
#include "../lifeClock/lifeClock.h"


/* 人生の入力方式どうしようか？
 *
 * linuxの1コマンドであるというイメージで設計する
 * > lifeclock -b 19841220 -l 80[ -n 20140701]
 * 10:50:51
 *
 * コマンドライン解析はgetoptを使うと割と簡単にできるらしい
*/




int main(int argc, char *argv[]){
	CommandLineOptions option;
	PersonData* data;
	int retOfSet;
	unsigned int time;


	option = commandLineParser(argc, argv);

	printf("b: enb=%d val=%d\n", option.b_enable, option.b);
	printf("l: enb=%d val=%d\n", option.l_enable, option.l);
	printf("n: enb=%d val=%d\n", option.n_enable, option.n);
	printf("Hello world\n");

	data = LifeClockData_create();
	retOfSet = LifeClockData_setRequisiteParameters(data, option.b, option.l);

	if(retOfSet != 0){
		printf("parameter is not set. code:%d\n", retOfSet);
	}
	time = lifeToClockTime(data, option.n);
	printf("time:%d\n", time);
	LifeClockData_delete(data);
	return 1;
}


