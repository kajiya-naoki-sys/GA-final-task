#include "Population.h"

Field* Population::field = NULL;

// コンストラクタ
Population::Population(Field* argField)
{
	int i;

	Population::field = argField;
	Individual::randArray = new int [field->nodeNum];
	used1 = new int [field->nodeNum];
	used2 = new int [field->nodeNum];
	ind = new Individual* [POP_SIZE];
	nextInd = new Individual* [POP_SIZE];
	for(i = 0; i < POP_SIZE; i++) {
		ind[i] = new Individual(this);
		nextInd[i] = new Individual(this);
	}
	evaluate();
}

// デストラクタ
Population::~Population()
{
	int i;

	for(i = 0; i < POP_SIZE; i++) {
		delete ind[i];
		delete nextInd[i];
	}
	delete [] ind;
	delete [] nextInd;
	delete [] Individual::randArray;
	delete [] used1;
	delete [] used2;
}

// 世代交代をする
void Population::alternate()
{
	int i, j, p1, p2;
	Individual **tmp;

	// ルーレット選択のための処理
	/*
	denom = 0.0;
	for(i = 0; i < POP_SIZE; i++) {
		trFit[i] = (ind[POP_SIZE - 1]->fitness - ind[i]->fitness) / (ind[POP_SIZE - 1]->fitness - ind[0]->fitness);
		denom += trFit[i];
	}
	*/

	// エリート保存戦略で子個体を作る
	for(i = 0; i < ELITE; i++) {
		for(j = 0; j < field->nodeNum; j++) {
			nextInd[i]->chrom[j] = ind[i]->chrom[j];
		}
	}

	// 親を選択し，交叉して子個体を作り，突然変異を起こす
	for(; i < POP_SIZE - 1; i += 2) {
		p1 = rankingSelect();
		p2 = rankingSelect();
		crossover(p1, p2, i, i + 1);
		nextInd[i]->mutate();
		nextInd[i + 1]->mutate();
	}

	// 半端が出たらランダムに生成する
	if(i != POP_SIZE) {
		nextInd[i]->setChrom();
	}

	// 次世代を現世代に変更する
	tmp = ind;
	ind = nextInd;
	nextInd = tmp;

	// 評価する
	evaluate();
}

// すべての個体を評価して，適応度順に並び替える
void Population::evaluate()
{
	int i;

	for(i = 0; i < POP_SIZE; i++) {
		ind[i]->evaluate();
	}
	sort(0, POP_SIZE - 1);
}

// ランキング選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
int Population::rankingSelect()
{
	int num, denom, r;

/*
	denomに1～POP_SIZEの和を代入する．
	rに1～denomの乱数を代入する（整数のビットをフルに使う）．
	numをPOP_SIZEから1まで1ずつ減らしながら以下を繰り返す．
		rがnum以下なら繰返しから抜ける．
		rからnumを引く．
*/
	return POP_SIZE - num;
}

// ルーレット選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
int Population::rouletteSelect()
{
	int rank;
	double prob, r;

/*
	rに0～1の実数の乱数を代入する（オブジェクト形式マクロを活用する）．
	rankを1からPOP_SIZE-1まで1ずつ増やしながら以下を繰り返す．
		probにtrFit[rank-1]/denomを代入する．
		rがprob以下なら繰返しから抜ける．
		rからprobを引く．
*/
	return rank - 1;
}

// トーナメント選択で親個体を1つ選択する
// 戻り値: 選択した親個体の添え字
int Population::tournamentSelect()
{
	int i, ret, num, r;
	double bestFit;
	int tmp[POP_SIZE];

/*
	tmp[0]～tmp[POP_SIZE-1]を0にする．
	retに-1，bestFitにDBL_MAX，numに0を代入する．
	以下を無限に繰り返す．
		rに0～POP_SIZE-1の乱数を代入する．
		tmp[r]が0なら以下を実行する．
			tmp[r]に1を代入する．
			ind[r]->fitnessがbestFitより小さかったら以下を実行する．
				retにrを代入する．
				bestFitにind[r]->fitnessを代入する．
			numに1を足す．
			numがTOURNAMENT_SIZEと等しかったら繰返しから抜ける．
*/
	return ret;
}

// 部分写像交叉でind[p1]とind[p2]からnextInd[c1]とnextInd[c2]を生成する．
// p1: 親個体1の添字
// p2: 親個体2の添字
// c1: 子個体1の添字
// c2: 子個体2の添字
void Population::crossover(int p1, int p2, int c1, int c2)
{
	int point1, point2, tmp, i, j, key;

	// used1, used2の初期化
/*
	used1[0]～used1[field->nodeNum-1] ，used2[0]～used2[field->nodeNum-1]を0にする．
*/

	// 交叉点の選択
/*
	point1に0～field->nodeNum-2の乱数を代入する．
	point2にpoint1とは異なる0～field->nodeNum-2の乱数を代入する．
	point1がpoint2より大きかったら入れ替える．
*/

	// 交叉点間のコピー
/*
	iをpoint1+1からpoint2-1まで1ずつ増やしながら以下を繰り返す．
		nextInd[c1]->chrom[i]にind[p2]->chrom[i]を代入する．
		nextInd[c2]->chrom[i]にind[p1]->chrom[i]を代入する．
*/

	// 交叉点外のコピー
/*
	iを0からpoint1まで1ずつ増やしながら以下を繰り返す．	
		--- ここから処理A ---
		keyにind[p1]->chrom[i]を代入する．
		以下を無限に繰り返す．
			jをpoint1+1からpoint2-1まで1ずつ増やしながら以下を繰り返す．
				keyがind[p2]->chrom[j]と等しかったら繰返しから抜ける．
			jがpoint2と等しかったら繰返しから抜ける．
			keyにind[p1]->chrom[j]を代入する．
		nextInd[c1]->chrom[i]にkeyを代入する．
		--- ここまで処理A ---

		--- ここから処理B ---
		処理Aのp1をp2，p2をp1，c1をc2にした処理を実行する．
		--- ここまで処理B ---
	iをpoint2からfield->nodeNum-1まで1ずつ増やしながら処理Aと処理Bを繰り返す．
*/
}

// ind[lb]～ind[ub]をクイックソートで並び替える
// lb: 並び替えの対象要素の添え字の下限
// ub: 並び替えの対象要素の添え字の上限
void Population::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	Individual *tmp;

	if(lb < ub) {
		k = (lb + ub) / 2;
		pivot = ind[k]->fitness;
		i = lb;
		j = ub;
		do {
			while(ind[i]->fitness < pivot) {
				i++;
			}
			while(ind[j]->fitness > pivot) {
				j--;
			}
			if(i <= j) {
				tmp = ind[i];
				ind[i] = ind[j];
				ind[j] = tmp;
				i++;
				j--;
			}
		} while(i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

// 経路を表示する
void Population::printRoute()
{
	int i;

	for(i = 0; i < field->nodeNum; i++) {
		printf("%d ", ind[0]->chrom[i] + 1);
	}
	printf("\n");
	printf("Total Distance : %f\n", ind[0]->fitness);
}
