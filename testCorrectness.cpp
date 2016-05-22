#include <cstdio>
#include "cube.h"
using namespace std;

const int ans[] =
{1, 18, 243, 3240, 43239, 574908, 7618438, 100803036, 1332343288};

int res[10] = {0};

cube A;
uc maxd = 0, d = 0;

hash_table S;

void init()
{
    freopen("/Users/Joshua/Desktop/Computer Science/Rubik's Cube/Cube3.0/Cube3.0/map.in", "r", stdin);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < m; j++)
            scanf("%hu", &sM[i][j]);
    
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < m; j++)
            scanf("%hu", &cM[i][j]);
}

void dfs(uc u)
{
    S.insert(A.S, A.C);
    if (d == maxd) return;
    for (uc v = 0; v < 18; v++)
        if (G[u][v])
        {
            ull C0 = A.C, S0 = A.S;
            A.turn(v);
            d++; dfs(v); d--;
            A.C = C0, A.S = S0;
        }
}

#define DEPTH 7

void work()
{
    maxd = 0;
    while (maxd < DEPTH)
    {
        printf("%d\n", maxd);
        S.clear();
        dfs(18);
        res[maxd] = S.size();
        maxd++;
    }
    for (int i = DEPTH - 1; i > 0; i--)
        res[i] -= res[i - 1];
}

void check()
{
    for (int i = 0; i < DEPTH; i++)
        if (ans[i] != res[i])
        {
            printf("Depth: %d\nError:%d %d\n", i, ans[i], res[i]);
            return;
        }
    printf("Nodes correctly generated.\n");
}

#undef DEPTH

int main()
{
    init();
    work();
    check();
    return 0;
}