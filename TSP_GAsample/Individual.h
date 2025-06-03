#pragma once

#include "Field.h"
#include "Population.h"
class Population;

class Individual
{
public:
	static int* randArray;	// 初期世代の個体を作るときに使う配列

	Individual(Population* argPop);
	~Individual();
	void setChrom();
	void evaluate();								// 適応度を算出する
	void mutate();									// 突然変異を起こす

	Population* pop;	// 属している集団
	int* chrom;			// 染色体
	double fitness;		// 適応度

private:
	void sortRandArray(int lb, int ub);
};
