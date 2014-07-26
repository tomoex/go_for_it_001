/*
 * lifeClockMain.h
 *
 *  Created on: 2014/07/09
 *      Author: tomoe
 */

#ifndef LIFECLOCKMAIN_H_
#define LIFECLOCKMAIN_H_

void LifeClockData_initialize(LifeClockData* target);

/** yyyymmdd形式の年月日から年を取り出す
 *
 * 年の有効範囲は0～9999とする。
 * 有効範囲外の年が指定された場合は無効値(-1)を返す。
 * 月日の値はdon't care。
 *
 * @param[in] yyyymmdd yyyymmdd形式の年月日
 *
 * @retval -1     無効な年
 * @retval -1以外 年
 */
int parseYear(unsigned int yyyymmdd);

/** yyyymmdd形式の年月日から月を取り出す
 *
 * 月の有効範囲は1～12とする。
 * 有効範囲外の月が指定された場合は無効値(-1)を返す。
 * 年日の値はdon't care。
 *
 * @param[in] yyyymmdd yyyymmdd形式の年月日
 *
 * @retval -1     無効な月
 * @retval -1以外 月
 */
int parseMonth(unsigned int yyyymmdd);

/** yyyymmdd形式の年月日から日を取り出す
 *
 * 日の有効範囲は1～31とする。
 * 有効範囲外の日が指定された場合は無効値(-1)を返す。
 * 年月の値はdon't care。
 *
 * @param[in] yyyymmdd 年月日
 *
 * @retval -1     無効な日
 * @retval -1以外 日
 */
int parseDay(unsigned int yyyymmdd);

/** yyyymmdd形式の年月日の妥当性を検証する
 *
 * 年月日の組み合わせがカレンダーの規則に即しているか検証する。
 * 年は0～9999の任意の値をとる
 * 月は1～12の任意の値をとる
 * 日は月が
 *  1,3,5,7,10,12の場合、1～31をとる
 *  2の場合、1～28をとる。ただしうるう年の場合は1～29をとる
 *  4,6,9,11の場合、1～30をとる
 *
 * @param[in] yyyy 年(西暦)
 * @param[in] mm   月
 * @param[in] dd   日
 *
 * @retval 0 正常
 * @retval 1 年が範囲外
 * @retval 2 月が範囲外
 * @retval 3 日が範囲外
 * @retval 4 日が年月に対して不正
 *
 */
int verifyYYYYMMDD(unsigned int yyyy, unsigned int mm, unsigned int dd);

/** yyyy年がうるう年かどうかを返す
 *
 * 1. 4で割り切れる年はうるう年
 * 2. かつ、100で割り切れる年はうるう年ではない
 * 3. かつ、400で割り切れる年はうるう年
 *
 * @param[in] yyyy 年(西暦)
 *
 * @retval 0     うるう年ではない
 * @retval 0以外 うるう年
 */
int isLeapYear(unsigned int yyyy);

#endif /* LIFECLOCKMAIN_H_ */
