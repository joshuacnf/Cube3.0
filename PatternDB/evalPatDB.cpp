#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include "../cube.h"
#include "../globals.h"

#define DEPTH 20

cube A;
databaseC DBC;
databaseS DBS;

uc buffer[M1024] = {0};
ui depth, d = 0;
ull cnt, nodes_cnt;
ull D[21], P[21][21];
long double num[21][18], sum[21];

void scramble()
{
    for (int i = 0; i < 200; i++)
	A.turn((uc)(rand() % 18));
}

void initSum()
{
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
}

void loadDB(const char *file_name)
{
    FILE *in; ull file_size;

    in = fopen(file_name, "rb");
    fseek(in, 0, SEEK_END);
    file_size = ftell(in);
    
    fseek(in, 0, SEEK_SET);
    while (file_size)
    {
	ull block_size = min_(M1024, file_size);
	fread(buffer, block_size, 1, in);
	for (int i = 0; i < block_size; i++)
	{
	    D[buffer[i] & MASK4]++;
	    D[(buffer[i] >> 4) & MASK4]++;
	}
	cnt += block_size << 1;
	file_size -= block_size;
    }
    fclose(in);
}

void DBInfo()
{
    for (int i = 1; i < 21; i++)
    	D[i] += D[i - 1];

    printf("Distribution Table:\n");
    printf("h\tDistribution (%%)\tCumulative (%%)\n");
    for (int i = 0; i < 21; i++)
    {
	double distribution = (D[i] - D[i - 1]) / (double)cnt * 100.0;
	double cumulative_distribution = D[i] / (double)cnt * 100.0;
	printf("%d\t%-16.4lf\t%.4lf\n", i, distribution, cumulative_distribution);
    }
    printf("\n");
}

void init()
{
    cnt = 0;
    memset(D, 0, sizeof(D));
    memset(num, 0, sizeof(num));
    memset(sum, 0, sizeof(sum));

    initSum();
    loadDB("databaseC.in");
    loadDB("databaseS.in");
    
    DBInfo();
}

void sample()
{
    
}

void dfs(uc u)
{
    if (DBC.load(A.C) + d > depth) return;
    if (DBS.load1(A.S) + d > depth) return;
    if (DBS.load2(A.S) + d > depth) return;
    nodes_cnt++;

    ull S0, C0;
    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    S0 = A.S, C0 = A.C; d++;
	    A.turn(v); dfs(v);
	    A.S = S0, A.C = C0; d--;
	}
}

void work()
{
    printf("Depth\t\tTheoretical\t\tExperimental\n");
    for (depth = 15; depth <= DEPTH; depth++)
    {
	printf("%d\t\t", depth);
	
	nodes_cnt = 0;
	for (int i = 0; i <= depth; i++)
	    nodes_cnt += sum[i] * (D[depth - i] / (double)cnt);
	printf("%-11llu\t\t", nodes_cnt);
       	
	ull avg = 0;
	for (int t = 0; t < 1; t++)
	{
	    nodes_cnt = 0;
	    scramble(); dfs(18);
	    avg += nodes_cnt;
	}
	nodes_cnt = (ull)(avg / 1.0);
	printf("%-11llu\n", nodes_cnt);
    }
}

int main()
{
    init();
    work();
    printf("\n");
    return 0;
}
