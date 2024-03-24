#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define rnt register int
constexpr int MAXN = 100;

int M, N, A[MAXN + 2][MAXN + 2], mark;
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
int fr, re;
int GroupLinkMark[MAXN * MAXN + 1];
int Visit[MAXN * MAXN + 1], VisitCount;
int Invalid[MAXN * MAXN + 1];
int ans = MAXN * MAXN + 1;

struct DATA {
	int r, c;
}que[MAXN * MAXN];

struct NODE {
	int GroupNum;
	NODE* Next;
	NODE* Alloc(int NewGroupNum, NODE* NewNode) {
		GroupNum = NewGroupNum, Next = NewNode;
		return this;
	}
} Buf[MAXN * MAXN * 10], *pstNode[MAXN * MAXN + 1];
int nNodeCnt;

void Input() 
{
	scanf("%d %d", &M, &N);
	for (rnt i = 1; i <= M; i++) {
		for (rnt j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
			A[i][j] -= 2; // black: -1, white: -2
		}
	}
}

void FloodFill(int r, int c) 
{
	fr = 0, re = 0;
	rnt nr, nc;
	rnt color = A[r][c];
	A[r][c] = mark;
	que[re++] = { r, c };
	while (fr < re)
	{
		DATA& cur = que[fr++];
		for (rnt d = 0; d < 4; d++) {
			nr = cur.r + dr[d], nc = cur.c + dc[d];
			rnt NewVal = A[nr][nc];
			if (NewVal == 0) continue; // out of boundary
			if (NewVal == mark) continue; // already marked
			if (NewVal == color) {
				A[nr][nc] = mark;
				que[re++] = { nr, nc };
			}
			else if (NewVal > 0 && GroupLinkMark[NewVal] < mark) {
				GroupLinkMark[NewVal] = mark;
				pstNode[mark] = Buf[nNodeCnt++].Alloc(NewVal, pstNode[mark]);
				pstNode[NewVal] = Buf[nNodeCnt++].Alloc(mark, pstNode[NewVal]);
			}
		}
	}
}

void GroupMark()
{
	mark = 0;
	for (rnt i = 1; i <= M; i++) {
		for (rnt j = 1; j <= N; j++) {
			if (A[i][j] == -1 || A[i][j] == -2) {
				++mark;
				FloodFill(i, j);
			}
		}
	}
}

void BFS(int Mark) 
{
	fr = re = 0;
	Visit[Mark] = ++VisitCount;
	que[re++] = { Mark, 0 };
	while (fr < re) {
		DATA& cur = que[fr++];
		for (NODE* p = pstNode[cur.r]; p; p = p->Next) {
			rnt nGroupNum = p->GroupNum;
			rnt t = cur.c + 1;
			if (Visit[nGroupNum] < VisitCount) {
				Visit[nGroupNum] = VisitCount;
				que[re++] = { nGroupNum, t };
			}
		}
	}

	int ret = que[re - 1].c;
	if (ans > ret) {
		ans = ret;
	}
	else if (ans <= ret) {
		for (rnt i = 0; i < re; i++) {
			if (que[i].c + ans <= ret) {
				Invalid[que[i].r] = 1;
			}

			if (que[i].c >= ans) {
				Invalid[que[i].r] = 1;
			}
		}
	}
}

void Link()
{
	for (rnt i = 1; i <= mark; i++) {
		if (Invalid[i] == 0) {
			BFS(i);
		}
	}
}

int main()
{
	Input();
	GroupMark();
	Link();
	printf("%d\n", ans);
	return 0;
}