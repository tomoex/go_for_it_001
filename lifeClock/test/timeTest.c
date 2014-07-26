/*
 * timeTest.c
 *
 *  Created on: 2014/07/26
 *      Author: 223emot
 */

#include "../../PCUnit/PCUnit.h"

#include "../inc/time.h"


static void test_secondToHHMMSS(void){
	PCU_ASSERT_EQUAL(0,      secondToHHMMSS(0));						// 最小
	PCU_ASSERT_EQUAL(81401,  secondToHHMMSS(8 * 3600 + 14 * 60 + 1));	// 適当な中間値
	PCU_ASSERT_EQUAL(235959, secondToHHMMSS(60 * 60 * 24 - 1));			// 丸められない範囲の最大
	PCU_ASSERT_EQUAL(0,      secondToHHMMSS(60 * 60 * 24));				// 丸められる範囲の値
}

static void test_HHMMSSToSecond(void){
	PCU_ASSERT_EQUAL(0, HHMMSSToSecond(0));
	PCU_ASSERT_EQUAL(0, HHMMSSToSecond(235959));
}

PCU_Suite *timeTest_suite(void){
	static PCU_Test tests[] = {
			{"test_secondToHHMMSS", test_secondToHHMMSS},
			{"test_HHMMSSToSecond", test_HHMMSSToSecond}
	};
	static PCU_Suite suite = { "timeTest", tests, sizeof tests / sizeof tests[0] };
	return &suite;
}
