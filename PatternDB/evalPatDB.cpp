#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include "../cube.h"
#include "../globals.h"

#define DEPTH 18

cube A;
databaseC DBC;
databaseS DBS;

uc buffer[M1024] = {0};
long double sum[21] = {0};

ui depth;
ull D[21] = {0}, nodes_cnt;
ull P[21][21] = {0};

void scramble()
{
    for (int i = 0; i < 200; i++)
	A.turn((uc)((rand() % 1000007) % 18));
}

void initSum()
{
    long double num[21][18];
    memset(num, 0, sizeof(num));
    
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
	file_size -= block_size;
    }
    fclose(in);
}

void writeDistributionTable(ull *T, FILE *out)
{
    fprintf(out, "h\tDistribution (%%)\tCumulative (%%)\n");
    for (int i = 1; i < 21; i++)
    {
	double distribution = (T[i] - T[i - 1]) / (double)T[20] * 100.0;
	double cumulative_distribution = T[i] / (double)T[20] * 100.0;
	fprintf(out, "%d\t%-16.4lf\t%.4lf\n", i, distribution, cumulative_distribution);
    }
    fprintf(out, "\n");
}

void dfs(uc u, uc d = 0)
{
    if (DBC.load(A.C) + d > depth) return;
    if (DBS.load1(A.S) + d > depth) return;
    if (DBS.load2(A.S) + d > depth) return;
    
    nodes_cnt++;

    ull S0, C0;
    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    S0 = A.S, C0 = A.C;
	    A.turn(v); dfs(v, d + 1);
	    A.S = S0, A.C = C0;
	}
}

void dfsRand(uc u, uc d = 0)
{
    uc h = 0;
    h = max_(DBC.load(A.C), h);
    h = max_(DBS.load1(A.S), h);
    h = max_(DBS.load2(A.S), h);
    P[d][h]++;
    
    if (d == 18) return;
    
    ull S0, C0;
    for (int i = 0; i < 3; i++)
    {
	uc v;
	do{
	    v = (rand() % 1000007) % 18;
	} while(!G[u][v]);
	S0 = A.S, C0 = A.C;
	A.turn(v); dfsRand(v, d + 1);
	A.S = S0, A.C = C0;
    }
}

void init()
{
    memset(D, 0, sizeof(D));
    memset(sum, 0, sizeof(sum));
    memset(P, 0, sizeof(P));

    initSum();
    printf("Loading database...\n");
    loadDB("databaseC.in");
    loadDB("databaseS.in");

    D[0] -= 40320;
    for (int i = 1; i < 21; i++) D[i] += D[i - 1];

    FILE *out = fopen("disTable.out", "a");
    fprintf(out, "Raw Distribution Table:\n");
    writeDistributionTable(D, out);
    fclose(out);
}

void sample()
{
    printf("Sampling...\n");
    
    for (int i = 1; i <= 100; i++)
    {
	scramble();
	dfsRand(18, 0);
	printf("Progress: %d%%\n", i);
    }

    FILE *out = fopen("disTable.out", "a");
    for (int d = 1; d < 21; d++)
    {
	fprintf(out, "Distribution Table at depth %d:\n", d);
	writeDistributionTable(P[d], out);
    }
    fclose(out);
}

void work()
{
    printf("Depth\t\tTheoretical0\t\tTheoretical1\t\tExperimental\n");
    for (depth = 10; depth <= DEPTH; depth++)
    {
	printf("%d\t\t", depth);
	
	nodes_cnt = 0;
	for (int i = 0; i <= depth; i++)
	    nodes_cnt += (ull)(sum[i] * (D[depth - i] / (long double)D[20]));
	printf("%-12llu\t\t", nodes_cnt);

	nodes_cnt = 0;
	for (int i = 0; i <= depth; i++)
	    nodes_cnt += (ull)(sum[i] * (P[i][depth - i] / (long double)P[i][20]));
	printf("%-12llu\t\t", nodes_cnt);

	nodes_cnt = 0;
	/*
	ull avg = 0;
	for (int t = 0; t < 25; t++)
	{
	    nodes_cnt = 0;
	    scramble(); dfs(18);
	    avg += nodes_cnt;
	}
	nodes_cnt = (ull)(avg / 25.0);*/
	
	printf("%-11llu\n", nodes_cnt);
    }
}

int main()
{
    init();
    sample();
    work();
    printf("\n");
    return 0;
}
