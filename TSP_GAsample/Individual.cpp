﻿#include "Individual.h"

int* Individual::randArray = NULL;

// コンストラクタ
// argPop: 属している集団
Individual::Individual(Population *argPop)
{
	pop = argPop;
	chrom = new int [pop->field->nodeNum];
	// randArray = new int[pop->field->nodeNum];
	setChrom();
}

// デストラクタ
Individual::~Individual()
{
	delete [] chrom;
	// delete [] randArray;
}

// ランダムに染色体を決める
void Individual::setChrom()
{
	int i;

/*
	chrom[0]に0を代入する．
	iを1からpop->field->nodeNum-1まで1ずつ増やしながら以下を繰り返す．
		chrom[i]にiを代入する．
		randArray[i]に乱数を代入する．
	sortRandArray(1, pop->field->nodeNum-1)を呼び出す．
	fitnessに-1.0を代入する．
*/
	chrom[0] = 0;
	for(i = 1; i < pop->field->nodeNum; i++) {
		chrom[i] = i;
		randArray[i] = rand();
	}
	sortRandArray(1, pop->field->nodeNum-1);

	printf("setChrom()結果: ");
	for (int i = 0; i < pop->field->nodeNum; i++) {
		printf("%d ", chrom[i]);
	}
	printf("\n");

	fitness = -0.1;
}

// 適応度を算出する
void Individual::evaluate()
{
	int i;

/*
	fitnessにpop->field->distance[chrom[pop->field->nodeNum-1]][chrom[0]]を代入する．
	iを0からpop->field->nodeNum-2まで1ずつ増やしながら以下を繰り返す．
		fitnessにpop->field->distance[chrom[i]][chrom[i+1]]を足す．
*/
	fitness = pop->field->distance[chrom[pop->field->nodeNum-1]][chrom[0]];
	// printf("distance[%d][%d] = %f\n", chrom[pop->field->nodeNum-1], chrom[0], pop->field->distance[chrom[pop->field->nodeNum-1]][chrom[0]]);
	for(i = 0; i < pop->field->nodeNum-1; i++) {
		// printf("distance[%d][%d] = %f\n", chrom[i], chrom[i+1], pop->field->distance[chrom[i]][chrom[i+1]]);
		fitness += pop->field->distance[chrom[i]][chrom[i+1]];
	}
	// printf("fitness = %f\n", fitness);
}

// 突然変異を起こす
void Individual::mutate()
{
	int i, r, tmp;

/*
	iを1からpop->field->nodeNum-1まで1ずつ増やしながら以下を繰り返す．
		オブジェクト形式マクロを活用して発生させた0～1の実数の乱数がMUTATE_PROB未満なら以下を実行する．
		rにiとは異なる1～pop->field->nodeNum-1の乱数を代入する．
		chrom[i]とchrom[r]を入れ替える．
*/
	for(i = 1; i < pop->field->nodeNum; i++) {
		if(RAND_01 < MUTATE_PROB) {
			while (true)
			{
				r = (rand() % pop->field->nodeNum-1)+1;
				if(r!=i)break;
			}
			int buf = chrom[i];
			chrom[i] = chrom[r];
			chrom[r] = buf;
		}
	}
}

// randArray[lb]～randArray[ub]を並び替えつつ，chrom[lb]～chrom[ub]も並び替える
// lb: 並び替えの対象要素の添え字の下限
// ub: 並び替えの対象要素の添え字の上限
void Individual::sortRandArray(int lb, int ub)
{
	int mid, i, j, key, tmp;

	if(lb < ub) {
		mid = (lb + ub) / 2;
		key = randArray[mid];
		i = lb;
		j = ub;
		do {
			while(randArray[i] < key) {
				i++;
			}
			while(randArray[j] > key) {
				j--;
			}
			if(i <= j) {
				tmp = randArray[i];
				randArray[i] = randArray[j];
				randArray[j] = tmp;
				tmp = chrom[i];
				chrom[i] = chrom[j];
				chrom[j] = tmp;
				i++;
				j--;
			}
		} while(i <= j);
		sortRandArray(lb, j);
		sortRandArray(i, ub);
	}
}
