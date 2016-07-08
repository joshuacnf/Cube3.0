#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned int ui;
typedef unsigned long long ull;

#define N 924

ui M[6][12] = {
    { 1, 2, 3, 0, 5, 6, 7, 4, 9, 10, 11, 8 },
    { 2, 6, 10, 7, 3, 1, 9, 11, 0, 5, 8, 4 },
    { 5, 9, 6, 1, 0, 8, 10, 2, 4, 11, 7, 3 },
    { 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3 },
    { 0, 3, 2, 1, 5, 4, 7, 6, 8, 11, 10, 9 },
    { 2, 1, 0, 3, 7, 6, 5, 4, 10, 9, 8, 11 },
};

bool flag[12] = {0};
int ans[N][12] = {0}; int cnt = 0;
bool G[N][N] = {0}, vis[N] = {0};

inline void store()
{
    for (ui i = 0, j = 0; i < 12; i++)
	if (flag[i])
	    ans[cnt][j++] = i;
    cnt++;
}

inline void map(int *A, int *B, ui v)
{
    for (int i = 0; i < 6; i++)
	B[i] = M[v][A[i]];
}

inline bool sameSet(int *A, int *B)
{
    for (int i = 0; i < 6; i++)
	if (A[i] != B[i])
	    return false;
    return true;
}

void combination(int u, int num)
{
    if (num == 6)
	store();
    for (int v = u; v < 12; v++)
    {
	flag[v] = true;
	combination(v + 1, num + 1);
	flag[v] = false;
    }
}

void dfs(int u)
{
    vis[u] = true;
    for (int v = 0; v < cnt; v++)
	if (G[u][v] && (!vis[v]))
	    dfs(v);
}

void work()
{
    for (int i = 0; i < cnt; i++)
    {
	int tmp[6];
	for (int v = 0; v < 6; v++)
	{
	    map(ans[i], tmp, v);
	    sort(tmp, tmp + 6);

	    for (int j = i + 1; j < cnt; j++)
		if (sameSet(tmp, ans[j]))
		    G[i][j] = G[j][i] = true;
	}
    }
    
    int tmp[N][12] = {0}, it = 0;
    for (int u = 0; u < cnt; u++)
	if (!vis[u])
	{
	    memcpy(tmp[it], ans[u], 24);
	    it++;
	    dfs(u);
	}
    cnt = it;

    for (int t = 0; t < cnt; t++)
    {
	bool flag[12];
	memset(flag, 0, 12);
	for (int i = 0; i < 6; i++) 
	    flag[tmp[t][i]] = true;

	for (int i = 6, j = 0; i < 12; i++)
	{
	    while (flag[j]) j++;
	    tmp[t][i] = j, flag[j] = true;
	}
	
	memcpy(ans[t], tmp[t], 48);
    }
}

void write()
{
    FILE *out = fopen("cubieSets.in", "w");

    for (int i = 0; i < cnt; i++)
    {
	for (int j = 0; j < 12; j++)
	    fprintf(out, "%d ", ans[i][j]);
	fprintf(out, "\n");
    }

    fclose(out);
}

int main()
{
    combination(0, 0);
    printf("%d sets generated.\n", cnt);
    work(); //remove duplicates & add complement sets
    printf("%d sets after duplicates removed.\n", cnt);
    write();
    printf("\n");
    return 0;
}
