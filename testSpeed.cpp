#include <cstdio>
#include <ctime>
#include <cmath>
#include "cube.h"

database DB; cube A;
ui cnt; uc maxd = 1, d = 0;

void dfs(uc u)
{
    cnt++;
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

int main()
{
    maxd = 1;
    while (maxd < 9)
    {
        d = cnt = 0;
        clock_t s = clock();
        dfs(18);
        double t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
        printf("Search Depth: %d\n", maxd);
        printf("Time: %lf\n", t);
        printf("Nodes Generated: %d (%d nodes/second)\n", cnt, (int)(cnt / t));
        printf("\n");
        maxd++;
    }
    return 0;
}
