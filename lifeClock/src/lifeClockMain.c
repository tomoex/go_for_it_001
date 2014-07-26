/*
 * lifeClockMain.c
 *
 *  Created on: 2014/07/08
 *      Author: tomoe
 */

/* 参照するヘッダ */
#include "../inc/date.h"
#include "../inc/time.h"
#include "../../common/emttype.h"
#include <stddef.h>
#include <stdlib.h>

/* 実装するヘッダ */
#include "../lifeClock.h"
#include "../inc/lifeClockMain.h"


struct PersonData_t{
	unsigned int birthday;
	unsigned int age;
};

PersonData* LifeClockData_create(){
	// 領域確保
	PersonData* object = malloc(sizeof(PersonData));

	// 初期化
	LifeClockData_initialize(object);

	return object;
}

void LifeClockData_delete(PersonData* target){
	// 解放
	free(target);
}

int LifeClockData_setRequisiteParameters(PersonData* target, unsigned int birthday, unsigned int age){
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
	target->age     = age;

	return 0;
}

unsigned int lifeToClockTime(const PersonData* target, unsigned int currentDay){
	int yyyy_currentDay;
	int mm_currentDay;
	int dd_currentDay;

	int lifeBegin_day;
	int lifeNow_day;
	int lifeEnd_day;

	int lifeCurrentDays;
	int lifeAllDays;
	double normalizedLife;

	unsigned int clockTimeSeconds;
	unsigned int clockTime;

	/* 引数(currentDay)のチェック */
	yyyy_currentDay = parseDay(currentDay);
	mm_currentDay   = parseMonth(currentDay);
	dd_currentDay   = parseDay(currentDay);
	if(yyyy_currentDay == -1 || mm_currentDay == -1 || dd_currentDay == -1){
		return CONVERT_LIFE_TO_CLOCKTIME_ERROR;
	}
	if(verifyYYYYMMDD(yyyy_currentDay, mm_currentDay, dd_currentDay) != VERIFY_YYYYMMDD_SUCCESS){
		return CONVERT_LIFE_TO_CLOCKTIME_ERROR;
	}

	/* 各年月日から生存している総日数と、任意の日付時点の生存日数を計算する */
	lifeBegin_day = YYYYMMDDToDay(target->birthday);
	lifeNow_day   = YYYYMMDDToDay(currentDay);
	lifeEnd_day   = YYYYMMDDToDay(target->birthday + target->age * 10000);

	if(lifeBegin_day == -1 || lifeNow_day == -1 || lifeEnd_day == -1){
		return CONVERT_LIFE_TO_CLOCKTIME_ERROR;
	}

	// TODO 細かいところがおかしい気がする
	lifeCurrentDays = lifeNow_day - lifeBegin_day;
	lifeAllDays     = lifeEnd_day - lifeBegin_day;

	/* 生存日数を総日数で正規化する(0～1.0) */
	normalizedLife = lifeCurrentDays / lifeAllDays;

	/* 正規化した生存日数を24時間に変換する */
	clockTimeSeconds = SECONDS_PER_DAY * normalizedLife;
	clockTime        = secondToHHMMSS(clockTimeSeconds);

	return clockTime;
}


void LifeClockData_initialize(PersonData* target){
	target->birthday = 0;
	target->age      = 0;
}




