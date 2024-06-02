#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
using namespace std;

#define rnt register int
#define ull unsigned long long

constexpr int MOD = 1000000007;

struct MAT
{
	ull a[2][2];
	
	MAT() {};
	MAT(ull b[2][2])
	{
		for (rnt i = 0; i < 2; i++)
			for (rnt j = 0; j < 2; j++)
			{
				a[i][j] = b[i][j];
			}
	}

	void operator=(MAT b)
	{
		for (rnt i = 0; i < 2; i++)
			for (rnt j = 0; j < 2; j++)
			{
				a[i][j] = b.a[i][j];
			}
	
	}
};

MAT MultiplyTwoMat(MAT left, MAT right)
{
	MAT sol;
	for (rnt i = 0; i < 2; i++)
		for (rnt j = 0; j < 2; j++)
		{
			sol.a[i][j] = 0;
			for (rnt k = 0; k < 2; k++)
			{
				sol.a[i][j] += (left.a[i][k] * right.a[k][j]) % MOD;
			}
		}

	return sol;
}

MAT Multiply(MAT stMat, ull nNtimes)
{
	if (nNtimes == 0)
	{
		ull Identity[2][2] = { {1, 0},{0,1} };
		return MAT(Identity);
	}
	else if (nNtimes == 1)
	{
		return stMat;
	}
	else if (nNtimes == 2)
	{
		return MultiplyTwoMat(stMat, stMat);
	}

	if (nNtimes % 2 == 0) // even number
	{
		return Multiply(Multiply(stMat, nNtimes / 2), 2);
	}
	else
	{
		return MultiplyTwoMat(Multiply(stMat, nNtimes - 1), stMat);
	}
}

int main()
{
	ull N, anMat[2][2] = { {2, 1}, {1, 1} };
	
	scanf("%llu", &N);
	const MAT stMat = MAT(anMat);
	ull a_0 = 0, a_1 = 1, nSol;

	MAT stSol = Multiply(stMat, N / 2);

	if (N & 1 == 1)
	{
		nSol = (stSol.a[0][0] * a_1) % MOD + (stSol.a[0][1] * a_0) % MOD;
	}
	else
	{
		nSol = (stSol.a[1][0] * a_1) % MOD + (stSol.a[1][1] * a_0) % MOD;
	}

	printf("%llu\n", nSol % MOD);

	return 0;
}
