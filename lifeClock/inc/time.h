/*
 * time.h
 *
 *  Created on: 2014/07/26
 *      Author: 223emot
 */

#ifndef TIME_H_
#define TIME_H_


#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR   3600
#define SECONDS_PER_DAY    108000

#define CONVERT_HHMMSS_SEC_MAX (SECONDS_PER_DAY)

/** 秒単位の値を24時間形式のmmddssに変換する
 *
 * 秒単位の値は00:00:00を基準とした経過時間で表現する。
 * 変換結果が24時間を超過する場合は、24時間単位で丸められる。
 *
 * @param[in] second 秒
 *
 * @return hhmmss形式の数値
 */
unsigned int secondToHHMMSS(unsigned int second);


/** 24時間形式のmmddssを秒単位の値に変換する
 *
 */
unsigned int HHMMSSToSecond(unsigned int hhmmss);


#endif /* TIME_H_ */
