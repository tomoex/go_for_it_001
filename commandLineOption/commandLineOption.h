/*
 * commandLineOption.h
 *
 *  Created on: 2014/07/07
 *      Author: tomoe
 */

#ifndef COMMANDLINEOPTION_H_
#define COMMANDLINEOPTION_H_


/** @struct CommandLineOptions
 *
 * コマンドラインオプションの解析結果を格納する構造体
 *
 * フィールド名の命名規則は下記の通りとする。
 * 値:
 * オプション名
 * 値を取らないオプションの場合は常に0とする
 *
 * オプション指定の有無:
 * オプション名_enable
*/
typedef struct{
	unsigned int b;
	unsigned int b_enable;
	unsigned int l;
	unsigned int l_enable;
	unsigned int n;
	unsigned int n_enable;
} CommandLineOptions;

/** CommandLineOptionsを初期化する
 *
 * @param[out] target 処理対象オブジェクト
 * */
void CommandLineOptions_initialize(CommandLineOptions* target);

/** コマンドラインオプションを解析し、解析結果オブジェクトを返す
 *
 * コマンドラインオプションを取るmain関数の引数と同様の引数を取る。
 * 定義されていないオプションは無視される。
 *
 * @param[in] argc オプションの数
 * @param[in] argv オプション配列
 */
CommandLineOptions commandLineParser(int argc, char *argv[]);






#endif /* COMMANDLINEOPTION_H_ */
