#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../globals.h"

ui cnt = 0;
long double num[21][18], sum[21], P[21];

void init()
{
    memset(P, 0, sizeof(P));
    memset(num, 0, sizeof(num));
    memset(sum, 0, sizeof(sum));
    
    num[0][0] = 1;
    for (int i = 0; i < 18; i++)
	num[1][i] = 1;
    for (int d = 2; d < 21; d++)
    {
	for (int u = 0; u < 18; u++)
	    for (int v = 0; v < 18; v++)
		if (G[u][v])
		    num[d][v] += num[d - 1][u];
    }

    for (int d = 0; d < 21; d++)
	for (int i = 0; i < 18; i++)
	    sum[d] += num[d][i];
    
    FILE *in; uc x;
    
    in = fopen("databaseS.in", "r");
    while (fscanf(in, "%hhu", &x) != EOF)
    {
	P[x & MASK4]++;
	P[(x >> 4) & MASK4]++;
	cnt += 2;
    }
    fclose(in);

    in = fopen("databaseC.in", "r");
    while (fscanf(in, "%hhu", &x) != EOF)
    {
	P[x & MASK4]++;
	P[(x >> 4) & MASK4]++;
	cnt += 2;
    }
    fclose(in);
    
    for (int i = 1; i < 21; i++)
	P[i] += P[i - 1];
    for (int i = 0; i < 21; i++)
	P[i] /= (long double)cnt;
}

void work()
{
    long double nodes_cnt = 0;
    for (int d = 0; d <= 18; d++)
	nodes_cnt += sum[d] * P[18 - d];
    printf("%.0Lf\n", nodes_cnt);
}

int main()
{
    init();
    work();
    return 0;
}
