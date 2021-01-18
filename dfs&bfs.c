#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 7
#define true 1

int matrix[MAX][MAX];
int matrix2[MAX][MAX]; //transpose
int visit[MAX];
int visit2[MAX];
char mark[MAX] = { "ABCDEFG" };
char finish[MAX]={ "ABCDEFG" };
int num = 0;
int num2 = 2;
int finish_num[MAX];

void initial() {
	FILE * fp = fopen("hw4.txt", "r");

	if (fp == NULL) {
		printf("파일오픈실패!");
	}

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			fscanf(fp, "%d ", &matrix[i][j]);
		}
	}

	fclose(fp);

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			matrix2[i][j] = matrix[j][i];
	}
}

void dfs(int x) {
	visit[x] = true;

	for (int i = 0; i < MAX; i++) {
		if (!visit[i] && matrix[x][i] == true) {
			visit[i] = true;
			printf("%c에서 %c로 이동 \n", mark[x], mark[i]);
			dfs(i);
		}
	}
	printf("backtracking %c \n", mark[x]);
	finish[num] = mark[x];
	num++;
}

void trans(int x) {
	visit2[x] = true;

	for (int i = 0; i < MAX; i++) {
		if (!visit2[i] && matrix2[x][i] == true) {
			visit2[i] = true;
			printf("%c에서 %c로 이동 \n", mark[x], mark[i]);
			trans(i);
		}
	}
	printf("backtracking %c \n", mark[x]);
}

void find() {

	for (int i = MAX - 1; i >= 0; i--) {
		if (i == 0)
			printf("%c", finish[i]);
		else printf("%c -> ", finish[i]);
	}

	for (int i = 0; i < MAX; i++) {
		if (finish[i] == 'A')
			finish_num[i] = 0;
		else if (finish[i] == 'B')
			finish_num[i] = 1;
		else if (finish[i] == 'C')
			finish_num[i] = 2;
		else if (finish[i] == 'D')
			finish_num[i] = 3;
		else if (finish[i] == 'E')
			finish_num[i] = 4;
		else if (finish[i] == 'F')
			finish_num[i] = 5;
		else
			finish_num[i] = 6;
	}
	printf("\n");

	for (int i = MAX - 1; i >= 0; i--) {
		if (i == 0)
			printf("%d", finish_num[i]);
		else printf("%d -> ", finish_num[i]);
	}
}

int main() {
	initial();
	int x;
	
	printf("Step1: DFS of graph.\n");
	printf("ref) A=0, B=1, C=2, D=3, E=4, F=5, G=6\n");
	printf("Enter root: ");
	scanf("%d", &x);
	if (x >= 7) {
		printf("Error: You can enter the number 0-6\n");
		exit(0);
	}
	printf("\n");
	
	dfs(x);
	
	for (int i = 0; i < MAX; i++) {
		if (!visit[i]) {
			dfs(i);
			printf("\n");
		}
	}

	printf("\n\nStep2: Making transposed matrix.\n");
	for (int i = 0; i < MAX; i++) {
		printf("\n");
		for (int j = 0; j < MAX; j++)
			printf("%d", matrix[i][j]);
	}
	printf("\n");

	printf("\nStep3: get array in order of decreasing finishing time in original graph.\n\n");

	find();

	printf("\n\nStep4: DFS of transposed graph.\n\n");

	printf("SCC 1: \n");
	trans(finish_num[MAX-1]);
	printf("\n");
	
	for (int i = 0; i < MAX; i++) {
		if (!visit2[i]) {
			printf("SCC %d: \n",num2);
			trans(i);
			printf("\n");
			num2++;
		}
	}

	return 0;
}
