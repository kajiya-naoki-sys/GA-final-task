#include "Population.h"
#include <stdio.h>
#include <time.h>

int main()
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	int i, dataNo;
	char fname[256];
	Population* pop;
	Field* field;
	char dataName[DATA_NUM][16] = {"berlin52", "eil51", "eil76", "kroA100", "test"};

	srand((unsigned int)time(NULL));

	printf("実行するデータの番号を入力してください．\n");
	for(i = 0; i < DATA_NUM; i++) {
		printf("%d : %s\n", i + 1, dataName[i]);
	}
	scanf("%d", &dataNo);
	sprintf(fname, "./TSPdata/%s.tsp", dataName[dataNo - 1]);
	field = new Field(fname);

	pop = new Population(field);
	for(i = 1; i <= GEN_MAX; i++) {
		// printf("i=%d\n", i);
		pop->alternate();
	}
	pop->printRoute();

	delete pop;
	delete field;
	
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	//結果をファイルに書き込む
	FILE* fp = fopen("clockTime.txt", "a");  // "a" にすると追記
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}
	fprintf(fp, "%f\n", cpu_time_used);
	return 0;
}
