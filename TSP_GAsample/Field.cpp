#include "Field.h"

// コンストラクタ
// fileName: データセットのファイル名
Field::Field(char *fileName)
{
	int i, j, cityNo;
	char line[LINE_LEN];
	char* pos = NULL;
	int flg;
	FILE *fp;
	double **coord;

	// ファイル読込み
	if((fp = fopen(fileName, "r")) == NULL) {
		printf("%sが開けません．\n", fileName);
		exit(1);
	}
	// 地点数取得
	flg = 0;
	while(fgets(line, LINE_LEN, fp)) {
		pos = strstr(line, "DIMENSION");
		if(pos) {
			flg = 1;
			break;
		}
	}
	if(!flg) {
		printf("DIMENSIONの行が存在しません．\n");
		exit(1);
	}
	pos = strchr(pos + 9, ':');
	if(!pos) {
		printf("DIMENSIONのデータに不備があります．\n");
		exit(1);
	}
	if(!sscanf(pos + 1, "%d" , &nodeNum)) {
		printf("DIMENSIONのデータに不備があります．\n");
		exit(1);
	}

	// 領域確保＆初期化
	coord = new double* [nodeNum];
	distance = new double* [nodeNum];
	for(i = 0; i < nodeNum; i++) {
		coord[i] = new double [2];
		distance[i] = new double [nodeNum];
	}

	// 各都市の座標取得
	flg = 0;
	while(fscanf(fp, "%s" , line) != EOF) {
		if(!strcmp(line, "NODE_COORD_SECTION")) {
			flg = 1;
			break;
		}
	}
	if(!flg) {
		printf("NODE_COORD_SECTIONの行が存在しません．\n");
		exit(1);
	}
	for(i = 0; i < nodeNum; i++) {
		if((fscanf(fp, "%d%lf%lf", &cityNo, &coord[i][0], &coord[i][1]) == EOF)
			|| (cityNo != i + 1)) {
			printf("%d番目の都市の座標データに不備があります．\n", i + 1);
			exit(1);
		}
	}
	fclose(fp);

	// 距離計算
	for(i = 0; i < nodeNum; i++) {
		for(j = 0; j < nodeNum; j++) {
			distance[i][j] = sqrt(pow(coord[i][0] - coord[j][0], 2) + pow(coord[i][1] - coord[j][1], 2));
		}
	}

	// 領域解放
	for(i = 0; i < nodeNum; i++) {
		delete [] coord[i];
	}
	delete [] coord;
}

// デストラクタ
Field::~Field()
{
	int i;

	for(i = 0; i < nodeNum; i++) {
		delete [] distance[i];
	}
	delete [] distance;
}
