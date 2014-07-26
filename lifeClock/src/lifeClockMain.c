/*
 * lifeClockMain.c
 *
 *  Created on: 2014/07/08
 *      Author: tomoe
 */

#include "../lifeClock.h"
#include "../inc/lifeClockMain.h"
#include "../../common/emttype.h"

#include <stddef.h>
#include <stdlib.h>

#define YYYY_MIN 0
#define YYYY_MAX 9999
#define MM_MIN   1
#define MM_MAX   12
#define DD_MIN   1
#define DD_MAX   31

#define VERIFY_YYYYMMDD_SUCCESS           0
#define VERIFY_YYYYMMDD_YYYY_OUT_OF_RANGE 1
#define VERIFY_YYYYMMDD_MM_OUT_OF_RANGE   2
#define VERIFY_YYYYMMDD_DD_OUT_OF_RANGE   3
#define VERIFY_YYYYMMDD_MM_DD_IS_UNJUST   4

struct LifeClockData_t{
	unsigned int birthday;
	unsigned int life;
};

LifeClockData* LifeClockData_create(){
	// 領域確保
	LifeClockData* object = malloc(sizeof(LifeClockData));

	// 初期化
	LifeClockData_initialize(object);

	return object;
}

void LifeClockData_delete(LifeClockData* target){
	// 解放
	free(target);
}

int LifeClockData_setRequisiteParameters(LifeClockData* target, unsigned int birthday, unsigned int life){
	int yyyy;
	int mm;
	int dd;
	int verifyed;

	/* 年月日を各要素に分割する */
	yyyy = parseYear(birthday);
	mm   = parseMonth(birthday);
	dd   = parseDay(birthday);

	/* パラメータを検証する */
	verifyed = verifyYYYYMMDD(yyyy, mm, dd);

	/* 検証 NG */
	if(verifyed != VERIFY_YYYYMMDD_SUCCESS){
		return 1;
	}

	/* パラメータを設定する */
	target->birthday = birthday;
	target->life     = life;

	return 0;
}

unsigned int lifeToClockTime(const LifeClockData* life, unsigned int day){
	return 0;
}


void LifeClockData_initialize(LifeClockData* target){
	target->birthday = 0;
	target->life     = 0;
}


int parseYear(unsigned int yyyymmdd){
	unsigned int year = yyyymmdd / 10000;

	if(YYYY_MAX < year){
		return -1;
	}

	return year;
}

int parseMonth(unsigned int yyyymmdd){
	unsigned int year  = yyyymmdd / 10000;
	unsigned int month = yyyymmdd / 100 - year;

	if(MM_MIN == month || MM_MAX < month){
		return -1;
	}

	return month;
}

int parseDay(unsigned int yyyymmdd){
	unsigned int yearMonth = yyyymmdd / 100;
	unsigned int day       = yyyymmdd - yearMonth;

	if(DD_MIN == day || DD_MAX < DD_MAX){
		return -1;
	}

	return day;
}


int verifyYYYYMMDD(unsigned int yyyy, unsigned int mm, unsigned int dd){
	const unsigned int DD_MAX_EACH_MM[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// 値の範囲のチェック
	if(yyyy < YYYY_MIN || YYYY_MAX < yyyy){
		return VERIFY_YYYYMMDD_YYYY_OUT_OF_RANGE;
	}
	if(mm < MM_MIN || MM_MAX < mm){
		return VERIFY_YYYYMMDD_MM_OUT_OF_RANGE;
	}
	if(dd < DD_MIN || DD_MAX < dd){
		return VERIFY_YYYYMMDD_DD_OUT_OF_RANGE;
	}

	// 月に対する日の対応のチェック
	// うるう年の2月の場合
	if(mm == 2 &&isLeapYear(yyyy) == BOOL_TRUE){
		if(DD_MAX_EACH_MM[mm - 1] + 1 < dd){
			return VERIFY_YYYYMMDD_MM_DD_IS_UNJUST;
		}
	}
	// それ以外の場合
	else{
		if(DD_MAX_EACH_MM[mm - 1] < dd){
			return VERIFY_YYYYMMDD_MM_DD_IS_UNJUST;
		}
	}


	// 検証OK
	return VERIFY_YYYYMMDD_SUCCESS;
}

int isLeapYear(unsigned int yyyy){

	if(yyyy % 4 == 0){
		if(yyyy % 100 == 0){
			if(yyyy % 400 == 0){
				return BOOL_TRUE;
			}
			else{
				return BOOL_FALSE;
			}
		}
		else{
			return BOOL_TRUE;
		}
	}
	else{
		return BOOL_FALSE;
	}

	return BOOL_FALSE;
}


