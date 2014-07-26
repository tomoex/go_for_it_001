/*
 * time.c
 *
 *  Created on: 2014/07/26
 *      Author: 223emot
 */

/* 参照するヘッダ */

/* 実装するヘッダ */
#include "../inc/time.h"

unsigned int secondToHHMMSS(unsigned int second){
	unsigned int secAll;
	unsigned int hh_sec;
	unsigned int mm_sec;
	unsigned int ss_sec;
	unsigned int hh;
	unsigned int mm;
	unsigned int ss;
	unsigned int hhmmss;

	secAll = second % CONVERT_HHMMSS_SEC_MAX;

	ss_sec = secAll                     % (SECONDS_PER_MINUTE);		// 秒(単位:秒)
	mm_sec = (secAll - ss_sec)          % SECONDS_PER_HOUR;			// 分(単位:秒)
	hh_sec = (secAll - mm_sec - ss_sec) % SECONDS_PER_DAY;			// 時(単位:秒)

	hh = hh_sec / SECONDS_PER_HOUR;									// 秒(単位:秒)
	mm = mm_sec / SECONDS_PER_MINUTE;								// 分(単位:分)
	ss = ss_sec;													// 時(単位:時)

	hhmmss = hh * 10000 + mm * 100 + ss;

	return hhmmss;
}


unsigned int HHMMSSToSecond(unsigned int hhmmss){
	// TODO 現状では使用しないため未実装

	return 0;
}


