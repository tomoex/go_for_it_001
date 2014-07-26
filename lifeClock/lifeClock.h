/*
 * lifeClock.h
 *
 *  Created on: 2014/07/07
 *      Author: tomoe
 */

#ifndef LIFECLOCK_H_
#define LIFECLOCK_H_


#define CONVERT_LIFE_TO_CLOCKTIME_ERROR 999999

struct PersonData_t;
typedef struct PersonData_t  PersonData;

/** 人生時計オブジェクトを生成する
 *
 * この関数で生成したオブジェクトは必ずLifeClockData_delete関数で解放しなければならない。
 * 解放しなかった場合はメモリリークが発生する。
 */
PersonData* LifeClockData_create();


/** 人生時計オブジェクトを削除する
 *
 */
void LifeClockData_delete(PersonData* target);


/** 人生時計オブジェクトに必須のパラメータを設定する
 *
 * 引数で指定した値がすべて有効な値の場合はオブジェクトのパラメータを設定する。
 * 1つ以上の引数が不正な場合はオブジェクトに変更を加えない。
 *
 * @param[out] target   処理対象オブジェクト
 * @param[in]  birthday yyyymmdd形式の年月日
 * @param[in]  life     寿命(単位:年)
 *
 * @retval 0     成功
 * @retval 0以外 失敗
 */
int LifeClockData_setRequisiteParameters(PersonData* target, unsigned int birthday, unsigned int age);

/** 人生時計オブジェクトを元に、寿命内の任意の日付を人生時間に変換する
 *
 * @param[in] target     処理対象オブジェクト
 * @param[in] currentDay yyyymmdd形式の年月日
 *
 * @retval CONVERT_LIFE_TO_CLOCKTIME_ERROR     変換失敗
 * @retval CONVERT_LIFE_TO_CLOCKTIME_ERROR以外 hhmmss形式の時分秒(24時間表記)
 */
unsigned int lifeToClockTime(const PersonData* target, unsigned int currentDay);


#endif /* LIFECLOCK_H_ */
