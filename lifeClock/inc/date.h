/*
 * date.h
 *
 *  Created on: 2014/07/26
 *      Author: 223emot
 */

#ifndef DATE_H_
#define DATE_H_


#define VERIFY_YYYYMMDD_SUCCESS           0
#define VERIFY_YYYYMMDD_YYYY_OUT_OF_RANGE 1
#define VERIFY_YYYYMMDD_MM_OUT_OF_RANGE   2
#define VERIFY_YYYYMMDD_DD_OUT_OF_RANGE   3
#define VERIFY_YYYYMMDD_MM_DD_IS_UNJUST   4

/** yyyymmdd形式の年月日を西暦0年基準の日数に変換する
 *
 * 年月日の有効範囲は0年1月1日から9999年12月31日とする。
 * 有効範囲外の年もしくは年月日として不正な値が指定された場合は無効値(-1)を返す
 *
 * @param[in] yyyymmdd 年月日
 *
 * @retval -1     無効な年月日
 * @retval -1以外 西暦0年基準の日数
 */
int YYYYMMDDToDay(unsigned int yyyymmdd);

/** 西暦0年基準の日数をyyyymmdd形式の年月日に変換する
 *
 * 未実装
 */
int dayToYYYYMMDD(unsigned int serial);


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
 * @retval VERIFY_YYYYMMDD_SUCCESS           正常
 * @retval VERIFY_YYYYMMDD_YYYY_OUT_OF_RANGE 年が範囲外
 * @retval VERIFY_YYYYMMDD_MM_OUT_OF_RANGE   月が範囲外
 * @retval VERIFY_YYYYMMDD_DD_OUT_OF_RANGE   日が範囲外
 * @retval VERIFY_YYYYMMDD_MM_DD_IS_UNJUST   日が年月に対して不正
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


#endif /* DATE_H_ */
