#pragma once

// 標準ヘッダのインクルード
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <limits.h>

// 定数の定義
#define GEN_MAX		1000	// 世代交代数
#define POP_SIZE	100		// 個体群のサイズ
#define ELITE		1		// エリート保存戦略で残す個体の数
#define MUTATE_PROB	0.01	// 突然変異確率
#define TOURNAMENT_SIZE 30	// トーナメントサイズ
#define LINE_LEN	1024	// ファイル読込み時の配列変数の長さ
#define DATA_NUM	5		// データ数

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Field
{
public:
	Field(char *fileName);
	~Field();

	int nodeNum;		// ノード数
	double **distance;	// ノード間距離
};

