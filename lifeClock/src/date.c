/*
 * date.c
 *
 *  Created on: 2014/07/26
 *      Author: 223emot
 */

/* 参照するヘッダ */
#include "../../common/emttype.h"

/* 実装するヘッダ */
#include "../inc/date.h"

/* ファイルスコープの定数 */
#define DAY_PER_YEAR  356

#define YYYY_MIN 0
#define YYYY_MAX 9999
#define MM_MIN   1
#define MM_MAX   12
#define DD_MIN   1
#define DD_MAX   31

/* ファイルスコープの関数宣言 */

/** 月ごとの最大日数を返す
 *
 * 2月を指定した場合、うるう年は考慮せず、常にうるう年でない場合の日数を返す。
 *
 * @param[in] month 月(1～12)
 *
 * @retval 0      取得失敗(monthの指定が不正)
 * @retval 28～31 月に対応する日
 */
unsigned int day_per_month(unsigned int month);

/** 範囲内の年でうるう年である年の数を返す
 *
 * 指定した始点と終点を含む年の範囲で、うるう年かどうかの判定を行う。
 * 年の有効範囲は0～9999とする。
 * 無効な年を指定した場合、始点が終点より後になる場合はエラーとなり常に0を返す。
 *
 * @param[in] yyyyBegin yyyy形式の年(範囲の始点)
 * @param[in] yyyyEnd   yyyy形式の年(範囲の終点)
 *
 * @retval TODO
 */
unsigned int countLeapYear(unsigned int yyyyBegin, unsigned int yyyyEnd);

/* 関数定義 */


unsigned int day_per_month(unsigned int month){
	const unsigned int DD_MAX_EACH_MM[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(1 <= month && month <= 12){
		return DD_MAX_EACH_MM[month - 1];
	}
	else{
		return 0;
	}
}

unsigned int countLeapYear(unsigned int yyyyBegin, unsigned int yyyyEnd){
	unsigned int yyyy;
	unsigned int countOfLeapYear;

	/* 引数の範囲チェック */
	if(YYYY_MAX < yyyyBegin || YYYY_MAX < yyyyEnd){
		return 0;
	}

	/* 始点・終点の関係のチェック */
	if(yyyyEnd < yyyyBegin){
		return 0;
	}

	countOfLeapYear = 0;
	for(yyyy = yyyyBegin; yyyy <= yyyyEnd; yyyy++){
		if(isLeapYear(yyyy) != 0){
			countOfLeapYear++;
		}
	}

	return countOfLeapYear;
}

int YYYYMMDDToDay(unsigned int yyyymmdd){
	int yyyy;
	int mm;
	int dd;
	int yyyy_day;
	int mm_day;
	int dd_day;
	int leapYear_day;
	int day;
	int i;

	yyyy = parseYear(yyyymmdd);
	mm   = parseMonth(yyyymmdd);
	dd   = parseDay(yyyymmdd);

	// 入力値チェック
	if(yyyy == -1){
		return -1;
	}
	if(mm == -1){
		return -1;
	}
	if(dd == -1){
		return -1;
	}
	if(verifyYYYYMMDD(yyyy, mm, dd) != VERIFY_YYYYMMDD_SUCCESS){
		return -1;
	}

	/* 単純に1年を365日とみなし日数を計算する */
	yyyy_day = yyyy * 365;

	for(i = 0; i < mm - 1; i++){
		mm_day += day_per_month(i);
	}

	dd_day = dd;

	/* うるう年の分の日数を加算する */
	leapYear_day = countLeapYear(0, yyyy);

	/* yyyy年がうるう年 かつ mmddが2/29を迎えていない場合は、yyyy年分の加算を取り消す */
	if(isLeapYear(yyyy) != 0){
		if(mm <= 2 && dd <= 28 ){
			leapYear_day -= 1;
		}
	}

	day = yyyy_day + mm_day + dd_day + leapYear_day;

	return day;
}

int dayToYYYYMMDD(unsigned int serial){
	// TODO 現状では使用しないため未実装
	return 0;
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
		if(day_per_month(mm) + 1 < dd){
			return VERIFY_YYYYMMDD_MM_DD_IS_UNJUST;
		}
	}
	// それ以外の場合
	else{
		if(day_per_month(mm) < dd){
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

