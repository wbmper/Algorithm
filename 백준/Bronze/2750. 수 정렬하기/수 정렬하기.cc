#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define rnt register int
#define MAXN (1000)
int N, A[MAXN], Temp[MAXN];

void Input(){
	scanf("%d", &N);
	for (rnt i = 0; i < N; i++){
		scanf("%d", A + i);
	}
}

void MergeSort(int s, int e, int* arr){
	if (s >= e) return;

	rnt m = (s + e) / 2;
	MergeSort(s, m, arr);
	MergeSort(m + 1, e, arr);

	rnt i = s, j = m + 1, k;
	for (k = s; k <= e; k++) {
		if (i > m) Temp[k] = arr[j++];
		else if (j > e) Temp[k] = arr[i++];
		else if (arr[i] < arr[j]) Temp[k] = arr[i++];
		else Temp[k] = arr[j++];
	}

	for (k = s; k <= e; k++) {
		arr[k] = Temp[k];
	}
}

void Output(){
	for (rnt i = 0; i < N; i++) {
		printf("%d\n", A[i]);
	}
}

int main()
{
	Input();
	MergeSort(0, N - 1, A);
	Output();
	return 0;
}