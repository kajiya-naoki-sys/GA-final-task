#pragma once

#include "Individual.h"
class Individual;

class Population
{
public:
	static Field* field;	// 巡回の場

	Population(Field* argField);
	~Population();
	void alternate();		// 世代交代をする
	void printRoute();		// 経路を表示する

	Individual **ind;		// 現世代の個体群のメンバ

private:
	void evaluate();								// 個体を評価する
	int rankingSelect();							// ランキング選択で親個体を選択する
	int rouletteSelect();							// ルーレット選択で親個体を選択する
	int tournamentSelect();							// トーナメント選択で親個体を選択する
	void crossover(int p1, int p2, int c1, int c2);	// 交叉により子を生成する
	void sort(int lb, int ub);						// 個体を良い順に並び替える

	Individual **nextInd;	// 次世代の個体群のメンバ
	int* used1;				// 交叉に使用する配列
	int* used2;				// 交叉に使用する配列
	double trFit[POP_SIZE];	// 適応度を変換した値（ルーレット選択用）
	double denom;			// 確率を求めるときの分母（ルーレット選択用）
};
