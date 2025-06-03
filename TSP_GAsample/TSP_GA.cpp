#include "Population.h"

int main()
{
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
	sprintf(fname, "%s.tsp", dataName[dataNo - 1]);
	field = new Field(fname);

	pop = new Population(field);
	for(i = 1; i <= GEN_MAX; i++) {
		pop->alternate();
	}
	pop->printRoute();

	delete pop;
	delete field;
	return 0;
}
