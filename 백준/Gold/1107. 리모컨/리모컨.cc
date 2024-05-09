#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
using namespace std;

#define rnt register int
#define MAXCHANNEL (500000)
#define MINCHANNEL (0)
#define MAXBROKENBUTTON (10)

#define ABS(x) ((x) > 0 ? (x) : (-(x)))

int nTargetChannel, nTargetNum, nMinTarget, nMaxTarget, nCurrentMax; // channel, channel 자리 수
int anBroken[10]; // 망가졌다면 1, 그렇지 않으면 0
int nBrokenButtonNum; // 망가진 Button 수
int nGuessChannel; // 근접한 channel 수 (+, - 사용 전)
int nSol;

int Get10Times(int index)
{
	if (index <= 1) return 1; // 1의 자리
	else return 10 * Get10Times(index - 1);
}

int GetNum(int num, int index) // index 1은 1의 자리, index 2는 10의 자리
{
	if (index == 1) return num % 10;
	else return GetNum(num / 10, index - 1);
}

int GetCount(int num) // 자리 수 (0 일 경우 1)
{
	int count = 1;
	while (num = num / 10)
	{
		count++;
	}

	return count;
}

void Input()
{
	scanf("%d", &nTargetChannel);
	scanf("%d", &nBrokenButtonNum);
	int a;
	for (rnt i = 0; i < MAXBROKENBUTTON; i++) anBroken[i] = 0;
	for (rnt i = 0; i < nBrokenButtonNum; i++)
	{
		scanf("%d", &a);
		anBroken[a] = 1; // a 버튼 망가짐
	}
}

void DFS(int index, int guess, int select)
{
	if (index == 0) // 1의 자리까지 모두 탐색 완료
	{
		rnt ans = ABS(guess - nTargetChannel) + select;
		if (ans < nSol) nSol = ans;
		return;
	}

	if (index == nCurrentMax)
	{
		for (rnt i = 1; i < 10; i++)
		{
			if (anBroken[i]) continue;
			DFS(index - 1, guess + i * Get10Times(index), select + 1);
		}
	}
	else
	{
		for (rnt i = 0; i < 10; i++)
		{
			if (anBroken[i]) continue;
			DFS(index - 1, guess + i * Get10Times(index), select + 1);
		}
	}
}

int Solve()
{
	nGuessChannel = 100;
	nTargetNum = GetCount(nTargetChannel); // 자리 수
	if ((nSol = ABS(nTargetChannel - nGuessChannel)) <= nTargetNum) // 둘 사이의 간격이 자리 수보다 작거나 같으면 +, - 를 이용하는 게 나음
	{
		return nSol;
	}

	nMaxTarget = nTargetNum == 6 ? 6 : nTargetNum + 1;
	nMinTarget = nTargetNum == 1 ? 1 : nTargetNum - 1;

	for (rnt nTarget = nMinTarget; nTarget <= nMaxTarget; nTarget++)
	{
		nCurrentMax = nMaxTarget;
		DFS(nTarget, 0, 0);
	}

	return nSol;
}

int main()
{
	Input();
	int ans = Solve();
	printf("%d\n", ans);
	return 0;
}