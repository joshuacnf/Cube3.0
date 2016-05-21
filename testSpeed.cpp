#include <cstdio>
#include <ctime>
#include <cmath>
#include "cube.h"
using namespace std;

cube A;
ui cnt = 0, cnt_ = 0, cnt__ = 0;
uc maxd = 1, d = 0;

void init()
{
    freopen("map.in", "r", stdin);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < m; j++)
            scanf("%llu", &sM[i][j]);
    
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < m; j++)
            scanf("%llu", &cM[i][j]);
}

void dfs(uc u)
{
    cnt++;
    if (d == maxd) { cnt_++; return; }
    if (d == maxd - 1) cnt__++;
    for (uc v = 0; v < 18; v++)
        if (G[u][v])
        {
            ull C0 = A.C, S0 = A.S;
            A.turn(v);
            d++; dfs(v); d--;
            A.C = C0, A.S = S0;
        }
}

int main()
{
    init();
    maxd = 1;
    while (maxd < 9)
    {
        d = cnt = cnt_ = cnt__ = 0;
        double e; clock_t s = clock();
        dfs(18);
        e = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
        printf("Search Depth: %d\n", maxd);
        printf("Time: %lf\n", e);
        printf("Nodes Generated: %d (%d nodes/second)\n", cnt, (int)(cnt / e));
        printf("Branching Factor: %lf\n", cnt_ / (cnt__ * 1.0));
        printf("\n");
        maxd++;
    }
    return 0;
}
