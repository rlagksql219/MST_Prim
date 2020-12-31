#include <stdio.h> 
#define M 999 
#define MAX 10

typedef struct Edge {
	int pair1;
	int pair2;
};

Edge edge[MAX - 1];

//그래프의 인접행렬
int W[MAX][MAX] = {
	{ 0, 32, M, 17, M, M, M, M, M, M }, //1
	{ 32, 0, M, M, 45, M, M, M, M, M }, //2
	{ M, M, 0, 18, M, M, 5, M, M, M }, //3
	{ 17, M, 18, 0, 10, M, M, 3, M , M }, //4
	{ M, 45, M, 10, 0, 28, M, M, 25, M }, //5
	{ M, M, M, M, 28, 0, M, M, M, 6 }, //6
	{ M, M, 5, M, M, M, 0, 59, M, M }, //7
	{ M, M, M, 3, M, M, 59, 0, 4, M }, //8
	{ M, M, M, M, 25, M, M, 4, 0, 12 }, //9
	{ M, M, M, M, M, 6, M, M, 12, 0 } //10
};

void prim(int start); //prim algorithm으로 Minimum Spanning Tree 구하는 함수
int IsVertex(int vertex[], int a); //특정 vertex인지 확인하는 함수

void main(void) {
	printf("Minimum Spanning Tree\n");
	printf("(MST를 만들며 선택되는 edge를 순서대로 표시)\n");
	printf("\n");
	prim(0);
	for (int i = 0; i < MAX - 1; i++)
		printf("edge = (v%d-v%d)\n", edge[i].pair1 + 1, edge[i].pair2 + 1);
}

//prim algorithm으로 Minimum Spanning Tree 구하는 함수
void prim(int start) { //시작점을 인자로 함
	int vertex[MAX] = { 0, }, index1 = 0;
	int v, k, nearst, index2 = 0;

	vertex[index1++] = start; //v1을 시작점으로 설정
	while (index1 < MAX) { //배열크기인 MAX까지 반복하여 알고리즘 수행
		nearst = M;
		//인접한 vertex 중에서 가장 적은 cost 값
		//초기에는 최댓값으로 설정

		for (int i = 0; i < index1; i++) {
			v = vertex[i]; //vertex 0으로 초기화

			for (int j = 0; j < MAX; j++) {
				k = W[j][v]; //j행 v열 일 때의 인접행렬 값을 k로 설정

				if (k > 0 && k < M && !IsVertex(vertex, j)) {
					//인접행렬 k의 값이 0보다 크고, 최댓값인 M보다는 작으며, 
					//vertex j가 아닐 경우에 다음의 조건문 실행

					if (k < nearst) { // 인접행렬의 값인 k가 인접한 vertex 중에서 가장 적은 cost 값인 nearst보다 작은 경우
						nearst = k; //nearst를 k로 변경
						edge[index2].pair1 = v; //v와 j를 연결하는 edge 생성
						edge[index2].pair2 = j; //v와 j를 연결하는 edge 생성
					}
				}
			}
		}
		vertex[index1++] = edge[index2].pair2; //vertex의 다음 index는 생성한 edge 중 하나의 vertex로
		index2++; //index를 그 다음으로
	}
}

//특정 vertex인지 확인하는 함수
int IsVertex(int vertex[], int a) {
	for (int i = 0; i < MAX; i++) //0부터 시작하여 배열크기인 MAX까지 vertex 검사
		if (vertex[i] == a) //vertex인 경우 1을 return
			return 1;
	return 0; //vertex가 아닌 경우 0을 return
}